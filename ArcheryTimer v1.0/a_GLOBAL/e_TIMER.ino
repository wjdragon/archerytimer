/* updateTime
 *  Uses the state machine to determine what to display
 *  STOPPED: Do not run anything in this timer
 *  PREPARE: Set the clock for 10s and decrement.  When 0, move state machine to RUNNING.  Sets alarm state machine
 *  RUNNING: Uses countdown timer and decrements down to 0.  Sets alarm state machine
 */
void updateTime() {
  //if we're not actively running, don't do anything
  switch(runStatus)
  {
    case STOPPED: 
      return;
      break;
    case PREPARE:
    {
      showNumber(prepclk);
      if (prepclk == 0)     //reset PREPARE time, move to next state
      {
        prepclk = 10;
        runStatus = RUNNING;
        Serial.println("State is RUNNING");
        alarmCount = 1;
        break;              //immediately move to RUNNING state, display time, and start countdown
      }
      prepclk--;
    }
      break;
    case RUNNING:
    {
      showNumber(runclk);
      if (runclk == 0)
      {
        runStatus = STOPPED;
        Serial.println("State is STOPPED");
        alarmCount = 3;
      }
      showNumber(runclk);
      runclk--;
    }
    break;
  }
}
