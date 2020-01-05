#include "main.h"

/**
All routines assume the robot has already been deployed and is facing forward
Eventually should implement an auton selector to choose which of these it runs
*/

/**
Autonomous routine for the blue corner near the big zone
Should start facing the stack of four
1) Set preload to the side nearest to the big goal
2) Move forward and tip over stack to land on tray
3) Move in front of the second rightmost row and move forward to pick up as many
other blocks as possible
4) Pick up the block near the zone for a stack of 7 or 8 (ideally)
5) Stack the blocks in the big zone and back up
*/
void bigBlue()
{

}

/**
Autonomous routine for the red corner near the big zone
Should start facing the stack of four
(Does the same thing as the big blue version)
*/
void bigRed()
{

}

/**
Autonomous routine for the red corner near the small zone
Should start facing the second row from the small zone (one cube stacked)
1) Set preload in front of robot
2) Move forward and try to pick up as many cubes as possible
3) Move in front of leftmost and move forward to pick up as many other blocks as
possible (Should aim for all 4)
4) Try to snag a block near the tower for a stack of 9 or 10 (ideally)
5) Stack the blocks in the small goal and back up
*/
void smallBlue()
{
  forwardSweep();
  drive.moveDistance(-20_in);
  backLeftSCurve();
  drive.moveDistanceAsync(-4_in);
  forwardSweep();
  intakeMove(127);
  drive.turnAngle(45_deg);
  drive.moveDistance(6_in);
  drive.moveDistance(-6_in);
  drive.turnAngle(-45_deg);
  drive.moveDistance(-3_ft);
  drive.turnAngle(-135_deg);
  intakeMove(0);
  drive.moveDistanceAsync(18_in);
  trayTargetSet(630);
  intakeMove(-5);
  pros::delay(1500);
  drive.moveDistance(-2_ft);
}

/**
Autonomous routine for the red corner near the small zone
Should start facing the second row from the small zone (one cube stacked)
(Does the same thing as the small blue version)
*/
void smallRed()
{

}