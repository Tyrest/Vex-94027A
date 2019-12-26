#include "main.h"

void trayTargetSet(int target)
{
  tray.setTarget(target);
}

void trayControl()
{
	if (trayUpBt.isPressed())
	{
		trayTarget += TRAY_STEP_RATE;
		if (trayTarget >= TRAY_HIT_INTAKE_DEGREE)
		{
			intakeMove(-TRAY_STEP_RATE);
		}
	}
	else if (trayDownBt.isPressed())
	{
		trayTarget -= TRAY_STEP_RATE * 5;
		if (trayTarget >= TRAY_HIT_INTAKE_DEGREE)
		{
			intakeMove(TRAY_STEP_RATE * 5);
		}
	}

  trayTargetSet(trayTarget);
}
