void rm(int mode, int percent) //void setup for the right motor
{
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
int duty = map(percent, 0, 100, 0, 255);

  switch(mode)
  {
    case 0: //stop right motor
   digitalWrite(ENA, LOW);
    break;

    case 1: // right motor forword
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, duty);
    break;

    case 2: // right motor bacwords
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, duty);
    break;
    }

}
// end of void rm

void lm(int mode, int percent) //void setup for left motor
{
//change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
    case 0: // stop left motor
    digitalWrite(ENB, LOW);  //set enable low to disable B
    break;

    case 1: // left motor forword
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, duty);
    break;

    case 2: // left motor backwords
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, duty);
    break;
  }
}
// end of void lm


void forword (int duty) //used to move robot forword. the duty sets the speed.
{
  rm(1,duty);
  lm(1,duty);
}

void backword (int duty)// used to move robot backwords
{
  rm(2,duty);
  lm(2,duty);
}

void left (int duty) // turn robot left
{
  rm(1,duty);
  lm(2,duty);
}
void right(int duty)//turn robot right
{
  rm(2,duty);
  lm(1,duty);
}

void stay ()//stop robot
{
  rm(0,0);
  lm(0,0);
}
