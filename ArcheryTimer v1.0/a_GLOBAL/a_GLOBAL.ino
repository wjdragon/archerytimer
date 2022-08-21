#include <FastLED.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ezButton.h>
#include <TimedAction.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define DEFAULT_COLOR 255
#define DEFAULT_BRIGHTNESS 100
#define LED_TYPE    WS2811
#define COLOR_ORDER BRG
#define NUM_LEDS    52
#define LED_PIN     7

/* 8 pin connectors wired as if the mating side facing observer
 * 
 *  2 4 6 8
 *  1 3 5 7
 *  
 *  Pin Color Purpose             Arduino Pin
 *  2 - GRN - Alarm return path - 9
 *  4 - RED - VIN (12V)         - VIN
 *  6 - WHT - 5V                - 5V
 *  8 - GND - Ground            - GND
 *  1 - N/C - Not Used
 *  3 - BLU - LED Data          - 7
 *  5 - BRN - Not Used          - (was Latch signal for Sparkfun 7 Digit)
 *  7 - YEL - Not Used          - (was Clock signal fro Sparkfun 7 Digit)
 */

const int SHORT_PRESS_TIME = 250;
const int LONG_PRESS_TIME = 500;

//GPIO declarations
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
byte colorPin = 5;    //Brown
byte brightPin = 6;    //Yellow
byte ledPin = LED_PIN;     //Blue
byte alarmInPin = 8;
byte alarmOutPin = 9;     //Green
byte timeAddPin = 10;
byte timeMinusPin = 11;
byte startStopPin = 12;
byte resetPin = 13;

//Button Declarations
ezButton btnColor(colorPin);
ezButton btnBright(brightPin);
ezButton btnAlarm(alarmInPin);
ezButton btnTimeAdd(timeAddPin);
ezButton btnTimeMinus(timeMinusPin);
ezButton btnStartStop(startStopPin);
ezButton btnReset(resetPin);

enum runningState {
  STOPPED,
  PREPARE,
  RUNNING,
};

enum alarmState {
  ACTIVE,
  INACTIVE,
};

//Global Variables
int countdown = 120;             //keeps the qualifier clock value.  Only changes when user sets clock time
int runclk = 0;                 //keeps the end clock value.  Decrements when the clock is running
int prepclk = 10;               //keeps the 10s prep clock value.  Decrements when the clock is running
int alarmCount;                 //number of beeps for the alarm cycle
alarmState alarmStatus = INACTIVE;
runningState runStatus = STOPPED;
byte red = DEFAULT_COLOR;
byte green = DEFAULT_COLOR;
byte blue = DEFAULT_COLOR;
byte palidx = 5;                //index to the color palette.  For testing
byte brightness = DEFAULT_BRIGHTNESS;

//Forward Function Declarations
void updateTime();
void runAlarm();
void button_check(void);
void showNumber(float value);
void centerText(String text);
void cycleColor(void);
void cycleBrightness(void);

//TimedAction Declarations
TimedAction timerAction = TimedAction(1000,updateTime);
TimedAction alarmAction = TimedAction(250,runAlarm);

//GFX Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//WS2811 array
CRGB leds[NUM_LEDS];

byte palette[] = {0x4, 0x2, 0x1, 0x6, 0x3, 0x7};
