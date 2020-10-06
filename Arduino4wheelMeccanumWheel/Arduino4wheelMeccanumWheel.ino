const int trigPin_0= 2,trigPin_90=8,echoPin_90=7;
const int echoPin_0 = 5;

int motor1_IN1=11;
int motor1_IN2=12;

int motor2_IN3=9;
int motor2_IN4=10;

int motor3_IN5=13;
int motor3_IN6=14;

int motor4_IN7=15;
int motor4_IN8=16;

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
state = 'P';//No movement initially
Serial.begin(9600); 
}
//The code inside loop keeps on looping forever.
void loop(){
  // Reads the data from the serial port (i.e from bluetooth in our case)
  // It receives one of the characters from W A S D L R.
   state = Serial.read(); 

  // execution(state) function takes in received character as argument.
   execution(state);
}

//Method responsible for controlling motors
//
void execution(char state){
  switch(state)
  {
    case 'W': {
  Serial.println("Forward");
  //motor 1 - on
  digitalWrite(motor1_IN1,HIGH);
  digitalWrite(motor1_IN2,LOW);

  //motor 2 - on
  digitalWrite(motor2_IN3,HIGH);
  digitalWrite(motor2_IN4,LOW);

  //motor 3 - on
  digitalWrite(motor3_IN5,HIGH);
  digitalWrite(motor3_IN6,LOW);

  //motor 4 - on
  digitalWrite(motor4_IN7,HIGH);
  digitalWrite(motor4_IN8,LOW);
  break;
}
    case 'A': { 
  Serial.println("Moving Left");
  
  //motor 1 - off
  digitalWrite(motor1_IN1,LOW);
  digitalWrite(motor1_IN2,HIGH);

  //motor 2 - on
  digitalWrite(motor2_IN3,HIGH);
  digitalWrite(motor2_IN4,LOW);

  //motor 3 - on
  digitalWrite(motor3_IN5,HIGH);
  digitalWrite(motor3_IN6,LOW);

  //motor 4 - off
  digitalWrite(motor4_IN7,LOW);
  digitalWrite(motor4_IN8,HIGH);
  break;
    }
    case 'D': {
  Serial.println("Moving Right");

  //motor 1 - on
  digitalWrite(motor1_IN1,HIGH);
  digitalWrite(motor1_IN2,LOW);

  //motor 2 - off
  digitalWrite(motor2_IN3,LOW);
  digitalWrite(motor2_IN4,HIGH);

  //motor 3 - off
  digitalWrite(motor3_IN5,LOW);
  digitalWrite(motor3_IN6,HIGH);

  //motor 4 - on
  digitalWrite(motor4_IN7,HIGH);
  digitalWrite(motor4_IN8,LOW);
  break;
}
    case 'S': {
  Serial.println("Backward");

  //motor 1 - off
  digitalWrite(motor1_IN1,LOW);
  digitalWrite(motor1_IN2,HIGH);

  //motor 2 - off
  digitalWrite(motor2_IN3,LOW);
  digitalWrite(motor2_IN4,HIGH);

  //motor 3 - off
  digitalWrite(motor3_IN5,LOW);
  digitalWrite(motor3_IN6,HIGH);

  //motor 4 - off
  digitalWrite(motor4_IN7,LOW);
  digitalWrite(motor4_IN8,HIGH);
  break;
}
    case 'R': {
  Serial.println("Rotating Clockwise/Right");

  //motor 1 is on
  digitalWrite(motor1_IN1,HIGH);
  digitalWrite(motor1_IN2,LOW);

  //motor 2 - off
  digitalWrite(motor2_IN3,LOW);
  digitalWrite(motor2_IN4,HIGH);

  //motor 3 - on
  digitalWrite(motor3_IN5,HIGH);
  digitalWrite(motor3_IN6,LOW);

  //motor 4 - off
  digitalWrite(motor4_IN7,LOW);
  digitalWrite(motor4_IN8,HIGH);
  break;
}
    case 'L': {
  Serial.println("Rotating AntiClockwise/Left");

  //motor 1 - off
  digitalWrite(motor1_IN1,LOW);
  digitalWrite(motor1_IN2,HIGH);

  //motor 2 - on
  digitalWrite(motor2_IN3,HIGH);
  digitalWrite(motor2_IN4,LOW);

  //motor 3 - off
  digitalWrite(motor3_IN5,LOW);
  digitalWrite(motor3_IN6,HIGH);

  //motor 4 - on
  digitalWrite(motor4_IN7,HIGH);
  digitalWrite(motor4_IN8,LOW);
  break;
}
  }
}
