/*
  ---------------------------------------------------------------
  Keypad class declaration
  Reads the keypad and runs the appropiate commands

  Notes:
  WiFi.status()-function does not properly work with scheduler. So we had to make up another way to setup WiFi
  Most of the Serial.println in loop() is commented out because its so slow it holds the other tasks waiting
  ---------------------------------------------------------------
*/
class HTTPTask : public Task {
  protected:
    void setup() {
      Serial.println(F("Starting HTTP Task..."));
    }

    void loop()  {
      
      yield(); // Allow other essential backgrund tasks to run
      delay(httpExeutionFrequency); // Frequency to check if HTTP request should run
      sendGETRequestPing = 1; // RUN THE TEST
    }

  private:

} http_task;

