#include "main.h"

void driveControl()
{
  // Tank drive with left and right sticks
  drive.tank(master.getAnalog(ControllerAnalog::leftY),
             master.getAnalog(ControllerAnalog::rightY));
}
