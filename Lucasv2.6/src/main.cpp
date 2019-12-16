#include "vex.h"

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
vex::motor DriveL           = vex::motor( vex::PORT1 );
vex::motor DriveR           = vex::motor( vex::PORT2, true );
vex::motor IntakeL          = vex::motor( vex::PORT3);
vex::motor IntakeR          = vex::motor( vex::PORT4, true );
vex::motor ArmL             = vex::motor( vex::PORT7, true );
vex::motor ArmR             = vex::motor( vex::PORT8 );
vex::motor LiftL            = vex::motor( vex::PORT5 );
vex::motor LiftR            = vex::motor( vex::PORT6, true );

const double upRightRamp = 1;
double armTarget = 0;

double speedMult = 0.8;

void pre_auton( void )
{
  DriveL.resetRotation();
  DriveR.resetRotation();
  IntakeL.resetRotation();
  IntakeR.resetRotation();
  ArmL.resetRotation();
  ArmR.resetRotation();
  LiftL.resetRotation();
  LiftR.resetRotation();
}

static void goResetRotation()
{
  DriveL.resetRotation();
  DriveR.resetRotation();
  IntakeL.resetRotation();
  IntakeR.resetRotation();
  //ArmL.resetRotation();
  //ArmR.resetRotation();
}

static void resetIntakeRotation()
{
  ArmL.resetRotation();
  ArmR.resetRotation();
}

// Negative speed for backwards
static void goForward(double speed, double rotations)
{
  goResetRotation();
  DriveL.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  DriveR.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  waitUntil(fabs(DriveL.rotation(vex::rotationUnits::rev)) >= rotations || fabs(DriveR.rotation(vex::rotationUnits::rev)) >= rotations);
  DriveL.stop();
  DriveR.stop();
}

// Positive speed for ccw and negative speed for cw
static void pivotTurn(double speed, double rotations)
{
  goResetRotation();
  DriveR.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  DriveL.spin(vex::directionType::fwd, -speed, vex::velocityUnits::pct);
  waitUntil(fabs(DriveL.rotation(vex::rotationUnits::rev)) >= rotations || fabs(DriveR.rotation(vex::rotationUnits::rev)) >= rotations);
  DriveL.stop();
  DriveR.stop();
}

// Positive speed for intake and negative speed for outturn
static void spinIntake(double speed, double rotations)
{
  goResetRotation();
  IntakeL.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  IntakeR.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  waitUntil(fabs(IntakeL.rotation(vex::rotationUnits::rev)) >= rotations || fabs(IntakeR.rotation(vex::rotationUnits::rev)) >= rotations);
  IntakeL.stop();
  IntakeR.stop();
}

void autonomous( void )
{
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  // UpDown.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  // vex::task::sleep(500);
  // UpDown.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  // vex::task::sleep(500);
  // UpDown.stop();

  // // Deploy Stuff
  // UpDown.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  // wait(0.5, vex::timeUnits::sec);
  // UpDown.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
  // IntakeL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  // IntakeR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  // wait(2, vex::timeUnits::sec);
  // spinRamp(5);
  // IntakeL.stop();
  // IntakeR.stop();
  // spinRamp(-5);
  // IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  // IntakeR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  // wait(2, vex::timeUnits::sec);

  // // Pick Up Blocks
  // goForward(20, 3.0);
  // UpDown.stop();
  // turnLeft(20, 1.2);
  // goForward(20, 2.4);
  // spinIntake(-20, 0.25);
  // spinRamp(1);
  // goForward(10, 0.2);
  // IntakeL.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
  // IntakeR.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
  // goForward(-20, 1.5);
  // IntakeL.stop();
  // IntakeR.stop();

  // // Stack Blocks
  // goForward(-10, 0.3);
  // spinIntake(-20, 3);
  // spinIntake(20, 1);
  // spinRamp(1);
  // // goForward(10, 0.1);
  // IntakeL.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
  // IntakeR.spin(vex::directionType::rev, 30, vex::velocityUnits::pct);
  // goForward(-10, 1.5);
  // IntakeL.stop();
  // IntakeR.stop();

  // stopDriveBase();

  // Current goal: 5-stack

  // Deploy intake

  // AFTER deploying intake set arm default position to default
  resetIntakeRotation();

  // Deploy ramp

  // 
}

// Raise ramp progressively slowly to vertical position
static void raiseRamp()
{
  goResetRotation();
  while(fabs(IntakeL.rotation(vex::rotationUnits::rev)) < upRightRamp && fabs(IntakeR.rotation(vex::rotationUnits::rev)) < upRightRamp)
  {
    LiftL.spin(vex::directionType::fwd, 80 - (LiftL.rotation(vex::rotationUnits::rev) / upRightRamp) * (7 / 10), vex::velocityUnits::pct);
    LiftR.spin(vex::directionType::fwd, 80 - (LiftR.rotation(vex::rotationUnits::rev) / upRightRamp) * (7 / 10), vex::velocityUnits::pct);
  }
  LiftL.stop();
  LiftR.stop();
}

// Toggle through different speeds for drivebase
static void stasisMode()
{
  if (speedMult == 0.8)
  {
    speedMult = 0.3;
  }
  else if (speedMult == 0.3)
  {
    speedMult = 0.5;
  }
  else
  {
    speedMult = 0.8;
  }
}

// Controls the intake
static void intakeControl()
{
  if(Controller1.ButtonR1.pressing())
  { 
    IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    IntakeR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  }
  else if(Controller1.ButtonR2.pressing())
  {
    IntakeL.spin(vex::directionType::rev, 20, vex::velocityUnits::pct);
    IntakeR.spin(vex::directionType::rev, 20, vex::velocityUnits::pct);
  }
  else {
    IntakeL.stop();
    IntakeR.stop(); 
  }
}

static void armTargetUp()
{
  if (armTarget == 0)
  {
    armTarget = 360;
  }
  else if (armTarget == 360)
  {
    armTarget = 540;
  }
}

static void armTargetDown()
{
  if (armTarget == 540)
  {
    armTarget = 360;
  }
  else if (armTarget == 360)
  {
    armTarget = 0;
  }
}

// Controls the arms
static void armTargetControl(double &target)
{
  Controller1.ButtonL1.pressed(armTargetUp);
  Controller1.ButtonL2.pressed(armTargetDown);
}

// target in degrees, returns current position, meant to be used within a while loop
static void runArmMotor(vex::motor mot, double delayBetweenRuns, double &lastPos)
{
  double currentPos = mot.rotation(vex::rotationUnits::deg);
  double veloc = (currentPos - lastPos) / delayBetweenRuns;
  double motorVal = 2 * (currentPos - armTarget) + 0.5 * (-veloc);

  mot.spin(vex::directionType::rev, motorVal, vex::velocityUnits::dps);
  lastPos = currentPos;
}

// 

// Controls the lift
static void liftControl()
{
  if (Controller1.ButtonA.pressing())
  {
    LiftL.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
    LiftR.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
  }
  else if (Controller1.ButtonB.pressing())
  {
    LiftL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    LiftR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  }
  else
  {
    LiftL.stop();
    LiftR.stop();
  }
}

// User Control Loop and Method
void usercontrol( void )
{
  double armPosL = 0;
  double armPosR = 0;
  resetIntakeRotation();
  while (1)
  {
    // Axis 2 and Axis 3 | Drive Base Control
    DriveL.spin(vex::directionType::fwd, Controller1.Axis3.position(percent) * speedMult, vex::velocityUnits::pct);
    DriveR.spin(vex::directionType::fwd, Controller1.Axis2.position(percent) * speedMult, vex::velocityUnits::pct);

    // Control
    intakeControl();                 // R1 and R2 | Intake Control
    armTargetControl(armTarget);     // L1 and L2 | Up Down Control
    liftControl();                   // A and B   | Lift Control

    // adjust arms:
    runArmMotor(ArmL, 20, armPosL);
    runArmMotor(ArmR, 20, armPosR);

    // Macros
    Controller1.ButtonUp.pressed(raiseRamp);  // Up | Raise ramp to vertical position
    Controller1.ButtonX.pressed(stasisMode);  // X  | Toggles speed of drive base

    vex::task::sleep(20); // Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

int main()
{
  vexcodeInit();

  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );
  
  //Run the pre-autonomous function. 
  pre_auton();
      
  //Prevent main from exiting with an infinite loop.                        
  while(1)
  {
    vex::task::sleep(100); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}