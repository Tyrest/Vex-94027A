#include "main.h"

void intakeMove(int voltage)
{
	IntakeL.moveVoltage(voltage);
	IntakeR.moveVoltage(voltage);
}

void intakeControl()
{
	if (intakeInBt.isPressed())
  {
    intakeMove(127);
  }
  else if (intakeOutBt.isPressed())
  {
		intakeMove(-127);
  }
  else
  {
		intakeMove(0);
  }
}
