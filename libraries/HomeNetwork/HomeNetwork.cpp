/**
*  HomeNetwork.cpp
* BE CAREFUL WITH SERIAL PRINTS!
* Serial prints add delay to execution of code and can alter overall performance and stability of program.
*/

#include "HomeNetwork.h"
#include "homeNetworkConfig.h"
#include <NilRTOS.h>
#include <NilSerial.h>

HomeNetwork::HomeNetwork(RF24& _radio, RF24Network& _network): radio(_radio), network(_network)
{
}

void HomeNetwork::begin(uint16_t nodeID, void (* _pmsgReceivedF)(uint16_t, unsigned char, int32_t))
{
	delay(2000); //Give some time for capacitor to charge up and stabilize before initializing RF24 module!
	radio.begin(); // Initialize radio
	network.begin(HOME_SETTING_CHANNEL, nodeID); // Start mesh Network
	// Radio settings must be run after network.begin
	radio.setPALevel(HOME_SETTING_POWERAMPLIFIERLEVEL);
	radio.setDataRate(HOME_SETTING_DATARATE);
	radio.setRetries(0, 0); // Does not work properly, should be just set to 0,0.
	network.txTimeout = 1; // Timeout for send-retrying in netowrk, This should be 1 because this function is not reliable.

	//Clear all incoming queued messages that was received by RF24 module before Arduino completed boot
	// while(1){
	//   network.update(); // Check the network regularly for the entire network to function properly
	//   if(network.available()){
	//     read(NULL, NULL); // Destroy incoming messages
	//   } else {
	//     break;
	//   }
	//   chThdSleepMicroseconds(100); // Give system some time to run other stuff
	// }

	pmsgReceivedF = _pmsgReceivedF;
	homeNetwork_autoUpdateTime = HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE;
}

/*

*/
bool HomeNetwork::setNetworkUpdateTime(int8_t _homeNetwork_autoUpdateTime)
{
	if (_homeNetwork_autoUpdateTime < 0) { // If its a negative value, or outside the boundaries of int8_t, then set to default
		homeNetwork_autoUpdateTime = HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE;
		return true;
	} else {
		homeNetwork_autoUpdateTime = _homeNetwork_autoUpdateTime;
		return false;
	}
}

void HomeNetwork::update()
{
	while (1) {
		// Get stuck in this loop while its ment to be paused
		if (!autoUpdateStatus) {
			currentAutoUpdateStatus = false;
			while (!autoUpdateStatus) {
				nilThdSleepMilliseconds(1);  //Check if autoUpdate should unpause every few ms
			}
			currentAutoUpdateStatus = true;
		}

		network.update(); // Check the network regularly for the entire network to function properly
		if (network.available()) // When a message is received send incoming message to Sketch function, if its just a command, return an ack-message
		{
			// Save received header & payload of message

			network.read(readHeader, &payload, sizeof(payload));

			if (readHeader.type == HOME_TYPE_COMMAND) { //A Command w/ confirmation request
				// Send back ACK-message
				// Set receiver of message
				header = RF24NetworkHeader(readHeader.from_node, NULL);

				// network.write() function returns wether someone picked up a message,
				// doesn't have to be the node you are trying to send to,
				// but could be a parent node. So its not very useful.
				network.write(header, &payload.arrendID, sizeof(payload.arrendID));

				if (debug) {
					Serial.print(F("Got Command->ID:"));
					Serial.print(payload.arrendID);
					Serial.print(F("->Sent ACK->"));
				}

				if (previousArrendID[0] != payload.arrendID && previousArrendID[1] != payload.arrendID && previousArrendID[2] != payload.arrendID) {
					previousArrendID[0] = previousArrendID[1];
					previousArrendID[1] = previousArrendID[2];
					previousArrendID[2] = payload.arrendID; // Save this ArrendID to newest ArrendID storage
					pmsgReceivedF(readHeader.from_node, readHeader.type, payload.msgContent); // deliver message to Sketch
				} else {
					if (debug)
						Serial.print(F("ARREND ALREADY DONE, NOT FORWARDING TO SKETCH"));
				}
				Serial.println(F(""));
			} else if (readHeader.type ==  HOME_TYPE_QUESTION) { // A question
				// Send back ACK-message
				// Set receiver of message
				header = RF24NetworkHeader(readHeader.from_node, NULL);

				// network.write() function returns wether someone picked up a message,
				// doesn't have to be the node you are trying to send to,
				// but could be a parent node. So its not very useful.
				network.write(header, &payload.arrendID, sizeof(payload.arrendID));

				if (debug) {
					Serial.print(F("Got Question->ID:"));
					Serial.print(payload.arrendID);
					Serial.print(F("->"));
				}

				pmsgReceivedF(readHeader.from_node, HOME_TYPE_QUESTION, payload.msgContent); // deliver message to Sketch
			}
			else { // Useless spam or trash talk gets here
				if (debug)
					Serial.println(F("USELESS SPAM MESSAGE FILTERED OUT AND NOT SENT TO SKETCH"));
			}
		}

		nilThdSleepMilliseconds(homeNetwork_autoUpdateTime);  //Give other threads some time to run
	}
}

void HomeNetwork::setNetworkUpdateStatus(bool status)
{
	// set autoUpdate to either enabled or disabled
	autoUpdateStatus = status;

	if (status) {
		// Wait for autoUpdate to pause
		while (!currentAutoUpdateStatus) {
			nilThdSleepMilliseconds(1); // Check if autoUpdate status changed every few ms
		}
	}
}

void HomeNetwork::setDebug(bool status) {
	debug = status;
}

bool HomeNetwork::send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType, uint8_t sendTries)
{
	if (debug)
		Serial.print(F("send()->"));

	//Only toggle update status if its enabled. If its disabled, dont toggle network update.
	//This is needed so that sendQuestion() functions will work
	toggleUpdateStatus = false;
	if (autoUpdateStatus == true) {
		toggleUpdateStatus = true;
		setNetworkUpdateStatus(false); // Pause autoUpdate
	}

	// Set receiver of message
	header = RF24NetworkHeader(msgReceiver, msgType);

	arrendID = millis();
	//Create payload to send which contains message and message ID
	payload = { msgContent, arrendID };
	if (debug) {
		Serial.print(arrendID);
		Serial.print(F(":ID->"));
	}

	for (uint8_t i = 0 ; i < sendTries ; i++) {
		// network.write() function returns wether someone picked up a message,
		// doesn't have to be the node you are trying to send to,
		// could be a parent node, or any node in between. So its not very useful as "sent successful"-verification
		startTime = millis();
		network.write(header, &payload, sizeof(payload));
		if (debug) {
			Serial.print(millis() - startTime);
			Serial.print(F("ms SendTime->"));
		}
		// Wait for response, when received read the payload and send back ack. Gets stuck in getAnswer() function either until
		// response is received or timed out waiting for response.
		startTime = millis();

		while (1) {
			network.update(); // Check the network regularly for the entire network to function properly

			if (millis() - startTime > HOME_SETTING_DEFAULT_ACK_TIMEOUT) { //Timed out, break out of "check incoming messages"-loop
				if (debug)
					Serial.print(F("ACK TIMEOUT->"));
				break;
			}
			if (network.available()) // When a message is finally received before timing out
			{
				// Save received message content
				network.read(readHeader, &arrendIDReceived, sizeof(arrendIDReceived));

				// Check if ACK message has correct arrendID
				if (arrendID == arrendIDReceived) {
					if (debug) {
						Serial.print(F("Got ACK:"));
						Serial.print(millis() - startTime);
						Serial.print(F("ms->"));
					}
					if (toggleUpdateStatus == true) {
						setNetworkUpdateStatus(true); // Resume autoUpdate
					}
					return true;
				} else {
					if (debug) {
						Serial.print(F("WRONG ACK,GOT: "));
						Serial.print(arrendIDReceived);
						Serial.print(F("->"));
						Serial.print(F("STILL WAITING FOR ACK->"));
					}
				}
			}
			nilThdSleepMilliseconds(HOME_SETTING_ACK_CHECKTIME); // Check every few ms if response-message is received
		}
		if (debug)
			Serial.print(F("RETRYING->"));
	}
	if (debug)
		Serial.print(F("FAILED TO SEND, OUT OF RETRIES->"));
	if (toggleUpdateStatus == true) {
		setNetworkUpdateStatus(true); // Resume autoUpdate
	}
	return false;
}

// This function acts as a default send function but with default retry time and timeout
bool HomeNetwork::send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType) {
	return send(msgReceiver, msgContent, msgType, HOME_SETTING_DEFAULT_SEND_TRIES);
}

bool HomeNetwork::sendCommand(uint16_t msgReceiver, int32_t msgContent) {
	if (debug)
		Serial.print(F("sendCommand()->"));
	return send(msgReceiver, msgContent, HOME_TYPE_COMMAND);
}

bool HomeNetwork::sendCommand(uint16_t msgReceiver, int32_t msgContent, uint8_t sendTries) {
	if (debug)
		Serial.print(F("sendCommand()->"));
	return send(msgReceiver, msgContent, HOME_TYPE_COMMAND, sendTries);
}

/**
* sendQuestion
* This function sends a question to a receiver, both which are set in parameter
* A response is expected
* returns whether answer was received or not
**/
bool HomeNetwork::sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse, uint16_t answerTimeout) {
	setNetworkUpdateStatus(false); // Pause autoUpdate

	if (debug)
		Serial.print(F("sendQuestion()->"));

	// Send question
	for (uint8_t i = 0; i < HOME_SETTING_DEFAULT_SEND_TRIES; i++) {
		if (debug)
			Serial.print(F("Send-try->"));
		if (send(msgReceiver, msgContent, HOME_TYPE_QUESTION, HOME_SETTING_DEFAULT_SEND_TRIES)) { // Send question, and wait for answer only if question was successfully sent
			Serial.print(F("Question Sent->"));

			startTime = millis();
			while (1) {
				network.update(); // Check the network regularly for the entire network to function properly
				if (millis() - startTime > answerTimeout) { //Timed out, break out of "check incoming messages"-loop
					if (debug)
						Serial.print(F("ANSWER TIME OUT!->"));
					break;
				}
				if (network.available()) // When a message is finally received before timing out
				{
					// Save received message content
					network.read(readHeader, &payload, sizeof(payload));

					// Check if answer message comes from correct node
					if (msgReceiver == readHeader.from_node) {
						if (debug)
							Serial.print(F("Got Answer->"));

						*pmsgResponse = payload.msgContent; // Save the answer
						setNetworkUpdateStatus(true); // Resume autoUpdate
						return true;
					} else {
						if (debug) {
							Serial.print(F("FROM WRONG NODE->STILL WAITING FOR ANSWER->"));
						}
					}
				}
				nilThdSleepMilliseconds(HOME_SETTING_ACK_CHECKTIME); // Check every few ms if answer-message is received
			}
		} else {
			if (debug)
				Serial.print(F("RETRYING SENDING->"));
		}
	}
	Serial.print(F("COULDN'T GET ANSWER->"));

	setNetworkUpdateStatus(true); // Resume autoUpdate
	return false;
}

void HomeNetwork::respondToQuestion(uint16_t _msgSender, int32_t _ResponseData) {
	if (debug)
		Serial.print(F("respondToQuestion()->"));

	nilThdSleepMilliseconds(1);
	header = RF24NetworkHeader(_msgSender, NULL);
	payload = { _ResponseData, NULL };
	network.write(header, &payload, sizeof(payload));
}
