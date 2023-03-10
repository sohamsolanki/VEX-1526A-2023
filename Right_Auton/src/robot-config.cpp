#include "vex.h"
using namespace vex;
using signature = vision::signature;
using code = vision::code;

/*----------------------------------------------------------------------------*/
/*                                DEVICES                                     */
/*----------------------------------------------------------------------------*/

brain  Brain;
competition Competition;
controller Controller1 = controller(primary);
pneumatics Piston1 = pneumatics(Brain.ThreeWirePort.A);
pneumatics Piston2 = pneumatics(Brain.ThreeWirePort.B);

// DRIVETRAIN
motor leftMotorA = motor(PORT1, ratio6_1, true);
motor leftMotorB = motor(PORT2, ratio6_1, true);
motor leftMotorC = motor(PORT3, ratio6_1, true);
motor rightMotorA = motor(PORT8, ratio6_1, true);
motor rightMotorB = motor(PORT9, ratio6_1, true);
motor rightMotorC = motor(PORT10, ratio6_1, true);

// INTAKE + ROLLER MECH
motor Motor6 = motor(PORT6, ratio18_1, false);

// FLYWHEEL
motor Motor7 = motor(PORT7, ratio18_1, false);

// MOTOR GROUPS (to make coding easier)
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

/*----------------------------------------------------------------------------*/
/*                              VOID FUNCTIONS                                */
/*----------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void autonomous(void) {
  Motor6.setVelocity(500, rpm);
  Drivetrain.setDriveVelocity(500, rpm);
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(0.35, seconds);
  Drivetrain.drive(forward);
  wait(0.25, seconds);
  Drivetrain.stop();
  LeftDriveSmart.spin(reverse);
  RightDriveSmart.spin(forward);
  wait(0.5, seconds);
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
  Motor6.spin(reverse);
  wait(1, seconds);
  Motor6.stop();
}

/*----------------------------------------------------------------------------*/
/*                           DRIVETRAIN CODE                                  */
/*----------------------------------------------------------------------------*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = (Controller1.Axis3.position() + Controller1.Axis1.position()*0.33); //*0.33 is to help slowdown turning speed
      int drivetrainRightSideSpeed = (Controller1.Axis3.position() - Controller1.Axis1.position()*0.33);

      // check if the value is inside of the deadband range
      // deadband range = where the joystick is
      if (drivetrainLeftSideSpeed < 0.001 && drivetrainLeftSideSpeed > 0.001) {
        // check if the left side of the drivetrain has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left side of the drivetrain
          LeftDriveSmart.stop();
          // tell the code that the left side of the drivetrain has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left side of the drivetrain the next time the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 0.001 && drivetrainRightSideSpeed > -0.001) {
        // check if the right side of the drivetrain has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right side of the drivetrain
          RightDriveSmart.stop();
          // tell the code that the right side of the drivetrain has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right side of the drivetrain next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left side of the drivetrain to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right side of the drivetrain to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
    
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(reverse);
      }

      // slow down the drivetrain when button Up is pressed for higher accuracy when aiming for the goal
      if(Controller1.ButtonUp.pressing()) {
        LeftDriveSmart.setVelocity((drivetrainLeftSideSpeed * 0.25), percent);
        LeftDriveSmart.spin(forward);
        RightDriveSmart.setVelocity((drivetrainRightSideSpeed * 0.25), percent);
        RightDriveSmart.spin(reverse);
      }
    }

/*----------------------------------------------------------------------------*/
/*                        USER CONTROL + FUNCTIONS                            */
/*----------------------------------------------------------------------------*/   

// Motor coast code
Drivetrain.setStopping(brakeType::coast);

/*----------------------------------------------------------------------------*/
/*                      CONTROLLER DISPLAY + VIBRATE                          */
/*----------------------------------------------------------------------------*/

// DISPLAY
// Description: Displays Flywheel status - checking to see if the RPM of the flywheel hits 80% or higher, and then displays "Flywheel READY" or "Flywheel NOT ready".
// Also checks for battery status for informational purposes.
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  if (Motor7.velocity(pct) > 80) {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Flywheel READY");
    Controller1.Screen.newLine();
    Controller1.Screen.print("RPM %f", Motor7.velocity(rpm));
    Controller1.Screen.newLine();
    Controller1.Screen.print("Battery %.2f%% full", (100 - (Brain.Battery.voltage()/Brain.Battery.capacity())*100));
  } else {
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Flywheel NOT ready");
    Controller1.Screen.newLine();
    Controller1.Screen.print("RPM %f", Motor7.velocity(rpm));
    Controller1.Screen.newLine();
    Controller1.Screen.print("Battery %.2f%% full", (100-(Brain.Battery.voltage()/Brain.Battery.capacity())*100));
  }

// VIBRATE
// Description: Sets the controller to vibrate when the RPM of the flywheel hits higher than 80%.
if (Motor7.velocity(pct) > 80) {
  Controller1.rumble("--");
}
 
/*----------------------------------------------------------------------------*/
/*              INTAKE + ROLLER MECH + PISTON + FLYWHEEL                      */
/*----------------------------------------------------------------------------*/

// INTAKE + ROLLER MECH
// Description: One motor controls the intake, which will get discs from the field and it also controls the roller mechanism, which is used for the rollers on the side of the field for extra points.
// Two booleans are used for buttons L1 and L2. Button L1 will spin the motor forward and Button L2 will spin the motor in a reverse direction.
bool L1buttonPressed = false;
bool L2buttonPressed = false;
Motor6.setVelocity(100, pct);
if(Controller1.ButtonL1.pressing()) {
  if(L1buttonPressed == true){
    L1buttonPressed = false;
    } else {
        L1buttonPressed = true;
        }
      }
if(Controller1.ButtonL2.pressing()) {
  if(L2buttonPressed == true) {
    L2buttonPressed = false;
    } else {
        L2buttonPressed = true;
        }
      }
if(L2buttonPressed == true) {
  Motor6.spin(forward);
  } else {
      Motor6.stop();
  }
if(L1buttonPressed == true){
  Motor6.spin(reverse);
    }

// PISTON (#1)
// Description: This is used as our indexer; it will push the discs from the intake down so the flywheel can efficiently grab them and shoot them out of the robot.
if (Controller1.ButtonX.pressing()){
      Piston1.open();
      Motor6.spin(forward);
      wait(1, seconds);
      Motor6.stop();
      Piston1.close();
    }

// FLYWHEEL
// Description: This will launch the disc out of the robot into the goal.
Motor7.setVelocity(-100, pct);
if(Controller1.ButtonR1.pressing()){
  Motor7.spin(forward);
  }
if(Controller1.ButtonR2.pressing()){
  Motor7.stop();
  }

// ENDGAME MECH
// Description: This is used for our endgame mechanism. 
if(Controller1.ButtonLeft.pressing()){
  Piston2.open();
}

/*----------------------------------------------------------------------------*/
/*                          MISCELLANEOUS FUNCTIONS                           */
/*----------------------------------------------------------------------------*/

    // wait before repeating the process
    wait(1, msec);
  }
  return 0;
}


int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(10, msec);
  }
}

/*
 Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}