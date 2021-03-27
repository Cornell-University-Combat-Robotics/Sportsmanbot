#ifndef WEAPON_DEF
#define WEAPON_DEF
#include<NewPing.h>
enum weaponState {isReady, isAttacking, isPrepping};

struct weapCBlock {
    weaponState currentState;
    NewPing sonar = NewPing(10, 10, 10);
    int trigger;
    int echo;
    int enable;
    int control1;
    int control2;
    int minDistance;
    int maxDistance;
    unsigned long lastCall;
    unsigned long timeInState;
    bool motorActive;
};

/*
    Initializes the weapon control block with its corresponding pins
*/
void weapInit(struct weapCBlock* weap, NewPing s, int t, int e, int en, int c1, int c2, int min = 10, int max = 20);

/*
    Determines based on the US sensor whether or not to attack.
    Uses the minDis and maxDis as the range for the strike distance.
    If not ready to attack, prime the weapon.
*/
void weaponHandler(struct weapCBlock* w);

#endif