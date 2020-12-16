set(COMPONENT_SRCS "main.c" "galvanometer.c" "gcode.c" "global.c" "job.c" "motion.c" "planner.c" "sd_card.c" "settings.c" "spindle.c" "stepper.c" "web.c"
    "api/api_util.c" "api/axis_api.c" "api/fs_api.c" "api/galvanometer_api.c" "api/job_api.c" "api/spindle_api.c" "api/stepper_api.c" "api/ws_api.c"
)
set(COMPONENT_ADD_INCLUDEDIRS "." "api/.")

register_component()
