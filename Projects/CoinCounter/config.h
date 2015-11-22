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

/**
  Coin customization
   1,2 and 5 kr has holes in the center of the coin, which affects precision performance,
   thats why delays are modified in order to correct the issue

   Testing:
   0.25 - untested but shoould work as good as 0.50kr
   0.50 kr - tested with only one coin worked fine, grouptest is unknown result
   1 kr - untested
   2 kr - seems to work fine
   5 kr - has some bugs
   10 kr - untested but should work
   20 kr - works most of the time
*/

#define KR_025_LAG_TIME 50
#define KR_025_POLLING_TIME 2

#define KR_050_LAG_TIME 50
#define KR_050_POLLING_TIME 2

#define KR_1_LAG_TIME 90
#define KR_1_POLLING_TIME 2

#define KR_2_LAG_TIME 90
#define KR_2_POLLING_TIME 2

#define KR_5_LAG_TIME 110
#define KR_5_POLLING_TIME 2

#define KR_10_LAG_TIME 70
#define KR_10_POLLING_TIME 2

#define KR_20_LAG_TIME 70
#define KR_20_POLLING_TIME 2

// LED Buzzer config
#define LED_BUZZER_PIN 2  //define a pin for LED which blinks while counting
#define LED_BUZZER_BEEP_LENGTH 60
#define LED_BUZZER_BEEP_SILENT_DIVIDER 60

// Buttons config
#define BUTTON_TOGGLE_COIN_VALUE_PIN 8  //define a pin for the button which toggles coin value
#define BUTTON_RESET_COUNT_PIN 9  //define a pin for the button which resets amount of coins
#define BUTTON_POLLING_TIME 80  //how often to check for button updates
