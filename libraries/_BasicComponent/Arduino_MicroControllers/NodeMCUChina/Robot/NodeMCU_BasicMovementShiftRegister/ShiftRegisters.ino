//do not touch
const int numOfRegisterPins = number_of_74hc595s * 8;
boolean registers[numOfRegisterPins];

//set all register pins to LOW
void clearRegisters() {
  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    registers[i] = LOW;
  }
}


//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters() {

  digitalWrite(rclkShiftRegister, LOW);

  for (int i = numOfRegisterPins - 1; i >=  0; i--) {
    digitalWrite(srclckShiftRegister, LOW);

    int val = registers[i];

    digitalWrite(serShiftRegister, val);
    digitalWrite(srclckShiftRegister, HIGH);

  }
  digitalWrite(rclkShiftRegister, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value) {
  registers[index] = value;
}

void initShiftRegisters() {
  pinMode(serShiftRegister, OUTPUT);
  pinMode(rclkShiftRegister, OUTPUT);
  pinMode(srclckShiftRegister, OUTPUT);


  //reset all register pins
  clearRegisters();
  writeRegisters();
}

