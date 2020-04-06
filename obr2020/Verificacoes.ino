// Checar as condições

#define ESQUERDA 0
#define DIREITA 1
#define FRENTE 2

void verificaFaixa(){

  if(s4 <= cortePonta and s5 <= cortePonta){                                         // Se as duas pontas estiverem lendo branco
     
      // FUNÇÕES DE ALINHAMENTO
      if(s1 <= corteB and s2 >= corteP) 
          direitaAlinha();
      else if(s2 <= corteB and s1 >= corteP) 
          esquerdaAlinha();
      else 
          frente();
          
  } 
  
  else {                                                                             // Se alguma ponta não estiver branca
      parar(); 
      lerCores();
  
      if(s5 > cortePonta and mcd > corteVerde and mce > corteVerdeEsquerda){         // Se a ponta preta for a da direita e enxergar não-verde na cor, faz o noventa ou T
        
          frente();
          delay(30);
          s3 = analogRead(pinos3);
          if(s3 <= corteP) noventaDireita(); // Se a frente for branco, faz noventa
        
      } 
      
      else if(s4 > cortePonta and mcd > corteVerde and mce > corteVerdeEsquerda){    // Se a ponta preta for a da esquerda e enxergar não-verde na cor, faz o noventa ou T
        
          frente();
          delay(30);
          s3 = analogRead(pinos3);
          if(s3 <= corteP) noventaEsquerda();                                        // Se a frente for branco, faz noventa
        
      }

      else if(mcd <= corteVerde and mce > corteVerdeEsquerda){                       // Se for verde na direita e não-verda na esquerda, faz o verde pra direita
          verdeDireita();
      } 

      else if(mce <= corteVerdeEsquerda and mcd > corteVerde) {                      // Se for verde na esquerda e não-verda na direita, faz o verde pra esquerda
          verdeEsquerda();
      }

      else if(mce <= corteVerdeEsquerda and mcd <= corteVerde){                      // Se for verde em ambos, faz beco sem saída
          becoSemSaida();
      }
  }
}
