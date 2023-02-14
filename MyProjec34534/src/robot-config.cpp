#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature VisionSensor__BLUEBOX = signature (1, -3441, -2785, -3113, 8975, 10355, 9665, 2.5, 0);
signature VisionSensor__GREENBOX = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionSensor__REDBOX = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
vision VisionSensor = vision (PORT5, 150, VisionSensor__BLUEBOX, VisionSensor__GREENBOX, VisionSensor__REDBOX);
/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}