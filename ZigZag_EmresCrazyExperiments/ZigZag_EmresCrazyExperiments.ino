#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(400, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(400, 2);
int loopCount = 0;
int pos = 0;
int zigzag = -70;

void setup() {
  Serial.begin(9600);
  AFMS.begin();

  myMotor1->setSpeed(20);  
  myMotor2->setSpeed(20); 
}

void loop() {
  
  //int zigzag = random(-200,200);
  zigzag *= -1;

  //printInt("pos:    ", pos);
  //printInt("zigzag: ", zigzag);
  
  
  if(zigzag>pos){
    downDiagonal(25, zigzag-pos, true);
  }
  else{
    downDiagonal(25, pos-zigzag, false);
  }
  
  pos=zigzag;
  
  /*down(20);
  if(zigzag>pos){
     right(zigzag-pos);
  }
  else{
     left(pos-zigzag);
  }
  pos=zigzag;*/
  
}

void DrawGrid(int width, int height){
  while(true){
    int height = 3500;
    int width = 200;
    up(height);
    right(width);
    left(2 * width);
    down(height);
    right(width);
    left(2 * width);
  }
}

void DrawSquare(int length){
  right(length);
  down(length);
  left(length);
  up(length);
}

void up(int length) {
  drawVerticalLine(length, false);
}

void down(int length) {
  drawVerticalLine(length, true); 
}

void right(int length) {
  drawHorizontalLine(length, false);
}

void left(int length) {
  drawHorizontalLine(length, true);
}

void downDiagonal(int downDist, int horDist, bool horDir){
  
    int k = horDist/downDist;
    
  while (downDist>0){
    
    down(1);
    if(horDir) right(k);
    else left(k);
    
    horDist -= k;
    downDist--;

    printInt("k:       ", k);
    printInt("horDist: ", horDist);
    Serial.println("");
    //delay(2000);
  }
  if(horDir) right(horDist);
  else left(horDist);
  
}

void drawHorizontalLine(int length, bool leftToRight) {
  int motor = 1;
  while (length > 0){
    if (motor == 1){
      myMotor1->step(1, leftToRight ? FORWARD : BACKWARD, SINGLE);
      motor = 2;
    }
    else
    {
      myMotor2->step(1, leftToRight ? FORWARD : BACKWARD, SINGLE);
      motor = 1;
    }
    length--;
  }
  
}

void drawVerticalLine(int length, bool topDown) {
  int motor = 1;
  while (length > 0){
    if (motor == 1){
      myMotor1->step(1, topDown ? BACKWARD : FORWARD, SINGLE);
      motor = 2;
    }
    else
    {
      myMotor2->step(1, topDown ? FORWARD : BACKWARD, SINGLE);
      motor = 1;
    }
    length--;
  } 
}


void printInt(String label, int integer)
{
  Serial.print(label);
  Serial.print(integer);
  Serial.println("");
}
















