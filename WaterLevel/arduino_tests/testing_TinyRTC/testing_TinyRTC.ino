#include <Wire.h>
//Carrega a biblioteca do RTC DS1307
#include <DS1307.h>
 
//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(A4, A5);

bool close_valve = true;

void setup () {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  //Aciona o relogio
  rtc.halt(false);
   
//  //As linhas abaixo setam a data e hora do modulo
//  //e podem ser comentada apos a primeira utilizacao
//  rtc.setDOW(WEDNESDAY);      //Define o dia da semana
//  rtc.setTime(23, 05, 0);     //Define o horario
//  rtc.setDate(26, 6, 2024);   //Define o dia, mes e ano

  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
   
  Serial.begin(9600);

  // start system with both valves closed
  digitalWrite(10, close_valve);
  digitalWrite(11, close_valve);
}

void loop () {
  
  //Mostra as informações no Serial Monitor
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));

  delay(15000);

//  // open grass valve for 45min
//  if (now.hour() == 17 && now.minute() >= 00 && now.minute() < 45){
  if (rtc.getTime().sec >= 30){
    digitalWrite(11, !close_valve);
    Serial.println("11 aberto");
  } else {
    digitalWrite(11, close_valve);
    Serial.println("11 fechado");
  }

//  // open garden valve for 15min
//  if (now.hour() == 17 && now.minute() >= 45 && now.minute() <= 59){
  if (rtc.getTime().sec >= 0 && rtc.getTime().sec < 30){
    digitalWrite(10, !close_valve);
    Serial.println("10 aberto");
  } else {
    digitalWrite(10, close_valve);
    Serial.println("10 fechado");
  }
  
}
