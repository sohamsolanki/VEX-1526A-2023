#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Motor1 = motor(PORT1, ratio18_1, false);
motor Motor2 = motor(PORT2, ratio18_1, false);
motor Motor3 = motor(PORT3, ratio18_1, false);
motor Motor4 = motor(PORT4, ratio18_1, false);
motor Motor5 = motor(PORT5, ratio18_1, false);
motor Motor6 = motor(PORT6, ratio18_1, false);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool Controller1UpDownButtonsControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;

// User generated functions - make code easier to debug
motor_group driveL(Motor1, Motor2, Motor3);
motor_group driveR(Motor4, Motor5, Motor6);
drivetrain myDriveTrain(driveL, driveR);

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {

      // changing RPM of motors
      driveL.setVelocity(500, rpm);
      driveR.setVelocity(500, rpm);
           
      // CONTROLS - LEFT JOYSTICK
      if (Controller1.Axis3.value() <= -20) {
        driveR.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;

      } else if (Controller1.Axis3.value() >= 20) {
        driveR.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;

      } else {
        driveR.stop();
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      
      // CONTROLS - RIGHT JOYSTICK
       if (Controller1.Axis2.value() <= -20) {
        driveL.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;

      } else if (Controller1.Axis2.value() >= 20) {
        driveL.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;

      } else {
        driveL.stop();
        Controller1LeftShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
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