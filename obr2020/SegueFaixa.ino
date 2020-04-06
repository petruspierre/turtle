// Executa as ações do segue faixa

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

void noventaDireita(){
  debugCores();
  debugAcao("90 direita");
  debugLED(DIREITA);
  
  andaComEncoder(7);
  direita();
  s2 = analogRead(pinos2);
  while(s2 <= corteP){
    s2 = analogRead(pinos2);
    delay(2);
  } 
  
  debugLED(FRENTE);
}

void noventaEsquerda(){
  debugAcao("90 esquerda");
  debugLED(ESQUERDA);
  
  andaComEncoder(7);
  esquerda();
  s1 = analogRead(pinos1);
  while(s1 <= corteP){
    s1 = analogRead(pinos1);
    delay(2);
  }
  
  debugLED(FRENTE);
}

void verdeDireita(){
  debugAcao("verde direita");
  debugLED(DIREITA);
  
  andaComEncoder(7);
  direita();
  delay(300);
  s2 = analogRead(pinos2);
  while(s2 <= corteP){
    s2 = analogRead(pinos2);
    delay(2);
  }
  
  debugLED(FRENTE);
}

void verdeEsquerda(){
  debugAcao("verde esquerda");
  debugLED(ESQUERDA);
  
  andaComEncoder(7);
  esquerda();
  delay(300);
  s1 = analogRead(pinos1);
  while(s1 <= corteP){
    s1 = analogRead(pinos1);
    delay(2);
  }
 
  debugLED(FRENTE);
}

void becoSemSaida(){
  debugAcao("Beco sem saída");
  debugLED(-1);
  
  direita();
  delay(750);
  s2 = analogRead(pinos2);
  while(s2 <= corteP){
    s2 = analogRead(pinos2);
    delay(2);
  }
  
  debugLED(FRENTE);
}
