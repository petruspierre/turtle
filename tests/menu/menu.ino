#include <Chrono.h>
#include <LightChrono.h>

#include <Arduino.h>
#include <Wire.h>
#include <MicroLCD.h>
#include <MPU6050_tockn.h>

LCD_SSD1306 lcd;
MPU6050 mpu6050(Wire);

int selecao = 1;
int cont=0;
double menuAtual = 0.1;
int a;
int y;

Chrono leituraGiro;

const PROGMEM uint8_t alpha[48 * 48 / 8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0x7E, 0x7E,
  0xFE, 0xFE, 0xFC, 0xF8, 0xF0, 0x70, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF,
  0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0x0F, 0x19, 0x10, 0x30, 0x20, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC1,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F,
  0xFF, 0xFE, 0xFE, 0xFC, 0xF8, 0xF0, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xFE,
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const PROGMEM uint8_t dist_vazio [32 * 32 / 8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

const PROGMEM uint8_t dist_1 [32 * 32 / 8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

const PROGMEM uint8_t dist_2 [32 * 32 / 8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

const PROGMEM uint8_t dist_3 [32 * 32 / 8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};

const PROGMEM uint8_t dist_4 [32 * 32 / 8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

const PROGMEM uint8_t obs [32 * 32 / 8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x92, 0x92, 0x92, 0x9E, 0x92, 0xF2, 0x92,
  0x9E, 0x92, 0xF2, 0x92, 0x92, 0x9E, 0xF2, 0x92, 0x92, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x24, 0x24, 0x27, 0xE4, 0x3C, 0x24, 0xE7,
  0x24, 0x24, 0x3C, 0x24, 0xE7, 0x24, 0x3C, 0x24, 0x24, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x04, 0x06, 0xFF, 0xFF, 0x06, 0x04, 0x00, 0xFF, 0x49, 0x49, 0x79, 0xC9, 0x4F, 0x49, 0x79,
  0x49, 0xCF, 0x49, 0x49, 0x79, 0xC9, 0x4F, 0x49, 0x49, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7F, 0x7F, 0x60, 0x60, 0x60, 0x63, 0x62, 0x62, 0x62, 0x63, 0x62, 0x62, 0x62,
  0x62, 0x63, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const PROGMEM uint8_t sem_obs [32 * 32 / 8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0xFC,
  0xFC, 0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
  0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const PROGMEM uint8_t sobe_rampa [32 * 32 / 8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x71, 0x3B, 0x1F, 0x0F, 0x1F, 0x3F,
  0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x81, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0x80, 0xC0, 0xE0, 0xB0, 0x98, 0x8C, 0x86, 0x83, 0x81, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF
};

const PROGMEM uint8_t desce_rampa [32 * 32 / 8] = {
  0xFF, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x81,
  0x03, 0x07, 0x0E, 0x1C, 0xB8, 0xF0, 0xE0, 0xF0, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x03, 0x06, 0x0C, 0x19, 0x31, 0x61, 0xC1, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x83, 0x86, 0x8C, 0x98, 0xB0, 0xE0, 0xC0, 0x80
};

const PROGMEM uint8_t no_plano [32 * 32 / 8] = {
  0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x18, 0x08, 0x08,
  0x08, 0x18, 0xF0, 0x00, 0x04, 0x0A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x30, 0x20, 0x20,
  0x20, 0x30, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00
};


const PROGMEM uint8_t arrow[8] = {0x18, 0x18, 0x18, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
const PROGMEM uint8_t limpa[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void setup()
{
  pinMode(13, INPUT_PULLUP);
  
  lcd.begin();
  mpu6050.begin();
  mpu6050.setGyroOffsets(0.43, 0.93, -2.65);
  mudaTela(0.1);
  
}

void loop()
{
  mpu6050.update();
  y = mpu6050.getAngleY() * -1;
  a = digitalRead(13);
  
  if(menuAtual == 3 && leituraGiro.hasPassed(500)){
    debugGiroDisplay();
  }

  handleTela();
}

void handleTela(){
  if(!a){
    if(menuAtual == 0.1){
      contaBotao();
      mudaTela(0);
      seleciona(selecao);
    } else if(menuAtual == 0){
      contaBotao();
      if(cont > 500 and cont < 3000){
        mudaTela(selecao);
      } else if(cont > 3000){
        mudaTela(0.1);
      } else {
        selecao++;
        if(selecao > 4) selecao = 1;
        seleciona(selecao); 
      }
    } else if(menuAtual == 2 || menuAtual == 2.1){
      contaBotao();
      if(cont > 500){
        mudaTela(0);
        seleciona(selecao); 
      }
      else {
        menuAtual == 2 ? mudaTela(2.1) : mudaTela(2);
      }
    } else if(menuAtual == 4 || menuAtual == 4.1){
      contaBotao();
      if(cont > 500){
        mudaTela(0);
        seleciona(selecao); 
      }
      else {
        menuAtual == 4 ? mudaTela(4.1) : mudaTela(4);
      }
    }
    else {
      contaBotao();
      if(cont > 500){
        mudaTela(0);
        seleciona(selecao);
      } 
    }
   cont=0; 
  }
}

void contaBotao(){
  while(!a){
    cont++;
    a = digitalRead(13);
    delay(1);
  }
}

void debugGiroDisplay(){
  leituraGiro.restart();
  lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.setCursor(56,3);
  lcd.print("     ");
  y >= 100 ? lcd.setCursor(56,3) : lcd.setCursor(64,3);
  lcd.print(String(y));
  lcd.setFontSize(FONT_SIZE_MEDIUM);
  lcd.setCursor(0,5);
  lcd.print("              ");
  lcd.setCursor(0,5);
  if(y < 80) {
    lcd.print("Descendo Rampa");
  } else if( y > 100 ){
    lcd.print(" Subindo Rampa");
  } else {
    lcd.print("   No plano");
  }
}

void mudaTela(double tela){
  lcd.clear();
  if(tela == 0){
    menuAtual = 0;
    desenhaLogo(0,2);
    desenhaMenu();
  } else if(tela == 0.1){
    menuAtual = 0.1;
    desenhaLogo(24,1);
  } else if(tela == 1){
    menuAtual = 1;
    lcd.setCursor(8,2);
    lcd.draw(obs,32,32);
    lcd.setCursor(88,2);
    lcd.draw(sobe_rampa,32,32);
  } else if(tela == 2){
    menuAtual = 2;
    lcd.setCursor(48,0);
    lcd.setFontSize(FONT_SIZE_XLARGE);
    lcd.println("TCRT");
    lcd.setFontSize(FONT_SIZE_MEDIUM);
    lcd.setCursor(48,2);
    lcd.println("1024");
    lcd.setCursor(0,4);
    lcd.println("1024");
    lcd.setCursor(92,4);
    lcd.println("1024");
    lcd.setCursor(24,6);
    lcd.println("1024");
    lcd.setCursor(72,6);
    lcd.println("1024");
  } else if(tela == 2.1) {
    menuAtual = 2.1;
    lcd.setCursor(0,0);
    lcd.setFontSize(FONT_SIZE_XLARGE);
    lcd.println("      COR");
    lcd.setFontSize(FONT_SIZE_MEDIUM);
    lcd.setCursor(24,4);
    lcd.println("1024");
    lcd.setCursor(72,4);
    lcd.println("1024");
    lcd.setFontSize(FONT_SIZE_SMALL);
    lcd.setCursor(24,6);
    lcd.println("VERDE");
    lcd.setCursor(72,6);
    lcd.println("N-VERDE");
  } else if(tela == 3){
    menuAtual = 3;
    lcd.setCursor(0,0);
    lcd.setFontSize(FONT_SIZE_XLARGE);
    lcd.println("  GIROSCOPIO");
    lcd.setCursor(40,3);
    lcd.print("Y:");
  } else if(tela == 4) {
    menuAtual = 4;
    lcd.setCursor(0,0);
    lcd.setFontSize(FONT_SIZE_XLARGE);
    lcd.println("   ULTRASSOM");
    lcd.setCursor(24,2);
    lcd.draw(dist_3, 32, 32);
    lcd.setCursor(32,6);
    lcd.println("12");
    lcd.setCursor(74,2);
    lcd.draw(dist_2, 32, 32);
    lcd.setCursor(82,6);
    lcd.println("30");
  } else if(tela == 4.1){
    menuAtual = 4.1;
    lcd.setCursor(0,0);
    lcd.setFontSize(FONT_SIZE_XLARGE);
    lcd.println(" FIM DE CURSO");
  }
}

void seleciona(int x){
  
  switch(x){
    case 1:
      lcd.setCursor(80,14);
      lcd.draw(limpa, 8, 8);
      lcd.setCursor(80,11);
      lcd.draw(arrow, 8, 8);
      break;
    case 2:
      lcd.setCursor(80,11);
      lcd.draw(limpa, 8, 8);
      lcd.setCursor(80,12);
      lcd.draw(arrow, 8, 8);
      break;
    case 3:
      lcd.setCursor(80,12);
      lcd.draw(limpa, 8, 8);
      lcd.setCursor(80,13);
      lcd.draw(arrow, 8, 8);
      break;
    case 4:
      lcd.setCursor(80,13);
      lcd.draw(limpa, 8, 8);
      lcd.setCursor(80,11);
      lcd.draw(limpa, 8, 8);
      lcd.setCursor(80,14);
      lcd.draw(arrow, 8, 8);
      break;
  }
}

void desenhaMenu(){
  lcd.setFontSize(FONT_SIZE_SMALL);
  lcd.setCursor(90,11);
  lcd.println("TUDO");
  lcd.setCursor(90,12);
  lcd.println("FAIXA");
  lcd.setCursor(90,13);
  lcd.println("GIRO");
  lcd.setCursor(90,14);
  lcd.println("DIST");
}

void desenhaLogo(int x, int y){
  lcd.setCursor(x+1, y+0);
  lcd.draw(alpha, 48, 48);
  lcd.setCursor(x+27,y+10);
  lcd.setFontSize(FONT_SIZE_LARGE);
  lcd.println("ALPHA");
  lcd.setCursor(x+27,y+12);
  lcd.setFontSize(FONT_SIZE_SMALL);
  lcd.println("IFPB");
}
