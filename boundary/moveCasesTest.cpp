
//#include <CppUnitTest.h>
#include "moveCases.h"
#include <iostream>
#include <stdio.h>  /* printf */
#include <assert.h> /* assert */
#include <chrono>
#include <string>
using namespace std;
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define LOW 0x0
#define HIGH 0x1
#define LEFT_C1 2  // left motor control 1
#define LEFT_C2 3  // left motor control 2
#define RIGHT_C1 4 // right motor control 1
#define RIGHT_C2 7 // right motor control 2
#define LEFT_E 5   // left motor enable
#define RIGHT_E 6  // right motor enable

//setup fake functions to replace arduino ones

void digitalWrite(int pin, int setting)
{
  //std::cout << "Fake Write\n";
  return;
}

void analogWrite(int pin, int setting)
{
  //std::cout << "Fake Write\n";
  return;
}

//Arduino function
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void fake_print(std::string s)
{
  //std::cout << (s + "\n");
  return;
}

void moveInit(struct movement* m, int len, int lca, int lcb, int ren, int rca, int rcb, bool t = true)
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

void forward(struct movement* m, int movespeed, bool t = true) //used to move robot forword. movespeed sets the speed.
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

void backward(struct movement* m, int movespeed, bool t = true) //used to move robot backwords
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

void left(struct movement* m, int movespeed, bool t = true) //turn robot left
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

void right(struct movement* m, int movespeed, bool t = true) //turn robot right
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

void stay(struct movement* m, bool t = true) //stop robot
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

int main()
{
  struct movement test_mve;
  moveInit(&test_mve, LEFT_E, LEFT_C1, LEFT_C2, RIGHT_E, RIGHT_C1, RIGHT_C2, true);

  //init state
  assert(test_mve.currentMovement == still);
  assert(test_mve.lmF == false);
  assert(test_mve.lmB == false);
  assert(test_mve.lSpeed == 0);
  assert(test_mve.rmF == false);
  assert(test_mve.rmB == false);
  assert(test_mve.rSpeed == 0);

  //move forward 50% speed
  forward(&test_mve, 50, true);
  assert(test_mve.currentMovement == mforward);
  assert(test_mve.lmF == true);
  assert(test_mve.lmB == false);
  assert(test_mve.lSpeed == 50);
  assert(test_mve.rmF == true);
  assert(test_mve.rmB == false);
  assert(test_mve.rSpeed == 50);

  //move backward 50% speed
  backward(&test_mve, 50, true);
  assert(test_mve.currentMovement == mbackward);
  assert(test_mve.lmF == false);
  assert(test_mve.lmB == true);
  assert(test_mve.lSpeed == 50);
  assert(test_mve.rmF == false);
  assert(test_mve.rmB == true);
  assert(test_mve.rSpeed == 50);

  //move left 50% speed
  left(&test_mve, 50, true);
  assert(test_mve.currentMovement == mleft);
  assert(test_mve.lmF == false);
  assert(test_mve.lmB == true);
  assert(test_mve.lSpeed == 50);
  assert(test_mve.rmF == true);
  assert(test_mve.rmB == false);
  assert(test_mve.rSpeed == 50);

  //move right 50% speed
  right(&test_mve, 50, true);
  assert(test_mve.currentMovement == mright);
  assert(test_mve.lmF == true);
  assert(test_mve.lmB == false);
  assert(test_mve.lSpeed == 50);
  assert(test_mve.rmF == false);
  assert(test_mve.rmB == true);
  assert(test_mve.rSpeed == 50);

  //stop robot
  stay(&test_mve, true);
  assert(test_mve.currentMovement == still);
  assert(test_mve.lmF == false);
  assert(test_mve.lmB == false);
  assert(test_mve.lSpeed == 0);
  assert(test_mve.rmF == false);
  assert(test_mve.rmB == false);
  assert(test_mve.rSpeed == 0);

  return 0;
}
