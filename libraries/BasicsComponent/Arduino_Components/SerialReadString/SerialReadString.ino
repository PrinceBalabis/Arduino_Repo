//This is the Serial Receiver
String recievedString = "";

void setup()
{
  Serial.begin(9600); // set up Serial library at 9600 bps
}

void loop()
{
  while (Serial.available()) 
  {
    recievedString += Serial.readString();
  }
  if(recievedString.length() != 0) // Print string if we got something
  {
    recievedString += "\r\n";
    Serial.print(recievedString); // Print string
  }
  recievedString = ""; // Clear variable
}
