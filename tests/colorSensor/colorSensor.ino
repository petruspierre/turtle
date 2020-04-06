#include <U8g2lib.h>
#include <U8x8lib.h>
#include <Wire.h>
#include <A2a.h>

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

#define endereco 8
#define pinLED1   2
#define pinLED2   3

A2a mini;

U8X8_SSD1306_128X64_NONAME_HW_I2C oled(U8X8_PIN_NONE);   

//            13
//      09          14
//      10  11  12  15  
int pinosTCRT[] = {9,13,14,12,11};

int pinoLeds[] = {51,52,53};
int sCorEsquerda = 10;
int sCorDireita = 15;

boolean calibrado = true;

float coresEsquerda[] = {0,0,0};
float coresDireita[] = {0,0,0};

float calibBrancoEsquerda[] = {339,190,252};
float calibPretoEsquerda[] = {885,605,586};
float calibBrancoDireita[] = {339,190,252};
float calibPretoDireita[] = {885,605,586};
float cinzaDifEsquerda = 0, cinzaDifDireita = 0;

int mediaLeituras;

void setup(){   

  mini.begin(); 

  pinMode(pinoLeds[0], OUTPUT);// LED VERMELHO
  pinMode(pinoLeds[1], OUTPUT);// LED VERDE
  pinMode(pinoLeds[2], OUTPUT);// LED AZUL

  pinMode(pinosTCRT[0], INPUT);
  pinMode(pinosTCRT[1], INPUT);
  pinMode(pinosTCRT[2], INPUT);
  pinMode(pinosTCRT[3], INPUT);
  pinMode(pinosTCRT[4], INPUT);

  mini.pinWireMode(endereco, pinLED1, OUTPUT);
  mini.pinWireMode(endereco, pinLED2, OUTPUT);

  mini.digitalWireWrite(endereco, pinLED1, HIGH);
  mini.digitalWireWrite(endereco, pinLED2, HIGH);

  configuraOLED();
  Wire.begin();
  desenhaHeader();
  
  Serial.begin(9600);

}

void loop()
{   

  checaCalibracao();    
  lerCores();   
  debugCores();
  //lerTCRT();

}

void lerTCRT(){
  Serial.print(analogRead(pinosTCRT[0]));
  Serial.print(" ");
  Serial.print(analogRead(pinosTCRT[1]));
  Serial.print(" ");
  Serial.println(analogRead(pinosTCRT[2]));
  Serial.print("  ");
  Serial.print(analogRead(pinosTCRT[3]));
  Serial.print(" ");
  Serial.println(analogRead(pinosTCRT[4]));
  Serial.println();
}

void configuraOLED(){
  oled.begin();
  oled.setPowerSave(0);
}

void desenhaBarra(uint8_t c, uint8_t is_inverse){  
  uint8_t r;
  oled.setInverseFont(is_inverse);
  for( r = 0; r < oled.getRows(); r++ )
  {
    oled.setCursor(c, r);
    oled.print(" ");
  }
}

void limpaTelaComBarra(){
  oled.setFont(u8x8_font_chroma48medium8_r);
  desenhaBarra(0, 1);
  for(uint8_t c = 1; c < oled.getCols(); c++ )
  {
    desenhaBarra(c, 1);
    desenhaBarra(c-1, 0);
    delay(50);
  }
  desenhaBarra(oled.getCols()-1, 0);
}

void desenhaHeader(){
  oled.setFont(u8x8_font_amstrad_cpc_extended_f);    
  oled.clear();
  oled.inverse();
  oled.print("   IFPB ALPHA   ");
  oled.noInverse();
}

void desenhaSeta(int dir){
  oled.setFont(u8x8_font_open_iconic_arrow_4x4);
  switch(dir){
    case ESQUERDA:
      oled.drawGlyph(0, 3, '@'+1);
      break;
    case FRENTE:
      oled.drawGlyph(6, 2, '@'+3);
      break;
    case DIREITA:
      oled.drawGlyph(12, 3, '@'+2);
      break;
  }
}

void checaCalibracao() {   
  if(calibrado == false){     
    calibracao();   
  }
}

void calibracao(){   
  Serial.println("Calibrando o branco");   
  delay(3000);   
  
  for(int i = 0;i<=2;i++){     
    digitalWrite(pinoLeds[i],HIGH);     
    delay(35);     
    mediaSensor(5, ESQUERDA);               
    calibBrancoEsquerda[i] = mediaLeituras;     
    mediaSensor(5, DIREITA);               
    calibBrancoDireita[i] = mediaLeituras;     
    digitalWrite(pinoLeds[i],LOW);     
    delay(35);   
  }

  Serial.println("Calibrando o preto");   
  delay(3000);   
  
  for(int i = 0;i<=2;i++){
    digitalWrite(pinoLeds[i],HIGH);
    delay(35);
    mediaSensor(5, ESQUERDA);               
    calibPretoEsquerda[i] = mediaLeituras;     
    mediaSensor(5, DIREITA);               
    calibPretoDireita[i] = mediaLeituras;
    digitalWrite(pinoLeds[i],LOW);
    delay(35);
  }   

  Serial.println("Sensor Calibrado");
  calibrado = true;
  delay(100);

  debugCalibracao();
}
  
void lerCores(){   
  for(int i = 0;i<=2;i++){
    digitalWrite(pinoLeds[i],HIGH);
    delay(10);
    
    mediaSensor(5, ESQUERDA);
    coresEsquerda[i] = mediaLeituras;
    mediaSensor(5, DIREITA);
    coresDireita[i] = mediaLeituras;

    cinzaDifEsquerda = calibBrancoEsquerda[i] - calibPretoEsquerda[i];
    cinzaDifDireita = calibBrancoDireita[i] - calibPretoDireita[i];
    
    coresEsquerda[i] = (coresEsquerda[i] - calibPretoEsquerda[i])/(cinzaDifEsquerda)*1024;
    coresDireita[i] = (coresDireita[i] - calibPretoDireita[i])/(cinzaDifDireita)*1024;
    
    digitalWrite(pinoLeds[i],LOW);
    delay(10);
  }
}

void mediaSensor(int vezes, int lado){
  int leituras;
  int somatorio=0;
  for(int i = 0;i < vezes;i++){
    lado == ESQUERDA ? leituras = analogRead(sCorEsquerda) : leituras = analogRead(sCorDireita);
    somatorio = leituras + somatorio;
    delay(5);
  }   
  mediaLeituras = (somatorio)/vezes;
}

void debugCalibracao(){
    oled.setFont(u8x8_font_chroma48medium8_r);
    oled.drawString(0,3, "Branco: ");  

    String msg = (String(int(calibBrancoEsquerda[0])) + "," + String(int(calibBrancoEsquerda[1])) + "," + String(int(calibBrancoEsquerda[2])));
    oled.drawString(0,4, msg.c_str());

    oled.drawString(0,6, "Preto: ");

    msg = (String(int(calibPretoEsquerda[0])) + "," + String(int(calibPretoEsquerda[1])) + "," + String(int(calibPretoEsquerda[2])));
    oled.drawString(0,7, msg.c_str());

    Serial.println(String(int(calibBrancoEsquerda[0])) + "," + String(int(calibBrancoEsquerda[1])) + "," + String(int(calibBrancoEsquerda[2])));
    Serial.println(String(int(calibPretoEsquerda[0])) + "," + String(int(calibPretoEsquerda[1])) + "," + String(int(calibPretoEsquerda[2])));
    
}

void debugCores(){   
  Serial.print("R = ");
  Serial.print(int(coresEsquerda[0]));   
  Serial.print(" G = ");
  Serial.print(int(coresEsquerda[1]));   
  Serial.print(" B = ");
  Serial.print(int(coresEsquerda[2]));
  Serial.print(" M = ");
  Serial.print((int(coresEsquerda[0]) + int(coresEsquerda[1]) + int(coresEsquerda[2])) / 3);
  Serial.print(" | R = ");
  Serial.print(int(coresDireita[0]));   
  Serial.print(" G = ");
  Serial.print(int(coresDireita[1]));   
  Serial.print(" B = ");
  Serial.print(int(coresDireita[2]));
  Serial.print(" M = ");
  Serial.println((int(coresDireita[0]) + int(coresDireita[1]) + int(coresDireita[2])) / 3);

  oled.setFont(u8x8_font_amstrad_cpc_extended_f);    
  oled.drawString(0,2, "Leitura: ");
  oled.setFont(u8x8_font_courB18_2x3_f);    
  String msg = (String(((int(coresEsquerda[0]) + int(coresEsquerda[1]) + int(coresEsquerda[2])) / 3)) + "|" + String(((int(coresDireita[0]) + int(coresDireita[1]) + int(coresDireita[2])) / 3)));
  oled.drawString(0,4, "                ");
  oled.drawString(0,4, msg.c_str()); 
}
