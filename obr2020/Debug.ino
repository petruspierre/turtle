// Apenas para depuração do código

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

void debug(String x){
  Serial.println(x);
}

void debugOLED(byte x, byte y, String msg){
  oled.drawString(x,y,msg.c_str());
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

void debugCores(){   
  Serial.print(s3);
  Serial.print("   ");
    
  Serial.print("R = ");
  Serial.print(int(coresEsquerda[0]));   
  Serial.print(" G = ");
  Serial.print(int(coresEsquerda[1]));   
  Serial.print(" B = ");
  Serial.print(int(coresEsquerda[2]));
  Serial.print(" M = ");
  Serial.print(mce);
  Serial.print(" | R = ");
  Serial.print(int(coresDireita[0]));   
  Serial.print(" G = ");
  Serial.print(int(coresDireita[1]));   
  Serial.print(" B = ");
  Serial.print(int(coresDireita[2]));
  Serial.print(" M = ");
  Serial.println(mcd);

  oled.setFont(u8x8_font_amstrad_cpc_extended_f);    
  oled.drawString(0,2, "Leitura: ");
  oled.setFont(u8x8_font_courB18_2x3_f);    
  String msg = (String(mce) + "|" + String(mcd));
  oled.drawString(0,4, "                ");
  oled.drawString(0,4, msg.c_str()); 
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

void debugTCRT(){
  lerTCRT();
  Serial.print(s4);
  Serial.print(" ");
  Serial.print(s3);
  Serial.print(" ");
  Serial.println(s5);
  Serial.print("  ");
  Serial.print(s1);
  Serial.print(" ");
  Serial.println(s2);
  Serial.println("\n\n\n");
}

void debugLED(int lado){
  switch(lado){
    case DIREITA:
      mini.digitalWireWrite(PROMINI_ADDR, ledEsq, HIGH);
      mini.digitalWireWrite(PROMINI_ADDR, ledDir, LOW);
      break;
    case ESQUERDA:
      mini.digitalWireWrite(PROMINI_ADDR, ledEsq, LOW);
      mini.digitalWireWrite(PROMINI_ADDR, ledDir, HIGH);
      break;
    case FRENTE:
      mini.digitalWireWrite(PROMINI_ADDR, ledEsq, LOW);
      mini.digitalWireWrite(PROMINI_ADDR, ledDir, LOW);
      break;
    default:
      mini.digitalWireWrite(PROMINI_ADDR, ledEsq, HIGH);
      mini.digitalWireWrite(PROMINI_ADDR, ledDir, HIGH);
  }
}
