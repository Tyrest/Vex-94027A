#include "main.h"

void gui()
{
  // colorSwitchInit();
  // sizeSwitchInit();
  // showLabels();
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	DriveL.setVoltageLimit(12700);
	DriveR.setVoltageLimit(12700);
	IntakeL.setVoltageLimit(12700);
	IntakeR.setVoltageLimit(12700);

  pros::delay(100);
	// gui();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
  /**
  When the color switch is "on," it means Red
  When the size switch is "on," it means Big Goal
  */

  smallBlue();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	drive->stop();

	while (true)
	{

		driveControl();
		intakesControl();
		trayControl();
		armsControl();

    if (forwardBt.isPressed())
    {
      DriveL.moveVoltage(12700);
      DriveR.moveVoltage(12700);
      intakesMove(12700);
    }

    if (autonTester.changedToPressed())
    {
      autonomous();
    }
		pros::delay(10);
	}
}
