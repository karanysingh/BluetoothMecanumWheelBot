int dirA = 10;
int dirB = 11;
int  speed = 12;

void  setup()
{
pinMode(dirA,OUTPUT);
pinMode(dirB,OUTPUT);
pinMode(speed,OUTPUT);
//move_forward();
//move_backward();
}

void loop()
{
  
}
void move_forward()
{
digitalWrite(dirA,HIGH);
digitalWrite(dirB,LOW);
digitalWrite(speed,HIGH);
} 
void move_backward()
{
digitalWrite(dirA,LOW);
digitalWrite(dirB,HIGH);
digitalWrite(speed,HIGH);
}
