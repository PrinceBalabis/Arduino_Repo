/*
  ---------------------------------------------------------------
    Here we set up the scheduler.
    This tab has to be the last tab in order to compile,
    that is why there is an "_" (underscore) in front of the tab name.
    These functions are the first function to be ran by Arduino, but has to be in the last tab because
    programming is linear and all calls made from these funtions has to be declared in previous tabs.
  ---------------------------------------------------------------
*/
void setup() {
  // Initialize LED
  pinMode(ledPinESP, OUTPUT);
  pinMode(ledPinBoard, OUTPUT);
  digitalWrite(ledPinESP, HIGH); // Turn off LED
  digitalWrite(ledPinBoard, LOW); // Turn on LED(LED is inverted, so LOW is on)

  // Initialize Serial
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(250000);
  delay(100); // Some time for serial buffer to empty
  Serial.println("");
  Serial.println("");
  Serial.println("This node controls the ceiling lights and 433MHZ switches");

  // Initialize relay for ceiling lights
  initCeilingLights();

  // Initialize wallswitches
  initWallSwitches();

  Serial.println("Starting scheduler...");
  delay(100); // Some time for serial buffer to empty

  // Declare tasks
  //  Scheduler.start(&wallswitch_task); // Declare HTTP webclient task
  Scheduler.start(&http_task); // Declare HTTP webclient task
  //Scheduler.start(&mem_task); // Declare printing of heap memory task

  // Start scheduler/all tasks declared
  Scheduler.begin();
}
/*
  ---------------------------------------------------------------
    This loop function is not used.
  ---------------------------------------------------------------
*/
void loop() {
  // Program never enter this function
}
