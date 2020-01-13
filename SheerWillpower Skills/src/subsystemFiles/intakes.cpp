#include "main.h"

void intakeMove(int voltage)
{
	IntakeL.moveVoltage(voltage);
	IntakeR.moveVoltage(voltage);
}

void intakeMoveVel(int velocity)
{
	IntakeL.moveVelocity(velocity);
	IntakeR.moveVelocity(velocity);
}

void intakeControl()
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
