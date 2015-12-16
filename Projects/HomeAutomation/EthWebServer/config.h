#define SERVER_IP 192,168,1,16
#define SERVER_PORT 9500
// How much time to give the web browser to receive the data
#define CLIENT_SEND_TIME 100
#define SERVER_BOOT_TIME 5000

#define TWI_CHECK_DELAY 1000
#define TWI_SLAVE_ID 1
#define TWI_BOOT_TIME SERVER_BOOT_TIME+2000

// Webserver Commands
#define CMD_MAINLIGHTS_TOGGLE 1 // Toggle mainlights
#define QSN_MAINLIGHTS_STATUS 2 // Ask mainlights status
#define CMD_APARTMENT_SHUTDOWN 3 // Shutdown Apartment
#define CMD_APARTMENT_STARTUP 4 // Startup Apartment
#define CMD_APARTMENT_TOGGLE 5 // Toggle Apartment
#define CMD_SPEAKER_MUTE_TOGGLE 6 // Toggle speaker mute
#define CMD_SPEAKER_MODE_TOGGLE 7 // Toggle speaker mode
#define CMD_PAINTINGLIGHTS_TOGGLE 8 // Toggle Painting Lights 
#define CMD_APARTMENT_MOOD_TOGGLE 9 // Toggle Apartment mood
