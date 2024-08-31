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
     
    // set the date and time manually based on the compilation time
    rtc.adjust(DateTime(2024, 8, 6, 11, 45, 0)); // Year, Month, Day, Hour, Minute, Second

  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Uncomment the next line to set the date and time manually
    // rtc.adjust(DateTime(2024, 6, 17, 16, 39, 0)); // Year, Month, Day, Hour, Minute, Second
  }

  // start system with both valves opened
  digitalWrite(10, false);
  digitalWrite(11, false);
}

void loop () {
 
  DateTime now = rtc.now();

  if (now.hour() == 16 && now.minute() >= 0 && now.minute() < 15){
    // open grass valve between 16 and 16h30
    digitalWrite(10, false); // open D10
    digitalWrite(11, true); // close D11
  } else if (now.hour() == 16 && now.minute() >= 15 && now.minute() <= 18){
    // open garden valve for 5min, between 16h30 and 16h35
    digitalWrite(11, false); // open D11
    digitalWrite(10, true); // close D10
  } else {
    digitalWrite(10, true); // close D11
    digitalWrite(11, true); // close D11
  }

  delay(1000);
  
}
