/**
Configurations

LiquidCrystal i2c Display connections
GND - GND
VCC - 5V
SDA - ANALOG Pin 4
SCL - ANALOG pin 5

*/

//Main
#define LED_STATUS_PIN 13  //define a pin for Status pin(using built in LED)

// Sensor config
#define PHOTO_DIODE_PIN A0  //define a pin for Photo resistor
#define PHOTO_DIODE_SENSOR_THRESHOLD 2  //if its below this value, a coin is being dropped, if its above, then there is no coin being dropped
#define COINSENSOR_POLLING_TIME 2 //get sensor value every chosen millisecond

// LED Buzzer config
#define LED_BUZZER_PIN 2  //define a pin for LED which blinks while counting
#define LED_BUZZER_BEEP_LENGTH 50
#define LED_BUZZER_BEEP_SILENT_DIVIDER 50

// Buttons config
#define BUTTON_TOGGLE_COIN_VALUE_PIN 8  //define a pin for the button which toggles coin value
#define BUTTON_RESET_COUNT_PIN 9  //define a pin for the button which resets amount of coins
#define BUTTON_POLLING_TIME 10  //how often to check for button updates
