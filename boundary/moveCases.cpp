#include "moveCases.h"

//enum to keep track of the state of movement

//Struct for movement

void moveInit(struct movement* m, int len, int lca, int lcb, int ren, int rca, int rcb)
{
  m->currentMovement = still;
  m->lEnable = len;
  m->lControlA = lca;
  m->lControlB = lcb;
  m->lmF = false;
  m->lmB = false;
  m->lSpeed = 0;
  m->rEnable = ren;
  m->rControlA = rca;
  m->rControlB = rcb;
  m->rmF = false;
  m->rmB = false;
  m->rSpeed = 0;
}

/*
 * Sets up the right motor
 * @param mode defines whether motor is off (0), moves
 * forward (1) or backward (2)
 * @param percent is the speed of the motor from 0-100%
 */
void rm(struct movement* m, int mode, int percent)
{
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int movespeed = map(percent, 0, 100, 0, 255);

  switch (mode)
  {
  case 0: //stop right motor
    digitalWrite(m->lEnable, LOW);
    break;

  case 1: // right motor forword
    digitalWrite(m->lControlA, LOW);
    digitalWrite(m->lControlB, HIGH);
    analogWrite(m->lEnable, movespeed);
    break;

  case 2: // right motor bacwords
    digitalWrite(m->lControlA, HIGH);
    digitalWrite(m->lControlB, LOW);
    analogWrite(m->lEnable, movespeed);
    break;
  }
}
//end of void rm

/*
 * Sets up the left motor
 * @param mode defines whether motor is off (0), moves
 * forward (1) or backward (2)
 * @param percent is the speed of the motor from 0-100%
 */
void lm(struct movement* m, int mode, int percent)
{
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int movespeed = map(percent, 0, 100, 0, 255);

  switch (mode)
  {
  case 0:                   //stop left motor
    digitalWrite(m->rEnable, LOW); //set enable low to disable B
    break;

  case 1: //left motor forword
    digitalWrite(m->rControlA, HIGH);
    digitalWrite(m->rControlB, LOW);
    analogWrite(m->rEnable, movespeed);
    break;

  case 2: //left motor backwords
    digitalWrite(m->rControlA, LOW);
    digitalWrite(m->rControlB, HIGH);
    analogWrite(m->rEnable, movespeed);
    break;
  }
}
//end of void lm

void forward(struct movement* m, int movespeed) //used to move robot forword. movespeed sets the speed.
{
  rm(m, 1, movespeed);
  lm(m, 1, movespeed);
  m->currentMovement = mforward;
  m->lmF = true;
  m->lmB = false;
  m->lSpeed = movespeed;
  m->rmF = true;
  m->rmB = false;
  m->rSpeed = movespeed;
}

void backward(struct movement* m, int movespeed) //used to move robot backwords
{
  rm(m, 2, movespeed);
  lm(m, 2, movespeed);
  m->currentMovement = mbackward;
  m->lmF = false;
  m->lmB = true;
  m->lSpeed = movespeed;
  m->rmF = false;
  m->rmB = true;
  m->rSpeed = movespeed;
}

//TODO: Maybe add pivots? i.e. one motor off and the other backward/forward?

void left(struct movement* m, int movespeed) //turn robot left
{
  rm(m, 1, movespeed);
  lm(m, 2, movespeed);
  m->currentMovement = mleft;
  m->lmF = false;
  m->lmB = true;
  m->lSpeed = movespeed;
  m->rmF = true;
  m->rmB = false;
  m->rSpeed = movespeed;
}

void right(struct movement* m, int movespeed) //turn robot right
{
  rm(m, 2, movespeed);
  lm(m, 1, movespeed);
  m->currentMovement = mright;
  m->lmF = true;
  m->lmB = false;
  m->lSpeed = movespeed;
  m->rmF = false;
  m->rmB = true;
  m->rSpeed = movespeed;
}

void stay(struct movement* m) //stop robot
{
  rm(m, 0, 0);
  lm(m, 0, 0);
  m->currentMovement = still;
  m->lmF = false;
  m->lmB = false;
  m->lSpeed = 0;
  m->rmF = false;
  m->rmB = false;
  m->rSpeed = 0;
}
