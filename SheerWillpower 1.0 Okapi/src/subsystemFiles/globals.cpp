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
Motor DriveL (DRIVEL_PORT, false,
  AbstractMotor::gearset::green,
  AbstractMotor::encoderUnits::degrees);
Motor DriveR (DRIVER_PORT, true,
  AbstractMotor::gearset::green,
  AbstractMotor::encoderUnits::degrees);
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
std::shared_ptr<ChassisController> drive = ChassisControllerBuilder()
  .withMotors(DriveL, DriveR)
  .withGains(IterativePosPIDController::Gains{0.002, 0, 0.0001},
  IterativePosPIDController::Gains{0.002, 0, 0.0001},
  IterativePosPIDController::Gains{0.002, 0, 0.0001})
  .build();

std::shared_ptr<AsyncPositionController<double, double>> tray =
AsyncPosControllerBuilder().build();
  // AsyncControllerFactory::posPID({TRAYL_PORT, -TRAYR_PORT}, 0.001, 0.0, 0.0001);
std::shared_ptr<AsyncPositionController<double, double>> arms =
AsyncPosControllerBuilder().build();
  // AsyncControllerFactory::posPID({-ARML_PORT, ARMR_PORT}, 0.01, 0.0, 0.0001);

// AsyncMotionProfileController moPro =
//   AsyncControllerFactory::motionProfile(1.0, 2.0, 10.0, drive);
// AsyncMotionProfileController moProB =
//   AsyncControllerFactory::motionProfile(1.0, 2.0, 10.0, driveB);

// Controller
Controller master;

// Buttons
ControllerButton intakeInBt(ControllerDigital::R1);
ControllerButton intakeOutBt(ControllerDigital::R2);
ControllerButton trayUpBt(ControllerDigital::A);
ControllerButton trayDownBt(ControllerDigital::B);
ControllerButton armUpBt(ControllerDigital::L1);
ControllerButton armDownBt(ControllerDigital::L2);
ControllerButton autonTester(ControllerDigital::Y);

// Constants
const int NUM_ARM_HEIGHTS = 3;
const int AH_0 = 0;
const int AH_1 = 720;
const int AH_2 = 1080;

const int ARM_HEIGHTS[NUM_ARM_HEIGHTS] = {AH_0, AH_1, AH_2};

int armHeightIndex = 0;

const int TRAY_STEP_RATE = 5;						// Should not go above 20
const int TRAY_HIT_INTAKE_DEGREE = 180;	// Degree at which tray contacts intakes
