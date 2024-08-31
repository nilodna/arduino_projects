#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup () {
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Uncomment the next line to set the date and time manually
    // rtc.adjust(DateTime(2024, 6, 15, 12, 0, 0)); // Year, Month, Day, Hour, Minute, Second
  }
}

void loop () {
  DateTime now = rtc.now();

  // opening relay 1 between 17h and 18
  if (now.hour() == 16 && now.minute() == 0) {
    // digitalWrite(relay1, LOW); // open relay 1
    Serial.print('Opening relay 1');
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  }

  // closing system 1
  if (now.hour() == 16 && now.minute() == 5){
      // digitalWrite(relay1, HIGH); // open relay 1
      Serial.print('Closing relay 1');
  }
  
  delay(60000); // check every minute
}
