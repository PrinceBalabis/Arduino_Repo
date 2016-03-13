#define COMMANDEXECUTIONER_MSGORIGIN_HOMENETWORK 0
#define COMMANDEXECUTIONER_MSGORIGIN_KEYPAD 1

/*
   ------------------------------------
    TWI
    ------------------------------------
*/
#define TWI_SLAVE_ID 1
#define TWI_CHECK_TIME 50 // How often to check for new messages for HomeNetwork 
#define TWI_BOOT_TIME 5000


/*
   ------------------------------------
    Keypad Button reservations
    ------------------------------------
*/
// NextBase
#define BUTTON_SPEAKER_POWER '3'
#define BUTTON_SPEAKER_VOLUME_UP 'A'
#define BUTTON_SPEAKER_VOLUME_DOWN 'B'
#define BUTTON_SPEAKER_MUTE 'C'
#define BUTTON_SPEAKER_MODE 'D'
// Lights
#define BUTTON_MAINLIGHTS_TOGGLE '1'
#define BUTTON_PAINTINGLIGHTS_TOGGLE '4'
// PC Controller
#define BUTTON_PC_POWER '*'
#define BUTTON_PC_MONITOR_DISABLE '7'
/*
   ------------------------------------
    Keypad Performance
    ------------------------------------
*/
#define KEYPAD_UPDATE_TIME 50 // How often to update keypad reads in milliseconds, 20ms has worked perfectly for many months
#define KEYPAD_HOLD_UPDATE_TIME 150 // How often to repeat command when holding a button, in milliseconds

/*
   ------------------------------------
    FastDigitalIO for PC Power Switch
    ------------------------------------
*/
#define PC_POWER_SWITCH_PIN 4
#define PC_POWER_SWITCH_INIT (DDRD |= _BV(PC_POWER_SWITCH_PIN))
#define PC_POWER_SWITCH_ON (PORTD |= _BV(PC_POWER_SWITCH_PIN))
#define PC_POWER_SWITCH_OFF (PORTD &= ~_BV(PC_POWER_SWITCH_PIN))
#define PC_POWER_SWITCH_TOGGLE (PORTD ^= _BV(PC_POWER_SWITCH_PIN))

/*
   ------------------------------------
    FastDigitalIO for Audio Switch
    ------------------------------------
*/
#define AUDIO_SWITCH_PIN 3
#define AUDIO_SWITCH_INIT (DDRD |= _BV(AUDIO_SWITCH_PIN))
#define AUDIO_SWITCH_SPEAKER (PORTD |= _BV(AUDIO_SWITCH_PIN))
#define AUDIO_SWITCH_HEADSET (PORTD &= ~_BV(AUDIO_SWITCH_PIN))
#define AUDIO_SWITCH_GET_MODE (!((PIND & _BV(AUDIO_SWITCH_PIN)) > 0))

