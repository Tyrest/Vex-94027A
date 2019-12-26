#include "main.h"

void armsTargetSet(int target)
{
  arms.setTarget(target);
}

void armsControl()
{
  if (armUpBt.changedToPressed() && armHeightIndex < NUM_ARM_HEIGHTS - 1)
	{
		armHeightIndex++;
	}
	else if (armDownBt.changedToPressed() && armHeightIndex > 0)
	{
		armHeightIndex--;
	}

  armsTargetSet(armHeightIndex);
}
