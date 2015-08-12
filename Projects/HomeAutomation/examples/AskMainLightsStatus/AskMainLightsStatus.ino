#include <ChibiOS_AVR.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>
#include <HomeNetwork.h>
#include "config.h"

RF24 radio(RF24_PIN_CE, RF24_PIN_CSN);
RF24Network network(radio);
HomeNetwork homeNetwork(radio, network, &homeNetwork);

void setup() {
  Serial.begin(115200);
  Serial.println(F("Testing Node"));

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  chBegin(mainThread);
  // chBegin never returns, main thread continues with mainThread()

  while (1);
}

static WORKING_AREA(hNListenThread, 64);
static WORKING_AREA(commandExecutioner, 64);
static WORKING_AREA(exampleSendThread, 64);

void mainThread() {
  SPI.begin(); // SPI is used by homeNetwork
  homeNetwork.begin(NODEID);

  chThdCreateStatic(commandExecutioner, sizeof(commandExecutioner), NORMALPRIO + 2, CommandExecutioner, NULL);

  chThdCreateStatic(exampleSendThread, sizeof(exampleSendThread), NORMALPRIO + 1, ExampleSendThread, NULL);

  homeNetwork.setAutoUpdateTime(HOME_AUTOUPDATE_DELAY);

  Serial.println(F("System booted up!"));
  Serial.println(F("Listening for incoming home network messages... "));

  while (1) {
    // Pauses here until a message is received
    homeNetwork.waitForIncomingMessage();
    Serial.print(F("New Message.. "));

    //Get received message
    uint16_t msgSender;
    unsigned char msgType;
    int32_t msgContent;
    homeNetwork.getIncomingMessage(&msgSender, &msgType, &msgContent);

    switch (msgType) {
      case typeCommand: // If its a simple command
        Serial.print(F("Command"));
        //Send message to CommandExecutionerThread for decoding
        executeCommand(msgContent, COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK);
        break;
      case typeAsk: // If its a question
        Serial.print(F("Question"));
        decodeQuestion(&msgSender, &msgContent);
    }
  }
}

void loop() {
  // not used
}
