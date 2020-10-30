#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Bounce2.h>

#define bt1  27
#define bt2  29
#define bt3  31
#define ledPodeTrocarCi  9
#define ledTestandoCi  10


bool testaCi(String s);
bool ciAND();
bool ciNAND();
bool ciNOR();
bool ciOR();
bool ciNOT();
bool ciXOR();
void buscaAuto();

LiquidCrystal_I2C lcd(0x27,16,2);
Bounce debouncer = Bounce();


uint8_t countbt1 = 0;
uint8_t countbt2 = 0;
uint8_t countbt3 = 0;


int ciParaTestar = 1;
int pinos14[14] = {32,33,34,35,36,37,38,39,40,41,42,43,44,45};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  lcd.init();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Escolha o CI:");

  pinMode(bt1,INPUT);
  pinMode(bt2,INPUT);
  pinMode(bt3,INPUT);
  pinMode(ledPodeTrocarCi,OUTPUT);
  pinMode(ledTestandoCi,OUTPUT);

  debouncer.attach(bt1);
  debouncer.interval(100);

}

void loop() {
  // put your main code here, to run repeatedly:
  debouncer.update();

  digitalWrite(ledPodeTrocarCi,HIGH);
  digitalWrite(ledTestandoCi,LOW);

  int b1 = debouncer.read();
  int b2 = digitalRead(bt2);
  int b3 = digitalRead(bt3);

  if(b1 == HIGH){
    lcd.setCursor(0,1);
    countbt1++;

    switch (countbt1)
    {
    case 1: lcd.print("7400 NAND");
            ciParaTestar = 1;
      break;
    case 2: lcd.print("7402 NOR ");
            ciParaTestar = 2;
      break;
    case 3: lcd.print("7404 NOT ");
            ciParaTestar = 3;
      break;
    case 4: lcd.print("7408 AND ");
            ciParaTestar = 4;
      break;
    case 5: lcd.print("7432 OR  ");
            ciParaTestar = 5;
      break;
    case 6: lcd.print("7486 XOR ");
            ciParaTestar = 6;
            countbt1 = 0;
      break;

    default:
      break;
    }
  }

  if(b2 == HIGH){
    digitalWrite(ledTestandoCi,HIGH);
    digitalWrite(ledPodeTrocarCi,LOW);
    
    lcd.clear();
    lcd.print("Busca automatica");
    delay(2000);
    buscaAuto();
    delay(3000);
    lcd.clear();
    lcd.print("Escolha o CI:");
  }

  if(b3 == HIGH){

    digitalWrite(ledTestandoCi,HIGH);
    digitalWrite(ledPodeTrocarCi,LOW);

    lcd.clear();
    lcd.print("Ok teste");
    lcd.setCursor(0,1);
    lcd.print("iniciando");
    delay(1000);
    lcd.clear();
    lcd.print("testando...");

    Serial.println(ciParaTestar);

    switch (ciParaTestar)
    {
    case 1: if(ciNAND() == false){
              lcd.clear();
              lcd.print("CI 7400 com erro");
            }
            else{
              lcd.clear();
              lcd.print("CI 7400: NAND");
              lcd.setCursor(0,1);
              lcd.print("esta ok");
            }
      break;
    case 2: if(ciNOR() == false){
              lcd.clear();
              lcd.print("CI 7402 com erro");
            }
            else{
              lcd.clear();
              lcd.print("CI 7402: NOR");
              lcd.setCursor(0,1);
              lcd.print("esta ok");
            }
      break;
    case 3: if(ciNOT() == false){
              lcd.clear();
              lcd.print("CI 7404 com erro");
            }
            else{
              lcd.clear();
              lcd.print("CI 7404: NOT");
              lcd.setCursor(0,1);
              lcd.print("esta ok");
            }
      break;
    case 4: if(ciAND() == false){
              lcd.clear();
              lcd.print("CI 7408 com erro");
            }
            else{
              lcd.clear();
              lcd.print("CI 7408: AND");
              lcd.setCursor(0,1);
              lcd.print("esta ok");
            }
      break;
    case 5: if(ciOR() == false){
              lcd.clear();
              lcd.print("CI 7432 com erro");
            }
            else{
              lcd.clear();
              lcd.print("CI 7432: OR");
              lcd.setCursor(0,1);
              lcd.print("esta ok");
            }
      break;
    case 6: if(ciXOR() == false){
              lcd.clear();
              lcd.print("CI 7486 com erro");
            }
            else{
              lcd.clear();
              lcd.print("CI 7486: XOR");
              lcd.setCursor(0,1);
              lcd.print("esta ok");
            }
      break;
    
    default: Serial.println("Ocorreu algum erro");
      break;
    }

    delay(3000);
    lcd.clear();
    lcd.print("Escolha o CI:");
  }
}

void buscaAuto(){

  if(ciAND() == true){
    lcd.clear();
    lcd.print("Ci encontrado");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("CI:  AND     ");
    lcd.setCursor(0,1);
    lcd.print("Estado OK");
  }
  else if (ciNAND() == true)
  {
    lcd.clear();
    lcd.print("Ci encontrado");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("CI:  NAND    ");
    lcd.setCursor(0,1);
    lcd.print("Estado OK");
  }
  else if (ciNOR() == true)
  {
    lcd.clear();
    lcd.print("Ci encontrado");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("CI:  NOR     ");
    lcd.setCursor(0,1);
    lcd.print("Estado OK");
  }
  else if (ciXOR() == true)
  {
    lcd.clear();
    lcd.print("Ci encontrado");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("CI:  XOR     ");
    lcd.setCursor(0,1);
    lcd.print("Estado OK");
  }
  else if (ciOR() == true)
  {
    lcd.clear();
    lcd.print("Ci encontrado");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("CI:  OR      ");
    lcd.setCursor(0,1);
    lcd.print("Estado OK");
  }
  else if (ciNOT() == true)
  {
    lcd.clear();
    lcd.print("Ci encontrado");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("CI:  NOT     ");
    lcd.setCursor(0,1);
    lcd.print("Estado OK");
  }
  

}

bool ciAND(){
  String casosDeTeste[4] = {"00L00LGL00L00V","01L01LGL01L01V","10L10LGL10L10V","11H11HGH11H11V"};
  bool resultado = true;
  
  for(int n = 0; n < 4; n++){
    resultado = testaCi(casosDeTeste[n]);

    if(resultado == false){
      return resultado;
    }
  }

  return resultado;
}

bool ciNAND(){

  String casosDeTeste[4] = {"00H00HGH00H00V","10H10HGH10H10V","01H01HGH01H01V","11L11LGL11L11V"};
  bool resultado = true;
  
  for(int n = 0; n < 4; n++){
    resultado = testaCi(casosDeTeste[n]);

    if(resultado == false){
      return resultado;
    }
  }

  return resultado;
}

bool ciNOR(){
  
  String casosDeTeste[4] = {"H00H00G00H00HV","L10L10G10L10LV","L01L01G01L01LV","L11L11G11L11LV"};
  bool resultado = true;
  
  for(int n = 0; n < 4; n++){
    resultado = testaCi(casosDeTeste[n]);

    if(resultado == false){
      return resultado;
    }
  }

  return resultado;
}

bool ciNOT(){
  
  String casosDeTeste[2] = {"0H0H0HGH0H0H0V","1L1L1LGL1L1L1V"};
  bool resultado = true;
  
  for(int n = 0; n < 2; n++){
    resultado = testaCi(casosDeTeste[n]);

    if(resultado == false){
      return resultado;
    }
  }

  return resultado;
}

bool ciOR(){
  
  String casosDeTeste[4] = {"00L00LGL00L00V","01H01HGH10H10V","10H10HGH01H01V","11H11HGH11H11V"};
  bool resultado = true;
  
  for(int n = 0; n < 4; n++){
    resultado = testaCi(casosDeTeste[n]);

    if(resultado == false){
      return resultado;
    }
  }

  return resultado;
}

bool ciXOR(){
  
  String casosDeTeste[4] = {"00L00LGL00L00V","01H01HGH01H01V","10H10HGH10H10V","11L11LGL11L11V"};
  bool resultado = true;
  
  for(int n = 0; n < 4; n++){
    resultado = testaCi(casosDeTeste[n]);

    if(resultado == false){
      return resultado;
    }
  }

  return resultado;
}


bool testaCi(String s){

  String teste = s;
  bool res = true;

  for(int i = 0; i < 14; i++){

    switch (teste[i]){

    case 'G': pinMode(pinos14[i],OUTPUT); digitalWrite(pinos14[i],LOW);
      break;

    case 'V': pinMode(pinos14[i],OUTPUT); digitalWrite(pinos14[i],HIGH);
      break;

    case 'L': digitalWrite(pinos14[i],LOW); pinMode(pinos14[i],INPUT);//pinMode(pinos14[i],INPUT_PULLUP); digitalRead(pinos14[i]);
      break;

    case 'H': digitalWrite(pinos14[i],LOW); pinMode(pinos14[i],INPUT);//pinMode(pinos14[i],INPUT_PULLUP); digitalRead(pinos14[i]);
      break;
    
    default: 
      break;
    }
  }

  delay(5);

  //faz o setup das saidas
  for (int i = 0; i < 14; i++){
    switch (teste[i])
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

  lcd.clear();
  //faz o setup das entradas
  for (int i = 0; i < 14; i++){
    switch (teste[i])
    {
    case 'H': if(digitalRead(pinos14[i]) == LOW){
              res = false;
              Serial.print(digitalRead(pinos14[i]));
              Serial.print("Pino ");
              Serial.print(pinos14[i]);
              Serial.println(" saida nivel LOW, onde deveria ser H");
              }
      break;

    case 'L': if(digitalRead(pinos14[i]) == HIGH){
                res = false;
                Serial.print(digitalRead(pinos14[i]));
                Serial.print("Pino ");
                Serial.print(pinos14[i]);
                Serial.println(" saida nivel HIGH, onde deveria ser L");
              }
      break;
    
    default: 
      break;
    }
  }

  return res;
}
