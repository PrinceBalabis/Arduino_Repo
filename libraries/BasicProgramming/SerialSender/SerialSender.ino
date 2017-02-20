//This is the Serial Sender

void setup()
{
  Serial.begin(9600); // set up Serial library at 9600 bps
}

void loop()
{
  Serial.println("This message is sent from an Arduino ");
  delay(1000);
}
