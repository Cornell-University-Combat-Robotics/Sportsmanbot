enum moveState
{
  still,
  forward,
  backward,
  left,
  right
};

struct movement
{
  moveState currentMovement;
  int lEnable;
  int lControlA;
  int lControlB;
  bool lmF;
  bool lmB;
  int lSpeed;
  int rEnable;
  int rControlA;
  int rControlB;
  bool rmF;
  bool rmB;
  int rSpeed;
};

/*
 * Initializes robot's movement state and corresponding pins for the left+right motors
 */
void moveInit(struct movement *m, int len, int lca, int lcb, int ren, int rca, int rcb)
{
}

/*
 * Sets up the right motor
 * @param mode defines whether motor is off (0), moves
 * forward (1) or backward (2)
 * @param percent is the speed of the motor from 0-100%
 */
void rm(int mode, int percent)
{
}

/*
 * Sets up the left motor
 * @param mode defines whether motor is off (0), moves
 * forward (1) or backward (2)
 * @param percent is the speed of the motor from 0-100%
 */
void lm(int mode, int percent)
{
}

/*
 * Moves robot forward at speed movespeed
 */
void forward(int movespeed)
{
}

/*
 * Moves robot backward at speed movespeed
 */
void backward(int movespeed)
{
}

/*
 * Turns robot left at speed movespeed
 */
void left(int movespeed)
{
}

/*
 * Turns robot right at speed movespeed
 */
void right(int movespeed)
{
}

/*
 * Stops movement of the robot
 */
void stay()
{
}
