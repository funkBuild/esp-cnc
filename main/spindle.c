#include "global.h"
#include "planner.h"
#include "spindle.h"
#include "motion.h"

#include <stdio.h>

static spindle_context_t spindles[N_SPINDLES];

static inline void clear_spindle_bit(int spindle_num){
  //set_i2s_bit(2 * (10+spindle_num));
}

static inline void set_spindle_bit(int spindle_num){
  //set_i2s_bit(2 * (10+spindle_num));
}

void spindle_set_dynamic_power(spindle_context_t* spindle_ctx, float power_percentage){
  spindle_ctx->threshold = (power_percentage * spindle_ctx->max_count * spindle_ctx->speed) / spindle_ctx->max_speed;
}

void spindle_calc_dynamic_power(spindle_context_t* spindle_ctx, motion_ctx_t *motion_ctx, MotionEvent event){
  if(event == Cruise) return;

  float progress;

  if(event == Accelerate)
    progress = (float)spindle_ctx->segment_count / motion_ctx->accel_ticks;
  else
    progress = (float)spindle_ctx->segment_count / motion_ctx->decel_ticks;

  float current_power = spindle_ctx->segment_power_start + progress * spindle_ctx->segment_power_delta;

  spindle_set_dynamic_power(spindle_ctx, current_power);
}

static void spindle_motion_update(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  spindle_context_t* spindle_ctx = (spindle_context_t*) self->ctx;

  if(spindle_ctx->count >= spindle_ctx->max_count){
    spindle_ctx->count = 0;
    self->t_next = spindle_ctx->threshold;
    clear_spindle_bit(spindle_ctx->idx);
  } else {
    self->t_next = spindle_ctx->max_count - spindle_ctx->threshold;
    set_spindle_bit(spindle_ctx->idx);
  }

  if(spindle_ctx->dynamic_power){
    spindle_calc_dynamic_power(spindle_ctx, motion_ctx, event);
  }

  spindle_ctx->segment_count += self->t_next;
  spindle_ctx->count += self->t_next;
}

static void spindle_motion_done(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  
}

static void spindle_motion_start(motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  spindle_context_t* spindle_ctx = (spindle_context_t*) self->ctx;

  if(spindle_ctx->dynamic_power){
    switch(event){
      case Accelerate: {
        spindle_ctx->segment_power_start = motion_ctx->block->entry_speed / motion_ctx->block->programmed_rate;
        spindle_ctx->segment_power_delta = (motion_ctx->block->max_feedrate / motion_ctx->block->programmed_rate) - spindle_ctx->segment_power_start;

        spindle_set_dynamic_power(spindle_ctx, spindle_ctx->segment_power_start);
        break;
      }
      case Cruise:
        spindle_set_dynamic_power(spindle_ctx, 1.0);
        break;
      case Decelerate:
        spindle_ctx->segment_power_start = motion_ctx->block->max_feedrate / motion_ctx->block->programmed_rate;
        spindle_ctx->segment_power_delta = (motion_ctx->block->exit_speed / motion_ctx->block->programmed_rate) - spindle_ctx->segment_power_start;

        spindle_set_dynamic_power(spindle_ctx, spindle_ctx->segment_power_start);
        break;
    };
  }

  if(spindle_ctx->count < spindle_ctx->threshold)
    self->t_next = spindle_ctx->threshold - spindle_ctx->count;
  else
    self->t_next = spindle_ctx->max_count - spindle_ctx->count;

  spindle_ctx->segment_count = self->t_next;
  spindle_ctx->count += self->t_next;
}

void spindle_motion_setup(motion_ctx_t *motion_ctx){
  for(int i=0; i < N_SPINDLES; i++){
    if(!spindles[i].enabled || spindles[i].output_type != PWM) continue;

    motion_action_t* action = motion_ctx_create_action(motion_ctx);

    action->ctx = (void*) &spindles[i];

    action->motion_update_callback = &spindle_motion_update;
    action->motion_start_callback = &spindle_motion_start;
    action->motion_done_callback = &spindle_motion_done;
  }
}




static void spindle_motion_analog_start(analog_motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  spindle_context_t* spindle_ctx = (spindle_context_t*) self->ctx;

  const float max_spindle_power = (float)spindle_ctx->speed / spindle_ctx->max_speed;

  if(spindle_ctx->dynamic_power){
    switch(event){
      case Accelerate: {
        spindle_ctx->segment_power_start = max_spindle_power * (motion_ctx->block->entry_speed / motion_ctx->block->programmed_rate);
        spindle_ctx->segment_power_delta = max_spindle_power * (motion_ctx->block->max_feedrate / motion_ctx->block->programmed_rate) - spindle_ctx->segment_power_start;
        break;
      }
      case Cruise:
        break;
      case Decelerate:
        spindle_ctx->segment_power_start = max_spindle_power * (motion_ctx->block->max_feedrate / motion_ctx->block->programmed_rate);
        spindle_ctx->segment_power_delta = max_spindle_power * (motion_ctx->block->exit_speed / motion_ctx->block->programmed_rate) - spindle_ctx->segment_power_start;
        break;
    };
  }
}

static void spindle_motion_analog_done(analog_motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){

}

static void spindle_motion_analog_update(analog_motion_ctx_t *motion_ctx, motion_action_t *self, MotionEvent event){
  spindle_context_t* spindle_ctx = (spindle_context_t*) self->ctx;
  float cruise_power = (float)spindle_ctx->speed / spindle_ctx->max_speed;

  if(event == Cruise || !spindle_ctx->dynamic_power){
    motion_ctx->channel_value[spindle_ctx->analog_channel_idx] = cruise_power;
    return;
  }

  float progress = (float)motion_ctx->ticks / (event == Accelerate ? motion_ctx->accel_ticks : motion_ctx->decel_ticks);
  float current_power = spindle_ctx->segment_power_start + progress * spindle_ctx->segment_power_delta;

  motion_ctx->channel_value[spindle_ctx->analog_channel_idx] = current_power;
}

void spindle_analog_setup(analog_motion_ctx_t *motion_ctx){
  for(int i=0; i < N_SPINDLES; i++){
    if(!spindles[i].enabled || spindles[i].output_type != Analog) continue;
    
    motion_action_t* action = analog_motion_ctx_create_action(motion_ctx);
    action->ctx = (void*) &spindles[i];

    action->motion_update_callback = &spindle_motion_analog_update;
    action->motion_start_callback = &spindle_motion_analog_start;
    action->motion_done_callback = &spindle_motion_analog_done;
  }
}

















void spindle_set_speed(unsigned int idx, unsigned int speed){
  if(idx >= N_SPINDLES) return;

  spindles[idx].speed = speed > spindles[idx].max_speed ? speed : spindles[idx].max_speed;
  spindles[idx].threshold = (spindles[idx].max_count * spindles[idx].speed) / spindles[idx].max_speed;
}

void spindle_init(){
  // Spindle defaults
  for(int i=0; i < N_SPINDLES; i++){
    spindles[i].output_type = PWM;
    spindles[i].idx = i;
    spindles[i].analog_channel_idx = i;
    spindles[i].enabled = true;
    spindles[i].dynamic_power = true;
    spindles[i].frequency = 1000;
    spindles[i].max_speed = 5000;
    spindles[i].speed = 4000;
    spindles[i].max_count = STEPPER_I2S_SAMPLE_RATE / spindles[i].frequency;
    spindles[i].count = 0;
    spindles[i].threshold = (spindles[i].max_count * spindles[i].speed) / spindles[i].max_speed;
  }
};
