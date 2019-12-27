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
