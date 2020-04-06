// Checar as condições

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

void verificaFaixa(){
  if(s4 <= cortePonta and s5 <= cortePonta){
    if(s1 <= corteB and s2 >= corteP){
      direitaAlinha();
    } else if(s2 <= corteB and s1 >= corteP){
      esquerdaAlinha();
    } else {
      frente();
    } 
  } else {
    parar();
    lerCores();
    
    if(s5 > cortePonta and mcd > corteVerde and mce > corteVerdeEsquerda){
      frente();
      delay(30);
      s3 = analogRead(pinos3);
      if(s3 <= corteP){
        noventaDireita();
      }
    } else if(s4 > cortePonta and mcd > corteVerde and mce > corteVerdeEsquerda){
      frente();
      delay(30);
      s3 = analogRead(pinos3);
      if(s3 <= corteP){
        noventaEsquerda();
      }
    }

    else if(mcd <= corteVerde and mce > corteVerdeEsquerda){
      verdeDireita();
    } 

    else if(mce <= corteVerdeEsquerda and mcd > corteVerde) {
      verdeEsquerda();
    }

    else if(mce <= corteVerdeEsquerda and mcd <= corteVerde){
      becoSemSaida();
    }
  }
}
