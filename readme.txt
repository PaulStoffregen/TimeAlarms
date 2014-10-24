Alarms

The Alarm library is a companion to the Time library that makes it easy to 
perform tasks at specific times or after specific intervals.

Tasks scheduled at a particular time of day are called Alarms,
tasks scheduled after an interval of time has elapsed are called Timers.
These tasks can be created to continuously repeat or to occur once only.  

Here is how you create an alarm to trigger a task repeatedly at a particular time of day:
  Alarm.alarmRepeat(8,30,0, MorningAlarm);  
This would call the function MorningAlarm()  at 8:30 am every day.

If you want the alarm to trigger only once you can use the alarmOnce  method:
  Alarm.alarmOnce(8,30,0, MorningAlarm);  
This calls a MorningAlarm() function in a sketch once only (when the time is next 8:30am)

Alarms can be specified to trigger a task repeatedly at a particular day of week and time of day:
  Alarm.alarmRepeat(dowMonday, 9,15,0, MondayMorningAlarm);  
This would call the function WeeklyAlarm() at 9:15am every Monday.

If you want the alarm to trigger once only on a particular day and time you can do this:
   Alarm.alarmOnce(dowMonday, 9,15,0, MondayMorningAlarm);  
This would call the function MondayMorning() Alarm on the next Monday at 9:15am.

Timers trigger tasks that occur after a specified interval of time has passed.
The timer interval can be specified in seconds, or in hour, minutes and seconds.
  Alarm.timerRepeat(15, Repeats);            // timer task every 15 seconds    
This calls the Repeats() function in your sketch every 15 seconds.

If you want a timer to trigger once only, you can use the timerOnce method:
  Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 
This calls the onceOnly() function in a sketch 10 seconds after the timer is created. 

If you want to trigger once at a specified date and time you can use the trigger Once() method:
  Alarm. triggerOnce(time_t value,  explicitAlarm); // value specifies a date and time
(See the makeTime() method in the Time library to convert dates and times into time_t)

Your sketch should call the Alarm.delay() function instead of the Arduino delay() function when
using the Alarms library.  The timeliness of triggers depends on sketch delays using this function.
  Alarm.delay( period); // Similar to Arduino delay - pauses the program for the period (in milliseconds).


 
Here is an example sketch:

This sketch  triggers daily alarms at 8:30 am and 17:45 pm.
A Timer is triggered every 15 seconds, another timer triggers once only after 10 seconds.
A weekly alarm is triggered every Sunday at 8:30:30

#include <Time.h>
#include <TimeAlarms.h>

void setup()
{
  Serial.begin(9600);
  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011
  // create the alarms 
  Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day 
  Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 

 
  Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds    
  Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 
}

void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

// functions to be called when an alarm triggers:
void MorningAlarm(){
  Serial.println("Alarm: - turn lights off");    
}

void EveningAlarm(){
  Serial.println("Alarm: - turn lights on");           
}

void WeeklyAlarm(){
  Serial.println("Alarm: - its Monday Morning");      
}

void ExplicitAlarm(){
  Serial.println("Alarm: - this triggers only at the given date and time");       
}

void Repeats(){
  Serial.println("15 second timer");         
}

void OnceOnly(){
  Serial.println("This timer only triggers once");  
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
Note that the loop code calls Alarm.delay(1000) -  Alarm.delay must be used
instead of the usual arduino delay function because the alarms are serviced in the Alarm.delay method.
Failing to regularly call Alarm.delay will result in the alarms not being triggered
so always use Alarm.delay instead of delay in sketches that use the Alarms library.

Functional reference:

// functions to create alarms and timers

Alarm.triggerOnce(value, AlarmFunction);
  Description: Call user provided AlarmFunction once at the date and time of the given value
  See the Ttime library for more on time_t values 
  
Alarm.alarmRepeat(Hour, Minute, Second,  AlarmFunction);
  Description:  Calls user provided AlarmFunction  every day at the given Hour, Minute and Second.

Alarm.alarmRepeat(value,  AlarmFunction);
  Description:  Calls user provided AlarmFunction  every day at the time indicated by the given value

Alarm.alarmRepeat(DayOfWeek, Hour, Minute, Second,  AlarmFunction);
  Description:  Calls user provided AlarmFunction  every week on the given  DayOfWeek, Hour, Minute and Second.

Alarm.alarmOnce(Hour, Minute, Second,  AlarmFunction);
  Description:  Calls user provided AlarmFunction once when the Arduino time next reaches the given Hour, Minute and Second.

Alarm.alarmOnce(value,  AlarmFunction);
  Description:  Calls user provided AlarmFunction  once at the next  time indicated by the given value

Alarm.alarmOnce(DayOfWeek, Hour, Minute, Second,  AlarmFunction);
  Description:  Calls user provided AlarmFunction  once only on the next  DayOfWeek, Hour, Minute and Second.

Alarm.timerRepeat(Period, TimerFunction);
  Description:  Continuously calls user provided TimerFunction  after the given period in seconds has elapsed. 

Alarm.timerRepeat(Hour, Minute, Second, TimerFunction);
  Description:  As timerRepeat above, but period is the number of seconds in the given Hour, Minute and Second parameters

Alarm.timerOnce(Period, TimerFunction);
  Description:  Calls user provided TimerFunction  once only after the given period in seconds has elapsed. 

Alarm.timerOnce(Hour, Minute, Second, TimerFunction);
  Description:  As timerOnce above, but period is the number of seconds in the given Hour, Minute and Second parameters

Alarm.delay( period)
 Description: Similar to Arduino delay - pauses the program for the period (in miliseconds) specified.
 Call this function rather than the Arduino delay function when using the Alarms library.
 The timeliness of the triggers  depends on sketch delays using this function.

Low level functions not usually required for typical applications:
  disable( ID);  -  prevent the alarm associated with the given ID from triggering   
  enable(ID);  -  enable the alarm 
  write(ID,  value);  -  write the value (and enable) the alarm for the given ID  
  read(ID);     - return the value for the given ID  
  readType(ID);  - return the alarm type for the given alarm ID
  getTriggeredAlarmId();   -  returns the currently triggered  alarm id, only valid in an alarm callback

FAQ

Q: What hardware and software is needed to use this library?
A: This library requires the Time library. No internal or external hardware is used by the Alarm library.

Q: Why must I use Alarm.delay() instead of delay()?
A: Task scheduling is handled in the Alarm.delay function.
Tasks are monitored and  triggered from within the Alarm.delay call so Alarm.delay should be called
whenever a delay is required in your sketch.
If your sketch waits on an external event (for example,  a sensor change),
make sure you repeatedly call Alarm.delay while checking the sensor.
You can call Alarm.delay(0) if you need to service the scheduler without a delay.

Q: Are there any restrictions on the code in a task handler function?
A: No. The scheduler does not use interrupts so your task handling function is no
different from other functions you create in your sketch. 

Q: What are the shortest and longest intervals that can be scheduled?
A:  Time intervals can range from 1 second to years.
(If you need timer intervals shorter than 1 second then the TimedAction library
by Alexander Brevig may be more suitable, see: http://www.arduino.cc/playground/Code/TimedAction)

Q: How are scheduled tasks affected if the system time is changed?
A: Tasks are scheduled for specific times designated by the system clock.
If the system time is reset to a later time (for example one hour ahead) then all
alarms and timers will occur one hour later.
If the system time is set backwards (for example one hour back) then the alarms and timers will occur an hour earlier.
If the time is reset before the time a task was scheduled, then the task will be triggered on the next service (the next call to Alarm.delay).
This is  the expected behaviour for Alarms – tasks scheduled for a specific time of day will trigger at that time, but the affect on timers may not be intuitive. If a timer is scheduled to trigger in 5 minutes time and the clock is set ahead by one hour, that timer will not trigger until one hour and 5 minutes has elapsed.

Q: What  is the valid range of times supported by these libraries?
A: The time library is intended to handle times from Jan 1 1970 through Jan 19 2038.
 The Alarms library expects dates to be on or after Jan1 1971 so clocks should no be set earlier than this if using Alarms.
(The functions to create alarms will return an error if an earlier date is given).

Q: How many alarms can be created?
A: Up to six alarms can be scheduled.  
The number of alarms can be changed in the TimeAlarms header file (set by the constant dtNBR_ALARMS,
note that the RAM used equals dtNBR_ALARMS  * 11)

onceOnly Alarms and Timers are freed when they are triggered so another onceOnly alarm can be set to trigger again.
There is no limit to the number of times a onceOnly alarm can be reset.

The following fragment gives one example of how a timerOnce  task can be rescheduled:
Alarm.timerOnce(random(10), randomTimer);  // trigger after random number of seconds

void randomTimer(){
  int period = random(2,10);             // get a new random period 
  Alarm.timerOnce(period, randomTimer);  // trigger for another random period 
}

