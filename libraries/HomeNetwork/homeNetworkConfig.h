// Set delay between retries & # of retries for a "radio.write" command
#define HOME_SETTING_RETRY_DELAY 2
#define HOME_SETTING_RETRY_TIMES 25

#define HOME_SETTING_POWERAMPLIFIERLEVEL RF24_PA_MAX   // Set power amplifier to highest
#define HOME_SETTING_DATARATE RF24_2MBPS  // Set data rate to 250kpbs(other settings: RF24_250KBPS, RF24_1MBPS, RF24_2MBPS)
#define HOME_SETTING_CHANNEL 90 // Default Home network is using channel 90, dont know other channels though

// Tweaks optimized for compatability, reliability, driftsecurity and at least performance for Prince home IOT network
// Tweak however you want though
#define HOME_SETTING_DEFAULT_TIMEOUT_SENDTIME 1000
#define HOME_SETTING_DEFAULT_TIMEOUT_ANSWERTIME 1000
#define HOME_SETTING_DEFAULT_AUTOUPDATETIME 5
