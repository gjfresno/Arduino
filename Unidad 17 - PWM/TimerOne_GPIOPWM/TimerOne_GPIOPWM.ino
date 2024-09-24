#include <TimerOne.h>

void setup() {
  PWM_Init(5);

  Serial.begin(9600);
  
  // put your setup code here, to run once:
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );

}

void loop() {
  PSerial_Recibir();
}

void Systick_Handler(void)
{
  static int Divisor = 0;

  PWM_Work();

  Divisor++;
  if(Divisor > 1000)
  {
    Divisor = 0;
    
  }
}
