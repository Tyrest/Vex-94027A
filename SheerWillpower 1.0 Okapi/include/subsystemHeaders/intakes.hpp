#include "main.h"

class Intakes
{
private:
  Motor motorL;
  Motor motorR;
public:
  Intakes(int motorLPort, int motorRPort, bool reversed);
  void move(int voltage);
  void moveVel(int velocity);
  void control();
};

void intakeMove(int voltage);

void intakeMoveVel(int velocity);

void intakeControl();
