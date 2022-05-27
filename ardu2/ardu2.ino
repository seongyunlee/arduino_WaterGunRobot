#include <LiquidCrystal_I2C.h>
//led pin
int led1=6;//노랑  
int led2=7;//초록
int led3=7;//빨강
int led4=8;//파랑
//btn pin
int btn1=2;//노랑
int btn2=3;//
int btn3=4;
int btn4=5;
//int game start
int startBtn =11;
int score=0;
int gameStart=0;

LiquidCrystal_I2C lcd(0x27, 16, 2);  //lcd 객체 선언


void lcdGameStart(){
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Game Start");
  
}
void lcdInit(){

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Push the start Buttom");
}
void lcdPrintScore(){
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Score:");
  lcd.println(score);

}

void setup(){
  Serial.begin(9600);       // 시리얼 속도 설정
  lcd.begin();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT); 
  pinMode(led3, OUTPUT); 
  pinMode(led4, OUTPUT); 
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(startBtn, INPUT_PULLUP);
  lcdInit(); //LCD 사용 시작
}

void loop(){
  if(digitalRead(btn1)==0){
    Serial.println("BTN1");
  }
  if(digitalRead(btn2)==0){
    Serial.println("BTN2");
  }
  if(digitalRead(btn3)==0){
    Serial.println("BTN3");
  }
  if(digitalRead(btn4)==0){
    Serial.println("BTN4");
  }
  if(digitalRead(startBtn)==0){
    gameStart=1;
    Serial.println("on");
    lcdGameStart();
  }
  while(gameStart){
    lcdPrintScore();
      int whichLEDpin=random(6,10);
      int delayTime=0;
      Serial.print("LED ON");
      Serial.println(whichLEDpin);
      digitalWrite(whichLEDpin,HIGH);
      while(delayTime<3000){//3초
        delayTime++;
          if(digitalRead(whichLEDpin-4)==0){
              Serial.print("get scrore");
              Serial.println(score);
              score++;
              lcdPrintScore();
              break;

          }
          delay(1);
      }
      digitalWrite(whichLEDpin,LOW);
  }
} 
