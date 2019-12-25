#include "main.h"

extern const int DRIVEL_PORT;
extern const int DRIVER_PORT;
extern const int INTAKEL_PORT;
extern const int INTAKER_PORT;
extern const int TRAYL_PORT;
extern const int TRAYR_PORT;
extern const int ARML_PORT;
extern const int ARMR_PORT;

// Motors
// extern Motor DriveL;
// extern Motor DriveR;
extern Motor IntakeL;
extern Motor IntakeR;
// extern Motor TrayL;
// extern Motor TrayR;
// extern Motor ArmL;
// extern Motor ArmR;

// Controllers
extern ChassisControllerPID drive;
extern AsyncPosPIDController tray;
extern AsyncPosPIDController arms;

// Controller
extern Controller master;

// Buttons
extern ControllerButton intakeInBt;
extern ControllerButton intakeOutBt;
extern ControllerButton trayUpBt;
extern ControllerButton trayDownBt;
extern ControllerButton armUpBt;
extern ControllerButton armDownBt;

// Constants
extern const int NUM_ARM_HEIGHTS;
extern const int AH_1;
extern const int AH_2;
extern const int AH_3;
extern const int AH_4;

extern const int ARM_HEIGHTS[];

extern const int TRAY_STEP_RATE;
extern const int TRAY_HIT_INTAKE_DEGREE;
