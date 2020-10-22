#include<SoftwareSerial.h>
const int rx_pin=10;
const int tx_pin=11;

SoftwareSerial blue_mod(rx_pin,tx_pin);
int dirFr0=1;
int dirFr1=1;
int dirBr0=1;
int dirBr1=1;
int spdFr=1;
int spdBr=1;
int dirFl0=1;
int dirFl1=1;
int dirBl0=1;
int dirBl1=1;
int spdFl=1;
int spdBl=1;

char state;
char mode;


void setup() {
Serial.begin(9600);
blue_mod.begin(9600);
pinMode(dirFr0,OUTPUT);
pinMode(dirFr1,OUTPUT);
pinMode(dirFl0,OUTPUT);
pinMode(dirFl1,OUTPUT);
pinMode(dirBr0,OUTPUT);
pinMode(dirBr1,OUTPUT);
pinMode(spdFr,OUTPUT);
pinMode(spdFl,OUTPUT);
pinMode(spdBl,OUTPUT);
pinMode(spdBr,OUTPUT);
state = '-';
}

void loop(){
  // Reads the data from the serial port (i.e from bluetooth in our case)
  // It receives one of the characters from W A S D L R.
  if(blue_mod.available())
  {
   state = blue_mod.read();
   execution(state); 
  }
  else
  {
    execution('P');
  }
  // execution(state) function takes in received character as argument.
   
}
void execution(char state){
  switch(state)
  {
    case 'W': {
  Serial.println("Forward");
  forward();
  break;
}
    case 'A': { 
  Serial.println("Moving Left");
  left();
  break;
    }
    case 'D': {
  Serial.println("Moving Right");
  right();
  break;
}
case 'S': {
  Serial.println("Backward");
  backward();
  break;
}
    case 'R': {
  Serial.println("Rotating Clockwise/Right");
  clockwise();
  break;
}
    case 'L': {  
  Serial.println("Rotating AntiClockwise/Left");
  anti_clockwise();
  break;
}
  case 'P' :
  {
    s_stop();
    break;
  }
 }
}


void forward()
{
   digitalWrite(dirFr0,HIGH);
  digitalWrite(dirFr1,LOW);
  digitalWrite(spdFr,HIGH);
  digitalWrite(dirFl0,HIGH);
  digitalWrite(dirFl1,LOW);
  digitalWrite(spdFl,HIGH);
  digitalWrite(dirBr0,HIGH);
  digitalWrite(dirBr1,LOW);
  digitalWrite(spdBr,HIGH);
  digitalWrite(dirBl0,HIGH);
  digitalWrite(dirBl1,LOW);
  digitalWrite(spdBl,HIGH);
}

void backward()
{
 digitalWrite(dirFr0,LOW);
  digitalWrite(dirFr1,HIGH);
  digitalWrite(spdFr,HIGH);
  digitalWrite(dirFl0,LOW);
  digitalWrite(dirFl1,HIGH);
  digitalWrite(spdFl,HIGH);
  digitalWrite(dirBr0,LOW);
  digitalWrite(dirBr1,HIGH);
  digitalWrite(spdBr,HIGH);
  digitalWrite(dirBl0,LOW);
  digitalWrite(dirBl1,HIGH);
  digitalWrite(spdBl,HIGH);
}
void left()
{
 digitalWrite(dirFr0,LOW);
  digitalWrite(dirFr1,HIGH);
  digitalWrite(spdFr,HIGH);
  digitalWrite(dirFl0,HIGH);
  digitalWrite(dirFl1,LOW);
  digitalWrite(spdFl,HIGH);
  digitalWrite(dirBr0,HIGH);
  digitalWrite(dirBr1,LOW);
  digitalWrite(spdBr,HIGH);
  digitalWrite(dirBl0,LOW);
  digitalWrite(dirBl1,HIGH);
  digitalWrite(spdBl,HIGH);
 }

 void right()
{
 digitalWrite(dirFr0,HIGH);
  digitalWrite(dirFr1,LOW);
  digitalWrite(spdFr,HIGH);
  digitalWrite(dirFl0,LOW);
  digitalWrite(dirFl1,HIGH);
  digitalWrite(spdFl,HIGH);
  digitalWrite(dirBr0,LOW);
  digitalWrite(dirBr1,HIGH);
  digitalWrite(spdBr,HIGH);
  digitalWrite(dirBl0,HIGH);
  digitalWrite(dirBl1,LOW);
  digitalWrite(spdBl,HIGH);
}
void clockwise()
{
 digitalWrite(dirFr0,LOW);
  digitalWrite(dirFr1,HIGH);
  digitalWrite(spdFr,HIGH);
  digitalWrite(dirFl0,HIGH);
  digitalWrite(dirFl1,LOW);
  digitalWrite(spdFl,HIGH);
  digitalWrite(dirBr0,LOW);
  digitalWrite(dirBr1,HIGH);
  digitalWrite(spdBr,HIGH);
  digitalWrite(dirBl0,LOW);
  digitalWrite(dirBl1,HIGH);
  digitalWrite(spdBl,HIGH);
  }

 void anti_clockwise()
{
 digitalWrite(dirFr0,HIGH);
  digitalWrite(dirFr1,LOW);
  digitalWrite(spdFr,HIGH);
  digitalWrite(dirFl0,LOW);
  digitalWrite(dirFl1,HIGH);
  digitalWrite(spdFl,HIGH);
  digitalWrite(dirBr0,HIGH);
  digitalWrite(dirBr1,LOW);
  digitalWrite(spdBr,HIGH);
  digitalWrite(dirBl0,HIGH);
  digitalWrite(dirBl1,LOW);
  digitalWrite(spdBl,HIGH);
}
void s_stop()
{
// change all speed to 0
  digitalWrite(spdFr  , LOW);
  digitalWrite(spdFl  , LOW);
  digitalWrite(spdBr  , LOW);
  digitalWrite(spdBl  , LOW);  
}
