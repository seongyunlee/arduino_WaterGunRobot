//This code is to use with L298n Dual H-bridge motor driver<br>//It just turns on a DC motor for a certain time and turn it off
//refer to surtrtech.blogspot.com for more information
int in1 = 9; //Declaring the pins where in1 in2 from the driver are wired 
int in2 = 8; //here they are wired with D9 and D8 from Arduino
void setup() {
  pinMode(in1, OUTPUT); //Declaring the pin modes, obviously they're outputs
  pinMode(in2, OUTPUT);
}c
//Before starting the loop you should create functions type "void" to control the driver's pins
//Here I created two functions, the first one turns a motor to a direction (you can change it by switching LOW and HIGH
//and the second one to stop the motor
void TurnMotorA(){              
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}
void TurnOFFA(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
void loop() {
  TurnMotorA(); //in the loop we use the function to turn the motor for 3s and stop it for 2s
}
