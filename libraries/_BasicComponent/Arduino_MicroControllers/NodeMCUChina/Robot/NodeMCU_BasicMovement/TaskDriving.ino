class DrivingTask : public Task {
  protected:
    void setup() {
      //Initialize H-Bridge
      pinMode(en1Motor, OUTPUT);
      pinMode(en2Motor, OUTPUT);
      pinMode(aMotor, OUTPUT);
      pinMode(bMotor, OUTPUT);
      pinMode(cMotor, OUTPUT);
      pinMode(dMotor, OUTPUT);
      setMovement(SHUT_MOTORS); // Turn off motors
      setMovement(FLOAT); // Set movement to float
      Serial.println(F("Motors are idle and waiting"));

      taskDrivingStarted = 1;
    }
    void loop() {
      currentMillis = millis();

      if (currentMillis - previousMillis >= interval && motorPowerState) {
        previousMillis = currentMillis;

        // Cycle through each movement
        chosenMovement++;

        if (chosenMovement > 4)
          chosenMovement = 0;

        setMovement(chosenMovement);
        lastPowerState = 1;
      }
      else if (!motorPowerState && lastPowerState) {
        setMovement(STOP);
        if (chosenMovement > 1)
          chosenMovement--; // Rewind a movement to be able to continue again
        previousMillis = 0; // Set to 0 in able to cycle to a new movenet as soon as it continues
        lastPowerState = 0;
      }

      delay(50);
    }
  private:
    unsigned long currentMillis;
    unsigned long previousMillis = 0;
    const long interval = 2000;
    int chosenMovement = 0;
    boolean lastPowerState = 0;

    enum Moves
    {
      STOP = 0,
      FORWARD = 1,
      TURN_RIGHT = 2,
      TURN_LEFT = 3,
      ROTATE_RIGHT = 4,
      ROTATE_LEFT = 5,
      BACKWARDS = 6,
      SHUT_MOTORS = 7,
      START_MOTORS = 8,
      FLOAT = 9
    };

    void setMovement(int movement) {
      switch (movement)
      {
        case STOP:
          Serial.println(F("Breaks"));
          digitalWrite(aMotor, HIGH);
          digitalWrite(bMotor, HIGH);
          digitalWrite(cMotor, HIGH);
          digitalWrite(dMotor, HIGH);
          break;
        case FORWARD:
          Serial.println(F("Forward"));
          digitalWrite(aMotor, HIGH);
          digitalWrite(bMotor, LOW);
          digitalWrite(cMotor, HIGH);
          digitalWrite(dMotor, LOW);
          break;
        case TURN_RIGHT:
          Serial.println(F("Right turn")); // Soft right turn, break right motor
          digitalWrite(aMotor, HIGH);
          digitalWrite(bMotor, HIGH);
          digitalWrite(cMotor, HIGH);
          digitalWrite(dMotor, LOW);
          break;
        case TURN_LEFT:
          Serial.println(F("Left turn")); // Soft left, break left motor
          digitalWrite(aMotor, HIGH);
          digitalWrite(bMotor, LOW);
          digitalWrite(cMotor, HIGH);
          digitalWrite(dMotor, HIGH);
          break;
        case ROTATE_RIGHT:
          Serial.println(F("Rotate right")); // Hard right
          digitalWrite(aMotor, LOW);
          digitalWrite(bMotor, HIGH);
          digitalWrite(cMotor, HIGH);
          digitalWrite(dMotor, LOW);
          break;
        case ROTATE_LEFT:
          Serial.println(F("Rotate left")); // Hard left
          digitalWrite(aMotor, HIGH);
          digitalWrite(bMotor, LOW);
          digitalWrite(cMotor, LOW);
          digitalWrite(dMotor, HIGH);
          break;
        case BACKWARDS:
          Serial.println(F("Backwards"));
          digitalWrite(aMotor, LOW);
          digitalWrite(bMotor, HIGH);
          digitalWrite(cMotor, LOW);
          digitalWrite(dMotor, HIGH);
          break;
        case SHUT_MOTORS:
          Serial.println(F("Shut down motors"));
          digitalWrite(en1Motor, LOW); // Disable motor 1 (Right motor)
          digitalWrite(en2Motor, LOW); // Disable motor 2 (Left motor)
          break;
        case START_MOTORS:
          Serial.println(F("Start motors"));
          digitalWrite(en1Motor, HIGH); // Enable motor 1 (Right motor)
          digitalWrite(en2Motor, HIGH); // Enable motor 2 (Left motor)
          break;
        case FLOAT:
          Serial.println(F("Floating / Coasting"));
          digitalWrite(aMotor, LOW);
          digitalWrite(bMotor, LOW);
          digitalWrite(cMotor, LOW);
          digitalWrite(dMotor, LOW);
          break;
      }
    }
} driving_task;
