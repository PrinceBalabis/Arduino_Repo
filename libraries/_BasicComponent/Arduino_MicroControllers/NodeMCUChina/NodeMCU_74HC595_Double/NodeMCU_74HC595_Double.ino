/*
  ---------------------------------------------------------------
    Double Shift registers
    individual pin command
  ---------------------------------------------------------------
*/

const int ledPinESP =  D4;// LED on ESP on pin D4(Must call D4 in code)
const int ledPinBoard =  D0; // LED on board on pin D0(Must call D0 in code)

int SER_Pin = D8;   //pin 14 on the 75HC595
int RCLK_Pin = D7;  //pin 12 on the 75HC595
int SRCLK_Pin = D6; //pin 11 on the 75HC595

//How many of the shift registers - change this
#define number_of_74hc595s 2

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];


void setup() {
  // Initialize LED
  pinMode(ledPinESP, OUTPUT);
  pinMode(ledPinBoard, OUTPUT);
  digitalWrite(ledPinESP, HIGH); // Turn off LED
  digitalWrite(ledPinBoard, LOW); // Turn on LED(LED is inverted, so LOW is on)

  // Initialize Serial
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(115200);
  delay(100); // Some time for serial buffer to empty
  Serial.println("");
  Serial.println("");
  Serial.println("Starting scheduler...");
  delay(100); // Some time for serial buffer to empty

  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);


  //reset all register pins
  clearRegisters();
  writeRegisters();
}

void loop() {
  //Set all pins(0-7) high
  setRegisterPin(0, HIGH);
  setRegisterPin(1, HIGH);
  setRegisterPin(2, HIGH);
  setRegisterPin(3, HIGH);
  setRegisterPin(4, HIGH);
  setRegisterPin(5, HIGH);
  setRegisterPin(6, HIGH);
  setRegisterPin(7, HIGH);
  setRegisterPin(8, HIGH);
  setRegisterPin(9, HIGH);
  setRegisterPin(10, HIGH);
  setRegisterPin(11, HIGH);
  setRegisterPin(12, HIGH);
  setRegisterPin(13, HIGH);
  setRegisterPin(14, HIGH);
  setRegisterPin(15, HIGH);

  writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
  //Only call once after the values are set how you need.
}


//set all register pins to LOW
void clearRegisters() {
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    registers[i] = LOW;
  }
}


//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters() {

  digitalWrite(RCLK_Pin, LOW);

  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value) {
  registers[index] = value;
}
