// Colocar aqui as coisas de configuração que não precisam ser mudadas depois

// CONSTANTES
#define PROMINI_ADDR 8
#define MPU6050_ADDR 0x68

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

// INSTANCIAÇÕES
A2a mini;
LCD_SSD1306 oled;
MPU6050 giro(Wire);

/// PINAGEM
//            13
//      09          14
//      10  11  12  15  

int s1, s2, s3, s4, s5;
int pinos1 = A11, pinos2 = A12, pinos3 = A13, pinos4 = A9, pinos5 = A14;
int pinoLeds[] = {51,52,53};
int sCorEsquerda = A10;
int sCorDireita = A15;
int ledEsq = 3, ledDir = 2;

// VARIAVEIS GLOBAIS

int corteB = 200, corteP = 400, cortePonta = 800;
int corteVerde = 350; // TAVA 300
int corteVerdeEsquerda = 400;

int mce, mcd;

boolean calibrado = true;

float coresEsquerda[] = {0,0,0};
float coresDireita[] = {0,0,0};
float calibBrancoEsquerda[] = {339,190,252};
float calibPretoEsquerda[] = {885,605,586};
float calibBrancoDireita[] = {339,190,252};
float calibPretoDireita[] = {885,605,586};
float cinzaDifEsquerda = 0, cinzaDifDireita = 0;

int mediaLeituras;

int Y;

// FUNÇÕES

void configuracaoInicial(){
  
  configuraOLED();
  configuraGiro();
  configuraSensores();
  mini.begin();

  mini.pinWireMode(PROMINI_ADDR, ledEsq, OUTPUT);
  mini.pinWireMode(PROMINI_ADDR, ledDir, OUTPUT);

}

//                    OLED                    //

void configuraOLED(){
  oled.begin();
}

//                   MPU6050                  //

void configuraGiro(){
  giro.begin();
  giro.setGyroOffsets(0.43, 0.93, -2.65);
}

void atualizaGiroscopio(){
  giro.update();
  Y = giro.getAngleY() * -1;
}

// SENSORES

void configuraSensores(){
  
  pinMode(pinoLeds[0], OUTPUT);// LED VERMELHO
  pinMode(pinoLeds[1], OUTPUT);// LED VERDE
  pinMode(pinoLeds[2], OUTPUT);// LED AZUL
  
  pinMode(pinos1, INPUT);
  pinMode(pinos2, INPUT);
  pinMode(pinos3, INPUT);
  pinMode(pinos4, INPUT);
  pinMode(pinos5, INPUT);

  pinMode(sCorEsquerda, INPUT);
  pinMode(sCorDireita, INPUT);

  checaCalibracao();

}

void checaCalibracao() {   
  if(calibrado == false){     
    calibracaoCor();   
  }
}

void calibracaoCor(){   
  Serial.println("Calibrando o branco");   
  delay(3000);   
  
  for(int i = 0;i<=2;i++){     
    digitalWrite(pinoLeds[i],HIGH);     
    delay(35);     
    mediaSensorCor(5, ESQUERDA);               
    calibBrancoEsquerda[i] = mediaLeituras;     
    mediaSensorCor(5, DIREITA);               
    calibBrancoDireita[i] = mediaLeituras;     
    digitalWrite(pinoLeds[i],LOW);     
    delay(35);   
  }

  Serial.println("Calibrando o preto");   
  delay(3000);   
  
  for(int i = 0;i<=2;i++){
    digitalWrite(pinoLeds[i],HIGH);
    delay(35);
    mediaSensorCor(5, ESQUERDA);               
    calibPretoEsquerda[i] = mediaLeituras;     
    mediaSensorCor(5, DIREITA);               
    calibPretoDireita[i] = mediaLeituras;
    digitalWrite(pinoLeds[i],LOW);
    delay(35);
  }   

  Serial.println("Sensor Calibrado");
  calibrado = true;
  delay(100);

  debugCalibracao();
}

//                   MOTORES                  //

void resetEncoder(){
  encoder.write(0);
  encoder2.write(0);
}

void frente() {
  mEsq.setSpeed(130);
  mDir.setSpeed(125);
  mEsq.run(FORWARD);
  mDir.run(FORWARD);
}

void direitaAlinha() {
  mDir.setSpeed(205);
  mEsq.setSpeed(120);
  mEsq.run(FORWARD);
  mDir.run(BACKWARD);
}

void direita() {
  mDir.setSpeed(170);
  mEsq.setSpeed(170);
  mEsq.run(FORWARD);
  mDir.run(BACKWARD);
}

void esquerdaAlinha(){
  mEsq.setSpeed(215);
  mDir.setSpeed(120);
  mEsq.run(BACKWARD);
  mDir.run(FORWARD);
}

void esquerda(){
  mDir.setSpeed(170);
  mEsq.setSpeed(170);
  mEsq.run(BACKWARD);
  mDir.run(FORWARD);
}

void tras(){
  mEsq.setSpeed(170);
  mDir.setSpeed(170);
  mEsq.run(BACKWARD);
  mDir.run(BACKWARD);
}

void parar() {
  mEsq.run(RELEASE);
  mDir.run(RELEASE);
}
