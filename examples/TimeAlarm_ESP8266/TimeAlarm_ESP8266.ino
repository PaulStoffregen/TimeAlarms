/*
 * TimeAlarm_ESP8266.ino
 *
 * This example calls two repetitive timers, one every
 * 5 seconds and one every 22 seconds. A single shot
 * timer is triggered after 58 seconds too. It finishes
 * 5 senconds timer
 *
 * An alarm is triggered 1 minute after current time.
 *
 * At startup the time is syncd to NTP server, so
 * it requires NTP Client library from 
 * https://github.com/gmag11/NtpClient
 *
 * It uses a class to initalize triggers
 * to show how to use class methods as callbacks.
 *
 */

#define YOUR_WIFI_SSID "Your_SSID"
#define YOUR_WIFI_SSID "Your_Pw"

#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <TimeAlarms.h>

#include <functional>
using namespace std;
using namespace placeholders;

class AlarmManager{
public:
	void begin() {
		while (timeStatus() != timeSet) {
			// Wait for time sync. Make yourself sure it can connect to WiFi
			Serial.print(".");
			delay(1000);
		}
		Serial.println();

		//Set alarms
		Alarm.timerRepeat(0, 0, 22, std::bind(&AlarmManager::timer22,this));
		alarm5 = Alarm.timerRepeat(0, 0, 5, std::bind(&AlarmManager::timer5, this));
		Alarm.timerOnce(0, 0, 58, std::bind(&AlarmManager::timerOnce, this));
		time_t alarm = now() + 60; // Current time + 1 minute
		Serial.printf("---- Set alarm at %s\r\n", NTP.getTimeDateString(alarm).c_str());
		Alarm.alarmOnce(hour(alarm), minute(alarm), second(alarm), std::bind(&AlarmManager::alarmOnce, this));
	}

protected:
	AlarmId alarm5;

	void timer22() {
		static int i = 0;
		Serial.printf("-- %02d. timerRepeat every 22 seconds. It's %s. Uptime: %s\r\n", i, NTP.getTimeDateString().c_str(), NTP.getUptimeString().c_str());
		i++;
	}

	void timer5() {
		static int i = 0;
		Serial.printf("- %02d. timerRepeat every 5 seconds. It's %s. Uptime: %s\r\n", i, NTP.getTimeDateString().c_str(), NTP.getUptimeString().c_str());
		i++;
	}

	void timerOnce() {
		Serial.printf("--- TimerOnce at 58 seconds. It's %s. Uptime: %s\r\n", NTP.getTimeDateString().c_str(), NTP.getUptimeString().c_str());
	}

	void alarmOnce() {
		Serial.printf("---- AlarmOnce. It's %s. Uptime: %s\r\n", NTP.getTimeDateString().c_str(), NTP.getUptimeString().c_str());
		Alarm.free(alarm5);
	}

};

AlarmManager manager;

void setup()
{
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	WiFi.begin(YOUR_WIFI_SSID, YOUR_WIFI_PASSWD);
	NTP.begin("pool.ntp.org", 1, true); //Start NTP Client
	manager.begin();
}

void loop()
{
	Alarm.delay(0);
}
