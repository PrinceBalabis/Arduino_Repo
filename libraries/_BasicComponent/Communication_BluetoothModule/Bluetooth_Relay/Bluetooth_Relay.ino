/*-------------------------------------------------------------
    Simple receiving/sending between bluetooth-connected deviced and Arduino serial monitor
  If you use the Tinysine bluetooth module HM-10, then use their app for testing to
  connect and send/receive data, which you can get
  From their HM-10 product page. You can also download the source-code for their app
  To make your own version for custom functions.


  Setting up Bluetooth configuration
  - Connect Blueooth module to Serial-to-USB adapter
  - Open Arduino Serial Monitor
  - Set to "No line ending" & 9600 baud(9600 baud is default but try 38400 or 115200 if that didnt work)
  - Send "AT" twice to test if AT commands work

  Setup TinySine bluetooth module with the Windows program which can be downloaded on their site: https://www.tinyosshop.com/bluetooth-ble-module-ibeacon
  Press Factory Set and it should work out of the box

  Connect Bluetooth module to Arduino
  Connect the bluetooth module RX pin to Arduino TX pin
  Connect the bluetooth module TX pin to Arduino RX pin

  Default bluetooth password is 000000
*/

//-------------------------------------------------------------
// Configuration
//-------------------------------------------------------------
// The configured serial rate of the bluetooth module
const int bluetoothSerialRate = 9600;

// Serial rate between computer and arduino
const int arduinoSerialRate = 9600;

// The delay between serial commands
const int delayBetweenATCommands = 1000;

// Timeout. Time before giving up on waiting for new character in buffer (milliseconds). With OnePlus 5T+Tinysine+9600baud, timeout= 10ms seems to work fine(could maybe go lower)
const long timeout = 5;

//-------------------------------------------------------------
// Includes
//-------------------------------------------------------------


//-------------------------------------------------------------
// Logic
//-------------------------------------------------------------
String readString = "";
unsigned long currentMillis = 0; // To store current time
unsigned long previousReceivedBufferedMessageMillis = 0; // To store last time character was received from buffer

//-------------------------------------------------------------
// Setup
//-------------------------------------------------------------
void setup()
{
  delay(6000); // Give Bluetooth module some time to initialize

  Serial.begin(arduinoSerialRate); // Open serial communications
  while (!Serial);// FOR DEBUGGING ONLY. REMOVE FOR LIVE VERSION. Wait for serial port to connect. (Arduino will idle until serial communication is established)
  delay(500); // Let capacitors stabilize

  Serial.println("Welcome to Testing Bluetooth Sketch!");

  // Initialize Bluetooth
  initBluetooth();

  Serial.println("Started Testing Mode for bluetooth...");
  Serial.println("Idle...");
}

//-------------------------------------------------------------
// Loop
//-------------------------------------------------------------
void loop()
{
  if (Serial1.available()) { // Received message from blueooth
    Serial.println("Received message from bluetooth, starting to receive");
    readString += (char) Serial1.read(); // Save one byte from serial buffer
    currentMillis = millis(); // Update current time
    previousReceivedBufferedMessageMillis = millis(); // Update current time
    //Serial.println("Check if there are several characters and start receiving all of them");
    while (true) // A timeout function, which if it detects a new character then it continues reading, but if it reaches timeout it assumes there are no more messagse
    {
      currentMillis = millis(); // Update current time
      if (currentMillis - previousReceivedBufferedMessageMillis >= timeout) { // Timeout reached since last character, stop waiting for more
        //Serial.println("Timeout waiting for new characters, jumping out of while loop");
        break; // Break out of "while(true)"-loop
      }
      if (Serial1.available()) { // Check if there are any message available, then save
        //Serial.println("Saving next character");
        readString += (char) Serial1.read(); // Saves one byte from serial buffer
        previousReceivedBufferedMessageMillis = currentMillis; // Reset timeout start-point
      }
      delay(1); // Some delay in between checks
      //Serial.println("Repeating loop again..."); // Great way to check how long time between receiving each character
    } // End while (true)
    Serial.print("Received: ");
    Serial.println(readString); // print the message from bluetooth
    readString = ""; // clean the buffer string for a new message
    //Serial.println("Finished receiving message!");
  } // End if (Serial1.available()) {

  if (Serial.available()) { // Received message from serial
    Serial.println("Received message from serial, starting to receive");
    readString += (char) Serial.read(); // Save one byte from serial buffer
    currentMillis = millis(); // Update current time
    previousReceivedBufferedMessageMillis = millis(); // Update current time
    //Serial.println("Check if there are several characters and start receiving all of them");
    while (true) // A timeout function, which if it detects a new character then it continues reading, but if it reaches timeout it assumes there are no more messagse
    {
      currentMillis = millis(); // Update current time
      if (currentMillis - previousReceivedBufferedMessageMillis >= timeout) { // Timeout reached since last character, stop waiting for more
        //Serial.println("Timeout waiting for new characters, jumping out of while loop");
        break; // Break out of "while(true)"-loop
      }
      if (Serial.available()) { // Check if there are any message available, then save
        //Serial.println("Saving next character");
        readString += (char) Serial.read(); // Saves one byte from serial buffer
        previousReceivedBufferedMessageMillis = currentMillis; // Reset timeout start-point
      }
      delay(1); // Some delay in between checks
      //Serial.println("Repeating loop again..."); // Great way to check how long time between receiving each character
    } // End while (true)
    Serial.print("Sent: ");
    Serial.println(readString); // print the message from serial which is to be sent to bluetooth
    Serial1.print(readString);
    Serial1.print("\r\n");

    readString = ""; // clean the buffer string for a new message
    //Serial.println("Finished receiving message!");
  } // End if (Serial.available()) {
  //Serial.println("Looping..."); // Looping diagnostic message
}


//-------------------------------------------------------------
// initBluetooth
//-------------------------------------------------------------
void initBluetooth() {
  Serial.println("Initializing Bluetooth module...");
  delay(500); // Let capacitors stabilize
  Serial1.begin(bluetoothSerialRate); // set the data rate for the SoftwareSerial port connected to the bluetooth module
  delay(1000); // Let capacitors stabilize
  while (Serial1.available()) { // Throw out any start-messages
    Serial1.read(); // Dump serial
  }
  while (Serial.available()) { // Throw out any start-messages
    Serial.read(); // Dump serial
  }
  delay(500); // Let capacitors stabilize
} // End initBluetooth();


