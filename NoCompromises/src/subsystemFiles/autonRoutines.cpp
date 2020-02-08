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
  // Move forward to deploy anti-tips
  // Move intakes out to deploy ramp
  deploy();

  // Sweep 4 blocks in front of robot
  traySetTarget(0);
  intakesMove(12700);
  drive->moveDistance(40_in);

  // Backup to stacking area
  drive->moveDistance(-30_in);
  // Turn towards goal zone
  drive->turnAngle(-135_deg);
  // Stop intakes for stability
  intakesMove(0);

  // Move towards goalzone
  drive->moveDistanceAsync(16_in);
  pros::delay(1280);
  // Stop drive to prevent messing with voltage control
  drive->stop();

  // Stacking
  // Move intakes out for block to stay stable on ground
  intakesMove(-4800);
  // Move tray to vertical position
  traySetTarget(840);
  pros::delay(960);
  // Move intakes in for bottom block to align with stack
  intakesMove(4800);
  pros::delay(1280);
  // Move tray back to back up
  traySetTarget(0);

  // Backup from stack and move intakes out
  DriveL.moveVoltage(-4800);
  DriveR.moveVoltage(-4800);
  intakesMove(-5600);
  pros::delay(2000);

  // Stop everything
  DriveL.moveVoltage(0);
  DriveR.moveVoltage(0);
  intakesMove(0);
}

/**
Autonomous routine for the red corner near the small zone
Should start facing the second row from the small zone (one cube stacked)
(Does the same thing as the small blue version)
*/
void smallRed()
{
  deploy();

  traySetTarget(0);
  intakesMove(12700);
  drive->moveDistance(40_in);
  drive->moveDistance(-30_in);
  drive->turnAngle(135_deg);
  intakesMove(0);

  drive->moveDistanceAsync(16_in);
  pros::delay(1280);
  drive->stop();

  intakesMove(-4800);
  traySetTarget(840);
  pros::delay(960);
  intakesMove(4800);
  pros::delay(1280);
  traySetTarget(0);

  DriveL.moveVoltage(-4800);
  DriveR.moveVoltage(-4800);
  intakesMove(-5600);
  pros::delay(2000);
  DriveL.moveVoltage(0);
  DriveR.moveVoltage(0);
  intakesMove(0);
}
