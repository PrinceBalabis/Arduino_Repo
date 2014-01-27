/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
//const int ledPin =  13;      // the number of the LED pin
const int ledPin =  12;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
unsigned long morseBlinkLength= 0;
int morseToneOn = 0;
unsigned long morseBlinkStartTime = 0;
unsigned long morseBlinkEndTime = 0;

///SOS CODE
int blinkStage = 0;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);        
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);    
  digitalWrite(ledPin, LOW);
 
}

void loop(){
  delay(25);
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is NOT PRESSED.
  // if it is not, the buttonState is HIGH:
  if (buttonState == LOW) {     
     //Serial.println("PRESSED");
    // turn LED on:
    if(morseToneOn == 0){
      morseBlinkStartTime = millis();
      morseToneOn = 1;
   }
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    //     Serial.println("noooooooot  PRESSED");
    // turn LED off:
   if(morseToneOn){
     morseBlinkEndTime = millis();
     morseBlinkLength = morseBlinkEndTime-morseBlinkStartTime;
     morseToneOn = 0;
 //    Serial.print("Morse-blink length: ");
 //    Serial.print(morseBlinkLength);
 //    Serial.println();
   }
    digitalWrite(ledPin, LOW); 
  }
  
  if(blinkStage>=0 && blinkStage<=2 && morseBlinkLength<=300 && morseBlinkLength!=0){
  //  if(blinkStage>=0 && morseBlinkLength<=150 && morseBlinkLength!=0){
    blinkStage++;
    Serial.println("SHORT, BLINK 1-3");
  } else if(blinkStage>=3 && blinkStage<=5 && morseBlinkLength>=450 && morseBlinkLength!=0){
    blinkStage++;
    Serial.println("LONG, BLINK 4-6");
  } else if(blinkStage>=6 && blinkStage<=9 && morseBlinkLength<=300 && morseBlinkLength!=0){
    Serial.println("SHORT, BLINK 7-9");
    blinkStage++;
    if(blinkStage==9){
      Serial.println("SOS AKTIVERAD");
      signalSOS();
       /// digitalWrite(ledPin, HIGH);
       /// delay(5000); 
       /// digitalWrite(ledPin, LOW);
      resetSOSCode();
    }
  } else if(morseBlinkLength!=0){
     resetSOSCode();
  }
 morseBlinkLength = 0;
}

void resetSOSCode(){
        morseToneOn = 0;
        blinkStage = 0;
        delay(50); 
        for(int i=0;i<15;i++){
         digitalWrite(ledPin, HIGH);
         delay(25); 
         digitalWrite(ledPin, LOW);
         delay(25); 
        }
        Serial.println("SOS RESETTAD");
}

void signalSOS() {
    delay(50); 
    for(int i=0;i<3;i++){
     digitalWrite(ledPin, HIGH);
     delay(100); 
     digitalWrite(ledPin, LOW);
     delay(100); 
    }
    delay(200); 
    for(int i=0;i<3;i++){
     digitalWrite(ledPin, HIGH);
     delay(300); 
     digitalWrite(ledPin, LOW);
     delay(300); 
    }
    delay(200); 
    for(int i=0;i<3;i++){
     digitalWrite(ledPin, HIGH);
     delay(100); 
     digitalWrite(ledPin, LOW);
     delay(100); 
    }
}
