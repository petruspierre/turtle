// INCLUSÃO DE BIBLIOTECAS
#include <A2a.h>

// DEFINIÇÃO DO ENDEREÇO DO SLAVE
#define endereco 8

// DEFINIÇÕES DE PINOS DO SLAVE
#define pinLED   6

// INSTANCIANDO OBJETOS
A2a arduinoSlave;

void setup() {
  // INICIA A COMUNICAÇÃO ENTRE ARDUINOS
  arduinoSlave.begin(); 

  // ENVIA O pinMode PARA O SLAVE
  arduinoSlave.pinWireMode(endereco, pinLED, OUTPUT);
}

void loop() {
    arduinoSlave.digitalWireWrite(endereco, pinLED, HIGH);
    delay(250);
    arduinoSlave.digitalWireWrite(endereco, pinLED, LOW);
    delay(250);
}
