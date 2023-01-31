#include "vex.h"

// soham was here
using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
competition Competition;
controller Controller1 = controller(primary);
limit Limit1 = limit(Brain.ThreeWirePort.C);
pneumatics Piston1 = pneumatics(Brain.ThreeWirePort.H);

// 6 motor drivetrain
motor leftMotorA = motor(PORT1, ratio6_1, true);
motor leftMotorB = motor(PORT2, ratio6_1, true);
motor leftMotorC = motor(PORT3, ratio6_1, true);
motor rightMotorA = motor(PORT8, ratio6_1, true);
motor rightMotorB = motor(PORT9, ratio6_1, true);
motor rightMotorC = motor(PORT10, ratio6_1, true);

// intake and roller mech
motor Motor6 = motor(PORT6, ratio18_1, false);

// flywheel
motor Motor7 = motor(PORT7, ratio18_1, false);

/* // string launcher
motor Motor8 = motor(PORT8, ratio36_1, false);
motor Motor9 = motor(PORT9, ratio36_1, false); */

// expansion motor 
// motor Motor11 = motor(PORT11, ratio18_1, false);

motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void autonomous(void) {
  Drivetrain.setDriveVelocity(500, rpm);
  Motor7.setVelocity(100, pct);
  Drivetrain.driveFor(forward, 100, mm);
  Motor7.rotateFor(5, seconds);
  // Drivetrain.driveFor(reverse, 200, mm);
}

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
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
     

      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();

      //Below code is trying to decrease turning speed
      /*
      if(Controller1.Axis1.position() > 0 && Controller1.Axis3.position() > -5 && Controller1.Axis3.position() < 5){
        drivetrainLeftSideSpeed = drivetrainLeftSideSpeed * 0.05;
        }
      if(Controller1.Axis1.position() < 0 && Controller1.Axis3.position() > -5 && Controller1.Axis3.position() < 5){
        drivetrainRightSideSpeed = drivetrainRightSideSpeed * 0.05;
        }
        */
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
         
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(reverse);
      }
    }

// Motor coast code
Drivetrain.setStopping(brakeType::coast);
  
// Flywheel code
Motor7.setVelocity(100, pct);
  if(Controller1.ButtonR1.pressing()){
  Motor7.spin(forward);
  }
  if(Controller1.ButtonR2.pressing()){
  Motor7.stop();
  }
  

/* // Expansion motor code
Motor9.setVelocity(100, pct);
if(Controller1.ButtonDown.pressing()){
  Motor9.rotateFor(90, rotationUnits::deg);
  wait(1, sec);
  Motor9.rotateFor(-90, rotationUnits::deg);
} */

// Controller Display code
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  // wait(6, seconds);
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

// Controller vibrate code
if (Motor7.velocity(pct) > 80) {
  Controller1.rumble("--");
}

// auton test
if(Controller1.ButtonLeft.pressing()) {
  Drivetrain.setDriveVelocity(500, rpm);
  Motor6.setVelocity(100, pct);
  Drivetrain.driveFor(forward, 100, mm);
  Motor6.rotateFor(5, seconds);
  // Drivetrain.driveFor(reverse, 200, mm);
}
    
// Intake code
bool L1buttonPressed = false;
bool L2buttonPressed = false;
Motor6.setVelocity(100, pct);
     if (Controller1.ButtonL1.pressing()) {
        if(L1buttonPressed == true){
          L1buttonPressed = false;
        }else{
          L1buttonPressed = true;
        }
      }

      if (Controller1.ButtonL2.pressing()) {
        if(L2buttonPressed == true) {
          L2buttonPressed = false;
        } else {
          L2buttonPressed = true;
        }
      }
  
    if (L2buttonPressed == true) {
      Motor6.spin(forward);
    } else {
      Motor6.stop();
    }

     if(L1buttonPressed == true){
      Motor6.spin(reverse);
    }

  // Limit switch code
    if(Limit1.pressing()) {
      Motor7.spin(forward);
    }

   // Piston code
    if (Controller1.ButtonX.pressing()){
      Piston1.close();
      wait(2, seconds);
      Piston1.open();
      wait (1, seconds);
      Motor7.stop();
    }

  /* // STRING LAUNCHER
  if (Controller1.ButtonDown.pressing()) {
    Motor8.rotateFor(-90, rotationUnits::deg);
    Motor9.rotateFor(90, rotationUnits::deg);
   //  wait(1, seconds);
    // Motor8.rotateFor(90, rotationUnits::deg);
   //  Motor3.rotateFor(-90, rotationUnits::deg);
  } */
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
    wait(100, msec);
  }
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}