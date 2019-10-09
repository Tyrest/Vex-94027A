/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       mitsukakiyohara                                           */
/*    Created:      Sat Sep 28 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"


// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

vex::competition Competition;
vex::rotationUnits revolutions = vex::rotationUnits::rev;
vex::motor leftIntake = vex::motor( vex::PORT1, true );
vex::motor rightIntake = vex::motor( vex::PORT3 );
vex::controller Controller1 = vex::controller();

int buttonState = 0; // 0, back/starting position, 1, forward

using namespace vex;

// define your global instances of motors and other devices here


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    
    if (Controller1.ButtonX.pressing())
    {
      if (buttonState == 0)
      {
        float revsPerClawbot90Turn = 1.7;
        leftIntake.startRotateFor(-1 * revsPerClawbot90Turn, revolutions);
        rightIntake.rotateFor(revsPerClawbot90Turn, revolutions);
    
        leftIntake.startRotateFor(2 * revsPerClawbot90Turn, revolutions);
        rightIntake.rotateFor(-2 * revsPerClawbot90Turn, revolutions);
        
        buttonState = 1;
      }
      else
      {
        buttonState = 0;
      }
    }


  }




}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) 
    {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}