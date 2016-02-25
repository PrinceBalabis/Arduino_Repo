#ifndef __HOMENETWORK_H__
#define __HOMENETWORK_H__

/*
HomeNetwork.h - Library for Prince Home Automation & IOT network of RF24 nodes
*/
#include "RF24.h"
#include "RF24Network.h"
#include "nodesConfig.h"

class RF24;
class RF24Network;

class HomeNetwork
{
public:

	/*****************************************************************************************
	PUBLIC FUNCTIONS START
	*****************************************************************************************/
	/*
	Function which runs when this class is objectified. Pointer-objects in parameter is saved locally to be easily accessed from this class.
	*/
	HomeNetwork(RF24& _radio, RF24Network& _network);
	/*
	Start the NRF24 Home Network and make it LIVE
	*/
	void begin(uint16_t nodeID, void (* _pmsgReceivedF)(uint16_t, unsigned char, int32_t));

	/*
	How often to auto-update the RF24 Home Network(polling time)
	*/
	bool setNetworkUpdateTime(int8_t _homeNetwork_autoUpdateTime);
	/*
	Enable or disable network auto-updates. Need to disable auto-update when sending messages or questions and expecting to receive specific
	messages. Re-enable again to listen for messages received.
	*/
	void setNetworkUpdateStatus(bool status);
	/*
	Enable or disable debug mode. Prints more detailed network message information.
	*/
	void setDebug(bool status);

	/*
	This function sends a message and gets an ACK-message back
	Returns if the message was sent successfully.
	*/
	bool send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType);
	/*
	Similar to the previous send(), but here you can specify how many retries to send the message before giving up.
	Returns if the message was sent successfully.
	*/
	bool send(uint16_t msgReceiver, int32_t msgContent, unsigned char msgType, uint8_t sendTries);
	/*
	Sends a command.
	Returns if the message was sent successfully.
	*/
	bool sendCommand(uint16_t msgReceiver, int32_t msgContent);
	/*
	Similar to the previous sendCommand(), but here you can specify how many retries to send the message before giving up.
	Returns if the message was sent successfully.
	*/
	bool sendCommand(uint16_t msgReceiver, int32_t msgContent, uint8_t sendTries);
	/*
	Sends a question. Specify a int32_t pointer in the paramter to which the answer to the question should be stored
	Returns if the message was sent successfully.
	*/
	bool sendQuestion(uint16_t msgReceiver, int32_t msgContent, int32_t *pmsgResponse, uint16_t answerTimeout);

	/*
	Function which is ran to send an answer to a question received from another node. Important to run this as fast as possible after receiving a question,
	as the other node will be waiting for the answer.
	*/
	void sendAnswer(uint16_t _msgSender, int32_t _ResponseData);

	/*
	Function needs to be executed in a thread in the Sketch. Execution will be stuck infinitely in this thread.
	This function must be run in order for home network to function properly.
	*/
	void update();

	/*****************************************************************************************
	PUBLIC FUNCTIONS END
	*****************************************************************************************/
private:
	RF24& radio;
	RF24Network& network;
	void (* pmsgReceivedF)(uint16_t, unsigned char, int32_t);

	bool autoUpdateStatus = true;
	bool currentAutoUpdateStatus = true;
	bool debug = false;
	unsigned long previousArrendID[3] = {0, 0, 0};

	int8_t homeNetwork_autoUpdateTime;

	// Structure of our payload
	struct payload_t {
		int32_t msgContent;
		unsigned long arrendID;
	};


	// Variables used for send/receive functions, declared here so variables wont be using child thread stack but stack from main thread.
	RF24NetworkHeader readHeader;
	payload_t payload;
	unsigned long startTime;
	unsigned long arrendID;
	unsigned long arrendIDReceived;
	RF24NetworkHeader header;
	bool toggleUpdateStatus;

};
#endif
