#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ezButton.h>
#include <TimedAction.h>

const int SHORT_PRESS_TIME = 250;
const int LONG_PRESS_TIME = 500;

//GPIO declarations
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
byte segmentClock = 6;    //Yellow
byte segmentLatch = 5;    //Brown
byte segmentData = 7;     //Blue
byte alarmInPin = 8;
byte alarmOutPin = 9;     //Green
byte timeAddPin = 10;
byte timeMinusPin = 11;
byte startStopPin = 12;
byte resetPin = 13;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

//Button Declarations
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

//Forward Function Declarations
void updateTime();
void runAlarm();
void button_check(void);
void showNumber(float value);
void centerText(String text);

//TimedAction Declarations
TimedAction timerAction = TimedAction(1000,updateTime);
TimedAction alarmAction = TimedAction(250,runAlarm);

//GFX Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
