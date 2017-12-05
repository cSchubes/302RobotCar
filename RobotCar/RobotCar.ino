/*
 * Robot Car Project Code
 * Authors: Carson Schubert
 * Last Modified: 12/3/2017
 */

 /*
  * CONTROLS
  * LeftForward: LeftEn1 HIGH LeftEn2 LOW
  * RightForward: RightEn1 HIGH RightEn2 LOW
  */

//MOTOR PINS
int leftSidePWM = 5;
int rightSidePWM = 6;
int leftEnable1 = 8;
int leftEnable2 = 7;
int rightEnable1 = 4;
int rightEnable2 = 3;

//SENSOR PINS
int frontIR = A0;
int leftIR = A1;
int rightIR = A2;
int leftPhoto = A3;
int midPhoto = A4;
int rightPhoto = A5;

//DATA VARIABLES
int black = 600;
//int red = 100;

void setup() {
  setUpMotors();
  setUpSensors();
  Serial.begin(9600);
  
}

void loop() {
  //check if obstacle is in front of us
  if(analogRead(frontIR) > 550){
    stopCar();  
  }
  /*
  Serial.print("Left: ");
  Serial.println(analogRead(leftPhoto));
  Serial.print("Mid: ");
  Serial.println(analogRead(midPhoto));
  Serial.print("Right: ");
  Serial.println(analogRead(rightPhoto));
  delay(500);
  */
  //if we are in the middle keep going
  else if((analogRead(midPhoto) < analogRead(leftPhoto)) && (analogRead(midPhoto) < analogRead(rightPhoto)))
  {
    goStraight();
  }
  //if we are veering right, go left
  else if((analogRead(leftPhoto) < analogRead(midPhoto)) && (analogRead(leftPhoto) < analogRead(rightPhoto)))
  {
    turnLeft();
  }
  //if we are veering left, go right
  else if((abs(analogRead(rightPhoto) - analogRead(midPhoto))<30) && (abs(analogRead(rightPhoto) - analogRead(leftPhoto))<30))
  {
    turnRight();
  }
  //default case
  else
  {
    goStraight();
  }
  //better for sensitivity
  delay(5);
  /*
  //if(onLine()){
    goStraight();
    if(analogRead(midPhoto) > black){
      if(analogRead(leftPhoto) < black){
          stopCar();
      }
      else if(analogRead(rightPhoto) < black){
          turnRight();
      }
    }
    else{
      goStraight();
    }
  //}
  /*
  else{   //if we arent on the line, assume we are in the walled area
    //check if we have reached the red finish line
    if(analogRead(midPhoto)>red){
      stopCar();
      return;
    }
    //otherwise, stay between the walls
    if(analogRead(rightIR) < 400)
      slowRight();
    else if(analogRead(rightIR) > 500)
      slowLeft();
    else
      goStraight();
  }
  */
}

//INIT METHODS

void setUpMotors() {
  pinMode(rightSidePWM, OUTPUT);
  pinMode(leftSidePWM, OUTPUT);
  pinMode(leftEnable1, OUTPUT);
  pinMode(leftEnable2, OUTPUT);
  pinMode(rightEnable1, OUTPUT);
  pinMode(rightEnable2, OUTPUT);
}

void setUpSensors() {
  pinMode(frontIR, INPUT);
  pinMode(rightIR, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(leftPhoto, INPUT);
  pinMode(midPhoto, INPUT);
  pinMode(rightPhoto, INPUT);
}

//MOVEMENT METHODS

void turnRight() {
  //turn left side forwards
  digitalWrite(leftEnable1, HIGH);
  digitalWrite(leftEnable2, LOW);
  //turn right side backwards
  digitalWrite(rightEnable1, HIGH);
  digitalWrite(rightEnable2, LOW);
  analogWrite(leftSidePWM, 160);
  analogWrite(rightSidePWM, 0);
}

void turnLeft() {
  //turn left side backwards
  digitalWrite(leftEnable1, HIGH);
  digitalWrite(leftEnable2, LOW);
  //turn right side forwards
  digitalWrite(rightEnable1, HIGH);
  digitalWrite(rightEnable2, LOW);
  analogWrite(leftSidePWM, 0);
  analogWrite(rightSidePWM, 140);
}

void goStraight() {
  //turn left side forwards
  digitalWrite(leftEnable1, HIGH);
  digitalWrite(leftEnable2, LOW);
  //turn right side forwards
  digitalWrite(rightEnable1, HIGH);
  digitalWrite(rightEnable2, LOW);
  analogWrite(leftSidePWM, 200);
  analogWrite(rightSidePWM, 150);
}

void slowRight(){
  //turn left side forwards
  digitalWrite(leftEnable1, HIGH);
  digitalWrite(leftEnable2, LOW);
  //turn right side forwards
  digitalWrite(rightEnable1, HIGH);
  digitalWrite(rightEnable2, LOW);
  analogWrite(leftSidePWM, 150);
  analogWrite(rightSidePWM, 200);
}

void slowLeft(){
  //turn left side forwards
  digitalWrite(leftEnable1, HIGH);
  digitalWrite(leftEnable2, LOW);
  //turn right side forwards
  digitalWrite(rightEnable1, HIGH);
  digitalWrite(rightEnable2, LOW);
  analogWrite(leftSidePWM, 180);
  analogWrite(rightSidePWM, 190);
}

void stopCar(){
  digitalWrite(leftSidePWM, LOW);
  digitalWrite(rightSidePWM, LOW);
}

//HELPER METHODS

boolean onLine(){
  return ((analogRead(midPhoto) < black)&&(analogRead(leftPhoto) < black)&&(analogRead(rightPhoto) < black));
}


