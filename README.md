

TODO
- position callback called on a timer. Motion handlers register with it for each axis
- Convert stepper to use position as mm instead of steps


- Brake outputs for each axis
- spindle speed variation. M138 / M139
  https://www.haascnc.com/service/codes-settings.type=mcode.machine=mill.value=M138.html


Haas - 
4th axis - M11 unclamp, M10 clamp
5th axis - M13 unclamp, M12 clamp

- Properly calculate feed rate on 3 axis (GRBL is wrong??)
- Calculate 5 axis feed rate using distance to axis of rotation
- Support inverse time feed rate

http://linuxcnc.org/docs/devel/html/motion/5-axis-kinematics.html
http://linuxcnc.org/docs/html/gcode/g-code.html#gcode:g93-g94-g95
