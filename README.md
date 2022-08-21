# archerytimer
Arduino-driven archery timer with buzzer

This project runs an archery time using an arduino uno and a set of three 7-segment displays from Sparkfun.  

Project Organization
-----------------------------------
This project is split into multiple files.  The Arduino IDE is pretty good about multi-file projects by placing them into
separate .ino files but bringing everything together into a single IDE.  A brief description about each of project files is as follows:

GLOBAL: Sets up forward and global declarations, all the required Arduino pins, all the buttons to be used

SETUP: Standard Arduino setup() function.  SSD1306 OLED display, ezButton initialization

LOOP: Standard Arduino loop() function.  We use the TimedAction library to perform "threading", and these threads are called here.

BUTTON: All button related functions are implemented here.  Short and long press actuation logic found here.

TIMER: All timer related functions are implemented here.  This thread is setup to trigger at 1HZ.  The value on the displayed clock is decremented here

ALARM: All alarm (whistle) related functions are implemented here.  The alarm uses a state machine to determine when to sound on and off.  Since the trigger is 250ms, the alarm is defaulted to stay on or off until the next trigger.  The number of "blasts" is determined by a global variable.

DISPLAY: All 7-segment display logic is implemented here.

GFX: All graphics related functions are implemented here.
