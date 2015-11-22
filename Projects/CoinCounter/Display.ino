#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

NIL_WORKING_AREA(display, 128);
NIL_THREAD(Display, arg) {
  //Serial.println(F("Started Display..."));

  LiquidCrystal_I2C  lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

  lcd.begin (16, 2); //  <<----- My LCD was 16x2

  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);

  while (TRUE) {
    lcd.clear(); // Clear Display
    lcd.home(); // Go home
    lcd.print(coinAmount); // Print amount of coins inserted
    lcd.print(" st  "); // Print multiplication sign
    lcd.print(coinValue); // Print chosen coin value
    lcd.print(" kr"); // Print 'kr'

    lcd.setCursor (0, 1);       // go to start of 2nd line
    lcd.print("Total: ");
    lcd.print(coinTotal);
    lcd.print(" kr");

    nilSemSignal(&semLEDBuzzer); // Beep LED and buzzer once

    nilSemWait(&semDisplay); // Wait for sensor service to tell this service to update display
    //Serial.println(F("Updating Display..."));
  }
}


