#include "main.h"
#include "autons.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
#if BIG_BOT //to be done
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {1, -2, 3, -4}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{-6, 7,-8, 9}

  // IMU Port
  ,9

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,3.25

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,1.6667
);
#else
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-10, 9, -8, 7}
  

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{-4, 3, -2, 1}

  // IMU Port
  ,13

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,3.25

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,1.6667
);
#endif


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0); // Sets the active brake kP. We recommend 0.1.
  chassis.opcontrol_curve_default_set(3.9, 4.3); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  #if BIG_BOT
  ez::as::auton_selector.autons_add({
    Auton("Big Bot Match Autonomous", big_bot_match_auton),
    Auton("Big Bot Skills", big_bot_skills),
  });
  #else
  ez::as::auton_selector.autons_add({
    Auton("Red bot Match FAR", red_bot_match_far),
    Auton("test", pid_test),
  Auton("Small Bot Match Autonomous", red_bot_match_close),
  Auton("Small Bot Skills", small_bot_skills),

    
  });
  #endif

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
  #if BIG_BOT
    ez::Piston leftWing('H', false);
    ez::Piston rightWing('A', false);
  #else
    ez::Piston rightWing('C', false);
  ez::Piston leftWing('A', false);
  #endif
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call(); // Calls selected auton from autonomous selector
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  
  
#if BIG_BOT
  pros::Motor intake_motor(10);
  pros::Motor winch_motor(16);
  pros::Motor climb_motor1(-20);
  pros::Motor climb_motor2(11);
  pros::MotorGroup climb({climb_motor1, climb_motor2});
  climb.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

  ez::Piston leftWing('H', false);
  ez::Piston rightWing('A', false);
  ez::Piston claw('B');

  bool leftWingDeployed = false;
  bool rightWingDeployed = false;
  bool clawDeployed = false;

#else
  // pros::Motor slapper(1);
  // slapper.set_gearing(pros::E_MOTOR_GEAR_200);
	// slapper.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

  pros::Motor intake_motor(11);
  intake_motor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  pros::Motor climb_motor1(-6);
  pros::Motor climb_motor2(20);
  pros::Motor_Group climb({climb_motor1, climb_motor2});
  climb_motor1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  climb_motor2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  ez::Piston rightWing('A', false);
  ez::Piston leftWing('B', false);

  bool leftWingDeployed = false;
  bool rightWingDeployed = false;
#endif

  
  while (true) {
    
    // // PID Tuner
    // // After you find values that you're happy with, you'll have to set them in auton.cpp
    // if (!pros::competition::is_connected()) { 
    //   // Enable / Disable PID Tuner
    //   //  When enabled: 
    //   //  * use A and Y to increment / decrement the constants
    //   //  * use the arrow keys to navigate the constants
    //   if (master.get_digital_new_press(DIGITAL_X)) 
    //     chassis.pid_tuner_toggle();
        
    //   // Trigger the selected autonomous routine
    //   if (master.get_digital_new_press(DIGITAL_B)) 
    //     autonomous();

    //   chassis.pid_tuner_iterate(); // Allow PID Tuner to iterate
    // } 

    // chassis.opcontrol_tank(); // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE); // Flipped single arcade

    #if BIG_BOT //big bot controls

    if(master.get_digital(DIGITAL_R1)){
      intake_motor = -127;
    }
    else if(master.get_digital(DIGITAL_R2)){
      intake_motor = 127;
    }
    else{
      intake_motor = 0;
    }

    if(master.get_digital_new_press(DIGITAL_L1)) {
			leftWingDeployed = !leftWingDeployed;
			leftWing.set(leftWingDeployed);
		}

    if(master.get_digital_new_press(DIGITAL_L2)) {
			rightWingDeployed = !rightWingDeployed;
			rightWing.set(rightWingDeployed);
		}

    //CLIMB CONTROLS
    if(master.get_digital(DIGITAL_UP)){
      climb = 127;
    }
    else if(master.get_digital(DIGITAL_DOWN)){
      climb = -127;
    }
    else{
      climb.brake();
    }

    if(master.get_digital(DIGITAL_RIGHT)){
      winch_motor = 127;
    }
    else if(master.get_digital(DIGITAL_LEFT)){
      winch_motor = -127;
    }
    else{
      winch_motor.brake();
    }

    if(master.get_digital_new_press(DIGITAL_X)) {
			clawDeployed = !clawDeployed;
			claw.set(clawDeployed);
		}
    

    #else

      if(master.get_digital(DIGITAL_R1)){
      intake_motor = -127;
      }
      else if(master.get_digital(DIGITAL_R2)){
        intake_motor = 127;
      }
      else{
        intake_motor = 0;
      }

      if(master.get_digital_new_press(DIGITAL_L1)) {
        leftWingDeployed = !leftWingDeployed;
        leftWing.set(leftWingDeployed);
		}

    if(master.get_digital_new_press(DIGITAL_L2)) {
        rightWingDeployed = !rightWingDeployed;
        rightWing.set(rightWingDeployed);
		}

    if(master.get_digital(DIGITAL_UP)){
      climb = -127;
    }
    else if(master.get_digital(DIGITAL_DOWN)){
      climb = 127;
    }
    else{
      climb.brake();
    }

    #endif

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
