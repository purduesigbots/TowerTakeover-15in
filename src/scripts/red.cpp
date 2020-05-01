#include "main.h"
using namespace drive;

//main red auto
void red(){
  deploy();

  //row 1
  intake::move(100);
  move(2.3_ft, 25);
  intake::move(15);

  //b-b-b-b-bonus cube
  moveFast(-1.8_ft);
  turn(36_dg);
  intake::move(100);
  move(2.1_ft, 30);
  turn(20_dg);
  moveFast(0.3_ft);

  //row 2
  moveFast(-4.4_ft);
  turn(-55_dg);
  moveFast(-0.5_ft);
  move(2.5_ft, 25);

  //crossfield
  move(-2.3_ft);
  turn(100_dg, 100, 0);

  //chungo preload
  lastCube();
  goalZone(45, 6);

  //stacko
  stack();

  //backout
  intake::move(-60);
  delay(500);
  tilter::move(-100);
  moveFast(-1.5_ft);
  intake::move(0);
  tilter::move(0);

  //cube shovel
  delay(400);
  turn(-50_dg);
  intake::move(100);
  moveFast(2.3_ft);
  turn(90_dg);
  intake::move(0);
  moveFast(0.4_ft);
  intake::move(-100);
  delay(600);
  moveFast(-1_ft);
}
