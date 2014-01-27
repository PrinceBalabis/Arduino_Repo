char command = 0;
int ledPin = 13;
 
void setup()
{
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);
 }
void loop()
{
 delay(100);
}
 
void serialEvent() // To check if there is any data on the Serial line
 
{
while (Serial.available())
 {
command = Serial.read();
Serial.println(command);
if(command == 'a')   //Switch on the LED, if the received value is 1.
{
digitalWrite(ledPin, HIGH);
}
else if(command == 'b') //Switch off the LED, if the received value is 1.
{
digitalWrite(ledPin, LOW);
}
}
 
Serial.println("Succesfully received.");
 }

