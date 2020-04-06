#include <Encoder.h>

#define IN1 8
#define IN2 9
#define IN3 11
#define IN4 12

Encoder encoder(2, 7);
Encoder encoder2(3, 6);

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(5, OUTPUT);
  analogWrite(5,220);

  pinMode(10, OUTPUT);
  analogWrite(10,220);

  Serial.begin(9600);
}

int contador = 1;
int leituraAnterior = 0;
int pulsosCm = 40;

void loop() {

  andaComEncoder(15);
  
  delay(1000);
}

void andaComEncoder(int pulsos){
  for(int i=0;i<pulsos;i++){
    frente();
    while (encoder2.read() <= 40 and encoder.read() <= 40) {
      Serial.print(encoder.read());
      Serial.print(" ");
      Serial.println(encoder2.read());
    }
    parar();
    Serial.print("Contagem final de pulsos ");
    Serial.print(encoder.read());
    Serial.print(" ");
    Serial.println(encoder2.read());
    encoder.write(0);
    encoder2.write(0);
  }
}

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
