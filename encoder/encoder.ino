#include "stdlib.h"
// motor control pin
const int motorDirPin = 8; // L298 Input 1
const int motorPWMPin = 9; // L298 Input 2

// encoder pin
const int encoderPinA = 2;
const int encoderPinB = 3;

int encoderPos = 0;
const float ratio = 360./103./52.;

// P control
float Kp = 3;
float targetDeg = 360;

void doEncoderA(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;}
void doEncoderB(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;}
void motorStop(){
  digitalWrite(motorDirPin,LOW);
  analogWrite(motorPWMPin,0);
}
void doMotor(bool dir, int vel){
  digitalWrite(motorDirPin, dir);
  analogWrite(motorPWMPin, dir?(255 - vel):vel);
}

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
 
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
 
  pinMode(motorDirPin, OUTPUT);

  Serial.begin(4800);
}

void loop() {
  if(Serial.available()){
    targetDeg=(float)Serial.parseInt();
    Serial.println(targetDeg);
  }
  while(1){
    float motorDeg = float(encoderPos)*ratio;
    float error = targetDeg - motorDeg;
    Serial.print("error");
    Serial.println(error);

    if(abs(error)<3.0){
          motorStop();
          break;
    }
    float control = Kp*error;
    float cali_speed=min(abs(control),255);
    if(abs(control)>5 && abs(control)<50){
      cali_speed=max(50,control*4); 
    }
    doMotor( (control>=0)?HIGH:LOW, cali_speed);
    
    Serial.print("target: ");
    Serial.print(targetDeg);
    Serial.print("  encoderPos : ");
    Serial.print(encoderPos);
    Serial.print("   motorDeg : ");
    Serial.print(float(encoderPos)*ratio);
    Serial.print("   error : ");
      Serial.print(error);
    Serial.print("    control : ");
    Serial.print(control);
    Serial.print("    motorVel : ");
    Serial.println(cali_speed);
    
  }
}
