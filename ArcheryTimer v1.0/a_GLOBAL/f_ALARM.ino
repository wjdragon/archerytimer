/* runAlarm
 *  Controls the alarm state (on/off) in 250ms intervals
 *  Gate is the alarm count, set whenever an event occurs (prepare, time complete, 5 whiste)
 *  State toggles between active/inactive.  Only decrement the count remaining when transitions from on to off
 */

void runAlarm()
{
  if (alarmCount)
  {
    if (alarmStatus == INACTIVE)
    {
      digitalWrite(alarmOutPin, HIGH);
      alarmStatus = ACTIVE;
    } else
    {
      digitalWrite(alarmOutPin, LOW);
      alarmStatus = INACTIVE;
      alarmCount--;
    }
  }
}
