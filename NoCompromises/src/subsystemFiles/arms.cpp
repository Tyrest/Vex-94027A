#include "main.h"

void armsTargetSet(int target)
{
  arms->setTarget(target);
}

void armsControl()
{
  if (armUpBt.changedToPressed() && armHeightIndex < NUM_ARM_HEIGHTS - 1)
	{
		armHeightIndex++;
    traySetTarget(360);
	}
	else if (armDownBt.changedToPressed() && armHeightIndex > 0)
	{
		armHeightIndex--;
    if (armHeightIndex == 0) {traySetTarget(0);}
	}

  armsTargetSet(ARM_HEIGHTS[armHeightIndex]);
}
