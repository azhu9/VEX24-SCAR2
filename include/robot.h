// define robot ports here
#pragma once

//what are we compiling to?
#define CATA_BOT true //false for red bot

#include "api.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

#if CATA_BOT
    #define RIGHT_MOTOR_1_PORT 1
    #define RIGHT_MOTOR_2_PORT 2
    #define RIGHT_MOTOR_3_PORT 3
    #define RIGHT_MOTOR_4_PORT 4

    #define INERTIAL_PORT 5

    #define INTAKE_PORT 6

    #define LEFT_MOTOR_1_PORT 7
    #define LEFT_MOTOR_2_PORT 8
    #define LEFT_MOTOR_3_PORT 9
    #define LEFT_MOTOR_4_PORT 10

    #define CLIMB_MOTOR_PORT 20

    #define FRONT_WINGS_PORT 'A'
    #define BACK_WINGS_PORT 'B'
#else
    #define RIGHT_MOTOR_1_PORT 12
    #define RIGHT_MOTOR_2_PORT 14
    #define RIGHT_MOTOR_3_PORT 16
    #define RIGHT_MOTOR_4_PORT 17

    #define INERTIAL_PORT 19

    #define INTAKE_PORT 20

    #define LEFT_MOTOR_1_PORT 11
    #define LEFT_MOTOR_2_PORT 13
    #define LEFT_MOTOR_3_PORT 15
    #define LEFT_MOTOR_4_PORT 18

    #define FRONT_WINGS_PORT 'A'
    #define BACK_WINGS_PORT 'B'
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

extern pros::Motor IntakeMotor;

extern pros::Motor_Group leftMotors;
extern pros::Motor_Group rightMotors;

extern pros::Motor climbMotor;

extern pros::Imu imu;

extern pros::ADIDigitalOut frontWings;
extern pros::ADIDigitalOut backWings;
