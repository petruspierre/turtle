// Leitura de sensores
#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

void mediaSensorCor(int vezes, int lado){
  int leituras;
  int somatorio=0;
  for(int i = 0;i < vezes;i++){
    lado == ESQUERDA ? leituras = analogRead(sCorEsquerda) : leituras = analogRead(sCorDireita);
    somatorio = leituras + somatorio;
    delay(5);
  }   
  mediaLeituras = (somatorio)/vezes;
}

void lerCores(){   
  for(int i = 0;i<=2;i++){
    digitalWrite(pinoLeds[i],HIGH);
    delay(10);
    
    mediaSensorCor(5, ESQUERDA);
    coresEsquerda[i] = mediaLeituras;
    mediaSensorCor(5, DIREITA);
    coresDireita[i] = mediaLeituras;

    cinzaDifEsquerda = calibBrancoEsquerda[i] - calibPretoEsquerda[i];
    cinzaDifDireita = calibBrancoDireita[i] - calibPretoDireita[i];
    
    coresEsquerda[i] = (coresEsquerda[i] - calibPretoEsquerda[i])/(cinzaDifEsquerda)*1024;
    coresDireita[i] = (coresDireita[i] - calibPretoDireita[i])/(cinzaDifDireita)*1024;
    
    digitalWrite(pinoLeds[i],LOW);
    delay(10);
  }

  mce = (int(coresEsquerda[0])*3 + int(coresEsquerda[1]) + int(coresEsquerda[2])*2) / 6;
  mcd = (int(coresDireita[0])*3 + int(coresDireita[1]) + int(coresDireita[2])*2) / 6;
}

void lerTCRT(){
  s1 = analogRead(pinos1);
  delay(1);
  s2 = analogRead(pinos2);
  delay(1);
  s3 = analogRead(pinos3);
  delay(1);
  s4 = analogRead(pinos4);
  delay(1);
  s5 = analogRead(pinos5);
}
