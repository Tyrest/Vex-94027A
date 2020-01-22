#include "main.h"

void intakesMove(int voltage)
{
	IntakeL.moveVoltage(voltage);
	IntakeR.moveVoltage(voltage);
}

void intakesMoveVel(int velocity)
{
	IntakeL.moveVelocity(velocity);
	IntakeR.moveVelocity(velocity);
}

void intakesControl()
{
	if (intakeInBt.isPressed())
  {
    intakesMove(12700);
  }
  else if (intakeOutBt.isPressed())
  {
		intakesMove(-6400);
  }
  else
  {
		intakesMove(0);
  }
}
