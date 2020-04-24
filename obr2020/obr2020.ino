// IMPORTAÇÃO DE BIBLIOTECAS
#include <Chrono.h>
#include <A2a.h>
#include <Encoder.h>
#include <Wire.h>
#include <Arduino.h>
#include <MicroLCD.h>
#include <MPU6050_tockn.h>
#include <AFMotor.h>

boolean rampa = false;

void  setup () {

  Serial.begin(9600);
  configuracaoInicial();
  
}

void  loop () {

  atualizaGiroscopio();
  lerTCRT();
  if(!rampa) verificaFaixa();
  
}
