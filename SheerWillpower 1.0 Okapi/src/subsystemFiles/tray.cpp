#include "main.h"

int trayTarget = 0;

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
			intakeMove(-TRAY_STEP_RATE * 100);
		}
	}
	else if (trayDownBt.isPressed())
	{
		trayTarget -= TRAY_STEP_RATE * 500;
		if (trayTarget >= TRAY_HIT_INTAKE_DEGREE)
		{
			intakeMove(TRAY_STEP_RATE * 500);
		}
	}

  if (trayTarget < 0)
  {
    trayTarget = 0;
  }

  trayTargetSet(trayTarget);
}
