#include "main.h"

Controller master(E_CONTROLLER_MASTER); // declare global controller

void initialize() {
	selector::init();
	intake::init();
	tilter::init();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	switch(selector::get()){
    case 0:
		  break;
    case 1:
      red();
      break;
    case 2:
      blue();
      break;
    case 3:
      skills();
      break;
  }
}

void opcontrol() {
	tilter::zero();
	while (true) {
		drive::opcontrol();
		intake::opcontrol();
		tilter::opcontrol();

		if(master.get_digital(DIGITAL_LEFT) && !competition::is_connected())
			autonomous();

		delay(10);
	}
}
