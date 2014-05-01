int flame = A5 ; //define the flame interface analog 0 interface
int Beep = 8 ; //buzzer interface defines the interface number 7
int val = 0 ; //define numeric variables

void setup ()
{
  pinMode (Beep, OUTPUT) ; //define LED as output interface
  pinMode (flame, INPUT) ; //define the buzzer as the input interface
  Serial.begin (9600) ; //set the baud rate to 9600
}
void loop () {
  val = analogRead (flame) ; //read the analog value flame sensor
  Serial.println (val) ; //output analog values, and print them out
  if (val >= 600) //When the analog value is greater than 600 when the buzzer sounds
  {
    digitalWrite (Beep, HIGH);
    delay(500);
  } else {
    digitalWrite (Beep, LOW);
  }
}
