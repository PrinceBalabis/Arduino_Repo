/*
  Interrupt example

  This sketch specializes in interrupts where its important to read whenever the input goes
  HIGH or LOW. This case goes for when using switches(not pushbuttons!);

  Sets an interrupt which triggers whenever the pin changes between GND and 3.3V.
  Also implemented a cooldown feature, which sets a cooldown after an interrupt is triggered.
  This way it fixes issues with for instance switches that debounce, that makes the interrupt trigger
  several times on a single switch.

  The reason we are not using the built-in button is because external pushbuttons/switches has
  a long debounce time which we will test. To set the debounce time change the variable "interruptDebounce"

   The digital pin reads "1" when the button is NOT pressed.
   It reads "0" when the button is pressed.

   Having the pull-up resistor activated(INPUT_PULLUP) means there is no need
   to have the pushbuttons "open pin" connected to 3.3V.


  We will be using a pushbutton to emulate a switch.... When using the progam just
  hold the pushbuttno a little longer before releasing, as the debounce cooldown will be in
  effect. We dont quickly toggle a switch all the time anyway...

   The pushbutton has four pins, but they are joined connected 2 and 2.
   So the pins which are opposite each other(on each side of the button) are
   constantly connected(even when the pushbuttis not pressed/open circuit).
   When the pushbutton is pressed, all 4 pins are closed circuited.

   Circuit:
   Here we see the pingroups A and B, A1 and A2 are always connected even
   though the button is not pressed. Same goes for B1 and B2.
   When the button is pressed, the two groups are connected.
    (A1)   (B1)
     |     |
     |-----|
     |     |
    (A2)   (B2)

   Connection between Arduino and button:
   Ground -> A1 -> B1 - Digital pin
   or
   Ground -> A2 -> B2 - Digital pin

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
// (Milliseconds)The amount of time to wait untill accepting another buttonpress
// 200ms seeems to be the sweet spot for the NodeMCU
const unsigned long interruptDebounce = 200;

// "volatile" tells the program that the variable can change at any time. This is
// needed when using the varibles in interrupts
volatile unsigned long lastinterruptDetected = 0; // Save last interrupt time

// This is the function which is called upon interrupt
// Keep this function as short as possible so it does not cause program malfunction,
// as this functin will be ran at any time in the runtime if interrupt is triggered
// Best to just use a variable which is modified in this function, then
// use a loop to check if the variable has changed
void interruptFunction() {
  // Run time-sensitive function in the top of this function.
  unsigned long interruptDetected = millis(); // Store current time(program runtime)
  bool buttonState = digitalRead(interruptPin);
  
  //Serial.print("Interrupt...");
  if (interruptDetected - lastinterruptDetected > interruptDebounce) {
    lastinterruptDetected = interruptDetected; // Save last interrupt detected
    Serial.print("Accepted: ");
    Serial.println(buttonState); // You will see both 1 or 0 print out, because of the debouncing
  } else {
    //Serial.println("On cooldown");
  }
}

void setup() {
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(250000);
  delay(100); // Some time for serial buffer to empty

  pinMode(interruptPin, INPUT_PULLUP); // Set the pin to the button as interrupt

  //CHANGE TO RISING OR FALLING DEPENDING ON YOUR GOALS. CHANGE IS NOT RELIABLE IN THIS PROGRAM.
  // Should be FALLING when its INPUT_PULLUP
  // Attach an interrupt to the pin of the button
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptFunction, CHANGE);

  Serial.println(F(""));
  Serial.println("Started interrupt program");
  delay(10); // Some time for serial buffer to empty
}

void loop() {
  // Not used
}



