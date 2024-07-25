#include <TimerOne.h>

int Pin_Led1 = 13; 
int Pin_Led2 = 12;

int estado_Led1 = 0;
int estado_Led2 = 0;
int contador1 = 0;
int contador2 = 0;

void setup() 
{ 
  pinMode(Pin_Led1, OUTPUT); 
  pinMode(Pin_Led2, OUTPUT); 

  Timer_Inicializacion();
} 

void Timer_Inicializacion(void){
  Timer1.initialize(1000);    // El parametro es el tiempo en useg
  Timer1.attachInterrupt(Timer);
}

void loop() 
{ 

} 

void Timer(void){   // Cada 1 mseg entro aca dentro
  Led1();

  Led2();
}

void Led1(void){
  contador1++;
  if(contador1 == 300){
    contador1 = 0;
    
    if(estado_Led1 == 0){
      digitalWrite(Pin_Led1, HIGH); 
      estado_Led1 = 1;
    } else {
      digitalWrite(Pin_Led1, LOW); 
      estado_Led1 = 0;
    }
  }
}

void Led2(void){
  contador2++;
  if(contador2 == 1000){
    contador2 = 0;
    
    if(estado_Led2 == 0){
      digitalWrite(Pin_Led2, HIGH); 
      estado_Led2 = 1;
    } else {
      digitalWrite(Pin_Led2, LOW); 
      estado_Led2 = 0;
    } 
  }
}
