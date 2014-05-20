int relay = 10; //relay turns trigger signal - active high;
int button = 4;
int relayState = 0;
int buttonState = 0;
int previousButtonState = 0;

void setup ()
{
  pinMode (relay, OUTPUT); //Define port attribute is output;
  pinMode(button, INPUT);
}

void loop ()
{
  buttonState = digitalRead(button);
  if (!buttonState && previousButtonState) // Wait for button to release
  {
    previousButtonState = 0;
    relayState = !relayState;
  } else if (buttonState) // Button pressed
  {
    previousButtonState = 1;
  }
  digitalWrite (relay, relayState);
  delay(50);
}
