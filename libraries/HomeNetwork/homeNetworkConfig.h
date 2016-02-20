// Set delay between retries & # of retries for a "radio.write" command. Need to run "network.txTimeout = 0;" before radio.setRetries() work
// REMOVE THESE BECAUSE ITS AUTOMATICALLY SET BY NETWORK, USE TXTIMEOUT VARIABLE INSTEAD(LOOK BELOW)
//#define HOME_SETTING_RETRY_DELAY 15 // How long to wait between each retry, in multiples of 250us, max is 15.  0 means 250us, 15 means 4000us
//#define HOME_SETTING_RETRY_TIMES 15 // Max 15 retries in library


// Avaliable commands: RF24_PA_MIN,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
// For RF24_PA_MAX a 100uF capacitor is needed!
#define HOME_SETTING_POWERAMPLIFIERLEVEL RF24_PA_MAX

#define HOME_SETTING_DATARATE RF24_2MBPS  // Set data rate to 250kpbs(other settings: RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), lower datarate=better signal
#define HOME_SETTING_CHANNEL 90 // Default Home network is using channel 90, dont know other channels though

// Tweaks optimized for compatability, reliability, driftsecurity and at least performance for Prince home IOT network
// Tweak however you want though
// Possible scenarios to consider, Nodes too far from each other(too high ping and too low variables times out the sending program), receiver node is offline(and you dont want transmitter node to freeze too long because of too high timeouttime/retries)
// Keep scenarios in mind to find perfect tweaks.
#define HOME_SETTING_SENDTIMEOUT 50 // Set the tx timeout for built-in tx retries in module(milliseconds), set it to at least 50ms, any shorter than that and sending messages will garantee to fail.
#define HOME_SETTING_ACK_CHECKTIME 1 // How often to check if a ACK-message has been received after sending either command or question
#define HOME_SETTING_DEFAULT_ACK_TIMEOUT 50 // The amount of time to wait for a confirmation after sending command(A very fast node can take minimum 50ms to respond, make sure its at least that)
#define HOME_SETTING_DEFAULT_SEND_TRIES 2 // The amount of times to try and send a message where its ACK-message failed to be received. Should be at least 2 to be safe, because sometimes sending actually fails for some reason.
#define HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE 20 // How often to auto-update the RF24 Home Network(polling time)

/*************************************************************************************************************************************
GLOBAL MESSAGE TYPES
Message type' is packet within the header of a message, it is read by
the receiver to understand what type of packet it is.
These message types can be used by all nodes when communicating with each other.
*************************************************************************************************************************************/
#define HOME_TYPE_COMMAND 'A' // Simple command(a number), which is a message and sender IS EXPECTED to get an ack-response back
#define HOME_TYPE_COMMAND_FAST 'C' // Simple command(a number), which is a message and NO NEED to return an ack-response back
//#define HOME_TYPE_MESSAGE 'A //TODO MESSAGE TYPE. A message(todo: maybe a string, char array that is max 32 bits(biggest message size))
//#define HOME_TYPE_QUESTION 'D'
//#define HOME_TYPE_QUESTION_FAST 'E'
//#define HOME_TYPE_ANSWER 'F'
/*************************************************************************************************************************************/
