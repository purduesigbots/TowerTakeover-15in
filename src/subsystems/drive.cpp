#include "main.h"
#include "okapi/impl/util/configurableTimeUtilFactory.hpp"

namespace drive{

bool leftEnabled = true;
bool rightEnabled = true;

//drive motors
okapi::Motor left1(5), left2(12);
okapi::Motor right1(-8), right2(-19);

//motor groups
okapi::MotorGroup leftMotors({left1, left2});
okapi::MotorGroup rightMotors({right1, right2});

ADILineSensor goal_line('C');

okapi::TimeUtilFactory customTimeUtilFactory = okapi::ConfigurableTimeUtilFactory(std::numeric_limits<double>::max(),10,50_ms);


/**************************************************/
//okapi controllers
auto driveController = okapi::ChassisControllerBuilder()
  .withMotors(leftMotors, rightMotors)
  .withDimensions(okapi::AbstractMotor::gearset::green, {{3.25_in, 12_in}, okapi::quadEncoderTPR})
  .withOdometry()
  .buildOdometry();

//default limits
okapi::PathfinderLimits normalLimits = {1, 3, 3};
okapi::PathfinderLimits fastLimits = {1, 8, 25};

auto profileController = okapi::AsyncMotionProfileControllerBuilder()
  .withOutput(driveController)
  .withLimits(normalLimits)
  .withTimeUtilFactory(customTimeUtilFactory)
  .buildMotionProfileController();

/**************************************************/
//autonomous functions
void move(okapi::PathfinderPoint p, int max, bool async, bool fast, bool turning){

  rightMotors.setReversed(true);
  leftMotors.setReversed(turning); // false for straight, true for turns

  okapi::PathfinderPoint startingPoint = {0_ft,0_ft,0_deg};

  //set motor reversal
  bool reversed = false;
  if(p.x < 0_ft){
    reversed = true;
  }

  okapi::PathfinderLimits limits = normalLimits;
  if(fast){
    limits = fastLimits;
  }

  //speed limiting
  double speed = max/(double)100;
  limits.maxVel = speed;


  profileController->moveTo(
    {startingPoint, p},
    limits,
    reversed,
    async
  );

}

void move(okapi::QLength x_target, int max, bool async){
  move({x_target, 0_ft, 0_deg}, max, async, false, false);
}

void moveFast(okapi::QLength target, int max, bool async){
  move({target, 0_ft, 0_deg}, max, async, true, false);
}

void turn(okapi::QLength target, int max, bool fast, bool async){
  move({target, 0_ft, 0_deg}, max, async, fast, true);
}

void waitUntilSettled(){
  profileController->waitUntilSettled();
}

void goalZone(int speed, int slant){
  double scaled_speed = speed/(double)100;
  double scaled_slant = slant/(double)100;


  while(goal_line.get_value() > 2700){
    driveController->getModel()->tank(scaled_speed-scaled_slant, scaled_speed+scaled_slant);
    delay(10);
  }

  driveController->getModel()->stop();

}

/**************************************************/
//operator control
void opcontrol(){

  //printf("x: %0.2f,   y: %0.2f,   theta: %0.2f\n", driveController->getState().x.convert(okapi::foot), driveController->getState().y.convert(okapi::foot),driveController->getState().theta.convert(okapi::degree));
  //printf("%d\n", goal_line.get_value());

  rightMotors.setReversed(true);
  leftMotors.setReversed(false);

  leftMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
  rightMotors.setBrakeMode(okapi::AbstractMotor::brakeMode::coast);

  int power = master.get_analog(ANALOG_LEFT_Y);
  int turn = master.get_analog(ANALOG_LEFT_X);
  double left = (power + turn)/(double)127;
  double right = (power - turn)/(double)127;

  driveController->getModel()->tank(left, right);
}

} //namespace drive
