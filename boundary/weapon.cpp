#include "weapon.h"

//enum to keep track of the state of the weapon control block

//Struct for the weapon control block
//Used in a state machine esque manner

void weapInit(struct weapCBlock* weap, NewPing s, int t, int e, int en, int c1, int c2, int min /*= 10*/, int max /*= 20*/){
    weap->currentState = isReady;
    weap->sonar = s; //TODO: Change to new contruction call?
    weap->trigger = t;
    weap->echo = e;
    weap->enable = en;
    weap->control1 = c1;
    weap->control2 = c2;
    weap->minDistance = min;
    weap->maxDistance = max;
    weap->lastCall = millis();
    weap->timeInState = 0;
    weap->motorActive = false;

    weap->sonar = NewPing(weap->trigger, weap->echo);
    //Setup the pins for this weapon control block
    
    Serial.begin(9600);
}



void weaponHandler(struct weapCBlock* w){
    /*TODO:
        1) Figure out how long it takes the hammer to drop, if it takes too long, adjust accordingly
        2) Currently for a DC motor
        3) Check the actual times for releasing versus priming weapon, and if possible use angles instead
    */

    //update the time in the current state
    //Serial.println("Weapon Handler Called");
    w->timeInState += (millis() - w->lastCall); 
    
    //For each state, we either are still in the state or we transition to the next state
    if(w->currentState == isPrepping){
        if (w->timeInState < 5000){
            if (!w->motorActive){
                Serial.println("Priming weapon!");
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
            Serial.println("Ready to engage!");
        }
    }
    else if (w->currentState == isReady){
        Serial.println("Weapon is Ready!");
        unsigned int weapS = w->sonar.ping_median(10); 
        weapS = w->sonar.convert_cm(weapS);
        Serial.println(weapS);
        if (weapS >= w->minDistance && weapS <= w->maxDistance){
            Serial.println("Going to attack!");
            w->currentState = isAttacking;
            //immediately execute next state
        }
    }
    if(w->currentState == isAttacking){
        
        if (w->timeInState < 5000){
            if (!w->motorActive){
                Serial.println("Weapon Released!");
                digitalWrite(w->control1, HIGH);
                digitalWrite(w->control2, LOW);
                digitalWrite(w->enable, HIGH);
                w->motorActive = true;
            }
        }
        else{
            if (w->timeInState < 10000){
                //wait a bit before bringing back up
                Serial.println("Out of juice!");
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
    w->lastCall = millis();
}

