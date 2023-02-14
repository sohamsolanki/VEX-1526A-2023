/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\vexrobotics                                      */
/*    Created:      Tue Jan 25 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
   
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// VisionSensor         vision        5               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"

using namespace vex;

#include "robot-config.h"

competition Competition;
int centerFOV = 158;
int offsetX = 15;
int run = 0; // Will be used as a precaution before running forward code
void auto_turn()
{
   Brain.Screen.clearLine();
   VisionSensor.takeSnapshot(VisionSensor__BLUEBOX);

   if(VisionSensor.largestObject.exists)
   {
     if(VisionSensor.largestObject.centerX > centerFOV + offsetX)//If the object is to the left then turns right
     {
       Drivetrain.spin(forward);
     }
   
   else if(VisionSensor.largestObject.centerX < centerFOV - offsetX) // If the object is to the right then turn left
   {
      Drivetrain.spin(reverse);
     //Spin Motors
   }
    else
    {
      Drivetrain.stop();
    }
   }

   //Extra precaution for running the forward code
   if(VisionSensor.largestObject.centerX > centerFOV + offsetX || VisionSensor.largestObject.centerX == centerFOV - offsetX )//If the object is to the left then turns right
     {
       run = 3;
     }  
}

int hw = 0;
int h = 0;
int w = 0;
void movefwd()
{
  h = VisionSensor.objects[0].height;
  w = VisionSensor.objects[0].width;
  hw = h*w; 
  if(hw < 53172)// It is less than bc height and width gets bigger as you get closer so once you are close enough you can stop
  {   
    LeftDriveSmart.spin(forward);
    RightDriveSmart.spin(forward);
  }
  else
  {
    LeftDriveSmart.stop();
    RightDriveSmart.stop();
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  while(true)
  {
   auto_turn();
   wait(350, msec); 
   if(run == 3)
   {
    movefwd();
   }
   else
   {
     run == 0;//Not necessary bc run is being overwritten each time but just in case
   }
  }
}