#include "main.h"

namespace tilter{

okapi::MotorGroup motors = {-18, 13};

ADIButton reset_button('B');

void init(){
  motors.setGearing(okapi::AbstractMotor::gearset::green);
  motors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  motors.setEncoderUnits(okapi::AbstractMotor::encoderUnits::degrees);
}

/**************************************************/
//basic control
void move(int speed){
  motors.moveVoltage(speed*120);
}

void zero(){
  motors.tarePosition();
}

double getPosition(){
  return motors.getPosition();
}

/**************************************************/
//operator control
void opcontrol(){
  static int speed;

  if(reset_button.get_value()){
    zero();
  }

  move(speed);

  if(master.get_digital(DIGITAL_L1)){
    if(motors.getPosition() < 450){
      speed = 100;
    }else if(motors.getPosition() < 600){
      speed = 60;
    }else{
      speed = 30;
    }
  }else if(master.get_digital(DIGITAL_L2) && !reset_button.get_value())
    speed = -100;
  else
    speed = 0;
}

} //namespace tilter
