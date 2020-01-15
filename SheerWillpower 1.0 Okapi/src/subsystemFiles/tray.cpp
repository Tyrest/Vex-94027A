#include "main.h"

Tray::Tray(int motorLPort, int motorRPort, bool reversed,
  double kp, double ki, double kd)
: motorL(motorLPort, reversed,
  AbstractMotor::gearset::red,
  AbstractMotor::encoderUnits::degrees),
  motorR(motorRPort, !reversed,
    AbstractMotor::gearset::red,
    AbstractMotor::encoderUnits::degrees)
{
  target = 0;
  tray = AsyncPosControllerBuilder()
  .withMotor({motorL, motorR})
  .withGains(IterativePosPIDController::Gains{kp, ki, kd})
  .build();
}

void Tray::setTarget(int target)
{
  tray->setTarget(target);
}

void Tray::control()
{
  if (trayUpBt.isPressed())
	{
		target += TRAY_STEP_RATE;
		intakeMoveVel(-5);
	}
	else if (trayDownBt.isPressed())
	{
		target -= TRAY_STEP_RATE * 5;
	}

  if (target < 0)
  {
    target = 0;
  }

  this->setTarget(target);
}
