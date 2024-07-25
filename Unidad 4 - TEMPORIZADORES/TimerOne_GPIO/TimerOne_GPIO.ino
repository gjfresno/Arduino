#include <TimerOne.h>

const int Pin_Led = 13;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );

  pinMode(Pin_Led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void Systick_Handler(void)
{
  static int Estado = 0;
  static int Divisor = 0;

  Divisor++;
  if(Divisor > 1000)
  {
    Divisor = 0;
    
    if(Estado)
    {
      Estado = 0;
      digitalWrite(Pin_Led, 0);
    }
    else
    {
      Estado = 1;
      digitalWrite(Pin_Led, 1);    
    }
  }
}
