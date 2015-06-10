
/*
 Program by Systemic
 Based on following sources:
 
 Arduino
 FinalKey
 
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 ** Pushbutton1 = 9
 ** Pushbutton1 = 10
 
 created   May 2015
 by Systemic
 modified 6 June 2015
 
 This code is in the public domain.
 	 
 */
 
#include <SD.h>
#include <SPI.h>

/*
*************************
VARIABLES
*************************
*/

File myFile;
const int buttonPinVBS = 9;          // input pin for VBS Sending pushbutton
const int buttonPinNOT = 10;          // input pin for Notepad Sending pushbutton
int previousButtonStateNOT = HIGH;   // for checking the state of VBS pushButton
int previousButtonStateVBS = HIGH;   // for checking the state of Notepad pushButton
int counterVBS= 0;                  // button VBS push counter
int counterNOT = 0;                  // button Notepad push counter

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
  // make the pushButton pin an input:
  pinMode(buttonPinNOT, INPUT);
  pinMode(buttonPinVBS, INPUT);
  
  // open serial port
  openserial()

  // open serial port
  opensdcard()
  
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
/*  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3,4,5.");
	// close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
 */ 
 /*
   if (SD.exists("host.vbs")) {
    Serial.println("host.vbs exists.");
  }
  else {
    Serial.println("host.vbs doesn't exist.");
  }
  
    if (SD.exists("HOST.VBS")) {
    Serial.println("HOST.VBS exists.");
  }
  else {
    Serial.println("HOSTS.VBS doesn't exist.");
  }
  
   if (SD.exists("test.txt")) {
    Serial.println("test.txt exists.");
  }
  else {
    Serial.println("test.txt doesn't exist.");
  }
 */
   // re-open the file for reading:
   
  delay(5000);                  // waits for 5 second
    Serial.println("opening keyboard");
  //KeyMaps.setKbMap(6);
//Keyboard.begin(6);
    Serial.println("keyboard open");
}

/*
*************************
LOOP
*************************
*/


void loop()
{
	// nothing happens after setup

  // read the pushbutton:
  int buttonStateVBS = digitalRead(buttonPinVBS);
  // if the button state has changed,
  if ((buttonStateVBS != previousButtonStateVBS)
      // and it's currently pressed:
      && (buttonStateVBS == HIGH)) {
    // increment the button counter
    counterVBS++;
    // type out a message
    Keyboard.print("You pressed the button VBS ");
    Keyboard.print(counterVBS);
    Keyboard.println(" times.");
    Serial.print("You pressed the button VBS ");
    Serial.print(counterVBS);
    Serial.println(" times.");
  }
    //Keyboard.println(" test keyboard");
    delay(1000);


/*
*************************
VBS File opening and copy
*************************
*/

  // read the pushbutton:
  //int buttonStateVBS = digitalRead(buttonPinVBS);
  // if the button state has changed,
  if ((buttonStateVBS != previousButtonStateVBS)
      // and it's currently pressed:
      && (buttonStateVBS == HIGH)) {
    // increment the button counter
    //counter++;
    // type out a message
    //Keyboard.print("You pressed the button ");
    //Keyboard.print(counter);
    //Keyboard.println(" times.");

  myFile = SD.open("host.vbs");
  if (myFile) {
    Serial.println("host.vbs content:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
  	// if the file didn't open, print an error:
    Serial.println("error opening host.vbs");
  }

  }
    //Keyboard.println(" test keyboard");
    delay(1000);


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
}
else
{
    // CapsLock is OFF - put your "off" code here
    Serial.println("CAPS OFF");
    //Serial.println(keyboard_leds);
}


/*
*************************
Open NotePAD
*************************
*/


  // read the pushbutton:
  int buttonStateNOT = digitalRead(buttonPinNOT);
  // if the button state has changed,
  if ((buttonStateNOT != previousButtonStateNOT)
      // and it's currently pressed:
      && (buttonStateNOT == HIGH)) {
    // increment the button counter
    counterNOT++;
    // type out a message
    Keyboard.print("You pressed the button NOT ");
    Keyboard.print(counterNOT);
    Keyboard.println(" times.");
    Serial.print("You pressed the button NOT ");
    Serial.print(counterNOT);
    Serial.println(" times.");
  }


/*
  // read the pushbutton:
  int buttonStateNOT = digitalRead(buttonPinNOT);
  // if the button state has changed,
  if ((buttonStateNOT != previousButtonStateNOT)
      // and it's currently pressed:
      && (buttonStateNOT == HIGH)) {
    // increment the button counter
    counterNOT++;
    // type out a message
    //Keyboard.print("You pressed the button ");
    //Keyboard.print(counter);
    //Keyboard.println(" times.");

      /*Keyboard.set_modifier(MODIFIERKEY_RIGHT_GUI); //Tell Teensy to press Windows key

      Keyboard.set_key1(KEY_R); //Tell Teensy to press R

      Keyboard.send_now(); //Press "Windows key + R"

      delay(500); //Wait for half second

      Keyboard.set_modifier(0); //Tell Teensy to release Windows key

      Keyboard.set_key1(0); //Tell Teensy to release R

      Keyboard.send_now(); //Release "Windows key + R"

      //Teensy should open a run prompt now

      Keyboard.print("notepad"); //Type notepad in the run prompt

      Keyboard.set_key1(KEY_ENTER); //Tell Teensy to press Enter key

      Keyboard.send_now(); //Press Enter

      Keyboard.set_key1(0); //Tell Teensy to release Enter

      Keyboard.send_now(); //Release Enter

      delay(2000); //Wait for notepad to open

      Keyboard.print("Hello World"); //Type Hello World in notepad
     */ 

/*
    Serial.print("You pressed the button ");
    Serial.print(counterNOT);
    Serial.println(" times.");
      
Keyboard.press(KEY_LEFT_GUI);
Keyboard.press('r');
Keyboard.releaseAll();
delay(500);

Keyboard.print("notepad");
delay(500);
    
Keyboard.press(KEY_RETURN);
Keyboard.releaseAll();
delay(750);

Keyboard.print("Hello World!!!");
    
Keyboard.press(KEY_RETURN);
Keyboard.releaseAll();


  }
*/

    //Keyboard.println(" test keyboard");
    delay(1000);


/*keyboard_leds = Keyboard.getLedStatus();
// This part should go inside your code where you want to test the state of the caps lock led
if (keyboard_leds & (1<<USB_LED_CAPS_LOCK)) // checks that the caps lock bit is set
{
    // CapsLock is ON - put your "on" code here
    Serial.println("CAPS ON");
}
else
{
    // CapsLock is OFF - put your "off" code here
    Serial.println("CAPS OFF");
    Serial.println(keyboard_leds);
}
*/
  
  // save the current button state for comparison next time:
  previousButtonStateNOT = buttonStateNOT;

  previousButtonStateVBS = buttonStateVBS;
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
Open SD Card
*************************
*/
void opensdcard()
{
Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(4, OUTPUT);
   
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}  