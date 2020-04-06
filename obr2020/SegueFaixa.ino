// Executa as ações do segue faixa

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

void noventaDireita(){
  desenhaHeader();
  desenhaSeta(ESQUERDA);
  debugCores();
  Serial.println("90 direita");
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, HIGH);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, LOW);
  andaComEncoder(7);
  direita();
  s2 = analogRead(pinos2);
  while(s2 <= corteP){
    s2 = analogRead(pinos2);
    delay(2);
  } 
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, LOW);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, LOW);
}

void noventaEsquerda(){
  desenhaHeader();
  desenhaSeta(ESQUERDA);
  Serial.println("90 esquerda");
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, LOW);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, HIGH);
  andaComEncoder(7);
  esquerda();
  s1 = analogRead(pinos1);
  while(s1 <= corteP){
    s1 = analogRead(pinos1);
    delay(2);
  }
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, LOW);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, LOW);
}

void verdeDireita(){
  desenhaHeader();
  desenhaSeta(DIREITA);
  Serial.println("verde direita");
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, HIGH);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, LOW);
  andaComEncoder(7);
  direita();
  delay(300);
  s2 = analogRead(pinos2);
  while(s2 <= corteP){
    s2 = analogRead(pinos2);
    delay(2);
  }
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, LOW);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, LOW);
}

void verdeEsquerda(){
  desenhaHeader();
  desenhaSeta(ESQUERDA);
  Serial.println("verde esquerda");
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, LOW);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, HIGH);
  andaComEncoder(7);
  esquerda();
  delay(300);
  s1 = analogRead(pinos1);
  while(s1 <= corteP){
    s1 = analogRead(pinos1);
    delay(2);
  }
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, LOW);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, LOW);
}

void becoSemSaida(){
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, HIGH);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, HIGH);
  Serial.println("beco");
  direita();
  delay(750);
  s2 = analogRead(pinos2);
  while(s2 <= corteP){
    s2 = analogRead(pinos2);
    delay(2);
  }
  mini.digitalWireWrite(PROMINI_ADDR, ledEsq, LOW);
  mini.digitalWireWrite(PROMINI_ADDR, ledDir, LOW);
}
