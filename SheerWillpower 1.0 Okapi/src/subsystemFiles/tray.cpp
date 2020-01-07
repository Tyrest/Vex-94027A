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
		intakeMove(-800);
	}
	else if (trayDownBt.isPressed())
	{
		trayTarget -= TRAY_STEP_RATE * 5;
		intakeMove(4000);
	}

  if (trayTarget < 0)
  {
    trayTarget = 0;
  }

  trayTargetSet(trayTarget);
}
