#include "main.h"

const int DRIVEL_PORT = 1;
const int DRIVER_PORT = 2;
const int INTAKEL_PORT = 3;
const int INTAKER_PORT = 4;
const int TRAYL_PORT = 5;
const int TRAYR_PORT = 6;
const int ARML_PORT = 7;
const int ARMR_PORT = 8;

// Motors
// Motor DriveL (INTAKEL_PORT, false,
//   AbstractMotor::gearset::green,
//   AbstractMotor::encoderUnits::degrees);
// Motor DriveR (INTAKER_PORT, true,
//   AbstractMotor::gearset::green,
//   AbstractMotor::encoderUnits::degrees);
Motor IntakeL (INTAKEL_PORT, true,
  AbstractMotor::gearset::green,
  AbstractMotor::encoderUnits::degrees);
Motor IntakeR (INTAKER_PORT, false,
  AbstractMotor::gearset::green,
  AbstractMotor::encoderUnits::degrees);
// Motor TrayL (TRAYL_PORT, false,
//   AbstractMotor::gearset::red,
//   AbstractMotor::encoderUnits::degrees);
// Motor TrayR (TRAYR_PORT, true,
//   AbstractMotor::gearset::red,
//   AbstractMotor::encoderUnits::degrees);
// Motor ArmL (ARML_PORT, true,
//   AbstractMotor::gearset::red,
//   AbstractMotor::encoderUnits::degrees);
// Motor ArmR (ARMR_PORT, false,
//   AbstractMotor::gearset::red,
//   AbstractMotor::encoderUnits::degrees);

// Controllers
ChassisControllerPID drive = ChassisControllerFactory::create
(
  DRIVEL_PORT, -DRIVER_PORT,
	IterativePosPIDController::Gains{0.001, 0, 0.0001},
  IterativePosPIDController::Gains{0.001, 0, 0.0001},
  IterativePosPIDController::Gains{0.001, 0, 0.0001},
  AbstractMotor::gearset::green,
  {4_in, 11.5_in}
);

AsyncPosPIDController tray = AsyncControllerFactory::posPID({TRAYL_PORT, -TRAYR_PORT},
                                           0.001, 0.0, 0.0001);
AsyncPosPIDController arms = AsyncControllerFactory::posPID({-ARML_PORT, ARMR_PORT},
                                           0.001, 0.0, 0.0001);

// Controller
Controller master;

// Buttons
ControllerButton intakeInBt(ControllerDigital::R1);
ControllerButton intakeOutBt(ControllerDigital::R2);
ControllerButton trayUpBt(ControllerDigital::A);
ControllerButton trayDownBt(ControllerDigital::B);
ControllerButton armUpBt(ControllerDigital::L1);
ControllerButton armDownBt(ControllerDigital::L2);

// Targets
int trayTarget = 0;
int armHeightIndex = 0;

// Constants
const int NUM_ARM_HEIGHTS = 4;
const int AH_0 = 0;
const int AH_1 = 60;
const int AH_2 = 100;
const int AH_3 = 140;

const int ARM_HEIGHTS[NUM_ARM_HEIGHTS] = {AH_0, AH_1, AH_2, AH_3};

const int TRAY_STEP_RATE = 5;						// Should not go above 20
const int TRAY_HIT_INTAKE_DEGREE = 360;	// Degree at which tray contacts intakes
