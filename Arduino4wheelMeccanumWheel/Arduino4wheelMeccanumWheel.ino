#include<softwareSerial.h>
const int rx_pin;
const int tx_pin;

SoftwareSerial blue_mod(rx_pin,tx_pin);

int d_front_l=11;
int d_front_r=12;
int p_front_l=11;
int p_front_r=12;

int d_back_l=11;
int d_back_r=12;
int p_back_l=11;
int p_back_r=12;

char state;
char mode;

void setup() {
pinMode(trigPin_0, OUTPUT); 
pinMode(echoPin_0, INPUT); 
pinMode(trigPin_90, OUTPUT);
pinMode(echoPin_90, INPUT);
pinMode(motor1_IN1,OUTPUT);
pinMode(motor1_IN2,OUTPUT);
pinMode(motor2_IN3,OUTPUT);
pinMode(motor2_IN4,OUTPUT);

extern char state; // global variable
state = '-';//No movement initially
Serial.begin(9600); 
}
//The code inside loop keeps on looping forever.
void loop(){
  // Reads the data from the serial port (i.e from bluetooth in our case)
  // It receives one of the characters from W A S D L R.
  if(Serial.available())
  {
   state = Serial.read();
   execution(state); 
  }
  else
  {
    execution("-");
  }
  // execution(state) function takes in received character as argument.
   
}

//Method responsible for controlling motors
//


void forward()
{
  //all wheels forward
  digitalWrite(d_front_l,HIGH);
  digitalWrite(p_front_l,HIGH);
  digitalWrite(d_front_r,HIGH);
  digitalWrite(p_front_r,HIGH);
  digitalWrite(d_back_l,HIGH);
  digitalWrite(p_back_l,HIGH);
  digitalWrite(d_back_r,HIGH);
  digitalWrite(p_back_r,HIGH);
}

void backward()
{
  digitalWrite(d_front_l,LOW);
  digitalWrite(p_front_l,HIGH);
  digitalWrite(d_front_r,LOW);
  digitalWrite(p_front_r,HIGH);
  digitalWrite(d_back_l,LOW);
  digitalWrite(p_back_l,HIGH);
  digitalWrite(d_back_r,LOW);
  digitalWrite(p_back_r,HIGH);
}

void left()
{
  digitalWrite(d_front_l,HIGH);
  digitalWrite(p_front_l,HIGH);
  digitalWrite(d_front_r,HIGH;
  digitalWrite(p_front_r,HIGH);
  digitalWrite(d_back_l,LOW);
  digitalWrite(p_back_l,HIGH);
  digitalWrite(d_back_r,LOW);
  digitalWrite(p_back_r,HIGH);
}
void right()
{
  digitalWrite(d_front_l,LOW);
  digitalWrite(p_front_l,HIGH);
  digitalWrite(d_front_r,LOW);
  digitalWrite(p_front_r,HIGH);
  digitalWrite(d_back_l,HIGH);
  digitalWrite(p_back_l,HIGH);
  digitalWrite(d_back_r,HIGH);
  digitalWrite(p_back_r,HIGH);
}
void clockwise()
{
  digitalWrite(d_front_l,HIGH);
  digitalWrite(p_front_l,HIGH);
  digitalWrite(d_front_r,LOW);
  digitalWrite(p_front_r,HIGH);
  digitalWrite(d_back_l,HIGH);
  digitalWrite(p_back_l,HIGH);
  digitalWrite(d_back_r,LOW);
  digitalWrite(p_back_r,HIGH);
}
void anti_clockwise()
{
  digitalWrite(d_front_l,LOW);
  digitalWrite(p_front_l,HIGH);
  digitalWrite(d_front_r,HIGH);
  digitalWrite(p_front_r,HIGH);
  digitalWrite(d_back_l,LOW);
  digitalWrite(p_back_l,HIGH);
  digitalWrite(d_back_r,HIGH);
  digitalWrite(p_back_r,HIGH);
}

void s_stop()
{
  digitalWrite(p_front_l,LOW);
  digitalWrite(p_front_r,LOW);
  digitalWrite(p_back_l,LOW);
  digitalWrite(p_back_r,LOW);
  
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
  case "-":
  {
    s_stop();
  }
  }
}
