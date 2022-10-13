/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\BRWNinc                                          */
/*    Created:      Tue Oct 11 2022                                           */
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

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  motor_group driveL(Motor1, Motor2, Motor3);
  motor_group driveR(Motor4, Motor5, Motor6);
  drivetrain myDriveTrain(driveL, driveR);

  

  }

 
 
 void driveForward(){
   Motor1.spin(forward);
   Motor2.spin(forward);
   Motor3.spin(forward);
   Motor4.spin(forward);
   Motor5.spin(forward);
   Motor6.spin(forward);
 }

 void driveBackward(){
   Motor1.spin(reverse);
   Motor2.spin(reverse);
   Motor3.spin(reverse);
   Motor4.spin(reverse);
   Motor5.spin(reverse);
   Motor6.spin(reverse);
 }

