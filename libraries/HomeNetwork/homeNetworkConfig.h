// Set delay between retries & # of retries for a "radio.write" command. Need to run "network.txTimeout = 0;" before radio.setRetries() work
#define HOME_SETTING_RETRY_DELAY 15 // How long to wait between each retry, in multiples of 250us, max is 15.  0 means 250us, 15 means 4000us
#define HOME_SETTING_RETRY_TIMES 15 // Max 15 retries in library

// Avaliable commands: RF24_PA_MIN,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
// For RF24_PA_MAX a 100uF capacitor is needed!
#define HOME_SETTING_POWERAMPLIFIERLEVEL RF24_PA_MAX

#define HOME_SETTING_DATARATE RF24_2MBPS  // Set data rate to 250kpbs(other settings: RF24_250KBPS, RF24_1MBPS, RF24_2MBPS)
#define HOME_SETTING_CHANNEL 90 // Default Home network is using channel 90, dont know other channels though

// Tweaks optimized for compatability, reliability, driftsecurity and at least performance for Prince home IOT network
// Tweak however you want though
#define HOME_SETTING_DEFAULT_TIMEOUT_CONFIRMATION 100 // The amount of time to wait for a confirmation after sending command(A very fast node can take minimum 100ms to respond, make sure its at least that)
#define HOME_SETTING_DEFAULT_SPAM_CONFIRMATION_TIMES 5 // The amount of times to spam confirmation return message in order to make sure the confirmation message is received. Too low and the confirmation message maybe wont reach, too many and it will be overkill and block other communications!
#define HOME_SETTING_DEFAULT_SPAM_ANSWER_TIMES 5 // The amount of times to spam answer return message in order to make sure the answer message is received. Too low and the confirmation message maybe wont reach, too many and it will be overkill and block other communications!
#define HOME_SETTING_DEFAULT_TIMEOUT_ANSWER 300 // The amount of time to wait for an answer after sending question
#define HOME_SETTING_DEFAULT_TIME_READ 1 // How often to check if a confirmation or answer has been received after sending either command or question
#define HOME_SETTING_DEFAULT_TIME_NETWORKAUTOUPDATE 5 // How often to update the RF24 Home Network
