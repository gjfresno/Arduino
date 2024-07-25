#include <TimerOne.h>

const int PIN_SEGMENTO_G = 8;
const int PIN_SEGMENTO_F = 7;
const int PIN_SEGMENTO_E = 6;
const int PIN_SEGMENTO_D = 5;
const int PIN_SEGMENTO_C = 4;
const int PIN_SEGMENTO_B = 3;
const int PIN_SEGMENTO_A = 2;

const int PIN_DIGITO_1 = 9;
const int PIN_DIGITO_2 = 10;
const int PIN_DIGITO_3 = 11;

#define CANTIDAD_DIGITOS 3

uint8_t Display_Buffer[CANTIDAD_DIGITOS];
uint8_t Indice = 0;

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

  pinMode(PIN_DIGITO_1, OUTPUT);
  pinMode(PIN_DIGITO_2, OUTPUT);
  pinMode(PIN_DIGITO_3, OUTPUT);
}

void DISPLAY_Print(uint32_t Numero){
  for(i = 0 ; i < CANTIDAD_DIGITOS ; i++){
    Display_Buffer[i] = Numero % 10;
    Numero /= 10;
  }
}

void DISPLAY_Presentar(uint32_t Numero){
  uint8_t Temporal = Tabla_Digitos_BCD_7seg[Numero];

  digitalWrite(PIN_SEGMENTO_G, (Temporal >> 0) & 1);
  digitalWrite(PIN_SEGMENTO_F, (Temporal >> 1) & 1);
  digitalWrite(PIN_SEGMENTO_E, (Temporal >> 2) & 1);
  digitalWrite(PIN_SEGMENTO_D, (Temporal >> 3) & 1);
  digitalWrite(PIN_SEGMENTO_C, (Temporal >> 4) & 1);
  digitalWrite(PIN_SEGMENTO_B, (Temporal >> 5) & 1);
  digitalWrite(PIN_SEGMENTO_A, (Temporal >> 6) & 1);
}

void DISPLAY_Barrido(void){
  digitalWrite(PIN_DIGITO_1, 0);
  digitalWrite(PIN_DIGITO_2, 0);
  digitalWrite(PIN_DIGITO_3, 0);

  DISPLAY_Presentar(Display_Buffer[Indice])

  switch(Indice){
    case 0:
      digitalWrite(PIN_DIGITO_3, 1);
      break;

    case 1:
      digitalWrite(PIN_DIGITO_2, 1);
      break;

    case 2:
      digitalWrite(PIN_DIGITO_1, 1);
      break;
  }

  Indice++
  if(Indice > CANTIDAD_DIGITOS)
    Indice = 0;  
}

void loop() {
  // put your main code here, to run repeatedly:
}

void Systick_Handler(void){
  static int Numero = 0;
  static int Divisor = 0;

  DISPLAY_Barrido();

  Divisor++;
  if(Divisor > 1000)
  {
    Divisor = 0;
    
    DISPLAY_Print(Numero);
    
    Numero++;
    if(Numero > 999)
      Numero = 0;
  }
}
