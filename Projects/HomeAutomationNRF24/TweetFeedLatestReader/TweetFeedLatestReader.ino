/* Setup shield-specific #include statements */
#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Temboo.h>
#include "TembooAccount.h" // Contains Temboo account information

byte ethernetMACAddress[] = ETHERNET_SHIELD_MAC;
EthernetClient client;

// We limit this so you won't use all of your Temboo calls while testing
int maxCalls = 10;

// The number of times this Choreo has been run so far in this sketch
int calls = 0;
int outputPin = 6;

String lastID = "";
String newID = "";

void setup() {
  Serial.begin(9600);

  // For debugging, wait until the serial console is connected
  delay(4000);
  while (!Serial);

  Serial.print("DHCP:");
  if (Ethernet.begin(ethernetMACAddress) == 0) {
    Serial.println("FAIL");
    while (true);
  }
  Serial.println("OK");
  delay(5000);

  // Initialize pins
  pinMode(outputPin, OUTPUT);

  Serial.println("Setup complete.\n");
}

void loop() {
  if (calls < maxCalls) {
    Serial.print("Checking twitter feed... ");
    runUserTimelineLatestTweet();
    calls++;
  } else {
    Serial.println("Skipping to save Temboo calls. Adjust maxCalls as required.");
  }
  delay(5000);
}

void runUserTimelineLatestTweet() {
  TembooChoreo UserTimelineLatestTweetChoreo(client);

  // Set Temboo account credentials
  UserTimelineLatestTweetChoreo.setAccountName(TEMBOO_ACCOUNT);
  UserTimelineLatestTweetChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  UserTimelineLatestTweetChoreo.setAppKey(TEMBOO_APP_KEY);

  // Set profile to use for execution
  UserTimelineLatestTweetChoreo.setProfile("TwitterArduino");
  // Identify the Choreo to run
  UserTimelineLatestTweetChoreo.setChoreo("/Library/Twitter/Timelines/UserTimelineLatestTweet");

  // Run the Choreo
  unsigned int returnCode = UserTimelineLatestTweetChoreo.run();

  bool alreadyRead = false;
  String dataText = "";

  // A return code of zero means everything worked
  if (returnCode == 0) {
    while (UserTimelineLatestTweetChoreo.available()) {
      String name = UserTimelineLatestTweetChoreo.readStringUntil('\x1F');
      name.trim();

      String data = UserTimelineLatestTweetChoreo.readStringUntil('\x1E');
      data.trim();

      if (name == "ID") {
        if (data == lastID) {
          alreadyRead = true;
          Serial.println("Already read tweet");
        } else {
          lastID = data;
          Serial.print("Havent read tweet... ");
        }
      } else if (name == "Text") {
        dataText = data;
      }
    }
  }

  if (!alreadyRead) {
    if (dataText.indexOf("room") >= 0) {
      Serial.println("Room lights!");
    } else {
      Serial.print("Unknown command: ");
      Serial.println(dataText);
    }
  }

  alreadyRead = false;

  UserTimelineLatestTweetChoreo.close();
}
