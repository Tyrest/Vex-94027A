#include "main.h"

const int DRIVEL_PORT = 11;
const int DRIVER_PORT = 12;
const int INTAKEL_PORT = 3;
const int INTAKER_PORT = 4;
const int TRAYL_PORT = 15;
const int TRAYR_PORT = 16;
const int ARML_PORT = 7;
const int ARMR_PORT = 8;
const int IMU_PORT = 9;

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
Motor TrayL (TRAYL_PORT, false,
  AbstractMotor::gearset::red,
  AbstractMotor::encoderUnits::degrees);
Motor TrayR (TRAYR_PORT, true,
  AbstractMotor::gearset::red,
  AbstractMotor::encoderUnits::degrees);
Motor ArmL (ARML_PORT, true,
  AbstractMotor::gearset::red,
  AbstractMotor::encoderUnits::degrees);
Motor ArmR (ARMR_PORT, false,
  AbstractMotor::gearset::red,
  AbstractMotor::encoderUnits::degrees);

// Controllers
std::shared_ptr<ChassisController> drive = ChassisControllerBuilder()
  .withMotors(DriveL, DriveR)
  .withDimensions(AbstractMotor::gearset::green,
    {{4_in, 11.5_in}, imev5GreenTPR})
  .withGains(IterativePosPIDController::Gains{0.0015, 0, 0.0001},
    IterativePosPIDController::Gains{0.0015, 0, 0.0001},
    IterativePosPIDController::Gains{0.0015, 0, 0.0001})
   //.withMaxVelocity(80)
  .build();
std::shared_ptr<AsyncPositionController<double, double>> tray =
  AsyncPosControllerBuilder()
  .withMotor({TrayL, TrayR})
  .withGains(IterativePosPIDController::Gains{0.002, 0, 0.0001})
  .build();
std::shared_ptr<AsyncPositionController<double, double>> arms =
  AsyncPosControllerBuilder()
  .withMotor({ArmL, ArmR})
  .withGains(IterativePosPIDController::Gains{0.005, 0, 0.0001})
  .withMaxVelocity(50)
  .build();

// AsyncMotionProfileController moPro =
//   AsyncControllerFactory::motionProfile(1.0, 2.0, 10.0, drive);
// AsyncMotionProfileController moProB =
//   AsyncControllerFactory::motionProfile(1.0, 2.0, 10.0, driveB);

// Inertial Sensor
pros::Imu imu(IMU_PORT);

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
ControllerButton forwardBt(ControllerDigital::up);
ControllerButton backwardBt(ControllerDigital::down);

// Constants
const int NUM_ARM_HEIGHTS = 3;
const int AH_0 = 0;
const int AH_1 = 420;
const int AH_2 = 540;

const int ARM_HEIGHTS[NUM_ARM_HEIGHTS] = {AH_0, AH_1, AH_2};

int armHeightIndex = 0;

const int TRAY_STEP_RATE = 3;						// Should not go above 20
const int TRAY_HIT_INTAKE_DEGREE = 180;	// Degree at which tray contacts intakes

// GUI
lv_obj_t * colorSwitch;
lv_obj_t * sizeSwitch;
