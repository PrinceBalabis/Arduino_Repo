// Tweaks optimized for compatability, reliability and driftsecurity for Prince home IOT network
// Tweak however you want though

const unsigned int homeNetwork_timeoutSendTime = 200; // Amount of time before trying to resend message again to node
const unsigned int homeNetwork_timeoutAnswerTime = 400; // Amount of time to wait until given up waiting of answer to question
const unsigned int homeNetwork_autoUpdateTime = 20; // How often the network is updated

// Set delay between retries & # of retries for a "radio.write" command
const uint8_t homeNetwork_retryDelay = 5;
const uint8_t homeNetwork_retryTimes = 15;

const uint8_t homeNetwork_powerAmplifierLevel = RF24_PA_MAX;  // Set power amplifier to highest
const rf24_datarate_e homeNetwork_dataRate = RF24_250KBPS;  // Set data rate to 250kpbs(other settings: RF24_1MBPS, RF24_2MBPS)

const uint8_t homeNetwork_channel = 90; // Default Home network is using channel 90
