class DrivingTask : public Task {
  protected:
    void setup() {
      Serial.println(F("Motors are idle and waiting"));

      taskDrivingStarted = 1;
    }
    void loop() {
      currentMillis = millis();

      if (currentMillis - previousMillis >= interval && motorPowerState) {
        previousMillis = currentMillis;

        // Cycle through each movement
        chosenMovement++;

        if (chosenMovement > 9)
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
          setRegisterPin(aMotor, HIGH);
          setRegisterPin(bMotor, HIGH);
          setRegisterPin(cMotor, HIGH);
          setRegisterPin(dMotor, HIGH);
          break;
        case FORWARD:
          Serial.println(F("Forward"));
          setRegisterPin(aMotor, HIGH);
          setRegisterPin(bMotor, LOW);
          setRegisterPin(cMotor, HIGH);
          setRegisterPin(dMotor, LOW);
          break;
        case TURN_RIGHT:
          Serial.println(F("Right turn")); // Soft right turn, break right motor
          setRegisterPin(aMotor, HIGH);
          setRegisterPin(bMotor, HIGH);
          setRegisterPin(cMotor, HIGH);
          setRegisterPin(dMotor, LOW);
          break;
        case TURN_LEFT:
          Serial.println(F("Left turn")); // Soft left, break left motor
          setRegisterPin(aMotor, HIGH);
          setRegisterPin(bMotor, LOW);
          setRegisterPin(cMotor, HIGH);
          setRegisterPin(dMotor, HIGH);
          break;
        case ROTATE_RIGHT:
          Serial.println(F("Rotate right")); // Hard right
          setRegisterPin(aMotor, LOW);
          setRegisterPin(bMotor, HIGH);
          setRegisterPin(cMotor, HIGH);
          setRegisterPin(dMotor, LOW);
          break;
        case ROTATE_LEFT:
          Serial.println(F("Rotate left")); // Hard left
          setRegisterPin(aMotor, HIGH);
          setRegisterPin(bMotor, LOW);
          setRegisterPin(cMotor, LOW);
          setRegisterPin(dMotor, HIGH);
          break;
        case BACKWARDS:
          Serial.println(F("Backwards"));
          setRegisterPin(aMotor, LOW);
          setRegisterPin(bMotor, HIGH);
          setRegisterPin(cMotor, LOW);
          setRegisterPin(dMotor, HIGH);
          break;
        case SHUT_MOTORS:
          Serial.println(F("Shut down motors"));
          setRegisterPin(en1Motor, LOW); // Disable motor 1 (Right motor)
          setRegisterPin(en2Motor, LOW); // Disable motor 2 (Left motor)
          break;
        case START_MOTORS:
          Serial.println(F("Start motors"));
          setRegisterPin(en1Motor, HIGH); // Enable motor 1 (Right motor)
          setRegisterPin(en2Motor, HIGH); // Enable motor 2 (Left motor)
          break;
        case FLOAT:
          Serial.println(F("Floating / Coasting"));
          setRegisterPin(aMotor, LOW);
          setRegisterPin(bMotor, LOW);
          setRegisterPin(cMotor, LOW);
          setRegisterPin(dMotor, LOW);
          break;
      }
      writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
    }
} driving_task;
