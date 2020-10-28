#include <Arduino.h>
#include "cis.h"


typedef struct 
{
  String nome;
  String numero;
  int numerosDePinos = 14;
  String casosDeTeste[4];

} CI;


CI getCiDados(String nome);
boolean buscaCiAuto();
boolean buscaCiManual(String nomeDoCi);
bool testCi(String caso, int pinagem);


int pinos14[] = {2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2};
String cis[] = {ciNand,ciAnd,ciNor,ciNot,ciOr,ciXor};
boolean resultado = true;
CI ci;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
  
  Serial.println("Iniciando o teste do CI. Defina o modo:\nbusca Manual = 1\nbusca automatica = 0");
}

void loop() {
  // put your main code here, to run repeatedly:

  
  if(Serial.available() > 0){
    
    switch (Serial.read())
    {
    case '0': resultado = buscaCiAuto();
            Serial.println(resultado); 
      break;

    case '1': Serial.print("Digite o nome do CI: ");
            ci.nome = Serial.readString();
            ci.nome.toUpperCase();
            resultado = buscaCiManual(ci.nome);
      break;
    
    default: Serial.println("Valor digitado incorreto!!!");
      break;
    }
  }
  

}

boolean buscaCiAuto(){

  boolean resultado = true;
  CI ci;

  for(int i = 0; i < 6; i++){
    ci = getCiDados(cis[i]);
    int n = sizeof(ci.casosDeTeste)/sizeof(ci.casosDeTeste[0]);

    String s = ci.nome;

    Serial.println(s);
    delay(10);

    for(int k = 0; k<n ; k++){
      resultado = testCi(ci.casosDeTeste[k],ci.numerosDePinos);
      
      if(!resultado){
        Serial.print(ci.casosDeTeste[k]);
        Serial.println(" falhou");
        break;
      }
    }

    Serial.print("Ci encontrado: ");
    Serial.println(ci.nome);
    break;
  }

  return resultado; 
}

boolean buscaCiManual(String nomeDoCi){

  boolean resultado = true;
  CI ci;

  ci = getCiDados(nomeDoCi);
  int n = sizeof(ci.casosDeTeste)/sizeof(ci.casosDeTeste[0]);

  for(int k = 0; k<n ; k++){
    resultado = testCi(ci.casosDeTeste[k],ci.numerosDePinos);
    
    if(!resultado)
      return resultado;
  }

  return resultado;
}


bool testCi(String caso, int pinagem){

  boolean resultado = true;

  
  // faz o setup dos pinos
  for(int i = 0; i < pinagem; i++){

    switch (caso[i])
    {
    case 'G': pinMode(pinos14[i],OUTPUT); digitalWrite(pinos14[i],LOW);
      break;

    case 'V': pinMode(pinos14[i],OUTPUT); digitalWrite(pinos14[i],HIGH);
      break;

    case 'L': digitalWrite(pinos14[i],LOW); pinMode(pinos14[i],INPUT);//pinMode(pinos14[i],INPUT_PULLUP); digitalRead(pinos14[i]);
      break;

    case 'H': digitalWrite(pinos14[i],LOW); pinMode(pinos14[i],INPUT);//pinMode(pinos14[i],INPUT_PULLUP); digitalRead(pinos14[i]);
      break;
    
    default: Serial.print("Ocorreu um erro no setup dos pinos");
      break;
    }
  }
  
  delay(5);

  //faz o setup das saidas
  for (size_t i = 0; i < pinagem; i++)
  {
    switch (caso[i])
    {
    case '0': pinMode(pinos14[i], OUTPUT); digitalWrite(pinos14[i],LOW);
      break;
    case '1': pinMode(pinos14[i], OUTPUT); digitalWrite(pinos14[i],HIGH);
      break;

    default:
      break;
    }
  }
  delay(5);

  //faz o setup das entradas
  for (size_t i = 0; i < pinagem; i++)
  {
    switch (caso[i])
    {
    case 'H': if(!digitalRead(pinos14[i])){
                resultado = false;
                Serial.print("Pino ");
                Serial.print(pinos14[i]);
                Serial.println(" está Danificado");
              }
      break;

    case 'L': if(digitalRead(pinos14[i])){
                resultado = false;
                Serial.print("Pino ");
                Serial.print(pinos14[i]);
                Serial.println(" está Danificado");
              }
      break;
    
    default: Serial.print("Pino ");
             Serial.print(pinos14[i]);
             Serial.println(" está ok");
      break;
    }
  }
  delay(5);

  
  return resultado;
  
}

CI getCiDados(String nome){

  CI ci;
  String buffer = nome;
  int begin = 0;
  int end = nome.indexOf('\n');
  int i = 0;

  ci.numero = nome.substring(begin,end);

  begin = ++end;
  ci.nome = buffer.substring(begin, (end = buffer.indexOf('\n',begin)));

  begin = ++end;
  ci.numerosDePinos = buffer.substring(begin, (end = buffer.indexOf('\n',begin))).toInt();


  while(buffer.indexOf('\n',begin) != -1){

    begin = ++end;
    ci.casosDeTeste[i] = buffer.substring(begin, (end = buffer.indexOf('\n',begin)));

    i++;
    /*begin = ++end;
    String caso1 = buffer.substring(begin, (end = buffer.indexOf('\n',begin)));

    begin = ++end;
    String caso2 = buffer.substring(begin, (end = buffer.indexOf('\n',begin)));

    begin = ++end;
    String caso3 = buffer.substring(begin, (end = buffer.indexOf('\n',begin)));

    begin = ++end;
    String caso4 = buffer.substring(begin);*/

  }

  return ci;
}

