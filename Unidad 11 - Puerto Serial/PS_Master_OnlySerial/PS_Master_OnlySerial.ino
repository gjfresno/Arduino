
#include <TimerOne.h>

#define CANTIDAD_DE_EQUIPOS   5
#define SIN_DATOS   0xffff

int Temperaturas[CANTIDAD_DE_EQUIPOS];

void setup() 
{
  Serial.begin(9600);

  Timer_Inicializacion();
}

void Timer_Inicializacion(void){
  Timer1.initialize(1000);    // El parametro es el tiempo en useg
  Timer1.attachInterrupt(Systick_Handler);
}

void Systick_Handler(void){   // Cada 1 mseg entro aca dentro
  PSerial_DescontarTimeOut();
}

void loop() 
{
  PSerial_Consultar();
}
