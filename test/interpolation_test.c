#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#include "fixmath.h"
#include "fix16.h"

#define SAMPLE_RATE 96000.0
#define WIDTH 200.0

int interpolate(int start, int end, uint64_t steps, uint64_t total_steps){
  uint64_t dy = (end - start) * steps;
  dy = dy / total_steps;

  return start + dy;
}

int float_interpolate(int start, int end, float fraction){
  return start + fraction*(end-start);
}



void main(){
  float acceleration = 10.245432;
  float velocity = 0;
  float position = 0;

  const int steps = 10000;

  float final_velocity = ((float)steps / SAMPLE_RATE) * acceleration;
  int int_fv = INT_MAX * ((float)final_velocity / WIDTH) / SAMPLE_RATE;
  int int_p = 0;

  for(int i=0; i <= steps; i++){
    float t = (float)i / SAMPLE_RATE;
    position = 0.5 * t * t * acceleration;

    float width_fraction = position / WIDTH;
    int position_float = INT_MAX * width_fraction;

    fix16_t time = fix16_mul(fix16_from_int(i), fix16_from_float(1000.0/SAMPLE_RATE)); // Can't divide by more than a 32-bit number;
    time = fix16_div(time, fix16_from_int(1000));
    time = fix16_mul(time, time);

    fix16_t fix_position = fix16_div( fix16_mul(time, fix16_from_float(acceleration)), fix16_from_int(2));

    printf("%f\t%f\t%f\t%f\n", t, position, fix16_to_float(fix_position), position - fix16_to_float(fix_position));

  }
}
