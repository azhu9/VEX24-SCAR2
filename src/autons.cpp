#include "EZ-Template/util.hpp"
#include "main.h"
#include "pros/rtos.hpp"

//see helpermethods.cpp for constants and helper methods

///
// Constants
///
const int DRIVE_SPEED = 70;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;


#if BIG_BOT
//Motor declaration
  pros::Motor intake(10);
  pros::Motor slapper(1);
  ez::Piston leftWing('H', false);
  ez::Piston rightWing('A', false);

#else
  pros::Motor intake(15);
  pros::Motor slapper(1);
  ez::Piston leftWing('C', false);
  ez::Piston rightWing('A', false);
#endif
//Helper Methods

void leftWingOut(){
  leftWing.set(true);
}

void leftWingIn(){
  leftWing.set(false);
}

void rightWingOut(){
  rightWing.set(true);
}

void rightWingIn(){
  rightWing.set(false);
}

#if BIG_BOT
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
        int angle = 600;  //this is 360 degrees
        slapper.tare_position();

        while(pos < angle){
          slapper = 127;
          pos = slapper.get_position();
          pros::delay(10);
        }
        slapper.brake();

        if(i != 9){
          pros::delay(1750);
        }
    }
}
#else
  void intakeIn(){
  intake = -127;
  }

  void intakeOut(){
  intake = 127;
  }

  void intakeStop(){
  intake = 0;
  }

  void slapperRev(int rep){
    for(int i = 0; i < rep; i++){
        int pos = 0;
        int angle = -660;  //this is 360 degrees
        slapper.tare_position();

        while(pos > angle){
          slapper = -127;
          pos = slapper.get_position();
          pros::delay(10);
        }
        slapper.brake();

        if(i != 9){
          pros::delay(1750);
        }
    }
}
#endif

void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(10, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}
  // DRIVE FUNCTION PARAMS
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
#if BIG_BOT 

  //BIG BOT SKILLS AUTON
  //20 matchloads, start at the matchload bar with tool
  void big_bot_skills(){
    
    // //matchload 20
    leftWingOut();
    pros::delay(500);

    // slapperRev(10);

    // chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);
    // chassis.pid_wait();

    // chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
    // chassis.pid_wait();

    // chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
    // chassis.pid_wait();
    
    // chassis.pid_drive_set(7_in, DRIVE_SPEED, true);
    // chassis.pid_wait();

    slapperRev(25);
    
    leftWingIn();
    pros::delay(500);
    rightWingOut();

    //align to 45 degrees
    chassis.pid_turn_relative_set(11_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //curve bot to hug the wall
    chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, 60, 35);
    // chassis.pid_turn_set(-45_deg, TURN_SPEED);
    chassis.pid_wait();

    //drive through alley
    chassis.pid_drive_set(-55_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //curve into the goal
    chassis.pid_swing_relative_set(ez::LEFT_SWING, -90_deg, SWING_SPEED, 60);
    chassis.pid_wait();

    chassis.pid_drive_set(-18_in, 127, true);
    chassis.pid_wait();
    
    //back up
    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    rightWingIn();
    pros::delay(500);

    //push into goal again
    chassis.pid_drive_set(-22_in, 127, true);
    chassis.pid_wait();

    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, SWING_SPEED, 60);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
    chassis.pid_wait();

  }
  //BIG BOT MATCH AUTON
  //10 matchloads, start at the matchload bar with tool
  void big_bot_match_auton(){
    leftWingOut();
    pros::delay(500);

    slapperRev(12);
    
    leftWingIn();
    pros::delay(500);
    rightWingOut();

    //align to 45 degrees
    chassis.pid_turn_relative_set(11_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //curve bot to hug the wall
    chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, 60, 35);
    // chassis.pid_turn_set(-45_deg, TURN_SPEED);
    chassis.pid_wait();

    //drive through alley
    chassis.pid_drive_set(-55_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //curve into the goal
    chassis.pid_swing_relative_set(ez::LEFT_SWING, -90_deg, SWING_SPEED, 60);
    chassis.pid_wait();

    chassis.pid_drive_set(-18_in, 127, true);
    chassis.pid_wait();
    
    //back up
    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    rightWingIn();
    pros::delay(500);

    //push into goal again
    chassis.pid_drive_set(-22_in, 127, true);
    chassis.pid_wait();

    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, SWING_SPEED, 60);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(45_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
    chassis.pid_wait();

  }
#else
  void small_bot_skills(){

    intakeIn();
    pros::delay(500);
    intakeStop();
    intakeOut();
    pros::delay(500);
    intakeStop();

    rightWingOut();
    pros::delay(500);

    slapperRev(20);
    
    rightWingIn();
    pros::delay(500);
    leftWingOut();

    // chassis.pid_turn_set(11_deg, TURN_SPEED);
    // chassis.pid_wait();

    // chassis.pid_drive_set(-28_in, 127, true);
    // chassis.pid_wait();

    //curve bot to hug the wall
    chassis.pid_turn_relative_set(-10_deg, TURN_SPEED);
    chassis.pid_wait();

    // chassis.pid_drive_set(-2_in, 127, true);
    // chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::RIGHT_SWING, 45_deg, 60, 40);
    chassis.pid_wait();

    //drive through alley
    chassis.pid_drive_set(-55_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // curve into the goal
    chassis.pid_swing_relative_set(ez::RIGHT_SWING, 90_deg, 70, 40);
    chassis.pid_wait();

    chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    //back up
    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    leftWingIn();
    pros::delay(500);

    chassis.pid_turn_relative_set(-25_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::RIGHT_SWING, 25_deg, 127, 95);
    chassis.pid_wait();

    //push into goal again
    chassis.pid_drive_set(22_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(-25_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::RIGHT_SWING, 25_deg, 127, 95);
    chassis.pid_wait();

    chassis.pid_drive_set(-22_in, 127, true);
    chassis.pid_wait();

  }

  void small_bot_match_auton(){
    intakeIn();
    pros::delay(500);
    intakeStop();
    intakeOut();
    pros::delay(500);
    intakeStop();

    chassis.pid_drive_set(35_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    intakeIn();

    chassis.pid_turn_relative_set(27_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(5_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    pros::delay(1000);
    intakeStop();

  }
#endif





//Below are old autons and tests

void small_AWP() {
  ez::Piston frontWing('C');

  //drive down lane
  chassis.pid_drive_set(-50_in, DRIVE_SPEED, true);  
  chassis.pid_wait();

  //turn to align with corner bar
  chassis.pid_swing_set(ez::LEFT_SWING, -45_deg, SWING_SPEED, 20);
  chassis.pid_wait();

  //open wings
  frontWing.set(true);
  //drive to the bar
  chassis.pid_drive_set(-17_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //hit ball out of corner
  chassis.pid_turn_set(-90_deg, 127);
  chassis.pid_wait();

  chassis.pid_drive_set(-20_in, 127, true);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //close wings
  frontWing.set(false);


  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(135_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  chassis.pid_drive_set(-14_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  chassis.pid_turn_set(0, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(40_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  frontWing.set(true);

}

///
// Turn Example
///
void turn_example() {
  ez::Piston frontWing('C');

  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(72_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 70);

  chassis.pid_drive_set(72_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(96_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  
  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  frontWing.set(true);

  chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

//

  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 50);
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .