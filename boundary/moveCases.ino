//void setup for the right motor
void rm(int mode, int percent)
{
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int movespeed = map(percent, 0, 100, 0, 255);

  switch(mode)
  {
    case 0: //stop right motor
    digitalWrite(ENA, LOW);
    break;

    case 1: // right motor forword
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, movespeed);
    break;

    case 2: // right motor bacwords
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, movespeed);
    break;
    }

}
//end of void rm


//void setup for left motor
void lm(int mode, int percent)
{
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int movespeed = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
    case 0: //stop left motor
    digitalWrite(ENB, LOW);  //set enable low to disable B
    break;

    case 1: //left motor forword
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, movespeed);
    break;

    case 2: //left motor backwords
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, movespeed);
    break;
  }
}
//end of void lm


void forward (int movespeed) //used to move robot forword. movespeed sets the speed.
{
  rm(1,movespeed);
  lm(1,movespeed);
}

void backward (int movespeed) //used to move robot backwords
{
  rm(2,movespeed);
  lm(2,movespeed);
}

void left (int movespeed) //turn robot left
{
  rm(1,movespeed);
  lm(2,movespeed);
}
void right(int movespeed) //turn robot right
{
  rm(2,movespeed);
  lm(1,movespeed);
}

void stay () //stop robot
{
  rm(0,0);
  lm(0,0);
}
