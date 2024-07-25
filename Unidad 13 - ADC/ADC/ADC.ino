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

void loop() {
  // Leer el valor analógico de A0
  int cuenta = analogRead(A0);

  //float voltage = ((float)cuenta * 5)/1023;
  int voltage = ((long)cuenta * 5 * 1000)/1023;

  // Imprimir el valor leído en el monitor serie
/*  Serial.print("Cuentas: ");
  Serial.print(cuenta);
  Serial.print(" Volt: ");
  Serial.println(voltage);*/
  sprintf(Buf, "Cuentas: %d Volt: %d.%d", cuenta, (voltage / 1000), (voltage % 1000));
  Serial.println(Buf);

  delay(1000);
}

void Systick_Handler(void)
{
  // Aca entro cada 1ms = 1000Hz
}
