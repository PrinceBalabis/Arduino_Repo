/*
  Simple example for client
  http://code.google.com/p/rc-switch/
*/

// Global variables to setup the client
int clientIDNumber = 39485847;
int shutdownTimer = 5; // Timer of when to shutshuts the lights off after no motion(minutes), if 0 its unlimited
int timerResetWhenMotion = 1; // Set to 1 to reset shutdown timer each time a motion has been detected
int motionSensitivity = 100; // Must calibrate this value accordingly
const int lightSwitchPin = 2;

// includes for libraries needed
#include <RCSwitch.h>
#include <FreeRTOS_AVR.h>

void setup() { // Start of setup-function
  Serial.begin(9600);
  // wait for Arduino
  while (!Serial) {}

  // Light switch setup and turn off lights
  pinMode (lightSwitchPin, OUTPUT);
  digitalWrite(lightSwitchPin, LOW);

  // create blink task
  xTaskCreate(vMotionSensorTask,
              (signed portCHAR *)"Task1",
              configMINIMAL_STACK_SIZE + 100,
              NULL,
              tskIDLE_PRIORITY + 2,
              NULL);

  // create print task
  xTaskCreate(vRFCommTask,
              (signed portCHAR *)"Task2",
              configMINIMAL_STACK_SIZE + 100,
              NULL,
              tskIDLE_PRIORITY + 1,
              NULL);

  // start FreeRTOS
  vTaskStartScheduler();
} // End of setup-function

void loop() {
  // FreeRTOS takes over, loop-function should not run
}
