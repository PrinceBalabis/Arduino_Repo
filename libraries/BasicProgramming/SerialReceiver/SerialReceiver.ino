//This is the Serial Receiver
char recievedChar = 'a';

void setup()
{
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println(recievedChar); //Check to see if Monitor is working
}

void loop()
{
  if (Serial.available()) {
    recievedChar = Serial.read();
    Serial.print(recievedChar);
  }

}
