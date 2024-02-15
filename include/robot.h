// define robot ports here
#pragma once

#define CATA_BOT true

#include "api.h"
#include "library/ChassisController.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

#if CATA_BOT
    #define RIGHT_MOTOR_1_PORT 4
    #define RIGHT_MOTOR_2_PORT 3
    #define RIGHT_MOTOR_3_PORT 2
    #define RIGHT_MOTOR_4_PORT 5

    #define LEFT_MOTOR_1_PORT 6
    #define LEFT_MOTOR_2_PORT 7
    #define LEFT_MOTOR_3_PORT 8
    #define LEFT_MOTOR_4_PORT 9

    #define INERTIAL_PORT 18
    #define INTAKE_PORT 17

    #define cata_motor1
    #define cata_motor2

    #define FRONT_WINGS_PORT 'B'
    #define BACK_WINGS_PORT 'C'
#else
    #define RIGHT_MOTOR_1_PORT 4
    #define RIGHT_MOTOR_2_PORT 3
    #define RIGHT_MOTOR_3_PORT 2
    #define RIGHT_MOTOR_4_PORT 5

    #define LEFT_MOTOR_1_PORT 6
    #define LEFT_MOTOR_2_PORT 7
    #define LEFT_MOTOR_3_PORT 8
    #define LEFT_MOTOR_4_PORT 9

    #define INERTIAL_PORT 18
    
    #define FRONT_WINGS_PORT 'B'
    #define BACK_WINGS_PORT 'C'
#endif


extern pros::Controller master;

extern pros::Motor rightMotor1;
extern pros::Motor rightMotor2;
extern pros::Motor rightMotor3;
extern pros::Motor rightMotor4;

extern pros::Motor leftMotor1;
extern pros::Motor leftMotor2;
extern pros::Motor leftMotor3;
extern pros::Motor leftMotor4;

#if CATA_BOT
    extern pros::Motor IntakeMotor;
    extern pros::Motor cataMotor1;
    extern pros::Motor cataMotor2;
#endif

extern pros::Motor_Group leftMotors;
extern pros::Motor_Group rightMotors;

extern pros::Imu imu;

extern pros::ADIDigitalOut frontWings;
extern pros::ADIDigitalOut backWings;

extern PID drivePid;
extern PID turnPid;
extern Chassis driveChassis;