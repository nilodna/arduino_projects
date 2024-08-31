#include <SPI.h>            // Include the SPI library (required for SD card access)
#include <SD.h>             // Include the SD library (required for SD card access)
#include <Wire.h>           // Include the Wire library (required for RTC communication)
#include <RTClib.h>         // Include the RTC library (required for Real-Time Clock functionality)

RTC_DS1307 rtc;             // Create an instance of the RTC object

void setup() {
    Serial.begin(9600);     // Initialize serial communication
    rtc.begin();            // Initialize RTC

    if (! rtc.isrunning()) {
        Serial.println("RTC is NOT running!");
        // If RTC is not running, you may need to set the time here.
        // Use rtc.adjust(DateTime(year, month, day, hour, minute, second));
    }
}

void loop() {
    DateTime now = rtc.now();      // Get the current time from RTC

    // Display hour on Serial Monitor
    Serial.print("Current hour: ");
    Serial.println(now.hour());

    delay(1000);  // Delay for 1 second (1000 milliseconds)
}
