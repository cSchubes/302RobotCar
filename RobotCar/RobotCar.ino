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
int leftSidePWM = 6;
int rightSidePWM = 5;
int leftEnable1 = 7;
int leftEnable2 = 8;
int rightEnable1 = 3;
int rightEnable2 = 4;

//SENSOR PINS
int frontIR = A0;
int leftIR = A1;
int rightIR = A2;
int leftPhoto = A6;
int midPhoto = A4;
int rightPhoto = A5;

//DATA VARIABLES
int black = 60;
int red = 100;

void setup() {
  setUpMotors();
  setUpSensors();
  Serial.begin(9600);
  
}

void loop() {
  //check if an obstacle is in front of the car
  if(analogRead(frontIR) > 550){
    stopCar();  
    return;
  }
  //check if we are still on the line
  if(onLine()){
    if(analogRead(leftPhoto) > black){
      while(analogRead(midPhoto) < black){
        turnRight();
      }
      return;
    }
    if(analogRead(rightPhoto) > black){
      while(analogRead(midPhoto) < black){
        turnLeft();
      }
      return;
    }
    goStraight();
  }
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
  digitalWrite(leftEnable1, LOW);
  digitalWrite(leftEnable2, HIGH);
  //turn right side backwards
  digitalWrite(rightEnable1, HIGH);
  digitalWrite(rightEnable2, LOW);
  analogWrite(leftSidePWM, 100);
  analogWrite(rightSidePWM, 100);
}

void turnLeft() {
  //turn left side backwards
  digitalWrite(leftEnable1, HIGH);
  digitalWrite(leftEnable2, LOW);
  //turn right side forwards
  digitalWrite(rightEnable1, LOW);
  digitalWrite(rightEnable2, HIGH);
  analogWrite(leftSidePWM, 100);
  analogWrite(rightSidePWM, 100);
}

void goStraight() {
  //turn left side forwards
  digitalWrite(leftEnable1, HIGH);
  digitalWrite(leftEnable2, LOW);
  //turn right side forwards
  digitalWrite(rightEnable1, HIGH);
  digitalWrite(rightEnable2, LOW);
  analogWrite(leftSidePWM, 200);
  analogWrite(rightSidePWM, 170);
}

void slowRight(){
  //turn left side forwards
  digitalWrite(leftEnable1, HIGH);
  digitalWrite(leftEnable2, LOW);
  //turn right side forwards
  digitalWrite(rightEnable1, HIGH);
  digitalWrite(rightEnable2, LOW);
  analogWrite(leftSidePWM, 200);
  analogWrite(rightSidePWM, 150);
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


