#include <Wire.h>
//Carrega a biblioteca do RTC DS1307
#include <DS1307.h>
 
//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(A4, A5);

bool close_valve = true;

void setup () {
  pinMode(10, OUTPUT); // laranja - 1
  pinMode(11, OUTPUT); // amarelo - 2

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
  
  delay(1);
  digitalWrite(10, !close_valve); // laranja - 1
  digitalWrite(11, !close_valve);  // amarelo - 2

//  delay(15000);
//
//  if (rtc.getTime().sec >= 30){
//    digitalWrite(11, !close_valve);
//  } else {
//    digitalWrite(11, close_valve);
//  }
//
//  if (rtc.getTime().sec >= 0 && rtc.getTime().sec < 30){
//    digitalWrite(10, !close_valve);
//  } else {
//    digitalWrite(10, close_valve);
//  }

}
