#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

#define CATA_BOT false
// Chassis constructor
#if CATA_BOT //to be done
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-11, 12, -13, 14}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{15, -16, 17, -18}

  // IMU Port
  ,1

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
  {-11, 12, -13, 14}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{15, -16, 17, -18}

  // IMU Port
  ,1

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
  ez::as::auton_selector.autons_add({
    Auton("Pancake Bot Auton Win Point", small_AWP),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

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

#if CATA_BOT
  //update this
  pros::Motor intake_motor1(1);
  pros::Motor intake_motor2(2, true); 
  pros::Motor_Group intake = pros::Motor_Group({intake_motor1, intake_motor2});

  pros::Motor cata_motor1(3);
  pros::Motor cata_motor2(4, true);
  pros::Motor_Group cata = pros::Motor_Group({cata_motor1, cata_motor2});
  // pros::ADIDigitalOut frontWings('A');
  // pros::ADIDigitalOut backWings('B');

  bool frontWingsDeployed = false;
  bool backWingsDeployed = false;
#else
  pros::Motor climb_motor1(19);
  pros::Motor climb_motor2(20, true);
  pros::Motor_Group climb = pros::Motor_Group({climb_motor1, climb_motor2});

  ez::Piston frontWing('C');
  ez::Piston climbPistonUp('B');
  ez::Piston climbPistonDown('A');


  bool frontWingsDeployed = false;
  int velo = 0;

#endif

  
  while (true) {
    
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) { 
      // Enable / Disable PID Tuner
      //  When enabled: 
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_X)) 
        chassis.pid_tuner_toggle();
        
      // Trigger the selected autonomous routine
      if (master.get_digital_new_press(DIGITAL_B)) 
        autonomous();

      chassis.pid_tuner_iterate(); // Allow PID Tuner to iterate
    } 

    // chassis.opcontrol_tank(); // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE); // Flipped single arcade

    #if CATA_BOT //cata bot controls
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			frontWingsDeployed = !frontWingsDeployed;
			frontWings.set_value(frontWingsDeployed);
		}
		if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			backWingsDeployed = !backWingsDeployed;
			backWings.set_value(backWingsDeployed);
		}

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
      intake = 80;
    }
    else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
      intake = -80;
    }
    else{
      intake = 0;
    }

    //cata code goes here 
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)){
      cata = 127;
    }
    else{
      cata = 0;
    }

    #else //u bot controls

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

    if(master.get_digital(DIGITAL_R1)){
      climbPistonDown.set(false);
      climbPistonUp.set(true);

      master.clear();
      pros::delay(100);
      master.print(0, 0, "climb out");
      pros::delay(100);
    }
    else if(master.get_digital(DIGITAL_R2)){
      climbPistonUp.set(false);
      climbPistonDown.set(true);

      master.clear();
      pros::delay(100);
      master.print(0, 0, "climb in");
      pros::delay(100);
    }
    //wings
    if(master.get_digital(DIGITAL_L1)) {
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
