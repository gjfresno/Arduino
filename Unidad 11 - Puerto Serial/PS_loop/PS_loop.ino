#include <TimerOne.h>

int contador1 = 0;

void setup() 
{ 
  Serial.begin(9600);

  Timer_Inicializacion();
} 

void Timer_Inicializacion(void){
  Timer1.initialize(1000);    // El parametro es el tiempo en useg
  Timer1.attachInterrupt(Systick_Handler);
}

void loop() 
{ 
  if (Serial.available() > 0) 
  { // Comprueba si hay datos disponibles en el buffer del puerto serial
    char receivedChar = Serial.read(); // Lee el primer byte de datos del buffer
    
    Serial.print("Caracter recibido: ");
    Serial.println(receivedChar); // Muestra el carácter recibido en el puerto serial
  }
} 

void Systick_Handler(void){   // Cada 1 mseg entro aca dentro
  contador1++;
  if(contador1 == 1000){
    contador1 = 0;

    Serial.write('G');
    Serial.write('u');
    Serial.write('s');
    Serial.write('\r');
    Serial.write('\n');
  }
}

    
