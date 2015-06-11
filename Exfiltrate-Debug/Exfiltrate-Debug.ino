
/*
 Program by Systemic
 Based on following sources:
 
 Arduino
 FinalKey
 
 created   May 2015
 by Systemic
 modified 6 June 2015
 
 This code is in the public domain.
 	 
 */
 
/*
*************************
VARIABLES
*************************
*/

int capslockState = 0;         // current state of the capslock button
int numlockState = 0;         // current state of the numlock button
int scrolllockState = 0;         // current state of the scrolllock button


uint8_t keyboard_leds;		// KeyboardLeds 

/*
*************************
CONSTANT
*************************
*/

// Bit numbers for each led - used to make it easier later to know what you were actually testing for...
#define USB_LED_NUM_LOCK 0
#define USB_LED_CAPS_LOCK 1
#define USB_LED_SCROLL_LOCK 2
#define USB_LED_COMPOSE 3
#define USB_LED_KANA 4


/*
*************************
SETUP
*************************
*/

void setup()
{  
  // open serial port
  openserial();   
   
  delay(5000);                  // waits for 5 second
//    Serial.println("opening keyboard");
//    Serial.println("keyboard open");
}

/*
*************************
LOOP
*************************
*/


void loop()
{

/*
*************************
Caps Lock Detection
*************************
*/

keyboard_leds = Keyboard.getLedStatus();

if (keyboard_leds & (1<<USB_LED_CAPS_LOCK))
{
    // CapsLock is ON - put your "on" code here
    Serial.println("CAPS ON");
	capslockState = 1;
}
else
{
    // CapsLock is OFF - put your "off" code here
    Serial.println("CAPS OFF");
	capslockState = 0;
}

if (keyboard_leds & (1<<USB_LED_NUM_LOCK))
{
    // NumLock is ON - put your "on" code here
    Serial.println("NUMLOCK ON");
	numlockState = 1;
}
else
{
    // NumLock is OFF - put your "off" code here
    Serial.println("NUMLOCK OFF");
	numlockState = 0;
}
if (keyboard_leds & (1<<USB_LED_SCROLL_LOCK))
{
    // ScrollLock is ON - put your "on" code here
    Serial.println("SCROLL ON");
	scrolllockState = 1;
}
else
{
    // NumLock is OFF - put your "off" code here
    Serial.println("SCROLL OFF");
	scrolllockState = 0;
}

Serial.println("capslockState");
Serial.println(capslockState);
Serial.println("numlockState");
Serial.println(numlockState);
Serial.println("scrolllockState");
Serial.println(scrolllockState);
Serial.println("keyboard_leds");
Serial.println(keyboard_leds);

delay(1000);
}

/*
*************************
Open Serial
*************************
*/
void openserial()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
   ; // wait for serial port to connect. Needed for Leonardo only
   }
}
