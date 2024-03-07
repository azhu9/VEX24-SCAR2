#include "main.h"

// These are out of 127
const int DRIVE_SPEED = 100;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

//Motor declaration
pros::Motor intake(10);
pros::Motor slapper(1);
ez::Piston backWing('C');


void backWingsOut(){
  backWing.set(true);
}

void backWingsIn(){
  backWing.set(false);
}

void intakeIn(){
  intake = 127;
}

void intakeOut(){
  intake = -127;
}

void intakeStop(){
  intake.brake();
}

void slapperRev(int rep){
    for(int i = 0; i < rep; i++){
        int pos = 0;
        int angle = 720;  //this is 360 degrees
        slapper.tare_position();

        while(pos < angle){
          slapper = 100;
          pos = slapper.get_position();
          pros::delay(10);
        }
        slapper.brake();

        if(i != 9){
          pros::delay(2000);
        }
    }
}