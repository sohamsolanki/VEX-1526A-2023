@ -5,15 +5,23 @@ using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
brain Brain;

// VEXcode device constructors

// Drivetrain
motor Motor1 = motor(PORT1, ratio18_1, false);
motor Motor2 = motor(PORT2, ratio18_1, false);
motor Motor3 = motor(PORT3, ratio18_1, false);
motor Motor4 = motor(PORT4, ratio18_1, false);
motor Motor5 = motor(PORT5, ratio18_1, false);
motor Motor6 = motor(PORT6, ratio18_1, false);

// Flywheel
motor Motor7 = motor(PORT7, ratio18_1, false);
motor Motor8 = motor(PORT8, ratio18_1, false);

// Controller
controller Controller1 = controller(primary);

// VEXcode generated functions
@ -29,8 +37,10 @@ bool Controller1XBButtonsControlMotorsStopped = true;
// User generated functions - make code easier to debug
motor_group driveL(Motor1, Motor2, Motor3);
motor_group driveR(Motor4, Motor5, Motor6);
motor_group flywheel(Motor7, Motor8);
drivetrain myDriveTrain(driveL, driveR);


// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
@ -41,6 +51,7 @@ int rc_auto_loop_function_Controller1() {
      // changing RPM of motors
      driveL.setVelocity(500, rpm);
      driveR.setVelocity(500, rpm);
      flywheel.setVelocity(500, rpm);


      // CONTROLS - LEFT joystick
@ -70,6 +81,16 @@ int rc_auto_loop_function_Controller1() {
        driveL.stop();
        Controller1LeftShoulderControlMotorsStopped = true;
      }

      // CONTROLS - FLYWHEEL
      if (Controller1.ButtonR1.pressing()) {
        Motor7.spin(forward);
        Motor8.spin(reverse);
      }
      if (Controller1.ButtonR2.pressing()) {
        Motor7.stop();
        Motor8.stop();
      }
    }
    // wait before repeating the process
    wait(20, msec);
