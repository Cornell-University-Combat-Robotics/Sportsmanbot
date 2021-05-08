
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


int main()
{
  struct movement test_mve;
  moveInit(&test_mve, LEFT_E, LEFT_C1, LEFT_C2, RIGHT_E, RIGHT_C1, RIGHT_C2);

  //init state
  assert(test_mve.currentMovement == still);
  assert(test_mve.lmF == false);
  assert(test_mve.lmB == false);
  assert(test_mve.lSpeed == 0);
  assert(test_mve.rmF == false);
  assert(test_mve.rmB == false);
  assert(test_mve.rSpeed == 0);

  //move forward 50% speed
  forward(&test_mve, 50);
  assert(test_mve.currentMovement == mforward);
  assert(test_mve.lmF == true);
  assert(test_mve.lmB == false);
  assert(test_mve.lSpeed == 50);
  assert(test_mve.rmF == true);
  assert(test_mve.rmB == false);
  assert(test_mve.rSpeed == 50);

  //move backward 50% speed
  backward(&test_mve, 50);
  assert(test_mve.currentMovement == mbackward);
  assert(test_mve.lmF == false);
  assert(test_mve.lmB == true);
  assert(test_mve.lSpeed == 50);
  assert(test_mve.rmF == false);
  assert(test_mve.rmB == true);
  assert(test_mve.rSpeed == 50);

  //move left 50% speed
  left(&test_mve, 50);
  assert(test_mve.currentMovement == mleft);
  assert(test_mve.lmF == false);
  assert(test_mve.lmB == true);
  assert(test_mve.lSpeed == 50);
  assert(test_mve.rmF == true);
  assert(test_mve.rmB == false);
  assert(test_mve.rSpeed == 50);

  //move right 50% speed
  left(&test_mve, 50);
  assert(test_mve.currentMovement == mright);
  assert(test_mve.lmF == true);
  assert(test_mve.lmB == false);
  assert(test_mve.lSpeed == 50);
  assert(test_mve.rmF == false);
  assert(test_mve.rmB == true);
  assert(test_mve.rSpeed == 50);

  return 0;
}
