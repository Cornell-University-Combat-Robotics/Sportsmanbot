
//TODO: Comment out when uploading to arduino
#define TESTING_ENV

#ifdef TESTING_ENV
#include "include/NewPing.h"
#else
#include <NewPing.h>
#endif

enum dir {LEFT, RIGHT, FORWARD, BACK, STOP};

struct detectionControlBlock {
    int (*readSensor)(int);
    enum dir currentDir;

    int rightSensor;
    int leftSensor;

    unsigned long lastCall;

};

/*
    Initializes the detection control block with its corresponding pins
*/
void detectInit(struct detectionControlBlock* detect, int (*readFunc)(int), int rS, int lS);

/*
Handler for the sensors
*/
void detectHandler(struct detectionControlBlock* detect);

