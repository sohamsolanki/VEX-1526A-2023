
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ssolanki                                                  */
/*    Created:      Wed Sep 28 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Motor2               motor         2               
// Motor3               motor         3               
// Motor4               motor         4               
// Motor5               motor         5               
// Motor6               motor         6               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
const int wheelTravel = 320;
const int trackWidth = 320;
const int wheelBase = 130;
motor_group driveL(Motor1, Motor2, Motor3);
motor_group driveR(Motor4, Motor5, Motor6);
drivetrain myDrivetrain(driveL, driveR, wheelTravel, trackWidth, wheelBase, mm);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
  
  /*
  Motor1.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
  Motor2.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
  Motor3.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
  Motor4.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
  Motor5.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
  Motor6.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
*/


      // check the ButtonL1/ButtonL2 status to control Motor1
      if (Controller1.Axis3.value() > 25) {
        driveL.spin(forward);
      }
      if(Controller1.Axis3.value() < -25) {
        driveR.spin(reverse);
      }
      /*
      if (Controller1.Axis1.value() > 25) {
        Motor1.spin(forward);
        Motor2.spin(forward);
        Motor3.spin(forward);
        // Motor4.spin(forward);
        // Motor5.spin(forward);
        // Motor6.spin(forward);
        //Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.Axis1.value() < -25) {
        // Motor1.spin(reverse);
        // Motor2.spin(reverse);
        // Motor3.spin(reverse);
        Motor4.spin(reverse);
        Motor5.spin(reverse);
        Motor6.spin(reverse);
        //Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.Axis1.value() > -10 && Controller1.Axis1.value() < 10) {
        Motor1.stop();
        Motor2.stop();
        Motor3.stop();
        Motor4.stop();
        Motor5.stop();
        Motor6.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        //Controller1LeftShoulderControlMotorsStopped = true;
      }
    */
  /*
      if(Controller1.Axis4.value() > 25){
        Motor1.spin(forward);
        Motor2.spin(forward);
        Motor3.spin(forward);
        Motor4.spin(reverse);
        Motor5.spin(reverse);
        Motor6.spin(reverse);

      }else if(Controller1.Axis4.value() < -25){
        Motor4.spin(forward);
        Motor5.spin(forward);
        Motor6.spin(forward);
        Motor1.spin(reverse);
        Motor2.spin(reverse);
        Motor3.spin(reverse);

      }else if(Controller1.Axis4.value() > -10 && Controller1.Axis4.value() < 10){
        Motor1.stop();
        Motor2.stop();
        Motor3.stop();
        Motor4.stop();
        Motor5.stop();
        Motor6.stop();

      }
*/
    




  

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
