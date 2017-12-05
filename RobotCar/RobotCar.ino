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
int leftEnable1 = 4;
int leftEnable2 = 3;
int rightEnable1 = 8;
int rightEnable2 = 7;

//SENSOR PINS
int frontIR = A0;
int leftIR = A1;
int rightIR = A2;
int leftPhoto = A3;
int midPhoto = A4;
int rightPhoto = A5;

//DATA VARIABLES
int black = 470;
//int red = 100;

void setup() {
  setUpMotors();
  setUpSensors();
  Serial.begin(9600);
  
}

void loop() {
  //Serial.println(analogRead(leftPhoto));
  //check if an obstacle is in front of the car
  //goStraight();
  /*
  if(analogRead(frontIR) > 550){
    stopCar();  
    return;
  }
  */
  //check if we are still on the line
  //Serial.println(analogRead(rightPhoto));
  /*
  Serial.print("Left: ");
  Serial.println(analogRead(leftPhoto));
  Serial.print("Mid: ");
  Serial.println(analogRead(midPhoto));
  Serial.print("Right: ");
  Serial.println(analogRead(rightPhoto));
  */
  if(analogRead(midPhoto) < black)
  {//right
    goStraight();
  }
  //data_sheet
  // if the line is under the right sensor, adjust relative speeds to turn to the right
  else if(analogRead(leftPhoto) < black)
  {//left
    turnLeft();
  }
  //data_sheet
  // if the line is under the left sensor, adjust relative speeds to turn to the left
  else if(analogRead(rightPhoto) < black)
  {//right
    turnRight();
  }
  //data_sheet
  // if all sensors are on black or up in the air, stop the motors.
  // otherwise, run motors given the control speeds above.
  if((analogRead(midPhoto) > black) && (analogRead(leftPhoto) > black) && (analogRead(rightPhoto) > black))
  {
    //stop
    stopCar();
  }
  else
  {
    goStraight();
  }
  delay(5);  // add a delay to decrease sensitivity.
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
  digitalWrite(leftEnable1, LOW);
  digitalWrite(leftEnable2, HIGH);
  //turn right side backwards
  digitalWrite(rightEnable1, LOW);
  digitalWrite(rightEnable2, LOW);
  analogWrite(leftSidePWM, 170);
  analogWrite(rightSidePWM, 150);
}

void turnLeft() {
  //turn left side backwards
  digitalWrite(leftEnable1, LOW);
  digitalWrite(leftEnable2, LOW);
  //turn right side forwards
  digitalWrite(rightEnable1, LOW);
  digitalWrite(rightEnable2, HIGH);
  analogWrite(leftSidePWM, 170);
  analogWrite(rightSidePWM, 150);
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


