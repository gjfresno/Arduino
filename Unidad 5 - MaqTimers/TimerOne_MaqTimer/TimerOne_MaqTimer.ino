#include <TimerOne.h>

const int Pin_Led = 13;
const int Pin_Pulsador = 2;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );

  pinMode(Pin_Led, OUTPUT);

  Timer_Inicializar(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(Pin_Pulsador) == 0)
  {
    Timer_Disparar(0, 10);
    Timer_Disparar(1, 15);
    Timer_Disparar(2, 20);
  }
  
}

void Systick_Handler(void)
{
  // Aca entro cada 1ms = 1000Hz
  Timer_Descontar();
}
