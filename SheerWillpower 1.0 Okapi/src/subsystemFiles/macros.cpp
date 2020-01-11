#import "main.h"

void deploy()
{
  trayTargetSet(270);
  intakeMoveVel(-20);
  drive->moveDistance(8_in);
  drive->moveDistance(-2_in);
  intakeMoveVel(0);
  armsTargetSet(360);
  trayTargetSet(0);
  pros::delay(500);
  armsTargetSet(0);
  pros::delay(500);
}

void forwardSweep()
{
  armsTargetSet(0);
  trayTargetSet(0);
  intakeMove(12700);
  drive->moveDistance(3.5_ft);
}

// void backLeftSCurve()
// {
//   moProB.generatePath({Point{0_ft, 0_ft, 0_deg},
//                        Point{2_ft, 2_ft, 0_deg}}, "BackLeft 2x2");
//   moProB.setTarget("BackLeft 2x2");
//   moProB.waitUntilSettled();
// }
//
// void backRightSCurve()
// {
//   moProB.generatePath({Point{0_ft, 0_ft, 0_deg},
//                        Point{2_ft, -2_ft, 0_deg}}, "BackRight 2x2");
//   moProB.setTarget("BackRight 2x2");
//   moProB.waitUntilSettled();
// }

// void moveWithGyro(double distance, double speed)
// {
//
// }
//
// void turnWithGyro(double degrees, double speed)
// {
//
// }
