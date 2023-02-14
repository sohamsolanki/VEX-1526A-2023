using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern signature VisionSensor__BLUEBOX;
extern signature VisionSensor__GREENBOX;
extern signature VisionSensor__REDBOX;
extern signature VisionSensor__SIG_4;
extern signature VisionSensor__SIG_5;
extern signature VisionSensor__SIG_6;
extern signature VisionSensor__SIG_7;
extern vision VisionSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );