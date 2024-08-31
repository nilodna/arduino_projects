#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

// default state is open (normally closed valves, so no energy is necessary to keep
// the valves closed, but it will be necessary to keep them open)
bool open_valve = false;

void setup () {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
 
  Serial.begin(9600); // inicializa comunicação serial
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }else{
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Uncomment the next line to set the date and time manually
    // rtc.adjust(DateTime(2024, 6, 17, 16, 39, 0)); // Year, Month, Day, Hour, Minute, Second
  }

  // start system with both valves closed
  digitalWrite(10, open_valve);
  digitalWrite(11, open_valve);
}

void loop () {
 
  DateTime now = rtc.now();

  // only for development purposes, delete when releasing a stable version
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

  delay(1000);

  // open grass valve for 45min
//  if (now.hour() == 17 && now.minute() >= 00 && now.minute() < 45){
  if (now.second() >= 30){
    digitalWrite(11, !open_valve); // open_valve becomes True
//    digitalWrite(10, open_valve);
  } else {
    digitalWrite(11, open_valve);
  }

//  // open garden valve for 15min
//  if (now.hour() == 17 && now.minute() >= 45 && now.minute() <= 59){
  if (now.second() >= 0 && now.second() < 30){
    digitalWrite(10, !open_valve); // open_valve becomes True
//    digitalWrite(11, open_valve);
  } else {
    digitalWrite(10, open_valve);
  }
}
