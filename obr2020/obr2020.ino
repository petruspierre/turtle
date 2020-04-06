// IMPORTAÇÃO DE BIBLIOTECAS
#include <U8g2lib.h>
#include <U8x8lib.h>
#include <A2a.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Encoder.h>
#include <AFMotor.h>

A2a mini;

void  setup () {

  Serial.begin(9600);
  configuracaoInicial();
  desenhaHeader();

  //andaComEncoder(75);
  
}

void  loop () {

  lerTCRT();
  verificaFaixa();
  
}
