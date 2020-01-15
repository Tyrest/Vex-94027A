#include "main.h"

Intakes::Intakes(int motorLPort, int motorRPort, bool reversed)
: motorL(motorLPort, !reversed,
  AbstractMotor::gearset::green,
  AbstractMotor::encoderUnits::degrees),
  motorR(motorRPort, reversed,
    AbstractMotor::gearset::green,
    AbstractMotor::encoderUnits::degrees)
{}

void Intakes::move(int voltage)
{
	motorL.moveVoltage(voltage);
	motorR.moveVoltage(voltage);
}

void Intakes::moveVel(int velocity)
{
	IntakeL.moveVelocity(velocity);
	IntakeR.moveVelocity(velocity);
}

void Intakes::control()
{
	if (intakeInBt.isPressed())
  {
    intakeMove(12700);
  }
  else if (intakeOutBt.isPressed())
  {
		intakeMove(-12700);
  }
  else
  {
		intakeMove(0);
  }
}
