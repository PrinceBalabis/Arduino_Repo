//Set pin in the 2nd parameter
NewRemoteTransmitter transmitter(15303606, mhz433Pin, 260, 2);

void setPaintingLights(bool status) {
  if (status) { // Turn on
    transmitter.sendUnit(paintingLights_mhz433Code, status);
    Serial.println("Painting Lights are now on");
  } else { // Turn off
    transmitter.sendUnit(paintingLights_mhz433Code, status);
    Serial.println("Painting Lights are now off");
  }
  paintingLightsStatus = status; // Save status to fast RAM
}

void togglePaintingLights() {
  Serial.print("Toggling Painting Lights.. ");
  setPaintingLights(!paintingLightsStatus);
}

void setDeskLights(bool status) {
  if (status) { // Turn on
    transmitter.sendUnit(deskLights_mhz433Code, status);
    Serial.println("Desk Lights are now on");
  } else { // Turn off
    transmitter.sendUnit(deskLights_mhz433Code, status);
    Serial.println("Desk Lights are now off");
  }
  deskLightsStatus = status; // Save status to fast RAM
}

void toggleDeskLights() {
  Serial.print("Toggling Desk Lights.. ");
  setPaintingLights(!paintingLightsStatus);
}

