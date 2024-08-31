#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup () {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  digitalWrite(10, true);
  digitalWrite(11, true);
  
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
    // rtc.adjust(DateTime(2024, 6, 17, 16, 39, 0)); // Year, Month, Day, Hour, Minute, Second
  }
}

void loop () {
  
  DateTime now = rtc.now();

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

  delay(1000); // Print every second

  if (now.hour() == 10 && now.minute() == 12){
    digitalWrite(10, false);
    digitalWrite(11, true);
  }else {
    digitalWrite(10, true);
    digitalWrite(11, false);
  }
}
