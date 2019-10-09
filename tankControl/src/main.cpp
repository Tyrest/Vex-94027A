/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Mon Mar 25 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// Tank Control 
// This program instructs your robot to use remote control values to move the robot. 
//
// Robot Configuration: 
// [Smart Port]    [Name]        [Type]           [Description]       [Reversed]
// Motor Port 1    LeftMotor     V5 Smart Motor    Left side motor     false
// Motor Port 10   RightMotor    V5 Smart Motor    Right side motor    true
// Motor Port 8    ArmMotor      V5 Smart Motor    Arm motor           false
// Motor Port 3    ClawMotor     V5 Smart Motor    Claw motor          false
//
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
vex::motor LeftMotorA       = vex::motor( vex::PORT1 );
vex::motor LeftMotorB       = vex::motor( vex::PORT2 );
vex::motor RightMotorA      = vex::motor( vex::PORT10, true );
vex::motor RightMotorB      = vex::motor( vex::PORT9 );
vex::motor ArmMotor         = vex::motor( vex::PORT8 );
vex::motor rightIntakeMotor = vex::motor( vex::PORT3 );
vex::motor leftIntakeMotor  = vex::motor( vex::PORT4 );
vex::controller Controller1 = vex::controller();

int main() {

    // Use these variables to set the speed of the arm and intake.
    int armSpeedPCT  = 50;
    int intakeSpeedPCT = 50;
    
    // Create an infinite loop so that the program can pull remote control values every iteration.
    // This loop causes the program to run forever.
    while(1) {
      //Drive Control
      //Set the left and right motor to spin forward using the controller's Axis positions as the velocity value.
      LeftMotorA.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);
      LeftMotorB.spin(vex::directionType::fwd, Controller1.Axis3.position(), vex::velocityUnits::pct);

      RightMotorA.spin(vex::directionType::fwd, Controller1.Axis2.position(), vex::velocityUnits::pct);
      RightMotorB.spin(vex::directionType::fwd, Controller1.Axis2.position(), vex::velocityUnits::pct);
    
      // Arm Control
      // If button up is pressed...
      if(Controller1.ButtonUp.pressing()) { 
        //...Spin the arm motor forward.
        ArmMotor.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
      }
      // else If the down button is pressed...
      else 
      if(Controller1.ButtonDown.pressing()) { 
        //...Spin the arm motor backward.
        ArmMotor.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
      }
      // else If neither up or down button is pressed...
      else { 
        //...Stop the arm motor.
        ArmMotor.stop(vex::brakeType::brake);
      }
    
      // Claw Control
      // If the A button is pressed...
      if(Controller1.ButtonA.pressing()) { 
        //...Spin the claw motor forward.
        rightIntakeMotor.spin(vex::directionType::fwd, intakeSpeedPCT, vex::velocityUnits::pct);
        leftIntakeMotor.spin(vex::directionType::fwd, intakeSpeedPCT, vex::velocityUnits::pct);
      }
      // else If the Y button is pressed...
      //else 
      //if(Controller1.ButtonY.pressing()) { 
        //...Spin the claw motor backward.
        //ClawMotor.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);
      //}
      // else If neither the A or Y button is pressed...
      else {
        //...Stop the claw motor.
        rightIntakeMotor.stop(vex::brakeType::brake);
        leftIntakeMotor.stop(vex::brakeType::brake);        
      }

    // Sleep the task for a short amount of time to prevent wasted resources.
    vex::task::sleep(20);
    }
}
