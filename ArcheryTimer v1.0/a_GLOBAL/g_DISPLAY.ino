//Takes a number and displays 2 numbers. Displays absolute value (no negatives)
void showNumber(float value)
{
  int number = abs(value); //Remove negative signs and any decimals

  String s_number = String(number);
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0,0);
  centerText(s_number);
  display.setTextSize(1);
  switch(runStatus) {
    case STOPPED:
      centerText("Stopped");
      break;
    case PREPARE:
      centerText("Approach Line");
      break;
    case RUNNING:
      centerText("Running");
      break;
  }
  display.display();
 
  //3 digits.  For each digit, push the digit to the display
  for (char x = 2 ; x >= 0 ; x--)
  {
    int remainder = number % 10;
    postNumber(remainder, x);
    number /= 10;
  } 
}

//choose the lower number of the above 7 segment index.  For segment "0,1", pass in 0
//red, green and blue values are global
void set_segment(byte base, byte offset)
{
  leds[base + offset].r = leds[base + 1 + offset].r = red;
  leds[base + offset].g = leds[base + 1 + offset].g = green;
  leds[base + offset].b = leds[base + 1 + offset].b = blue;
}

//Given a number, or '-', shifts it out to the display
void postNumber(int digit, byte pos)
{
  byte ix = 14*pos;                       //offset for a position (0 for 1st digit, 14 for second digit, etc)
  byte i;

  for (i = 0; i <= 13; i++)
  {
    leds[i + ix] = CRGB(0,0,0);
  }

  switch(digit)
  {
    case 0: set_segment(4, ix); set_segment(6, ix); set_segment(2, ix); set_segment(8, ix); set_segment(12, ix); set_segment(10, ix); break;
    case 1: set_segment(2, ix); set_segment(12, ix); break;
    case 2: set_segment(4, ix); set_segment(2, ix); set_segment(0, ix); set_segment(8, ix); set_segment(10, ix); break;
    case 3: set_segment(4, ix); set_segment(2, ix); set_segment(0, ix); set_segment(12, ix); set_segment(10, ix); break;
    case 4: set_segment(6, ix); set_segment(2, ix); set_segment(0, ix); set_segment(12, ix); break;
    case 5: set_segment(4, ix); set_segment(6, ix); set_segment(0, ix); set_segment(12, ix); set_segment(10, ix); break;
    case 6: set_segment(4, ix); set_segment(6, ix); set_segment(0, ix); set_segment(8, ix); set_segment(12, ix); set_segment(10, ix); break;
    case 7: set_segment(4, ix); set_segment(2, ix); set_segment(12, ix); break;
    case 8: set_segment(4, ix); set_segment(6, ix); set_segment(2, ix); set_segment(0, ix); set_segment(8, ix); set_segment(12, ix); set_segment(10, ix); break;
    case 9: set_segment(4, ix); set_segment(6, ix); set_segment(2, ix); set_segment(0, ix); set_segment(12, ix); break;
  }
  FastLED.show();
}
