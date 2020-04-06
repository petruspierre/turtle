// Apenas para depuração do código

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

double menuAtual = 0.1;

void debug(String x){
  Serial.println(x);
}

void debugOLED(byte x, byte y, String msg, int _size){
  oled.clear();
  oled.setFontSize(_size);
  oled.setCursor(x,y);
  oled.println(msg.c_str());
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
}

void debugCalibracao(){
    Serial.println(String(int(calibBrancoEsquerda[0])) + "," + String(int(calibBrancoEsquerda[1])) + "," + String(int(calibBrancoEsquerda[2])));
    Serial.println(String(int(calibPretoEsquerda[0])) + "," + String(int(calibPretoEsquerda[1])) + "," + String(int(calibPretoEsquerda[2])));
}

void debugAcao(String msg){
  Serial.println("Ação realizada:");
  Serial.println(msg);
  Serial.println();
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

void printarEncoder(){
  debug(String("- E: ") +  String(encoder2.read()) + String(" D:") + String(encoder.read()));
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
