#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors

controller Controller1 = controller(primary);
limit Limit1 = limit(Brain.ThreeWirePort.C);
pneumatics Piston1 = pneumatics(Brain.ThreeWirePort.H);

motor leftMotorA = motor(PORT1, ratio18_1, true);
motor leftMotorB = motor(PORT2, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT9, ratio18_1, false);
motor rightMotorB = motor(PORT10, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

// intake
motor Motor4 = motor(PORT4, ratio18_1, false);

// string launcher
motor Motor8 = motor(PORT8, ratio36_1, false);
motor Motor3 = motor(PORT3, ratio36_1, false);

// flywheel motor #1
motor Motor7 = motor(PORT7, ratio6_1, false);

// expansion motor #2
motor Motor9 = motor(PORT9, ratio18_1, false);


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
        RightDriveSmart.spin(forward);
      }
    }

// Motor coast code
Drivetrain.setStopping(brakeType::coast);
  
// Flywheel #1 code
Motor7.setVelocity(100, pct);
  if(Controller1.ButtonR1.pressing()){
  Motor7.spin(forward);
  }
  if(Controller1.ButtonR2.pressing()){
  Motor7.stop();
  }

// Flywheel #2 code
Motor9.setVelocity(100, pct);
if(Controller1.ButtonDown.pressing()){
  Motor9.rotateFor(90, rotationUnits::deg);
  wait(1, sec);
  Motor9.rotateFor(-90, rotationUnits::deg);
}

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
    Controller1.Screen.print("Battery %.2f%% full", (Brain.Battery.voltage()/Brain.Battery.capacity())*100);
  }

// Controller vibrate code
if (Motor7.velocity(pct) > 80) {
  Controller1.rumble("--");
}
    
// Intake code
bool L1buttonPressed = false;
bool L2buttonPressed = false;
Motor4.setVelocity(150, rpm);
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
      Motor4.spin(reverse);
    } else {
      Motor4.stop();
    }

     if(L1buttonPressed == true){
      Motor4.spin(forward);
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

  if (Limit1.pressing()) {
    Motor7.spin(forward);
  }

  // STRING LAUNCHER
  if (Controller1.ButtonDown.pressing()) {
    Motor8.rotateFor(90, rotationUnits::deg);
    Motor3.rotateFor(-90, rotationUnits::deg);
    wait(1, seconds);
    Motor8.rotateFor(-90, rotationUnits::deg);
    Motor3.rotateFor(90, rotationUnits::deg);
  }
    // wait before repeating the process
    wait(1, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}