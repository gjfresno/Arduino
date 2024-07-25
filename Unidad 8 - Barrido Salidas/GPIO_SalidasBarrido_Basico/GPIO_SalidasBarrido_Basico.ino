#include <TimerOne.h>


#define Pin_Led   13

#define CANTIDAD_MAXIMA_SALIDAS   10
struct
{
  int numPin;
  char estado;
}Outs[CANTIDAD_MAXIMA_SALIDAS];

void OUT_Set(int index, int numPin, int estado)
{
  Outs[index].numPin = numPin;
  Outs[index].estado = estado;
}

void OUT_Barrido(int index)
{
  if(0 == Outs[index].estado)
    digitalWrite(Outs[index].numPin, LOW);
  else
    digitalWrite(Outs[index].numPin, HIGH);
}

void setup() {
  Serial.begin(9600);

  pinMode(Pin_Led, OUTPUT);
  
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );
  
}

void loop() {
  OUT_Set(0, Pin_Led, 1);
  Serial.println("Out 1");
  delay(2000); 
 
  OUT_Set(0, Pin_Led, 0);
  Serial.println("Out 0");
  delay(2000); 
}

void Systick_Handler(void)
{
  OUT_Barrido(0);
}
