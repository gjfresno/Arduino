#include <TimerOne.h>
#include "GPIO_DriverSalida.h"

#define Pin_Led   13

GPIO_Salida Outs;

void setup() {
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );

  Outs.Config(Pin_Led);
}

void loop() {
  Outs.Set(Pin_Led, 1);
  delay(2000); 
 
  Outs.Set(Pin_Led, 0);
  delay(2000); 
}

void Systick_Handler(void)
{
  Outs.Barrido();
}
