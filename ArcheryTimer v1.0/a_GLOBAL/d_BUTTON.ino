/* Process buttons in order of importance:
    1. Alarm
    2. Start/Stop
    3. Timer adjust

    Timer adjust will only function when the state machine is stopped.
*/

void button_check(void)
{
  long pressDuration;

  btnAlarm.loop();
  btnTimeAdd.loop();
  btnTimeMinus.loop();
  btnStartStop.loop();
  btnReset.loop();

  /* Check and act on alarm button */
  if (btnAlarm.isPressed()) {
    btnAlarm.pressTime = millis();
    btnAlarm.isPressing = true;
    btnAlarm.isLongDetected = false;
  }
  if (btnAlarm.isReleased()) {
    btnAlarm.isPressing = false;
    btnAlarm.releaseTime = millis();
    pressDuration = btnAlarm.releaseTime - btnAlarm.pressTime;
    if (pressDuration < SHORT_PRESS_TIME)
      if (!btnAlarm.isLongDetected)
      {
        alarmCount = 3;
        runStatus = STOPPED;
      }
  }
  if (btnAlarm.isPressing && !btnAlarm.isLongDetected) {
    pressDuration = millis() - btnAlarm.pressTime;
    if (pressDuration > LONG_PRESS_TIME) {
      btnAlarm.isLongDetected = true;
    }
  }

  //actively pressing and long press is true
  if (btnAlarm.isPressing && btnAlarm.isLongDetected) {
    digitalWrite(alarmOutPin, HIGH);    //5 whistle blast and reset everything
    runStatus = STOPPED;
  } else if (!btnAlarm.isPressing && btnAlarm.isLongDetected) {
    digitalWrite(alarmOutPin, LOW);
    showNumber(countdown);
    alarmCount = 0;
    btnAlarm.isLongDetected = false;    //btn released, alarm is stopped, reset long state
  }

  /* Check and act on start/stop button */
  if (btnStartStop.isPressed()) {
    btnStartStop.pressTime = millis();
    btnStartStop.isPressing = true;
    btnStartStop.isLongDetected = false;
  }
  if (btnStartStop.isReleased()) {
    btnStartStop.isPressing = false;
    btnStartStop.releaseTime = millis();
    pressDuration = btnStartStop.releaseTime - btnStartStop.pressTime;
    if (pressDuration < SHORT_PRESS_TIME)
    {
      switch (runStatus)
      {
        case STOPPED:
          runStatus = PREPARE;
          runclk = countdown;   //set the running timer
          prepclk = 10;
          alarmCount = 2;
          Serial.print("State is PREPARE.  Timer is set to ");
          Serial.println(runclk);
          break;
        case PREPARE:
          runStatus = STOPPED;
          Serial.println("State is STOPPED");
          break;
        case RUNNING:
          runStatus = STOPPED;
          Serial.println("State is STOPPED");
          break;
      }
    }
  }

  if (runStatus == STOPPED)   //only allow timer adjustments if we're in STOPPED state
  {
    /* Check and act on time plus button */
    if (btnTimeAdd.isPressing && btnTimeAdd.isLongDetected) {   //handle long press
      countdown = (countdown + 10 >= 990 ? 990 : countdown + 10);
      showNumber(countdown);
      delay(100);
    }
    if (btnTimeAdd.isPressed()) {
      btnTimeAdd.pressTime = millis();
      btnTimeAdd.isPressing = true;
      btnTimeAdd.isLongDetected = false;
    }
    if (btnTimeAdd.isReleased()) {
      btnTimeAdd.isPressing = false;
      btnTimeAdd.releaseTime = millis();
      pressDuration = btnTimeAdd.releaseTime - btnTimeAdd.pressTime;
      if (pressDuration < SHORT_PRESS_TIME) {
        countdown = (countdown + 10 >= 990 ? 990 : countdown + 10);
        showNumber(countdown);
      }
    }
    if (btnTimeAdd.isPressing && !btnTimeAdd.isLongDetected) {
      pressDuration = millis() - btnTimeAdd.pressTime;
      if (pressDuration > LONG_PRESS_TIME) {
        btnTimeAdd.isLongDetected = true;
      }
    }

    /* Check and act on time minus button */
    if (btnTimeMinus.isPressing && btnTimeMinus.isLongDetected) {
      countdown = (countdown - 10 <= 10 ? 10 : countdown - 10);
      showNumber(countdown);
      delay(100);
    }
    if (btnTimeMinus.isPressed()) {
      btnTimeMinus.pressTime = millis();
      btnTimeMinus.isPressing = true;
      btnTimeMinus.isLongDetected = false;
    }
    if (btnTimeMinus.isReleased()) {
      btnTimeMinus.isPressing = false;
      btnTimeMinus.releaseTime = millis();
      pressDuration = btnTimeMinus.releaseTime - btnTimeMinus.pressTime;
      if (pressDuration < SHORT_PRESS_TIME) {
        countdown = (countdown - 10 <= 10 ? 10 : countdown - 10);
        showNumber(countdown);
      }
    }
    if (btnTimeMinus.isPressing && !btnTimeMinus.isLongDetected) {
      pressDuration = millis() - btnTimeMinus.pressTime;
      if (pressDuration > LONG_PRESS_TIME) {
        btnTimeMinus.isLongDetected = true;
      }
    }
  }//End runStatus == STOPPED

  //Handle Reset button.  Reset state, display, kill alarm, etc
  if (btnReset.isPressed()) {
      runStatus = STOPPED;
      showNumber(countdown);
      alarmCount = 0;
    }
}
