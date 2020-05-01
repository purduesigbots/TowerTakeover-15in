#ifndef _LIFT_H_
#define _LIFT_H_

namespace lift{
  
void init();

// basic functions
void move(int speed);
void move_voltage(int speed);

// drive controls
void opcontrol();

}

#endif
