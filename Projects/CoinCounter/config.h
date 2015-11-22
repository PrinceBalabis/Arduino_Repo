#define PHOTO_DIODE_PIN A0  //define a pin for Photo resistor
#define LED_STATUS_PIN 13  //define a pin for Status pin(using built in LED)
#define LED_COUNT_PIN 12  //define a pin for LED which blinks while counting

#define PHOTO_DIODE_SENSOR_THRESHOLD 2  //If its below this value, a coin is being dropped, if its above, then there is no coin being dropped
#define COINSENSOR_POLLING_TIME 2 // Get sensor value every chosen millisecond
