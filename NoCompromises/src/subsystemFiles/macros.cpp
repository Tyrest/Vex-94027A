#import "main.h"

void deploy()
{
  intakesMove(-12700);
  pros::delay(1500);
  intakesMove(0);
}

void forwardSweep()
{
  armsTargetSet(0);
  traySetTarget(0);
  intakesMove(12700);
  drive->moveDistance(4_ft);
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
