#include "main.h"

#define DRIVEL_PORT 1
#define DRIVER_PORT 2
#define INTAKEL_PORT 3
#define INTAKER_PORT 4
#define TRAYL_PORT 5
#define TRAYR_PORT 6
#define ARML_PORT 7
#define ARMR_PORT 8

const int NUM_ARM_HEIGHTS = 4;
const int aH1 = 20;
const int aH2 = 60;
const int aH3 = 100;
const int aH4 = 140;

const int armHeights[NUM_ARM_HEIGHTS] = {aH1, aH2, aH3, aH4};

const int trayStepRate = 5;						// Should not go above 20
const int trayHitIntakeDegree = 360;	// Degree at which tray contacts intakes

// Chassis Controller - lets us drive the robot around with open- or closed-loop control
auto drive = ChassisControllerFactory::create
(
  DRIVEL_PORT, -DRIVER_PORT,
	IterativePosPIDController::Gains{0.001, 0, 0.0001},
  IterativePosPIDController::Gains{0.001, 0, 0.0001},
  IterativePosPIDController::Gains{0.001, 0, 0.0001},
  AbstractMotor::gearset::green,
  {4_in, 11.5_in}
);

auto tray = AsyncControllerFactory::posIntegrated({TRAYL_PORT, -TRAYR_PORT});
auto arms = AsyncControllerFactory::posIntegrated({-ARML_PORT, ARMR_PORT});

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

	Motor IntakeL (INTAKEL_PORT, true,
		AbstractMotor::gearset::green,
		AbstractMotor::encoderUnits::degrees);
	Motor IntakeR (INTAKER_PORT, false,
		AbstractMotor::gearset::green,
		AbstractMotor::encoderUnits::degrees);
	Motor TrayL (TRAYL_PORT, false,
		AbstractMotor::gearset::red,
		AbstractMotor::encoderUnits::degrees);
	Motor TrayR (TRAYR_PORT, true,
		AbstractMotor::gearset::red,
		AbstractMotor::encoderUnits::degrees);
	Motor ArmL (ARML_PORT, true,
		AbstractMotor::gearset::red,
		AbstractMotor::encoderUnits::degrees);
	Motor ArmR (ARMR_PORT, false,
		AbstractMotor::gearset::red,
		AbstractMotor::encoderUnits::degrees);
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

void intakeControl(Motor IntakeL, Motor IntakeR,
									 ControllerButton intakeInBt, ControllerButton intakeOutBt)
{
	if (intakeInBt.isPressed())
  {
    IntakeL.moveVelocity(200);
    IntakeR.moveVelocity(200);
  }
  else if (intakeOutBt.isPressed())
  {
		IntakeL.moveVelocity(-200);
    IntakeR.moveVelocity(-200);
  }
  else
  {
		IntakeL.moveVelocity(0);
    IntakeR.moveVelocity(0);
  }
}

void trayControl(int &trayTarget, Motor IntakeL, Motor IntakeR,
								 ControllerButton trayUpBt, ControllerButton trayDownBt)
{
	if (trayUpBt.isPressed())
	{
		trayTarget += trayStepRate;
		if (trayTarget >= trayHitIntakeDegree)
		{
			IntakeL.moveVelocity(-trayStepRate * 2);
	    IntakeR.moveVelocity(-trayStepRate * 2);
		}
	}
	else if (trayDownBt.isPressed())
	{
		trayTarget -= trayStepRate * 5;
		if (trayTarget >= trayHitIntakeDegree)
		{
			IntakeL.moveVelocity(trayStepRate * 10);
	    IntakeR.moveVelocity(trayStepRate * 10);
		}
	}
}

void armControl(int &armHeightIndex,
								ControllerButton armUpBt, ControllerButton armDownBt)
{
	if (armUpBt.changedToPressed() && armHeightIndex < NUM_ARM_HEIGHTS - 1)
	{
		armHeightIndex++;
	}
	else if (armDownBt.changedToPressed() && armHeightIndex > 0)
	{
		armHeightIndex--;
	}
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
	Motor IntakeL (INTAKEL_PORT);
	Motor IntakeR (INTAKER_PORT);
	Motor TrayL (TRAYL_PORT);
	Motor TrayR (TRAYR_PORT);
	Motor ArmL (ARML_PORT);
	Motor ArmR (ARMR_PORT);

	Controller master;

	ControllerButton intakeInBt(ControllerDigital::R1);
	ControllerButton intakeOutBt(ControllerDigital::R2);
	ControllerButton trayUpBt(ControllerDigital::A);
	ControllerButton trayDownBt(ControllerDigital::B);
	ControllerButton armUpBt(ControllerDigital::L1);
	ControllerButton armDownBt(ControllerDigital::L2);

	int armHeightIndex = 0;
	int trayTarget = 0;

	while (true)
	{
		// Tank drive with left and right sticks
    drive.tank(master.getAnalog(ControllerAnalog::leftY),
               master.getAnalog(ControllerAnalog::rightY));

		intakeControl(IntakeL, IntakeR, intakeInBt, intakeOutBt);
		trayControl(trayTarget, IntakeL, IntakeR, trayUpBt, trayDownBt);
		armControl(armHeightIndex, armUpBt, armDownBt);

		tray.setTarget(trayTarget);
		arms.setTarget(armHeights[armHeightIndex]);

		pros::delay(10);
	}
}
