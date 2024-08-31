#include <SPI.h>            // Include the SPI library (required for SD card access)
#include <SD.h>             // Include the SD library (required for SD card access)
#include <Wire.h>           // Include the Wire library (required for RTC communication)
#include <RTClib.h>         // Include the RTC library (required for Real-Time Clock functionality)
#include "DHT.h"

RTC_DS1307 rtc;             // Create an instance of the RTC object

int Pino_CS = 10;           //Pino CS do cartao SD

//Definicoes do sensor de temperatura DHT11
#define DHTPIN_EXT A0 //Pino de conexao
#define DHTPIN_INT A1 //Pino de conexao
#define DHTTYPE DHT11 //Tipo de sensor
DHT dht_ext(DHTPIN_EXT, DHTTYPE); //Cria objeto DHT
DHT dht_int(DHTPIN_INT, DHTTYPE); //Cria objeto DHT

void setup() {
    Serial.begin(9600);     // Initialize serial communication
    rtc.begin();            // Initialize RTC

    if (! rtc.isrunning()) {
        Serial.println("RTC is NOT running!");
        // If RTC is not running, you may need to set the time here.
        // Use rtc.adjust(DateTime(year, month, day, hour, minute, second));
    }

  Serial.println("Data logger com sensor de temperatura DHT11");
  Serial.println();

  Serial.println("Iniciando cartao SD...");
  if (!SD.begin(Pino_CS))
  {
    Serial.println("Falha na inicializacao do SD!");
    return;
  }
  Serial.println("Cartao SD iniciado. OK");
  Serial.println();
  //Verifica as condicoes do RTC
  if (! rtc.begin())
  {
    Serial.println("RTC nao encontrado!");
    while (1);
  }
  if (! rtc.isrunning())
  {
    Serial.println("RTC nao operante!");
    //A linha abaixo ajusta o RTC com a data e hora do momento da compilacao
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //A linha abaixo permite ajustar manualmente a data e hora do RTC
    //Formato: DateTime(ano, mes, dia, hora, minuto, segundo)
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //Inicializa o DHT11
  dht_ext.begin();
  dht_int.begin();

  // Create a file for logging
  File dataFile = SD.open("TRIAL02.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Time;UR_INT;T_INT;UR_EXT;T_EXT");
    dataFile.close();
    Serial.println("Log file created.");
  } else {
    Serial.println("Error opening log file!");
  }  
}


void loop() 
{
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h_ext = dht_ext.readHumidity();
  float t_ext = dht_ext.readTemperature();

  float h_int = dht_int.readHumidity();
  float t_int = dht_int.readTemperature();
  
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t_ext) || isnan(h_ext)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  {
  // Log data to SD card
  logData(h_int, t_int, h_ext, t_ext);
  }

  // reads every 10 seconds
  delay(10000);
}


void logData(float hum1, float temp1, float hum2, float temp2) {
  // Get current date and time from RTC
  DateTime now = rtc.now();
  
  // Open the log file
  File dataFile = SD.open("TRIAL02.txt", FILE_WRITE);
  
  if (dataFile) {
    // Format datetime
    String dateTime = String(now.year()) + "-";
  
    if (now.month() < 10)
      dateTime += "0";
    dateTime += String(now.month()) + "-";
 
    if (now.day() < 10)
      dateTime += "0";
    dateTime += String(now.day()) + " ";
  
    if (now.hour() < 10)
      dateTime += "0";
    dateTime += String(now.hour()) + ":";
  
    if (now.minute() < 10)
      dateTime += "0";
    dateTime += String(now.minute()) + ":";
  
    if (now.second() < 10)
      dateTime += "0";
    dateTime += String(now.second());

    // Write data to file
    dataFile.print(dateTime);
    dataFile.print("; ");
    dataFile.print(hum1);
    dataFile.print("; ");
    dataFile.print(temp1);
    dataFile.print("; ");
    dataFile.print(hum2);
    dataFile.print("; ");
    dataFile.println(temp2);

    // Close the file
    dataFile.close();
  } else {
    Serial.println("Error opening log file for data logging!");
  }
}
