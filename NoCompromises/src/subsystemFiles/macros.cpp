#import "main.h"

void deploy()
{
  drive->moveDistance(8_in);
  intakesMove(-12700);
  drive->moveDistanceAsync(-6_in);
  pros::delay(1500);
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
