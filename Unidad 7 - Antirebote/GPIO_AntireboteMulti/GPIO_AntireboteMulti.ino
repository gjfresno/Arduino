#include <TimerOne.h>

#define ENTRADA0  5
#define ENTRADA1  6
#define ENTRADA2  7
#define ENTRADA3  8

const int Bomba = 13;

int EstadoBomba = 0;

void setup() {
  
  pinMode(Bomba, OUTPUT);

  // Inicializo las entradas a filtrar
  pinMode(ENTRADA0, INPUT);
  pinMode(ENTRADA1, INPUT);
  pinMode(ENTRADA2, INPUT);
  pinMode(ENTRADA3, INPUT);
  GPIO_Antirebote_Init();
  
  // Inicializo el Systick
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );
}

void Systick_Handler(void)
{
  // Aca vamos a entrar cada 1mseg
  GPIO_Antirebote();
}

void loop() {
  
  MaqEst_Bomba();
}

void MaqEst_Bomba(void)
{
  switch(EstadoBomba)
  {
    case 0:
      Estado_NoLlenando();
      break;
    case 1:
      Estado_Llenando();
      break; 
    default:
      break;   
  }
}

void Estado_NoLlenando(void)
{
  if(digitalRead_Debounce(0) == 0)
  {
    digitalWrite(Bomba, 1);
    EstadoBomba = 1;
  }
}

void Estado_Llenando(void)
{
  if(digitalRead_Debounce(1) == 1)
  {
    digitalWrite(Bomba, 0);
    EstadoBomba = 0;
  }  
}
