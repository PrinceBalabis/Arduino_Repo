#include <Servo.h>

Servo myservo;

void setup()
{
  myservo.attach(8);
}

void loop()
{
  myservo.writeMicroseconds(1800); //Turn counter-clockwise
  delay(3000);
  myservo.writeMicroseconds(1500); //Stop
  delay(3000);
  myservo.writeMicroseconds(1200); //Turn clockwise
  delay(3000);
}
