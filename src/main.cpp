#include "main.h"
#include "autons.hpp"
/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
#if BIG_BOT //to be done
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-17, 18, -19, 20}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{12, -13, 14, -15}

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
  {16, -17, 18, -19}
  

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{-11, 12, -13, 14}

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
  chassis.opcontrol_curve_default_set(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  #if BIG_BOT
  ez::as::auton_selector.autons_add({
    Auton("Big Bot Skills", big_bot_skills),
    Auton("Big Bot Match Autonomous", big_bot_match_auton),
  });
  #else
  ez::as::auton_selector.autons_add({
    Auton("Small Bot Skills", small_bot_skills),
    Auton("Small Bot Match Autonomous", small_bot_match_auton),
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
  ez::Piston climbPistonDown('A');
  climbPistonDown.set(true);
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
  pros::Motor slapper(1);

  pros::ADIDigitalOut backWings('B');

  bool frontWingsDeployed = false;
  bool backWingsDeployed = false;

  slapper.set_gearing(pros::E_MOTOR_GEAR_200);
	slapper.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
#else
  pros::Motor climb_motor1(2);
  pros::Motor climb_motor2(3, true);
  pros::Motor_Group climb = pros::Motor_Group({climb_motor1, climb_motor2});

  pros::Motor intake_motor(15);

  ez::Piston frontWing('C');
  ez::Piston climbPistonUp('B');
  ez::Piston climbPistonDown('A');


  bool frontWingsDeployed = false;
  int velo = 0;

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
		if(master.get_digital_new_press(DIGITAL_L2)) {
			backWingsDeployed = !backWingsDeployed;
			backWings.set_value(backWingsDeployed);
		}

    if(master.get_digital(DIGITAL_R1)){
      intake_motor = 127;
    }
    else if(master.get_digital(DIGITAL_R2)){
      intake_motor = -127;
    }
    else{
      intake_motor = 0;
    }

    if(master.get_digital(DIGITAL_X)){
      int pos = 0;
      int angle = 825;  //this is 360 degrees
      slapper.tare_position();

      while(pos < angle){
        slapper = 100;
        pos = slapper.get_position(); 
      }
    }
    else{
      slapper.brake();
    }


    #else //small bot controls


    if(master.get_digital(DIGITAL_R1)){
      intake_motor = 127;
    }
    else if(master.get_digital(DIGITAL_R2)){
      intake_motor = -127;
    }
    else{
      intake_motor = 0;
    }

    //climb rotate
    if(master.get_digital(DIGITAL_UP)){
      velo = 127;

      master.clear();
      pros::delay(100);
      master.print(0, 0, "climb up");
      pros::delay(100);

    }
    else if(master.get_digital(DIGITAL_DOWN)){
      velo = -100;

      master.clear();
      pros::delay(100);
      master.print(0, 0, "climb down");
      pros::delay(100);
    }

    climb_motor1 = velo;

    if(master.get_digital(DIGITAL_L1)){
      climbPistonDown.set(false);
      climbPistonUp.set(true);

      master.clear();
      pros::delay(100);
      master.print(0, 0, "climb out");
      pros::delay(100);
    }
    else if(master.get_digital(DIGITAL_L2)){
      climbPistonUp.set(false);
      climbPistonDown.set(true);

      master.clear();
      pros::delay(100);
      master.print(0, 0, "climb in");
      pros::delay(100);
    }
    //wings
    if(master.get_digital(DIGITAL_A)) {
			frontWingsDeployed = !frontWingsDeployed;
			frontWing.set(frontWingsDeployed);

      master.clear();
      pros::delay(100);
      master.print(0, 0, "wings activated");
      pros::delay(100);

		}

    #endif

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
