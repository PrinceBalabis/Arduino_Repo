/**   Addresses/Topology                           Node Numbers  (To simplify address assignment in this demonstration)
 *           00                  - Master Node         ( 0 )
 *         01  02                - 1st Level children ( 1,2 )
 *  32 22 12    15 25 35 45    - 2nd Level children (7,5,3-4,6,8)
 */
const uint16_t node00 = 00; // Master Node

const uint16_t node01 = 01; // 1st level child
const uint16_t node011 = 011; // 2nd level child of 01
const uint16_t node021 = 021; // 2nd level child of 01

const uint16_t node02 = 02; // 1st level child
const uint16_t node012 = 012; // 2nd level child of 02
const uint16_t node022 = 022; // 2nd level child of 02

// This is the nodeID of this Arduino.
// WARNING! DONT FORGET TO SET UNIQUE NODE ID IN config.h FOR EACH NODE!
const uint16_t nodeID = node02 ;

// Tweaks optimized for compatability, reliability and driftsecurity
const uint8_t retryDelay = 5;
const uint8_t retryTimes = 15;
const uint8_t powerAmplifierLevel = RF24_PA_HIGH;
const rf24_datarate_e dataRate = RF24_250KBPS;


/**
 * ----------DEMO AREA----------
 */
// Set the preferred of this node role for the demo.
// if isSender is set as 1 - then the role of this node is sender
// if isSender is set as 0 - then the role of this node is receiver
const int isSender = 1 ; 
const long interval = 2000; // How often should it send the message?(ms)
int32_t msgContent = 01; // random message to send to receiver
const uint16_t msgNode = node01; // node ID to send a message to
/**
 * ----------DEMO AREA----------
 */

