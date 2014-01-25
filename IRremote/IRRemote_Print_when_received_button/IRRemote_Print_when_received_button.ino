#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{

  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {

  if (irrecv.decode(&results)) {
    Serial.print(F("result = 0x"));
    Serial.println(results.value, HEX);

    if (results.value == 0xFF30CF)  {
      Serial.println("yes");
    }
    else {
      Serial.println("No");
    }
    irrecv.resume(); // Receive the next value
  }
}
