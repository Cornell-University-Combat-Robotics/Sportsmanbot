enum moveState
{
  still,
  mforward,
  mbackward,
  mleft,
  mright
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
void moveInit(struct movement* m, int len, int lca, int lcb, int ren, int rca, int rcb)
{
}

/*
 * Moves robot forward at speed movespeed and updates
 * movement state
 */
void forward(struct movement* m, int movespeed)
{
}

/*
 * Moves robot backward at speed movespeed and updates
 * movement state
 */
void backward(struct movement* m, int movespeed)
{
}

/*
 * Turns robot left at speed movespeed and updates
 * movement state
 */
void left(struct movement* m, int movespeed)
{
}

/*
 * Turns robot right at speed movespeed and updates
 * movement state
 */
void right(struct movement* m, int movespeed)
{
}

/*
 * Stops movement of the robot and updates
 * movement state
 */
void stay(struct movement* m)
{
}
