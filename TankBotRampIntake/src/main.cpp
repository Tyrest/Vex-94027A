// To complete the VEXcode V5 Text project upgrade process, please follow the
// steps below.
// 
// 1. You can use the Robot Configuration window to recreate your V5 devices
//   - including any motors, sensors, 3-wire devices, and controllers.
// 
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Configuration window. 
// 
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       marvinmok                                                 */
/*    Created:      Thu Oct 10 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here

vex::controller Controller1 = vex::controller();
vex::motor LeftMotorA       = vex::motor( vex::PORT1, true );
vex::motor LeftMotorB       = vex::motor( vex::PORT2 );
vex::motor RightMotorA      = vex::motor( vex::PORT11 );
vex::motor RightMotorB      = vex::motor( vex::PORT12, true );
vex::motor IntakeA          = vex::motor( vex::PORT3);
vex::motor IntakeB          = vex::motor( vex::PORT4, true );
vex::motor UpDown           = vex::motor( vex::PORT9 );
vex::motor rampMotor        = vex::motor( vex::PORT5 );
double speedMult = 1;

bool buttonPressedLast = false;

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

static void goResetRotation()
{
  LeftMotorA.resetRotation();
  LeftMotorB.resetRotation();
  RightMotorA.resetRotation();
  RightMotorB.resetRotation();
  IntakeA.resetRotation();
  IntakeB.resetRotation();
  rampMotor.resetRotation();
}

static void stopDriveBase()
{
  LeftMotorA.stop();
  LeftMotorB.stop();
  RightMotorA.stop();
  RightMotorB.stop();
}

// if you want to go backwards, use negative speed
static void goForward(double speed, double rotations)
{
  goResetRotation();
  LeftMotorA.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  LeftMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorA.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  waitUntil(fabs(LeftMotorA.rotation(vex::rotationUnits::rev)) >= rotations);
  stopDriveBase();
}

// static void turnRight(double speed, double rotations)
// {
//   goResetRotation();
//   LeftMotorA.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
//   LeftMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
//   RightMotorA.spin(vex::directionType::fwd, -speed, vex::velocityUnits::pct);
//   RightMotorB.spin(vex::directionType::fwd, -speed, vex::velocityUnits::pct);
//   waitUntil(LeftMotorA.rotation(vex::rotationUnits::rev) >= rotations);
//   stopDriveBase();
// }

static void turnLeft(double speed, double rotations)
{
  goResetRotation();
  LeftMotorA.spin(vex::directionType::fwd, -speed, vex::velocityUnits::pct);
  LeftMotorB.spin(vex::directionType::fwd, -speed, vex::velocityUnits::pct);
  RightMotorA.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  waitUntil(fabs(RightMotorA.rotation(vex::rotationUnits::rev)) >= rotations);
  stopDriveBase();
}

static void spinIntake(double speed, double rotations)
{
  goResetRotation();
  IntakeA.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  IntakeB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  waitUntil(fabs(IntakeA.rotation(vex::rotationUnits::rev)) >= rotations);
  IntakeA.stop();
  IntakeB.stop();
}

static void spinRamp(int direction)
{
  goResetRotation();
  rampMotor.spin(vex::directionType::fwd, 20 * direction, vex::velocityUnits::pct);
  waitUntil(fabs(rampMotor.rotation(vex::rotationUnits::rev)) >= 3.5);
  rampMotor.stop();
}

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  // UpDown.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  // vex::task::sleep(500);
  // UpDown.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  // vex::task::sleep(500);
  // UpDown.stop();
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

    

    if (Controller1.ButtonY.pressing())
    {
      //flip out the intake
      /*
      UpDown.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      vex::task::sleep(500);
      UpDown.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      vex::task::sleep(500);
      UpDown.stop();
      */

      // Deploy Stuff
      UpDown.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      wait(0.5, vex::timeUnits::sec);
      UpDown.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
      IntakeA.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      IntakeB.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      wait(2, vex::timeUnits::sec);
      spinRamp(5);
      IntakeA.stop();
      IntakeB.stop();
      spinRamp(-5);
      IntakeA.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      IntakeB.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      wait(2, vex::timeUnits::sec);

      // Pick Up Blocks
      goForward(20, 3.0);
      UpDown.stop();
      turnLeft(20, 1.2);
      goForward(20, 2.4);
      spinIntake(-20, 0.25);
      spinRamp(1);
      goForward(10, 0.2);
      IntakeA.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
      IntakeB.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
      goForward(-20, 1.5);
      IntakeA.stop();
      IntakeB.stop();

      // Stack Blocks
      goForward(-10, 0.3);
      spinIntake(-20, 3);
      spinIntake(20, 1);
      spinRamp(1);
      // goForward(10, 0.1);
      IntakeA.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
      IntakeB.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
      goForward(-10, 1.5);
      IntakeA.stop();
      IntakeB.stop();

      stopDriveBase();
    }


    if (Controller1.ButtonX.pressing() && !buttonPressedLast)
    {
      buttonPressedLast = true;
      if (speedMult == 0.3)
      {
        speedMult = 1;
      }
      else
      {
        speedMult = 0.3;
      }
    }
    else if (!Controller1.ButtonX.pressing())
    {
      buttonPressedLast = false;
    }


    //Drive Control
    //Set the left and right motor to spin forward using the controller's Axis positions as the velocity value.
    LeftMotorA.spin(vex::directionType::fwd, Controller1.Axis3.position() * speedMult, vex::velocityUnits::pct);
    LeftMotorB.spin(vex::directionType::fwd, Controller1.Axis3.position() * speedMult, vex::velocityUnits::pct);
    RightMotorA.spin(vex::directionType::fwd, Controller1.Axis2.position() * speedMult, vex::velocityUnits::pct);
    RightMotorB.spin(vex::directionType::fwd, Controller1.Axis2.position() * speedMult, vex::velocityUnits::pct);

    // Intake Control
    // If the R1 button is pressed...
    if(Controller1.ButtonR1.pressing()) { 
      //...Spin the claw motor forward.
      IntakeA.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      IntakeB.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR2.pressing())
    {
      IntakeA.spin(vex::directionType::rev, 20, vex::velocityUnits::pct);
      IntakeB.spin(vex::directionType::rev, 20, vex::velocityUnits::pct);
    }
    // else R1 is not pressed....
    else {
      //...Stop the motor.
      IntakeA.stop();
      IntakeB.stop(); 
    }

    // Up Down Control
    // If the L1 button is pressed...
    //THIS IS INTAKE
    if(Controller1.ButtonL1.pressing()) { 
      //...Spin the claw motor forward.
      UpDown.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing())
    {
      UpDown.spin(vex::directionType::rev, 20, vex::velocityUnits::pct);
    }
    // else R1 is not pressed....
    else {
      //...Stop the motor.
      UpDown.stop();
    }

    if (Controller1.ButtonA.pressing())
    {
      rampMotor.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
    }
    else if (Controller1.ButtonB.pressing())
    {
      rampMotor.spin(vex::directionType::rev, 40, vex::velocityUnits::pct);
    }
    else
    {
      rampMotor.stop();
    }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  vexcodeInit();
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