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

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // check the ButtonL1/ButtonL2 status to control Motor4

      //Seeing if we can make it faster
      Motor1.setVelocity(500, rpm);
      Motor2.setVelocity(500, rpm);
      Motor3.setVelocity(500, rpm);
      Motor4.setVelocity(500, rpm);
      Motor5.setVelocity(500, rpm);
      Motor6.setVelocity(500, rpm);
           
   
      if (Controller1.Axis3.value() <= -20) {

   Motor4.spin(reverse);
   Motor5.spin(reverse);
   Motor6.spin(reverse);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.Axis3.value() >= 20) {

   Motor4.spin(forward);
   Motor5.spin(forward);
   Motor6.spin(forward);
        Controller1LeftShoulderControlMotorsStopped = false;
      } else {

        Motor4.stop();
        Motor5.stop();
        Motor6.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      
      
       if (Controller1.Axis2.value() <= -20) {
        Motor1.spin(forward);
   Motor2.spin(forward);
   Motor3.spin(forward);

        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.Axis2.value() >= 20) {
        Motor1.spin(reverse);
   Motor2.spin(reverse);
   Motor3.spin(reverse);

        Controller1LeftShoulderControlMotorsStopped = false;
      } else {
        Motor1.stop();
        Motor2.stop();
        Motor3.stop();

        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      


      
      


      // check the ButtonR1/ButtonR2 status to control Motor3
      if (Controller1.ButtonR1.pressing()) {
        Motor3.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        Motor3.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        Motor3.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
      // check the ButtonUp/ButtonDown status to control Motor2
      if (Controller1.ButtonUp.pressing()) {
        Motor2.spin(forward);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonDown.pressing()) {
        Motor2.spin(reverse);
        Controller1UpDownButtonsControlMotorsStopped = false;
      } else if (!Controller1UpDownButtonsControlMotorsStopped) {
        Motor2.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1UpDownButtonsControlMotorsStopped = true;
      }
      // check the ButtonX/ButtonB status to control Motor1
      if (Controller1.ButtonX.pressing()) {
        Motor1.spin(forward);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (Controller1.ButtonB.pressing()) {
        Motor1.spin(reverse);
        Controller1XBButtonsControlMotorsStopped = false;
      } else if (!Controller1XBButtonsControlMotorsStopped) {
        Motor1.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1XBButtonsControlMotorsStopped = true;
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