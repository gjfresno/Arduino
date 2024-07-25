#include <TimerOne.h>

const int PIN_SEGMENTO_G = 8;
const int PIN_SEGMENTO_F = 7;
const int PIN_SEGMENTO_E = 6;
const int PIN_SEGMENTO_D = 5;
const int PIN_SEGMENTO_C = 4;
const int PIN_SEGMENTO_B = 3;
const int PIN_SEGMENTO_A = 2;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );

  pinMode(PIN_SEGMENTO_G, OUTPUT);
  pinMode(PIN_SEGMENTO_F, OUTPUT);
  pinMode(PIN_SEGMENTO_E, OUTPUT);
  pinMode(PIN_SEGMENTO_D, OUTPUT);
  pinMode(PIN_SEGMENTO_C, OUTPUT);
  pinMode(PIN_SEGMENTO_B, OUTPUT);
  pinMode(PIN_SEGMENTO_A, OUTPUT);
}

void DISPLAY_Presentar(uint32_t Numero)
{
  uint8_t Temporal = Tabla_Digitos_BCD_7seg[Numero];


  digitalWrite(PIN_SEGMENTO_G, (Temporal >> 0) & 1);
  digitalWrite(PIN_SEGMENTO_F, (Temporal >> 1) & 1);
  digitalWrite(PIN_SEGMENTO_E, (Temporal >> 2) & 1);
  digitalWrite(PIN_SEGMENTO_D, (Temporal >> 3) & 1);
  digitalWrite(PIN_SEGMENTO_C, (Temporal >> 4) & 1);
  digitalWrite(PIN_SEGMENTO_B, (Temporal >> 5) & 1);
  digitalWrite(PIN_SEGMENTO_A, (Temporal >> 6) & 1);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void Systick_Handler(void)
{
  static int Numero = 0;
  static int Divisor = 0;

  Divisor++;
  if(Divisor > 1000)
  {
    Divisor = 0;
    
    DISPLAY_Presentar(Numero);
  }
}
