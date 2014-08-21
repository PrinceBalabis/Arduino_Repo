/*
 First this client sends a hello-message to server, in the hello
 message is the identification of the client. This tells the server that
 this client just got online and is switched off
*/

RCSwitch myClient = RCSwitch();

static void vRFCommTask(void *pvParameters) {
  myClient.enableReceive(0); // Receiver on inerrupt 0 => that is pin #2
  myClient.enableTransmit(10); // Transmitter is connected to Arduino Pin #10

  // Send Hello-message to server
  myClient.send(clientIDNumber, 24); //
  vTaskDelay((500L * configTICK_RATE_HZ) / 1000L);

  while (1) {
    if (myClient.available()) {
      int value = myClient.getReceivedValue();

      Serial.print("Received ");
      Serial.print( myClient.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( myClient.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( myClient.getReceivedProtocol() );

      myClient.resetAvailable();
    }
  }
}
