#include "EZ-Template/util.hpp"
#include "main.h"
#include "okapi/api/units/QAngle.hpp"
#include "pros/rtos.hpp"

//see helpermethods.cpp for constants and helper methods

///
// Constants
///
const int DRIVE_SPEED = 90;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;


#if BIG_BOT
//Motor declaration
  pros::Motor intake(7);
  // pros::Motor winch_motor1(-1);
  // pros::Motor winch_motor2(10);
  // pros::MotorGroup winch({winch_motor1, winch_motor2});

  // pros::Motor climb_motor1(2);
  // pros::Motor climb_motor2(-8);
  // pros::MotorGroup climb({climb_motor1, climb_motor2});
  // climb.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

  ez::Piston leftWing('A', false);
  ez::Piston rightWing('C', false);
  ez::Piston claw('D', false);

#else
  pros::Motor intake(11);

  pros::Motor climb_motor1(-6);
  pros::Motor climb_motor2(20);
  pros::Motor_Group climb({climb_motor1, climb_motor2});

  ez::Piston rightWing('A', false);
  ez::Piston leftWing('B', false);
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

//intake helpers with time and auto stop
  void intakeIn(int ms){
    intake = -127;
    pros::delay(ms);
    intake = 0;
  }

  void intakeOut(int ms){
    intake = 127;
    pros::delay(ms);
    intake = 0;
  }
  
  //intake helpers without time (have to set delay in the auton in order to set time and use intakeStop())
  void intakeIn(){
    intake = -127;
  }

  void intakeOut(){
    intake = 127;
  }

  void intakeStop(){
    intake = 0;
  }

#if BIG_BOT

//intake helpers with time and auto stop
//   void intakeIn(int ms){
//     intake = 127;
//     pros::delay(ms);
//     intake = 0;
//   }

//   void intakeOut(int ms){
//     intake = -127;
//     pros::delay(ms);
//     intake = 0;
//   }

//   //intake helpers without time (have to set delay in the auton in order to set time and use intakeStop())
// void intakeIn(){
//   intake = 127;
// }

// void intakeOut(){
//   intake = -127;
// }

// void intakeStop(){
//   // intake.brake();
//   intake = 0;
// }

void slapperRev(int rep){
    for(int i = 0; i < rep; i++){
        rightWingOut();
        pros::delay(1000);
        rightWingIn();
        pros::delay(1250);
    }
}
#else

#endif

void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(10, 0, 100); //10 0 100
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(75_ms, 3_deg, 200_ms, 7_deg, 450_ms, 450_ms);
  chassis.pid_swing_exit_condition_set(75_ms, 3_deg, 200_ms, 7_deg, 450_ms, 450_ms);
  chassis.pid_drive_exit_condition_set(75_ms, 1_in, 200_ms, 3_in, 450_ms, 450_ms);

  //300 500

  chassis.slew_drive_constants_set(7_in, 80);
}
  // DRIVE FUNCTION PARAMS
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
#if BIG_BOT 

  //BIG BOT MATCH AUTON
  //10 matchloads, start at the matchload bar with tool
  void big_bot_match_close(){
    slapperRev(11);

    chassis.pid_turn_relative_set(12, TURN_SPEED);
    chassis.pid_wait();

    // intakeOut();
    chassis.pid_drive_set(15_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    leftWingOut();

    chassis.pid_swing_relative_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 35);
    chassis.pid_wait();

    chassis.pid_drive_set(55_in, 50, true);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::RIGHT_SWING, -90_deg, SWING_SPEED, 35);
    chassis.pid_wait();

    chassis.pid_drive_set(15_in, 127, true);
    chassis.pid_wait();

    chassis.pid_drive_set(-15_in, 127, true);
    chassis.pid_wait();

    leftWingIn();

    chassis.pid_turn_relative_set(-135, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(10_in, 127, true);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::LEFT_SWING, 48_deg, SWING_SPEED, 25);
    chassis.pid_wait();
    
    chassis.pid_drive_set(35_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    rightWingOut();

    chassis.pid_drive_set(-14_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    // chassis.pid_turn_relative_set(90, TURN_SPEED);
    // chassis.pid_wait();

    // chassis.pid_drive_set(35_in, DRIVE_SPEED, true);
    // chassis.pid_wait();
    // intakeStop();
    // leftWingIn();
    // chassis.pid_drive_set(-65_in, 50, true);
    // chassis.pid_wait();

    // chassis.pid_turn_relative_set(-90, TURN_SPEED);
    // chassis.pid_wait();

    

    

    // slapperRev(10);

    // chassis.pid_swing_relative_set(ez::RIGHT_SWING, -20_deg, SWING_SPEED, 35);
    // chassis.pid_wait();
    // intakeOut(10000);
    // leftWingOut();

    // chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
    // chassis.pid_wait();

    // chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
    // chassis.pid_wait();
  }
#else

  void red_bot_match_far_6ball(){
    // intakeIn();
    //drive through alley
    chassis.pid_drive_set(54_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    intakeStop();

    chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //dump match triball into corner
    intakeOut(500);

    //turn to triball 1
    chassis.pid_turn_relative_set(-105_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(45_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    intakeIn();

    chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(-40, TURN_SPEED);
    chassis.pid_wait();

    //put triball 1 infront of goal
    intakeOut(500);

    chassis.pid_turn_set(-90, TURN_SPEED);
    chassis.pid_wait();

    //intake triball 2
    intakeIn();
    chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(90, TURN_SPEED);
    chassis.pid_wait();

    //dump triball 2
    intakeOut(500);

    chassis.pid_turn_relative_set(-90, TURN_SPEED);
    chassis.pid_wait();

    //intake triball 3
    intakeIn();
    chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_drive_set(-4_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(90, TURN_SPEED);
    chassis.pid_wait();
    //outake triball 3
    intakeOut(500);

    chassis.pid_turn_set(180, TURN_SPEED);
    chassis.pid_wait();

    //intake triball 4
    intakeIn();
    chassis.pid_drive_set(15_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //open wings to sweep
    leftWingOut();
    rightWingOut();

    chassis.pid_drive_set(-38_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    // chassis.pid_wait();

    // chassis.pid_turn_relative_set(45, TURN_SPEED);
    // chassis.pid_wait();

    // chassis.pid_swing_relative_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 65);
    // chassis.pid_wait();

    chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    leftWingIn();
    rightWingIn();

    chassis.pid_turn_set(0, TURN_SPEED);
    chassis.pid_wait();
    intakeStop();

    chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //outake triball 4
    intakeOut(500);

    chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(85, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(60_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(90, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, SWING_SPEED, 40);
    chassis.pid_wait();

    leftWingOut();
    chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    leftWingIn();
    pros::delay(500);
    rightWingOut();

    chassis.pid_drive_set(4_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, SWING_SPEED, 25);
    chassis.pid_wait();

    chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    rightWingIn();

    chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(90, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(180, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(-28_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    rightWingOut();
  }


  void red_bot_match_far_5ball(){
    intakeOut(500);
    //drive through alley
    chassis.pid_drive_set(54_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    intakeStop();

    chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //dump match triball into corner
    intakeOut(500);

    //turn to triball 1
    chassis.pid_turn_relative_set(-105_deg, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(45_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    intakeIn();

    chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(-40, TURN_SPEED);
    chassis.pid_wait();

    //put triball 1 infront of goal
    intakeOut(500);

    chassis.pid_turn_set(-90, TURN_SPEED);
    chassis.pid_wait();

    //intake triball 2
    intakeIn();
    chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(90, TURN_SPEED);
    chassis.pid_wait();

    //dump triball 2
    intakeOut(500);

    chassis.pid_turn_relative_set(-90, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(-90, TURN_SPEED);
    chassis.pid_wait();

    //intake triball 4
    intakeIn();
    chassis.pid_drive_set(15_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //open wings to sweep
    leftWingOut();
    rightWingOut();

    chassis.pid_drive_set(-38_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    leftWingIn();
    rightWingIn();

    chassis.pid_turn_set(0, TURN_SPEED);
    chassis.pid_wait();
    intakeStop();

    chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //outake triball 4
    intakeOut(500);

    chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_set(85, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(60_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(90, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(-6_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, SWING_SPEED, 40);
    chassis.pid_wait();

    leftWingOut();
    chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    
    leftWingIn();
    pros::delay(500);
    rightWingOut();

    chassis.pid_drive_set(4_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, SWING_SPEED, 25);
    chassis.pid_wait();

    chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    rightWingIn();

    chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_drive_set(-14_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_drive_set(13_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(90, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    chassis.pid_turn_relative_set(180, TURN_SPEED);
    chassis.pid_wait();

    chassis.pid_drive_set(-28_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    rightWingOut();
  }
  // void red_bot_match_old(){
  //   // intakeIn();
  //   //drive through alley
  //   chassis.pid_drive_set(54_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();
  //   intakeStop();

  //   chassis.pid_turn_relative_set(-45_deg, TURN_SPEED);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   //dump match triball into corner
  //   intakeOut(500);

  //   //turn to triball 1
  //   chassis.pid_turn_relative_set(-105_deg, TURN_SPEED);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(45_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   intakeIn();

  //   chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_set(-40, TURN_SPEED);
  //   chassis.pid_wait();

  //   //put triball 1 infront of goal
  //   intakeOut(500);

  //   chassis.pid_turn_set(-90, TURN_SPEED);
  //   chassis.pid_wait();

  //   //intake triball 2
  //   intakeIn();
  //   chassis.pid_drive_set(26_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_relative_set(90, TURN_SPEED);
  //   chassis.pid_wait();

  //   //dump triball 2
  //   intakeOut(500);

  //   chassis.pid_turn_relative_set(-90, TURN_SPEED);
  //   chassis.pid_wait();

  //   //intake triball 3
  //   intakeIn();
  //   chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();
  //   chassis.pid_drive_set(-4_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_relative_set(90, TURN_SPEED);
  //   chassis.pid_wait();
  //   //outake triball 3
  //   intakeOut(500);

  //   chassis.pid_turn_set(180, TURN_SPEED);
  //   chassis.pid_wait();

  //   //intake triball 4
  //   intakeIn();
  //   chassis.pid_drive_set(15_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   //open wings to sweep
  //   leftWingOut();
  //   rightWingOut();

  //   chassis.pid_drive_set(-38_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   // chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  //   // chassis.pid_wait();

  //   // chassis.pid_turn_relative_set(45, TURN_SPEED);
  //   // chassis.pid_wait();

  //   // chassis.pid_swing_relative_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 65);
  //   // chassis.pid_wait();

  //   chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();
  //   leftWingIn();
  //   rightWingIn();

  //   chassis.pid_turn_set(0, TURN_SPEED);
  //   chassis.pid_wait();
  //   intakeStop();

  //   chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   //outake triball 4
  //   intakeOut(500);

  //   chassis.pid_drive_set(-45_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(35_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_set(85, TURN_SPEED);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(60_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_relative_set(90, TURN_SPEED);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, SWING_SPEED, 40);
  //   chassis.pid_wait();

  //   leftWingOut();
  //   chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();
  //   leftWingIn();
  //   rightWingOut();

  //   chassis.pid_swing_relative_set(ez::LEFT_SWING, -45_deg, SWING_SPEED, 30);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(-18_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();
  //   rightWingIn();

  //   chassis.pid_drive_set(15_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();
  
  //   // chassis.pid_swing_relative_set(ez::LEFT_SWING, 90_deg, SWING_SPEED, 10);
  //   // chassis.pid_wait();

  //   chassis.pid_turn_relative_set(90, TURN_SPEED);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_relative_set(180, TURN_SPEED);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(-28_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   rightWingOut();
  // }

  // void red_bot_match_close(){
  //   //Intake preload
  //   intakeIn();

  //   rightWingOut();
  //   pros::delay(100);
    
  //   chassis.pid_drive_set(-8_in, 10, true);
  //   chassis.pid_wait();

  //   rightWingIn();
  //   pros::delay(100);
  //   leftWingOut();

  //   chassis.pid_swing_relative_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 30);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(-12_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();
  //   //score alliance triball


  //   chassis.pid_drive_set(8_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();    

  //   leftWingIn();
  //   pros::delay(100);

  //   chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(-8_in, 127, true);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(41_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_relative_set(90_deg, TURN_SPEED);
  //   chassis.pid_wait();

  //   intakeOut(500);
  //   //dump preload

  //   chassis.pid_turn_relative_set(-180_deg, TURN_SPEED);
  //   chassis.pid_wait();


  //   //grab triball 1
  //   intakeIn();
  //   chassis.pid_drive_set(18_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_relative_set(180_deg, TURN_SPEED);
  //   chassis.pid_wait();

  //   intakeStop();
  //   chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   //dump triball 1
  //   intakeOut(500);

  //   //drive and grab triball 2
  //   chassis.pid_drive_set(-9_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_relative_set(175_deg, TURN_SPEED);
  //   chassis.pid_wait();

  //   intakeIn();
  //   chassis.pid_drive_set(20_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();
  //   // pros::delay(500);

  //   chassis.pid_drive_set(-30_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();
  //   intakeStop();

  //   chassis.pid_turn_relative_set(180_deg, TURN_SPEED);
  //   chassis.pid_wait();  

  //   //dump triball 2
  //   intakeOut(500);

  //   //drive and grab triball 3
  //   chassis.pid_drive_set(-7_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_relative_set(-135_deg, TURN_SPEED);
  //   chassis.pid_wait();

  //   intakeIn();
  //   chassis.pid_drive_set(23_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_drive_set(-23_in, DRIVE_SPEED, true);
  //   chassis.pid_wait();

  //   chassis.pid_turn_relative_set(125_deg, TURN_SPEED);
  //   chassis.pid_wait();

  //   //dump triball 3
  //   intakeOut(500);

  //   //drive and grab triball 4
  //   chassis.pid_turn_relative_set(-90_deg, TURN_SPEED);
  //   chassis.pid_wait();

  //   chassis.pid_swing_relative_set(ez::RIGHT_SWING, -90_deg, SWING_SPEED, 30);
  //   chassis.pid_wait();

  //   intakeIn();
  //   chassis.pid_drive_set(8_in, 50, true);
  //   chassis.pid_wait();

  //   chassis.pid_swing_relative_set(ez::RIGHT_SWING, 90_deg, SWING_SPEED, 20);
  //   chassis.pid_wait();
  // }

#endif
