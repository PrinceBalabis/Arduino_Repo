int LDR = 0;                                //analog pin to which LDR is connected, here we set it to 0 so it means A0
int LDRValue = 0;                    //that’s a variable to store LDR values
int light_sensitivity = 400;  //This is the approx value of light surrounding your LDR

int LDRValuePrevious = 0;
int LDRValueDifference = 0;

int countDown = 0;
int lightswitch = 0;

void setup()
{
  Serial.begin(9600);            //start the serial monitor with 9600 buad
  pinMode(13, OUTPUT);     //we mostly use13 because there is already a built in yellow LED in arduino which shows output when 13 pin is enabled
  digitalWrite(13, LOW);
  LDRValuePrevious = LDRValue;
}

void loop()
{
  LDRValue = analogRead(LDR);          //reads the ldr’s value through LDR which we have set to Analog input 0 “A0″
  //Serial.println(LDRValue);                  //prints the LDR values to serial monitor
  delay(80);                                                //This is the speed by which LDR sends value to arduino
  Serial.println(LDRValue);

  LDRValueDifference = LDRValue - LDRValuePrevious;

  if (LDRValueDifference > 160 ) {
    countDown += 1;
    if (countDown >= 1) {
      countDown = 0;
      Serial.println("BOOM SWITCHED!!!!!");
      if (lightswitch) {
        lightswitch = 0;
      } else {
        lightswitch = 1;
      }
    }
  }

  if (lightswitch)
  {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  LDRValuePrevious = LDRValue;
}

