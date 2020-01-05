#include "main.h"

void controllerAnalogToMotor(ControllerAnalog analogInput, Motor motor)
{
  double voltage = master.getAnalog(analogInput) * 12700;
  if (fabs(voltage) > 1000)
  {
    motor.moveVoltage(voltage);
  }
  else
  {
    motor.moveVoltage(0);
  }
}

void driveControl()
{
  // Tank drive with left and right sticks
  // drive.tank(master.getAnalog(ControllerAnalog::leftY),
  //            master.getAnalog(ControllerAnalog::leftY));
  controllerAnalogToMotor(ControllerAnalog::leftY, DriveL);
  controllerAnalogToMotor(ControllerAnalog::rightY, DriveR);
}
