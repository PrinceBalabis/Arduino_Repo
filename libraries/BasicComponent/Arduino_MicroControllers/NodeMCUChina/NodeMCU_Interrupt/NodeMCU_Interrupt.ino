/*
  Interrupt example

  Sets an interrupt which triggers whenever the pin changes between GND and 3.3V.
  Also implemented a cooldown feature, which sets a cooldown after an interrupt is triggered.
  This way it fixes issues with for instance switches that debounce, that makes the interrupt trigger
  several times on a single switch.  

  When using the pins, use the Arduino macros for pins(D2 for Digital pin 2, A0 for analog pin 0 etc)

  MAJOR BUG:
  If it cannot connect to the Wi-Fi hotspot, try reconnecting the power/USB cable to reset the ESP

  Put a large capacitor(or even better, several small ones) between 5V/VIN and Ground to improve reliability

  Remember to install the CH340G drivers.

  Board settings:
  -NodeMCU 1.0(ESP-12E)
  -80MHz
  -921600
  -4M(3M)


    -There is noise on the ADC when receiving/transmitting on Wi-Fi
    while using the ADC! Try to use one function at a time to minimize ADC noise

    -Sometimes it won't be able to connect to Wi-Fi after uploading new
    code, try pressing the RESET switch on the ESP8266, this should reset the Wi-Fi module.
      If it didn't work, try disconnecting then reconnecting the power/USB-cable.

*/
const uint8_t interruptPin = D4; // pin to interrupt
unsigned long interruptCoolDown = 100000; // (Microseconds)The amount of time to wait untill accepting another interrupt

unsigned long interruptDetected = 0; // Has a value above 0 when an interrupt is detected
unsigned long lastinterruptDetected = 0; // Save last interrupt time

// This is the function which is called upon interrupt
// Keep this function as short as possible so it does not cause program malfunction,
// as this functin will be ran at any time in the runtime if interrupt is triggered
// Best to just use a variable which is modified in this function, then
// use a loop to check if the variable has changed
void interruptFunction() {
  interruptDetected = micros(); // Store current time(program runtime)
}

void setup() {
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(250000);
  delay(100); // Some time for serial buffer to empty

  pinMode(interruptPin, INPUT_PULLUP);
  //pinMode(interruptPin, OUTPUT); // Next line won't work if the pin is not set to output
  //digitalWrite(interruptPin, 0); // Set to low so we can see the rise
  //CHANGE TO RISING OR FALLING DEPENDING ON YOUR GOALS
  //attachInterrupt(digitalPinToInterrupt(interruptPin), interruptFunction, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptFunction, CHANGE);

  Serial.println(F(""));
  Serial.println("Started interrupt program");
  delay(100); // Some time for serial buffer to empty
}

void loop() {
  if (interruptDetected > 0) {
    Serial.print("Interrupt: ");
    if (interruptDetected - lastinterruptDetected > interruptCoolDown) {
      lastinterruptDetected = interruptDetected; // Save last interrupt detected
      Serial.println("Accepted");
    } else {
      Serial.println("On cooldown");
    }
    interruptDetected = 0;
  }
  delayMicroseconds(1);
}



