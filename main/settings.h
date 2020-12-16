#pragma once

typedef struct axis_config_t axis_config_t;

void settings_fetch_all();
void fetch_axis_config(unsigned int idx);
void save_axis_config(unsigned int idx);
void fetch_stepper_config(unsigned int idx);
void save_stepper_config(unsigned int idx);
void fetch_spindle_config(unsigned int idx);
void save_spindle_config(unsigned int idx);
void fetch_galvanometer_config(unsigned int idx);
void save_galvanometer_config(unsigned int idx);
