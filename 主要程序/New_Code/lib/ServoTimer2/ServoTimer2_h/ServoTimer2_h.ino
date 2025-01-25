#include<ServoTimer2.h>
#define myservoPin 3
ServoTimer2 myservo;
int a;
void setup() 
{
  // put your setup code here, to run once:
  myservo.attach(myservoPin);
  pinMode( 9 , OUTPUT );
  pinMode( 10 , OUTPUT );
}

void loop() 
{
  // put your main code here, to run repeatedly: 
  analogWrite( 9 , 200 );
  delay(1000);
  analogWrite( 9 ,100 );
  delay(1000);
  a=map(60,20,160,750,2250);
  myservo.write(a);
}
