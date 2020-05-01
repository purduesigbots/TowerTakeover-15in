#ifndef _TILTER_H_
#define _TILTER_H_

namespace tilter{

void init();

// basic functions
void move(int speed);
void zero();
double getPosition();

// drive controls
void opcontrol();

}

#endif
