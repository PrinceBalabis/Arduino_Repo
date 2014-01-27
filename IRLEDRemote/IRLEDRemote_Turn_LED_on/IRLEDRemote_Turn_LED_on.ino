#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
int ledState = 0;
int ledPin = 13;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print(F("result = 0x"));
    Serial.println(results.value, HEX);

    if (results.value == 0xFF30CF)  {
      ledState = !ledState;
      Serial.println("Pressed button (1) - Changing LED state");
      digitalWrite(ledPin, ledState);
    }
    else if (results.value == 0xFFFFFFFF){
      Serial.println("Just repeating...");
    }
    else {
      Serial.println("No");
    }
    irrecv.resume(); // Receive the next value
  }
}
