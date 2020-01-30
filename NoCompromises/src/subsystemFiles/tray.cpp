#include "main.h"

int target = 0;

void traySetTarget(int target)
{
  tray->setTarget(target);
}

void trayControl()
{
  if (trayUpBt.isPressed())
	{
		target += TRAY_STEP_RATE;
		intakesMoveVel(-5);
	}
	else if (trayDownBt.isPressed())
	{
		target -= TRAY_STEP_RATE * 5;
	}

  if (target < 0)
  {
    target = 0;
  }

  traySetTarget(target);
}
