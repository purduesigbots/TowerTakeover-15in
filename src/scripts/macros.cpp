#include "main.h"
using namespace drive;

ADILineSensor cube_line('F');

void lastCube(){
  intake::move(60);
  move(8_ft, 100, 1);
  while(cube_line.get_value() > 2300) delay(20);
  intake::move(15);
  waitUntilSettled();
}

void stack(){
  tilter::move(100);
  while(tilter::getPosition() < 600) delay(20);
  tilter::move(60);
  intake::move(-15);
  while(tilter::getPosition() < 900) delay(20);
  intake::move(0);
  tilter::move(30);
  delay(1500);
  tilter::move(0);
}

void deploy(){
  tilter::zero();
  tilter::move(-10);

  //cube scooch
  moveFast(0.8_ft);
  moveFast(-0.8_ft);

  tilter::move(0);

  //deploy
  intake::move(-100);
  delay(800);
  intake::move(0);
  delay(600);
}
