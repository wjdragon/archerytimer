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

## Hardware
This project uses the following hardware:
- Arduino Uno board
- WS2811 LEDs (12v) arranged into 8-digit displays (times 3).
- Two MAX485 chips for long distance communication
- 120dB alarm (3v, 5v, or 12v)
- PN2222A

If using a short (less than 1 meter) run from the Arduino to LED board, the signal should be strong enough.  Anything longer and the signal will degrade.  For this project, we use a 30ft 8-wire cable to connect the controller box (Arduino) to the LED display panel.  However, the signal gets too weak and needs to be boosted.  See schematic

## Use
+10/-10 seconds to adjust the time needed for one end
"Start" will blast two whistles and put 10s on the timer.  At the end of the 10s, it will blast one whistle and display the time for the end, which will sound three whistles.  Clicking again will "Stop" the countdown, the clock will freeze, and the unit is in idle state.  No whistles are blasted if the timer is stopped prematurely.
"3/5" whistle: Pressing once will blast three whistles to immediately end the round and stop the timer. The clock will not reset.  Holding this button will blast 5 whistles and stop the timer.  The clock will not reset.
"Reset Clock" will stop the timer and reset the clock
"AB/CD" will toggle the LEDs for line 1 or line 2.

For tournaments with two lines:
Press "Start/Start" to start the AB line.
- if an archer looks to burn the time, allow the clock to finish and blast the three whistles.  Clicking "Start" again will start the 10s countdown and allow CD line to approach
- if all archers finish early, press "Start/Stop" to stop the countdown.  Click "Reset Clock" to reset the clock.  Click "Start/Stop" to start the 10s countdown for CD line.  3 whistles will not be issued in this way.
