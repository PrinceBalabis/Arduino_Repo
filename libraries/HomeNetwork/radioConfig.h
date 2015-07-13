// Tweaks optimized for compatability, reliability and driftsecurity for home IOT network

const unsigned int timeoutSendTime = 200; // Amount of time before trying to resend message again to node

// Set delay between retries & # of retries for a "radio.write" command
const uint8_t retryDelay = 5;
const uint8_t retryTimes = 15;

const uint8_t powerAmplifierLevel = RF24_PA_HIGH;  // Set power amplifier to highest
const rf24_datarate_e dataRate = RF24_250KBPS;  // Set data rate to 250kpbs(other settings: RF24_1MBPS, RF24_2MBPS)

const uint8_t channel = 40; // Home network is using channel 90
