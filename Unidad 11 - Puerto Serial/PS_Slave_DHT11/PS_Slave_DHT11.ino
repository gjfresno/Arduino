
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <TimerOne.h>

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);  

const char EQUIPO_ID = '1';

int Temperatura_Leida = 0;
char flag_1_seg = 0;

void setup() 
{
  // Inicializamos el timer1
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );

  // Inicializamos el puerto serial
  Serial.begin(9600);

  // Comenzamos el sensor DHT
  dht.begin();
}

void Systick_Handler(void)
{
  // Aca entro cada 1ms = 1000Hz
  static int divisor = 1000;

  divisor--;
  if(divisor == 0)
  {
    divisor = 1000;

    flag_1_seg = 1;
  }
}

void loop() 
{
  // Analizamos la recepcion de la trama
  PSerial_Recibir();
  
  if(flag_1_seg)
  {
    // Aca entramos cada 1 seg
    flag_1_seg = 0;
    
    // Leemos la temperatura en grados centígrados (por defecto)
    Temperatura_Leida = dht.readTemperature();

  } 
}
