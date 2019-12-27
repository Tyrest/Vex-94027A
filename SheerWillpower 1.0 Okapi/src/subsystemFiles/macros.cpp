#import "main.h"

void deploy()
{
  drive.moveDistanceAsync(6_in);
  intakeMove(-127);
  trayTargetSet(360);
  armsTargetSet(360);
  drive.waitUntilSettled();
  drive.moveDistanceAsync(-6_in);
  trayTargetSet(0);
  armsTargetSet(0);
  pros::delay(200);
  intakeMove(0);
}

void forwardSweep()
{
  armsTargetSet(0);
  trayTargetSet(0);
  intakeMove(127);
  drive.moveDistanceAsync(4_ft);
}

void backLeftSCurve()
{
  moProB.generatePath({Point{0_ft, 0_ft, 0_deg},
                       Point{2_ft, 2_ft, 0_deg}}, "BackLeft 2x2");
  moProB.setTarget("BackLeft 2x2");
  moProB.waitUntilSettled();
}

void backRightSCurve()
{
  moProB.generatePath({Point{0_ft, 0_ft, 0_deg},
                       Point{2_ft, -2_ft, 0_deg}}, "BackRight 2x2");
  moProB.setTarget("BackRight 2x2");
  moProB.waitUntilSettled();
}
