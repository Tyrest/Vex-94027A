#include "vex.h"
#include <string>

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
vex::motor IntakeL          = vex::motor( vex::PORT3, true );
vex::motor IntakeR          = vex::motor( vex::PORT4 );
vex::motor ArmL             = vex::motor( vex::PORT7, true );
vex::motor ArmR             = vex::motor( vex::PORT8 );
vex::motor TrayL            = vex::motor( vex::PORT5 );
vex::motor TrayR            = vex::motor( vex::PORT6, true );

const double midTowerArm = 1080;
const double lowTowerArm = 720;

// const double fastBase = 1;
// const double medBase = 0.8;
// const double slowBase = 0.3;

double armTarget = 0;
double speedMult = 1;

static void stopEverything ()
{
  DriveL.stop();
  DriveR.stop();
  IntakeL.stop();
  IntakeR.stop();
  ArmL.stop();
  ArmR.stop();
  TrayL.stop();
  TrayR.stop();
}

void pre_auton( void )
{
  DriveL.resetRotation();
  DriveR.resetRotation();
  IntakeL.resetRotation();
  IntakeR.resetRotation();
  ArmL.resetRotation();
  ArmR.resetRotation();
  TrayL.resetRotation();
  TrayR.resetRotation();
}

static void goResetRotation()
{
  DriveL.resetRotation();
  DriveR.resetRotation();
  IntakeL.resetRotation();
  IntakeR.resetRotation();
}

static void resetIntakeRotation()
{
  ArmL.resetRotation();
  ArmR.resetRotation();
}

static void deploy()
{
  TrayL.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  TrayR.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  IntakeR.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  wait(1.5, seconds);

  TrayL.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  TrayR.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  ArmL.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  ArmR.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  wait(1.5, seconds);

  TrayL.stop(); 
  TrayR.stop();
  ArmL.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  ArmR.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
  wait(1.5, seconds);

  stopEverything();
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
}

// Toggle through different speeds for drivebase
// static void stasisMode()
// {
//   if (speedMult == fastBase)
//   {
//     speedMult = slowBase;
//   }
//   else if (speedMult == slowBase)
//   {
//     speedMult = medBase;
//   }
//   else
//   {
//     speedMult = fastBase;
//   }
// }

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
    IntakeL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    IntakeR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  }
  else
  {
    IntakeL.stop();
    IntakeR.stop(); 
  }
}

static void cycleArmTarget()
{
  if (armTarget == 0)
  {
    armTarget = lowTowerArm;
  }
  else if (armTarget == lowTowerArm)
  {
    armTarget = midTowerArm;
  }
  else
  {
    armTarget = 0;
  }
}

// target in degrees, returns current position, meant to be used within a while loop
static void PID(vex::motor motor, double target, double delayBetweenRuns, double &lastPos)
{
  double currentPos = motor.rotation(vex::rotationUnits::deg);
  double veloc = (currentPos - lastPos) / delayBetweenRuns;
  double motorVal = 2 * (currentPos - target) + 0.5 * (-veloc);

  motor.spin(vex::directionType::rev, motorVal, vex::velocityUnits::dps);
  lastPos = currentPos;
}

// Controls the lift
static void liftControl(double &trayTarget)
{
  if (Controller1.ButtonA.pressing())
  {
    trayTarget += 10;
    IntakeL.spin(vex::directionType::rev, 5, vex::velocityUnits::pct);
    IntakeR.spin(vex::directionType::rev, 5, vex::velocityUnits::pct);
  }
  else if (Controller1.ButtonB.pressing())
  {
    trayTarget -= 50;
  }

  if (trayTarget < 0)
  {
    trayTarget = 0;
  }
}

static void controllerScreen(double armTarget, double trayTarget)
{
  Controller1.Screen.print("Arm Target: ");
  Controller1.Screen.print(armTarget);
  Controller1.Screen.newLine();
  Controller1.Screen.print("Tray Target: ");
  Controller1.Screen.print(trayTarget);
  Controller1.Screen.newLine();
}

// User Control Loop and Method
void usercontrol( void )
{
  double trayTarget = 0;
  double armPosL = 0;
  double armPosR = 0;
  double trayPosL = 0;
  double trayPosR = 0;
  resetIntakeRotation();

  while (1)
  {
    // Axis 2 and Axis 3 | Drive Base Control
    DriveL.spin(vex::directionType::fwd, Controller1.Axis3.position(percent) * speedMult, vex::velocityUnits::pct);
    DriveR.spin(vex::directionType::fwd, Controller1.Axis2.position(percent) * speedMult, vex::velocityUnits::pct);

    // Control
    intakeControl();         // R1 and R2 | Intake Control
    liftControl(trayTarget); // A and B   | Lift Control

    // Run PID loops
    // For Arms
    PID(ArmL, armTarget, 20, armPosL);
    PID(ArmR, armTarget, 20, armPosR);
    // For Tray
    PID(TrayL, trayTarget, 20, trayPosL);
    PID(TrayR, trayTarget, 20, trayPosR);

    // Macros
    Controller1.ButtonL1.pressed(cycleArmTarget); // L1 | Cycles through the heights the arm can be at
    // Controller1.ButtonX.pressed(stasisMode);      // X  | Toggles speed of drive base
    if (Controller1.ButtonY.pressing())
    {
      deploy();
    }
    if (Controller1.ButtonUp.pressing())
    {
      DriveL.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
      DriveR.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
    }

    controllerScreen(armTarget, trayTarget);

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