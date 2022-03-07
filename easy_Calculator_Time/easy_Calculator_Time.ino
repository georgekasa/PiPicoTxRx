
#include "RTClib.h"
RTC_DS3231 rtc;

void setup () {
    Serial.begin(9600);
#ifndef ESP8266
    while (!Serial); // wait for serial port to connect. Needed for native USB
#endif
    DateTime dt0 (2020, 12,13, 15, 30, 0);
     rtc.adjust(dt0);
}

void loop () {
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

}
