// Colocar aqui a parte de movimentação

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

AF_DCMotor mEsq(2);
AF_DCMotor mDir(3);

Encoder encoder(18, 22);
Encoder encoder2(19, 23);

// ainda da pra criar outra função tipo andaComEncoderFator10
void andaComEncoder(int cm){

  mEsq.setSpeed(245);
  mDir.setSpeed(255);
  
  for(int i = 0; i < cm; i++){
    
    frente();
    debug("---=== ENCODER ===---");
    
    while (encoder2.read() <= 40 and encoder.read() <= 40) {
      printarEncoder();
    }
    
    parar();
    debug(String("--- Contagem final de pulsos: E: ") + String(encoder2.read()) + String(" D:") + String(encoder.read()));
    resetEncoder();
  }
  mEsq.setSpeed(120);
  mDir.setSpeed(120);
  
}

void giraNoventaGraus(int lado){
  switch(lado){
    case DIREITA:
      break;
    case ESQUERDA:
      break;
  }
}

void gira180(){
  
}
