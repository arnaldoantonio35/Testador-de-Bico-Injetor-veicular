#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2);


const int botao1 = 1; //Liga bomba
const int botao2 = 2; //passa quantidade de testes
const int botao3 = 4; //Volta quantidade de teste
const int botao4 = 5; //Passa 100uS 
const int botao5 = 6; //Volta 100uS
const int botao6 = 7; //Start

const int pwm1 = 9; //Saida PWM
const int pwm2 = 3; //Saida PWM

int estado1 = 0;
int estado2 = 0;
int estado3 = 0;
int estado4 = 0;
int estado5 = 0;
int estado6 = 0;



int guarda_estado1 = LOW;
int guarda_estado2 = LOW;
int guarda_estado3 = LOW;
int guarda_estado4 = LOW;
int guarda_estado5 = LOW;
int guarda_estado6 = LOW;

int deadzone = 0;
int contador = 0;
int n = 0;

float LIGADO = 0;
int DESLIGADO = 0;

void setup() {

  pinMode( 1, INPUT);
  pinMode( 2, INPUT);
  pinMode( 4, INPUT);
  pinMode( 5, INPUT);
  pinMode( 6, INPUT);
  pinMode( 7, INPUT);
  
  pinMode( 3, OUTPUT); //PWM
  pinMode( 9, OUTPUT); //PWM
  pinMode(10, OUTPUT); //bomba
  
  lcd.init();

}

void BOMBA(){
estado1 = digitalRead(1);

if(estado1 == HIGH){ 
delay(500);
guarda_estado1 = !guarda_estado1; 
delay(500);
}
if(guarda_estado1 == HIGH){
digitalWrite(10, HIGH);
}else{
  digitalWrite(10, LOW);
  }
}
void LCD(){

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Tempo: ");
  lcd.setCursor(8,0);
  
  if(LIGADO >= 1000){
      lcd.setCursor(8,0);
      lcd.print(LIGADO / 1000);
      lcd.setCursor(12,0);
      lcd.print("  mS"); 
    }else{
      lcd.print(LIGADO);
      lcd.setCursor(12,0);
      lcd.print("  uS");
      }

  lcd.setCursor(0,1);
  lcd.print("Qtde: ");
  lcd.setCursor(5,1);
  lcd.print(contador);

  lcd.setCursor(9,1);
  lcd.print("DZ:");
  lcd.setCursor(12,1);
  if(guarda_estado1 == HIGH){
  lcd.print(deadzone);
  }
}

/*
void DEADZONE(){

 estado1 = digitalRead(1);

if(estado1 == HIGH){ 
delay(500);
guarda_estado1 = !guarda_estado1; 
delay(500);
}
if(guarda_estado1 == HIGH){

//}


////////////////////////////////////
  
  estado4 = digitalRead(5);

if(estado4 == HIGH){ 
delay(500);
deadzone += 100;
}

estado5 = digitalRead(6);

if(estado5 == HIGH){ 
delay(500);
deadzone -= 100;
}
  
  }
  
}
*/
void loop() {

//BOMBA(); 

//DEADZONE();

LCD(); 


estado1 = digitalRead(1);

if(estado1 == HIGH){ 
delay(500);
guarda_estado1 = !guarda_estado1; 
delay(500);
}

if(guarda_estado1 == HIGH){

  estado4 = digitalRead(5);

if(estado4 == HIGH){ 
delay(500);
deadzone += 100;
}

  estado5 = digitalRead(6);

if(estado5 == HIGH){ 
delay(500);
deadzone -= 100;
}

}
else{ 
estado4 = digitalRead(5);

if(estado4 == HIGH){ 
delay(500);
LIGADO += 100;
}

estado5 = digitalRead(6);

if(estado5 == HIGH){ 
delay(500);
LIGADO -= 100;
}
}
////////////////////////////////////////////
 
estado2 = digitalRead(2);

if(estado2 == HIGH){ 
delay(500);
  contador += 50;
}

estado3 = digitalRead(4);

if(estado3 == HIGH){ 
delay(500);
  contador -= 50;
}

//////////////////////////////////////////////
estado6 = digitalRead(7);
n = 0;
if(estado6 == HIGH){ 
  delay(500);

digitalWrite(10, HIGH);
delay(3000);
  
  while(n != contador){

    digitalWrite(9, HIGH);
    digitalWrite(3, HIGH);
    delayMicroseconds(LIGADO + deadzone);
    //delay(10);
  
    digitalWrite(9, LOW);
    digitalWrite(3, LOW);
    delayMicroseconds(LIGADO + deadzone);
    //delay(20);
    n++;
}
delay(2000);
digitalWrite(10, LOW);
}

}

///////////////////////////////////////////
