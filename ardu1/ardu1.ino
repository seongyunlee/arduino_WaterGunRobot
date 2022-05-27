//encoder for main motor
int encoderApin =2;
int encoderBpin =3;

//main motor control pin;
int mainMotorDirPin = 5;
int mainMotorPWMPin = 7;

//water pump 
int pumpDirPin = 6;
int pumpPWMPin = 8;

//set For encoder
int encoderPos=0;
const float ratio = 360./103./52.;
float Kp=3;
float targetDeg=0;

//start Button
int startBtnPin =11;
int gameStart=0;

//distance Sensor
int disTrigPin = 12;
int disEchoPin = 13;

//interrupt function
void doEncoderA(){  encoderPos += (digitalRead(encoderApin)==digitalRead(encoderBpin))?1:-1;}
void doEncoderB(){  encoderPos += (digitalRead(encoderApin)==digitalRead(encoderBpin))?-1:1;} 

//Settings for game
int disLine = 300; //300mm 이하 감지




void mainMotorStop(){
  digitalWrite(mainMotorDirPin,LOW);
  analogWrite(mainMotorPWMPin,0);
}
void mainMotorRun(bool dir, int vel){
  digitalWrite(mainMotorDirPin, dir);
  analogWrite(mainMotorPWMPin, dir?(255 - vel):vel);
}
void pumpOn(){              
  digitalWrite(pumpPWMPin, HIGH);/// analogWrite(pumpPWMPin,speed);
  digitalWrite(pumpDirPin, LOW);
}
void pumpOff(){
  digitalWrite(pumpDirPin, LOW);
  digitalWrite(pumpPWMPin, LOW);
}

void rotateToDeg(int deg){
  while(1){
    float motorDeg = float(encoderPos)*ratio;
    float error = targetDeg - motorDeg;
    Serial.print("error");
    Serial.println(error);

    if(abs(error)<3.0){
          mainMotorStop();
          break;
    }
    float control = Kp*error;
    float cali_speed=min(abs(control),255);
    if(abs(control)>5 && abs(control)<50){
      cali_speed=max(50,control*4); 
    }
    mainMotorRun( (control>=0)?HIGH:LOW, cali_speed);
    //모터가 움직임이 이상하면 보이면 수정
    if(checkDistance()==1){
      pumpOff();
      delay(3000);
      pumpOff();
      mainMotorStop();
      gameStart=0;//game 종료
    }
  }
}
 
int checkDistance(){
  long duration, distance;
  digitalWrite(disTrigPin, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(disTrigPin, LOW);
 
  duration = pulseIn(disEchoPin, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 1000) / 2; 
  if(distance<disLine){
    return 1;
  }
  else{
    return 0;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(disEchoPin,INPUT);
  pinMode(disTrigPin,OUTPUT);
  pinMode(pumpPWMPin,OUTPUT);
  pinMode(pumpDirPin,OUTPUT);
  pinMode(encoderApin,INPUT_PULLUP);
  attachInterrupt(0,doEncoderA,CHANGE);
  pinMode(encoderBpin,INPUT_PULLUP);
  attachInterrupt(1,doEncoderB,CHANGE);
  pinMode(mainMotorDirPin,OUTPUT);
  pinMode(mainMotorPWMPin,OUTPUT);
  pinMode(startBtnPin,INPUT_PULLUP);
}

void loop() {
  if(digitalRead(startBtnPin)==0){
    gameStart=1;
  }
  while(gameStart){
    int toDeg = random(-100,100);
    rotateToDeg(toDeg);
    
  }
}
