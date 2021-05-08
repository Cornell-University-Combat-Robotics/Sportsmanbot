
//#include <CppUnitTest.h>
#include "weapon.h"
#include <iostream>
#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */
#include <chrono>
#include <string>
using namespace std;
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define LOW 0x0
#define HIGH 0x1
#define TRIGGER_PIN 8
#define ECHO_PIN    9
#define MAX_DISTANCE 50000
#define WEAPON_E 10 //weapon motor enable
#define WEAPON_C1 11 //weapon motor control 1
#define WEAPON_C2 12 //weapon motor control 2

//setup fake functions to replace arduino ones

unsigned long tracker = 0;
unsigned long millis(bool read = false){
    //return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if (read == false){
        tracker += 1;
    }
    return tracker;
}

void digitalWrite(int pin, int setting){
    //std::cout << "Fake Write\n";
    return;
}

void fake_print(std::string s){
    //std::cout << (s + "\n");
    return;
}

void weapInit(struct weapCBlock* weap, int t, int e, int en, int c1, int c2, int min /*= 10*/, int max /*= 20*/){
    weap->currentState = isReady;
    weap->trigger = t;
    weap->echo = e;
    weap->enable = en;
    weap->control1 = c1;
    weap->control2 = c2;
    weap->minDistance = min;
    weap->maxDistance = max;
    weap->lastCall = millis(true);
    weap->timeInState = 0;
    weap->motorActive = false;

    //weap->sonar = NewPing(weap->trigger, weap->echo);
    //Setup the pins for this weapon control block
    
    //Serial.begin(9600);
}

//added [atk] to act as a false trigger for sensor
void weaponHandler(struct weapCBlock* w, bool atk = false){
    /*TODO:
        1) Figure out how long it takes the hammer to drop, if it takes too long, adjust accordingly
        2) Currently for a DC motor
        3) Check the actual times for releasing versus priming weapon, and if possible use angles instead
    */

    //update the time in the current state
    //fake_print("Weapon Handler Called");
    w->timeInState += (millis() - w->lastCall); 
    
    //For each state, we either are still in the state or we transition to the next state
    if(w->currentState == isPrepping){
        if (w->timeInState < 5000){
            if (!w->motorActive){
                fake_print("Priming weapon!");
                digitalWrite(w->control1, LOW);
                digitalWrite(w->control2, HIGH);
                digitalWrite(w->enable, HIGH);
                w->motorActive = true;
            }
            //sets motor to rotate, otherwise keeps rotating
        }
        else{
            digitalWrite(w->enable, LOW);
            w->motorActive = false;
            w->currentState = isReady;
            w->timeInState = 0;
            fake_print("Ready to engage!");
        }
    }
    else if (w->currentState == isReady){
        fake_print("Weapon is Ready!");
        unsigned int weapS = 0; 
        //weapS = w->sonar.convert_cm(weapS);
        //fake_print(weapS);
        if (atk || (weapS >= w->minDistance && weapS <= w->maxDistance)){
            fake_print("Going to attack!");
            w->currentState = isAttacking;
            //immediately execute next state
        }
    }
    if(w->currentState == isAttacking){
        
        if (w->timeInState < 5000){
            if (!w->motorActive){
                fake_print("Weapon Released!");
                digitalWrite(w->control1, HIGH);
                digitalWrite(w->control2, LOW);
                digitalWrite(w->enable, HIGH);
                w->motorActive = true;
            }
        }
        else{
            if (w->timeInState < 10000){
                //wait a bit before bringing back up
                fake_print("Out of juice!");
                digitalWrite(w->enable, LOW);
            }
            else{
                //waited long enough go to next state
                w->motorActive = false;
                w->currentState = isPrepping;
                w->timeInState = 0;
            }
        }
    }
    w->lastCall = millis(true);
}


int main(){
    struct weapCBlock test_wcb;
    weapInit(&test_wcb, TRIGGER_PIN, ECHO_PIN, WEAPON_E, WEAPON_C1, WEAPON_C2);
    assert(test_wcb.lastCall == 0);
    //init state
    assert(test_wcb.currentState==isReady);

    //no attack -> no change
    weaponHandler(&test_wcb, false);
    assert(test_wcb.currentState==isReady);

    //attack -> state isAttacking
    weaponHandler(&test_wcb, true);
    assert(test_wcb.currentState==isAttacking);

    while (millis(true) < 5000){
        weaponHandler(&test_wcb, false);
        assert(test_wcb.currentState==isAttacking);
    }

    while (millis(true) < 10000){
        assert(test_wcb.currentState==isAttacking);
        weaponHandler(&test_wcb, false);
    }
    
    weaponHandler(&test_wcb, false);
    assert(test_wcb.currentState==isPrepping);

    while (millis(true) < 15000){
        assert(test_wcb.currentState==isPrepping);
        weaponHandler(&test_wcb, false);
    }

    weaponHandler(&test_wcb, false);
    assert(test_wcb.currentState==isReady);

    return 0;
}