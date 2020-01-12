#include "main.h"

void gui()
{
  /*Create a Label on the currently active screen*/
  lv_obj_t * label1 =  lv_label_create(lv_scr_act(), NULL);

  /*Modify the Label's text*/
  lv_label_set_text(label1, "Hello world!");

  /* Align the Label to the center
   * NULL means align on parent (which is the screen now)
   * 0, 0 at the end means an x, y offset after alignment*/
  lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
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

	gui();
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
	// deploy();
	// bigBlue();
	// bigRed();
	// smallBlue();
	// smallRed();
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
		intakeControl();
		trayControl();
		armsControl();
		// if (autonTester.changedToPressed())
		// {
		// 	autonomous();
		// }

		pros::delay(10);
	}
}
