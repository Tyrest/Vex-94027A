#include "main.h"

#define DRIVEL_PORT 1
#define DRIVER_PORT 2
#define INTAKEL_PORT 3
#define INTAKER_PORT 4
#define TRAYL_PORT 5
#define TRAYR_PORT 6
#define ARML_PORT 7
#define ARMR_PORT 8

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);

	pros::Motor DriveL (DRIVEL_PORT);
	pros::Motor DriveR (DRIVER_PORT, true);
	pros::Motor IntakeL (INTAKEL_PORT, true);
	pros::Motor IntakeR (INTAKER_PORT);
	pros::Motor TrayL (TRAYL_PORT);
	pros::Motor TrayR (TRAYR_PORT, true);
	pros::Motor ArmL (ARML_PORT, true);
	pros::Motor ArmR (ARMR_PORT, true);
	pros::Controller master (CONTROLLER_MASTER);
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
void autonomous() {}

void intakeControl(pros::Controller master, pros::Motor IntakeL, pros::Motor IntakeR)
{
	if(master.get_digital(DIGITAL_R1))
  {
    IntakeL.move_velocity(200);
    IntakeR.move_velocity(200);
  }
  else if(master.get_digital(DIGITAL_R2))
  {
		IntakeL.move_velocity(-200);
    IntakeR.move_velocity(-200);
  }
  else
  {
		IntakeL.move_velocity(0);
    IntakeR.move_velocity(0);
  }
}

void trayControl(pros::Controller master, double &trayTarget)
{
	if(master.get_digital(DIGITAL_A))
  {
    trayTarget += 10;
  }
  else if(master.get_digital(DIGITAL_B))
  {
		trayTarget -= 50;
  }
}

void armControl(pros::Controller master, int &armTargetIndex, int length)
{
	if (master.get_digital_new_press(DIGITAL_L1) && armTargetIndex < length - 1)
	{
		armTargetIndex++;
	}
	else if (master.get_digital_new_press(DIGITAL_L2) && armTargetIndex > 0)
	{
		armTargetIndex--;
	}
}

#define AKF 1
#define AKP 1
#define AKI 1
#define AKD 1
#define TKF 1
#define TKP 1
#define TKI 1
#define TKD 1

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
	pros::Motor DriveL (DRIVEL_PORT);
	pros::Motor DriveR (DRIVER_PORT);
	pros::Motor IntakeL (INTAKEL_PORT);
	pros::Motor IntakeR (INTAKER_PORT);
	pros::Motor TrayL (TRAYL_PORT);
	pros::Motor TrayR (TRAYR_PORT);
	pros::Motor ArmL (ARML_PORT);
	pros::Motor ArmR (ARMR_PORT);
	pros::Controller master (CONTROLLER_MASTER);

	pros::motor_pid_s_t ArmPID = pros::Motor::convert_pid(AKF, AKP, AKI, AKD);
	pros::motor_pid_s_t TrayPID = pros::Motor::convert_pid(TKF, TKP, TKI, TKD);

	TrayL.set_pos_pid(TrayPID);
	TrayR.set_pos_pid(TrayPID);

	ArmL.set_pos_pid(ArmPID);
	ArmR.set_pos_pid(ArmPID);

	double trayTarget = 0;
	int armTargetIndex = 0;
	double armTargets [3] = {0, 720, 1080};

  while (true)
	{
    DriveL.move(master.get_analog(ANALOG_LEFT_Y));
    DriveR.move(master.get_analog(ANALOG_RIGHT_Y));

		intakeControl(master, IntakeL, IntakeR);
		trayControl(master, trayTarget);
		armControl(master, armTargetIndex, sizeof(armTargets));

		TrayL.move_absolute(trayTarget, 100);
		TrayR.move_absolute(trayTarget, 100);

		ArmL.move_absolute(armTargets[armTargetIndex], 100);
		ArmR.move_absolute(armTargets[armTargetIndex], 100);

    pros::delay(2);
  }
}
