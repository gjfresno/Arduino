
void PSerial_Recibir(void)
{ 
  if (Serial.available() > 0) 
  { // Comprueba si hay datos disponibles en el buffer del puerto serial
    char receivedChar = Serial.read(); // Lee el primer byte de datos del buffer
    Serial.print("Caracter recibido: ");
    Serial.println(receivedChar); // Muestra el carácter recibido en el puerto serial

    PSerial_Analisis(receivedChar);
  }
}

void PSerial_Analisis(char dato)
{
  static char dutycicle = 5;
  
  if(dato == '+')
  {
    dutycicle += 1;
    if(dutycicle > 10)
      dutycicle = 10;
      
    PWM_Set(dutycicle);      
  }

  if(dato == '-')
  {
    if(dutycicle >= 1)
      dutycicle -= 1;
      
    PWM_Set(dutycicle); 
  }
}
