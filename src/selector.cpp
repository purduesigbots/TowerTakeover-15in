#include "main.h"

namespace selector{

int autoNumber = 0; // keeps track of what auton is selected

ADIDigitalIn nav('D');

void task(void* parameter){
  delay(200); // prevent the bug where buttons trigger randomly on startup

  //amount and names of autons
  const int autoCount = 4;
  const char *autoNames[autoCount] = {
    "None",
    "Red",
    "Blue",
    "Skills"
  };

  //auton selector
  master.print(2, 0, "%s", autoNames[autoNumber]);

  while(1){
    //display auton
    if(master.get_digital_new_press(DIGITAL_RIGHT) || nav.get_new_press()){
      autoNumber++;
      if(autoNumber == autoCount)
        autoNumber = 0;

      master.print(2,0,"                       ");
      delay(100);
      master.print(2, 0, "%s", autoNames[autoNumber]);
    }
    delay(50);
  }
}

void init(){
  Task selector_task(
    task,
    NULL,
    TASK_PRIORITY_DEFAULT,
    TASK_STACK_DEPTH_DEFAULT,
    ""
  );
}

int get(){
  return autoNumber;
}

} //namespace selector
