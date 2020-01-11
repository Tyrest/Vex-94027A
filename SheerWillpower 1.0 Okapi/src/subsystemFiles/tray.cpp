#include "main.h"

int trayTarget = 0;

void trayTargetSet(int target)
{
  tray->setTarget(target);
}

void trayControl()
{
	if (trayUpBt.isPressed())
	{
		trayTarget += TRAY_STEP_RATE;
		intakeMoveVel(-5);
	}
	else if (trayDownBt.isPressed())
	{
		trayTarget -= TRAY_STEP_RATE * 5;
	}

  if (trayTarget < 0)
  {
    trayTarget = 0;
  }

  trayTargetSet(trayTarget);
  master.setText(0, 0, std::to_string(trayTarget));
}
