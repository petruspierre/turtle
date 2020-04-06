#include <U8x8lib.h>

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);        

//https://github.com/olikraus/u8g2/wiki/fntgrpiconic#open_iconic_arrow_1x1

void setup(void){
  
  configuraOLED();
  
}

void configuraOLED(){
  u8x8.begin();
  u8x8.setPowerSave(0);
}

void desenhaBarra(uint8_t c, uint8_t is_inverse){  
  uint8_t r;
  u8x8.setInverseFont(is_inverse);
  for( r = 0; r < u8x8.getRows(); r++ )
  {
    u8x8.setCursor(c, r);
    u8x8.print(" ");
  }
}

void limpaTelaComBarra(){
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  desenhaBarra(0, 1);
  for(uint8_t c = 1; c < u8x8.getCols(); c++ )
  {
    desenhaBarra(c, 1);
    desenhaBarra(c-1, 0);
    delay(50);
  }
  desenhaBarra(u8x8.getCols()-1, 0);
}

void desenhaHeader(){
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);    
  u8x8.clear();
  u8x8.inverse();
  u8x8.print("    OBR 2020    ");
  u8x8.noInverse();
}

void desenhaSeta(int dir){
  u8x8.setFont(u8x8_font_open_iconic_arrow_4x4);
  switch(dir){
    case ESQUERDA:
      u8x8.drawGlyph(0, 3, '@'+1);
      break;
    case FRENTE:
      u8x8.drawGlyph(6, 2, '@'+3);
      break;
    case DIREITA:
      u8x8.drawGlyph(12, 3, '@'+2);
      break;
  }
}

void loop(void){
  
  desenhaHeader();

  desenhaSeta(ESQUERDA);
  desenhaSeta(FRENTE);
  desenhaSeta(DIREITA);

  delay(2000);

  limpaTelaComBarra();

  
}
