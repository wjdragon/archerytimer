void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Archery Countdown Timer");
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  pinMode(segmentClock, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(segmentLatch, OUTPUT);
  pinMode(alarmOutPin, OUTPUT);

  btnAlarm.setDebounceTime(50);
  btnTimeAdd.setDebounceTime(50);
  btnTimeMinus.setDebounceTime(50);
  btnStartStop.setDebounceTime(50);

  digitalWrite(segmentClock, LOW);
  digitalWrite(segmentData, LOW);
  digitalWrite(segmentLatch, LOW);

  display.clearDisplay();         //Adafruit splash logo is in initial buffer,  Clear it.
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  centerText("El Dorado Archers");
  centerText("Archery Timer");
  centerText("Developed by:");
  centerText("Micah Ting");
  display.display();
  delay(2000);
  
  showNumber(countdown);

  Serial.println("State is STOPPED");
}
