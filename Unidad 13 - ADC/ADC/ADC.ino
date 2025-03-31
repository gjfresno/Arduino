#include <TimerOne.h>

const int Pin_Led = 13;
const int Pin_Pulsador = 2;

void setup() {
  // Inicializamos el puerto serial
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );

  pinMode(Pin_Led, OUTPUT);
}

char Buf[30];

long suma = 0;
long promedio = 0;
char contador = 0;

char flag_ADC = 0;

#define DELTA_VARIACION               20
#define CANTIDAD_MUESTRAS_PROMEDIO    10

void loop() {
  // Leer el valor analógico de A0

  if(flag_ADC){
    flag_ADC = 0;

    ADC_Leer();
  }

}

void ADC_Leer(void){
  int medicion_actual = analogRead(A0);

  suma += medicion_actual;
  contador++;
  if(contador >= CANTIDAD_MUESTRAS_PROMEDIO)
  {
    promedio = suma / CANTIDAD_MUESTRAS_PROMEDIO;

    sprintf(Buf, "Suma: %d Prom: %d", suma, promedio);
    Serial.println(Buf);
    
    suma = 0;
    contador = 0;

    int voltage = ((long)promedio * 5 * 1000)/1023;
  
    // Imprimir el valor leído en el monitor serie
    sprintf(Buf, "Cuentas: %d Volt: %d.%d", medicion_actual, (voltage / 1000), (voltage % 1000));
    Serial.println(Buf);
  }
}

void Systick_Handler(void)
{
  // Aca entro cada 1ms = 1000Hz
  static unsigned int divisor = 100;

  divisor--;
  if(divisor == 0){
    divisor = 100;

    // Flag que indica que tengo que realizar una nueva medicion de ADC
    flag_ADC = 1;
  }
}
