void setup() {
  Serial.begin(9600);

}

void loop() {
  if (Serial.available() > 0) {
    String string = "";

    while (Serial.available() > 0) {
      delay(5);
      string += (char)Serial.read();
    }

    Serial.println(string);
  }
}
