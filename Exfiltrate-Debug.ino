
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

int capslockPushCounter = 0;   // counter for the number of capslock button presses
int capslockState = 0;         // current state of the capslock button
int lastcapslockState = 0;     // previous state of the capslock button


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
//  openserial();   
   
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
capslockState = keyboard_leds & (1<<USB_LED_CAPS_LOCK);

if (keyboard_leds & (1<<USB_LED_CAPS_LOCK))
{
  if ((capslockState != lastcapslockState)
      // and it's currently pressed:
      && (capslockState == 2)) {
    // increment the button counter
    capslockPushCounter++;
	}
    // CapsLock is ON - put your "on" code here
//    Serial.println("CAPS ON");
}
else
{
    // CapsLock is OFF - put your "off" code here
//    Serial.println("CAPS OFF");
	capslockState = 0;
}

	if (capslockPushCounter == 2 && capslockState == 0)
	{
		opennotepad();
		capslockPushCounter = 0;
	}	      
lastcapslockState = capslockState;

/*Serial.println(capslockState);
Serial.println(lastcapslockState);
Serial.println(capslockPushCounter);
*/
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

/*
*************************
Open NotePAD
*************************
*/
void opennotepad()
{
Keyboard.begin();
Keyboard.press(KEY_LEFT_GUI);
Keyboard.press('r');
Keyboard.releaseAll();
delay(500);

Keyboard.print("notepad");
delay(500);
    
Keyboard.press(KEY_RETURN);
Keyboard.releaseAll();
delay(750);

Keyboard.println("Hello");
Keyboard.println("La tortue a tres faim...!!!");
Keyboard.println("Merci de la remplir et atteindre le prochain palier de 150 CHF");
    
Keyboard.press(KEY_RETURN);
Keyboard.releaseAll();
Keyboard.end();
}  