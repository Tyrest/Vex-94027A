/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;
vex::motor LeftMotor1 = vex::motor( vex::PORT1, true );
vex::motor LeftMotor2 = vex::motor( vex::PORT2 );
vex::motor RightMotor1 = vex::motor( vex::PORT3 );
vex::motor RightMotor2 = vex::motor( vex::PORT4, true );
vex::motor rampMotor = vex::motor(vex::PORT5);
vex::controller Controller1 = vex::controller();

int buttonState = 0; // 0, back/starting position, 1, forward

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
    /*
    LeftMotor1.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
    LeftMotor2.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
    RightMotor1.spin(vex::directionType::fwd, Controller1.Axis2.position(), vex::velocityUnits::pct);
    RightMotor2.spin(vex::directionType::fwd, Controller1.Axis2.position(), vex::velocityUnits::pct);
    */
    double leftMotorSpeed = 0;
    double rightMotorSpeed = 0;

    leftMotorSpeed += Controller1.Axis4.position();
    leftMotorSpeed += Controller1.Axis3.position();

    rightMotorSpeed -= Controller1.Axis4.position();
    rightMotorSpeed += Controller1.Axis3.position();

    LeftMotor1.spin(vex::directionType::fwd, leftMotorSpeed, vex::velocityUnits::pct);
    RightMotor1.spin(vex::directionType::fwd, rightMotorSpeed, vex::velocityUnits::pct);

    rampMotor.spin(vex::directionType::fwd, Controller1.Axis1.position()/10, vex::velocityUnits::pct);

    /*
    if (Controller1.ButtonA.pressing())
    {
      if (buttonState == 0)
      {
        rampMotor.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
        vex::task::sleep(900);
        rampMotor.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
        buttonState = 1;
      }
      else 
      {
        rampMotor.spin(vex::directionType::rev, 7, vex::velocityUnits::pct);
        vex::task::sleep(900);
        rampMotor.spin(vex::directionType::rev, 0, vex::velocityUnits::pct);
        buttonState = 0;
      }
    }
    */


    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
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
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}