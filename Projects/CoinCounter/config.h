/**
Hardware connections

LiquidCrystal i2c Display connections
GND - GND
VCC - 5V
SDA - ANALOG Pin 4
SCL - ANALOG pin 5

*/
#define PHOTO_DIODE_PIN A0  //define a pin for Photo resistor
#define LED_STATUS_PIN 13  //define a pin for Status pin(using built in LED)
#define LED_BUZZER_PIN 2  //define a pin for LED which blinks while counting

// Sensor config
#define PHOTO_DIODE_SENSOR_THRESHOLD 2  //If its below this value, a coin is being dropped, if its above, then there is no coin being dropped
#define COINSENSOR_POLLING_TIME 2 // Get sensor value every chosen millisecond


// LED Buzzer config
#define LED_BUZZER_BEEP_LENGTH 50
#define LED_BUZZER_BEEP_SILENT_DIVIDER 50
