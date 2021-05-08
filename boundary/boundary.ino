//pin for h-bridge motor controler
#include "moveCases.h"
#define LEFT_C1 2
#define LEFT_C2 3
#define RIGHT_C1 4
#define RIGHT_C2 7
#define LEFT_E 5
#define RIGHT_E 6

//pin sensor
#include <NewPing.h>
#include "weapon.h"
#define TRIGGER_PIN 8
#define ECHO_PIN    9
#define MAX_DISTANCE 50000
#define WEAPON_E 10 //weapon motor enable
#define WEAPON_C1 11 //weapon motor control 1
#define WEAPON_C2 12 //weapon motor control 2

unsigned long previousMillis = 0;
const long interval = 1000;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
struct weapCBlock wcb;
struct movement mve;

//int for random turn direction
int ranturn = 0;
long r1 = 0;
long r2 = 500;

void setup() {
  
  pinMode(LEFT_C1, OUTPUT);
  pinMode(LEFT_C2, OUTPUT);
  pinMode(RIGHT_C1, OUTPUT);
  pinMode(RIGHT_C2, OUTPUT);
  pinMode(LEFT_E, OUTPUT);
  pinMode(RIGHT_E, OUTPUT);
  moveInit(&mve, LEFT_E, LEFT_C1, LEFT_C2, RIGHT_E, RIGHT_C1, RIGHT_C2);
  pinMode(WEAPON_E, OUTPUT);
  pinMode(WEAPON_C1, OUTPUT);  
  pinMode(WEAPON_C2, OUTPUT); 
  weapInit(&wcb, sonar, TRIGGER_PIN, ECHO_PIN, WEAPON_E, WEAPON_C1, WEAPON_C2);
  Serial.begin(9600);
  Serial.println("Setup Done");
}


void loop() {

  //int IR_front = analogRead(IR_sensor_front);
  //int IR_back = analogRead(IR_sensor_back);
  Serial.println("func1");
  delay(200);
  weaponHandler(&wcb); 
  Serial.println("func1");
  delay(200);
  Serial.println("func2");
  delay(300);
  Serial.println("func3");
//   unsigned long currentMillis = millis();   //time for no delay
//   unsigned long randomDirection = millis(); //timer for setting random turn direction
//   unsigned int uS = sonar.ping();           //check distance


// Potentially useful for IR sensor code:
//
//
// if(randomDirection-r1 > r2 && ranturn==0){  //check to see if the corect time has passed
//   ranturn = ranturn+1;                      //if time has passed and ranturn ==0 then set ranturn to 1
//   r1 = randomDirection;
// }
// else if(randomDirection-r1 > r2 && ranturn==1){
//   ranturn = ranturn-1; //if ranturn is == to 1 set it to 0
//   r1 = randomDirection;
// }
//   //Serial.print(ranturn); 

//   if (uS  >= 3000) //if every thing is clear go forward
//   {
//     forward(50);
//   }
//   else if (uS < 3000 && ranturn==0) //if something is there turn left.
//   {
//     stay();
//     delay(500);
//     backward(90);
//     delay(1000);
//     left(100);
//     delay(500);
//     unsigned int uS2 = sonar.ping();
//     if (uS2 < 2000){
//       left(100);
//       delay(500);
//       unsigned int uS2 = sonar.ping();
//       if (uS2 < 2000){
//         left(100);
//         delay(500);
//       }
//     } 
//   }
//   else if (uS < 3000 && ranturn==1){
//     stay();
//     delay(500);
//     backward(75);
//     delay(500);
//     right(100);
//     delay(500);
//     unsigned int uS2 = sonar.ping();
//     if (uS2 < 2000){
//       right(100);
//       delay(500);
//       unsigned int uS2 = sonar.ping();
//       if (uS2 < 2000){
//         right(100);
//         delay(500);
//       }
//     }
//   }
//   Serial.print("uS");
//   Serial.print(uS);
//   Serial.println();
  

}
