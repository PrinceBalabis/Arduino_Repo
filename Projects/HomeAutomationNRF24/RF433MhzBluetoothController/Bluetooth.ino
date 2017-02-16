
NIL_WORKING_AREA(bluetooth, 130); //65 bytes works great
NIL_THREAD(Bluetooth, arg)
{
  Serial.println(F("Started Bluetooth Thread"));

  Serial.println(F("Initializing Bluetooth Module.."));
  initBluetoothModule();

  while (1) {
    bluetoothModule.flush(); // Clear any trash data from bluetooth module
//    nilThdSleepMilliseconds(10); // Wait for module to think
//    Serial.print(F("Searching"));
//    bluetoothModule.print("AT+DISC?");
//
//    nilThdSleepMilliseconds(5000); // Wait for module to think
//    Serial.print(F("."));
//    while (bluetoothModule.available()) { // When the list of close bluetooth devices is printed, then continue
//      serialBuffer = bluetoothModule.readString();
//    }
//    Serial.print(F("."));
serialBuffer = "dfgdfg";
    Serial.print(serialBuffer);

    //    while (serialBuffer.indexOf("DISCE") != -1) { // Keep reading serial until DISCE is found
    //      while (bluetoothModule.available()) { // When the list of close bluetooth devices is printed, then continue
    //        serialBuffer = bluetoothModule.readString();
    //      }
    //    }



    //    Serial.print(F("Answer:"));
    //    if (bluetoothModule.find("2A1B4")) {
    //      Serial.println(F("Prince is home"));
    //    } else {
    //      Serial.println(F("My master is not home"));
    //    }

    //    while (bluetoothModule.available())
    //      Serial.write(bluetoothModule.read());
    Serial.println(F("...OK..."));

    nilThdSleepMilliseconds(1000); // Redo the search every few seconds
  }
}

void initBluetoothModule() {
  Serial.print(F("Testing communication with module..."));

  // Test if the communication is working
  // Run AT twice because the first time doesn't reply with a OK-message if the module has been rebooted
  bluetoothModule.print("AT");
  nilThdSleepMilliseconds(100);
  bluetoothModule.flush(); // Reading of first "AT"-answer not needed

  bluetoothModule.print("AT");
  nilThdSleepMilliseconds(100);
  //  if (bluetoothModule.available()) {
  if (bluetoothModule.read() == 'O') {
    Serial.println(F("Done"));
  } else {
    Serial.println(F("ERROR. FAILED!!\nRestarting Arduino...\n\n"));
    resetFunc();  //Reset Arduino
  }
  //  }

  Serial.println(F("Bluetooth initialized and ready"));
}

