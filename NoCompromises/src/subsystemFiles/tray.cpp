#include "main.h"

int target = 0;

void traySetTarget(int target)
{
  tray->setTarget(target);
}

void trayControl()
{
  if (armHeightIndex > 0)
  {
    target = 360;
  }
  else if (trayUpBt.isPressed())
	{
		target += TRAY_STEP_RATE;
		intakesMoveVel(50);
	}
	else if (trayDownBt.isPressed())
	{
		target -= TRAY_STEP_RATE * 4;
	}

  if (target < 0)
  {
    target = 0;
  }
  else if (target > 880)
  {
    target = 880;
  }

  traySetTarget(target);
}
