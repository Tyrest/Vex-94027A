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
  drive->moveDistanceAsync(2_ft);
  pros::delay(2000);
  drive->moveDistance(-1_ft);
  pros::delay(1000);
  drive->stop();
  deploy();
}

/**
Autonomous routine for the red corner near the big zone
Should start facing the stack of four
(Does the same thing as the big blue version)
*/
void bigRed()
{
  drive->moveDistanceAsync(2_ft);
  pros::delay(2000);
  drive->moveDistance(-1_ft);
  pros::delay(1000);
  drive->stop();
  deploy();
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
  deploy();

  pros::delay(1500); // to let the ramp lower below the intakes

  intakesMove(12700);
  drive->moveDistance(40_in);
  pros::delay(500);
  drive->turnAngleAsync(-146_deg);
  pros::delay(2000);
  intakesMove(0);

  drive->moveDistanceAsync(30.5_in);
  intakesMoveVel(-20);
  pros::delay(1400);

  // stacking

  traySetTarget(600);
  pros::delay(3150);

  // backing out

  intakesMoveVel(-20);
  drive->moveDistanceAsync(-10_in);
  pros::delay(1800);
}

/**
Autonomous routine for the red corner near the small zone
Should start facing the second row from the small zone (one cube stacked)
(Does the same thing as the small blue version)
*/
void smallRed()
{
  deploy();

  pros::delay(1500); // to let the ramp lower below the intakes

  intakesMove(12700);
  drive->moveDistance(40_in);
  pros::delay(500);
  drive->turnAngleAsync(146_deg);
  pros::delay(2000);
  intakesMove(0);

  drive->moveDistanceAsync(30.5_in);
  intakesMoveVel(-20);
  pros::delay(1400);

  // stacking

  traySetTarget(600);
  pros::delay(3150);

  // backing out

  intakesMoveVel(-20);
  drive->moveDistanceAsync(-10_in);
  pros::delay(1800);
}
