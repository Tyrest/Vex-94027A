#include "main.h"

class Tray
{
private:
  std::shared_ptr<AsyncPositionController<double, double>> tray;
  int target;
  Motor motorL;
  Motor motorR;
public:
  const int STEP_RATE = 5;

  Tray(int motorLPort, int motorRPort, bool reversed, double kp, double ki, double kd);

  void setTarget(int target);

  void control();
};
