// Define key pin
int K1 = 13;
int K2 = 12;
int K3 = 11;
int K4 = 10;
// Define led pin
int GND = 6;
int D1 = 5;
int D2 = 4;
int D3 = 3;
int D4 = 2;
int D5 = 1;
int D6 = 0;
// variables will change:
int buttonState = 0; // variable for reading the pushbutton status
// the setup routine runs once when you press reset:
void setup() {
// initialize the keys pin as an input.
pinMode(K1, INPUT);
pinMode(K2, INPUT);
pinMode(K3, INPUT);
pinMode(K4, INPUT);
// initialize the leds pin as an output.
pinMode(GND, OUTPUT);
pinMode(D1, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(D3, OUTPUT);
pinMode(D4, OUTPUT);
pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);
//Activate key pin internal pull-up resistors
digitalWrite(K1, HIGH);
digitalWrite(K2, HIGH);
digitalWrite(K3, HIGH);
digitalWrite(K4, HIGH);
//as LED GND
digitalWrite(GND, LOW);
}
// the loop routine runs over and over again forever:
void loop() {
buttonState = digitalRead(K1);
digitalWrite(D1, buttonState); //
buttonState = digitalRead(K2);
digitalWrite(D2, buttonState); //
buttonState = digitalRead(K3);
digitalWrite(D3, buttonState); //
buttonState = digitalRead(K4);
digitalWrite(D4, buttonState); //
digitalWrite(D5, HIGH); // turn the LED on (HIGH is the voltage level)
digitalWrite(D6, HIGH); // turn the LED on (HIGH is the voltage level)
}

