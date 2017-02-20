/*
  MAJOR BUG:
  If it cannot connect to the Wi-Fi hotspot, try reconnecting the power/USB cable to reset the ESP

  Put a large capacitor(or even better, several small ones) between 5V/VIN and Ground to improve reliability

  Remember to install the CH340G drivers.

  Board settings:
  -NodeMCU 1.0(ESP-12E)
  -160MHz
  -921600
  -4M(3M)
 */

#include <Arduino.h>
#include <Scheduler.h>

const int ledPinESP =  D4;// LED on ESP on pin D4(Must call D4 in code)
const int ledPinBoard =  D0; // LED on board on pin D0(Must call D0 in code)

class PrintTask : public Task {
  protected:
    void loop()  {
      Serial.println(F("Print Loop Start"));
      delay(5000);
      Serial.println(F("Print Loop End"));
      delay(5000);
    }
} print_task;

class BlinkTask : public Task {
  protected:
    void setup() {
      state = HIGH;
      pinMode(ledPinBoard, OUTPUT);
      pinMode(ledPinBoard, state);
    }
    void loop() {
      state = state == HIGH ? LOW : HIGH;
      pinMode(ledPinBoard, state);

      delay(1000);
    }
  private:
    uint8_t state;
} blink_task;

class MemTask : public Task {
  public:
    void loop() {
      Serial.print(F("Free Heap: "));
      Serial.print(ESP.getFreeHeap());
      Serial.println(F(" bytes"));

      delay(10000);
    }
} mem_task;

void setup() {
  delay(2000); // Wait some time, in order to allow ESP8266 to boot
  Serial.begin(250000);
  delay(100); // Some time for serial buffer to empty

  Serial.println("");
  Serial.println("Started scheduler program");

  Scheduler.start(&print_task);
  Scheduler.start(&blink_task);
  Scheduler.start(&mem_task);

  Scheduler.begin();
}

void loop() {}
