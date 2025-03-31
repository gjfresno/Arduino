  
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
  // Voy a recibir [>][id][T][?][chk][<]
  // chk = Suma de los bytes anteriores
  
  static int estadoRecepcion = 0;
  
  switch(estadoRecepcion)
  {
    case 0:
      if(dato == '>')
      {
        estadoRecepcion = 1;      
      }
      break;
      
    case 1:
      if(dato == EQUIPO_ID)
      {
        estadoRecepcion = 2;      
      }
      else
      {
        estadoRecepcion = 0; 
      }
      break;

    case 2:
      if(dato == 'T')
      {
        estadoRecepcion = 3;      
      }
      else
      {
        estadoRecepcion = 0; 
      }
      break;

    case 3:
      if(dato == '?')
      {
        estadoRecepcion = 4;      
      }
      else
      {
        estadoRecepcion = 0; 
      }
      break;

    case 4:
      if(dato == (char)('>'+EQUIPO_ID+'T'+'?')) // En este caso no hace falta el checksum ya q todos los datos recibidos son fijos
      {
        estadoRecepcion = 5;      
      }
      else
      {
        estadoRecepcion = 0; 
      }
      break;

    case 5:
      if(dato == '<')
      {
        // Si recibimos la trama completa debemos enviar la temperatura      
        PSerial_Enviar_Respuesta();
      }
      estadoRecepcion = 0; 
      break;
  }
}

void PSerial_Enviar_Respuesta(void)
{
  // La trama a enviar es [>][id][T][temp max 5 digitos][chk][<]
  // Indices               0  1   2  3 4 5 6 7           8    9
  
  char Buf[12];   // El tamaño del buffer depende del tamaño maximo de la trama + un extra por las dudas

  sprintf(Buf, ">%cT%05d", EQUIPO_ID, Temperatura_Leida); // Armo la trama
  
  char checksum = 0;
  for(int i = 0 ; i < UBICACION_BYTES_CHECKSUM ; i++)
  {
    checksum += Buf[i]; 
  }
  Buf[UBICACION_BYTES_CHECKSUM] = checksum;
  Buf[UBICACION_BYTES_CHECKSUM + 1] = '<';

  // Envio la trama generada
  for(int i = 0 ; i < 10 ; i++)
  {
    Serial.write(Buf[i]); 
  }
}
