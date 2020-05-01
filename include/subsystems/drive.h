#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "okapi/api.hpp"

namespace drive{

using namespace okapi::literals;

// auto functions
void move(okapi::PathfinderPoint iwaypoint, int max = 100, bool async = false, bool fast = false, bool turning = false);
void move(okapi::QLength x_target, int max = 100, bool async = false);
void moveFast(okapi::QLength target, int max = 100, bool async = false);
void turn(okapi::QLength target, int max = 100, bool fast = true, bool async = false);
void waitUntilSettled();
void goalZone(int speed, int slant);

// drive controls
void opcontrol();

}

#endif
