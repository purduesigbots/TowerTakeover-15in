#include "main.h"

namespace intake{

okapi::MotorGroup motors = {14, 16, -10, -17};

void init(){
  motors.setGearing(okapi::AbstractMotor::gearset::green);
  motors.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
  motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

/**************************************************/
//basic control
void move(int speed){
  motors.moveVoltage(speed*120);
}

/**************************************************/
//operator control
void opcontrol(){
  static int speed;

  move(speed);

  if(master.get_digital(DIGITAL_R1))
    speed = 100;
  else if(master.get_digital(DIGITAL_R2))
    speed = -100;
  else if(master.get_digital(DIGITAL_A))
    speed = -45;
  else
    speed = 0;
}

} //namespace intake
