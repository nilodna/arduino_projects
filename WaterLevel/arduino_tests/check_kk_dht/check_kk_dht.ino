#include <SPI.h>            // Include the SPI library (required for SD card access)
#include <SD.h>             // Include the SD library (required for SD card access)
#include <Wire.h>           // Include the Wire library (required for RTC communication)
#include <RTClib.h>         // Include the RTC library (required for Real-Time Clock functionality)
#include "DHT.h"

RTC_DS1307 rtc;             // Create an instance of the RTC object

int Pino_CS = 10;           //Pino CS do cartao SD

//Definicoes do sensor de temperatura DHT11
#define DHTPIN_EXT A0 //Pino de conexao
#define DHTTYPE DHT11 //Tipo de sensor
DHT dht(DHTPIN_EXT, DHTTYPE); //Cria objeto DHT

void setup() {
    Serial.begin(9600);     // Initialize serial communication

  //Inicializa o DHT11
  dht.begin();
}


void loop() 
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  {
  // Log data to SD card
    Serial.println(t);
  }

  // reads every 10 seconds
  delay(1000);
}
