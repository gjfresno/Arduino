
int Timeout = 2000;      // Timeout de 2000 mseg = 2seg por si el equipo slave no responde
char Indice_Envio = 0;   // Indice de equipo consultado
int Estado_Envio = 0;    // Variable para el estado 
    
void PSerial_Consultar(void)
{
  switch(Estado_Envio)
  {
    case 0:
      PSerial_Enviar_Consulta(Indice_Envio + '0');
      Estado_Envio = 1;
      Timeout = 2000;
      break;

    case 1:
      PSerial_Recibir();

      if(Timeout == 0)
      {
        // Si entre aca es que el equipo no responde o esta desconectado
        Temperaturas[Indice_Envio] = SIN_DATOS;
        
        Estado_Envio = 0;

        // Incremento el indice para leer el proximo equipo
        Indice_Envio++;
        if(Indice_Envio >= CANTIDAD_DE_EQUIPOS)
          Indice_Envio = 0;
      }
      break;
  }
}

void PSerial_DescontarTimeOut(void)
{
  if(Timeout)
  {
    Timeout--;
  }
}
  
void PSerial_Recibir(void)
{ 
  if (Serial.available() > 0) 
  { // Comprueba si hay datos disponibles en el buffer del puerto serial
    char receivedChar = Serial.read(); // Lee el primer byte de datos del buffer
        
    PSerial_Analisis(receivedChar);
  }
}

void PSerial_Analisis(char dato)
{
  // Voy a recibir [>][id][T][temp max 5 digitos][chk][<]
  // chk = Suma de los bytes anteriores
  
  static int estadoRecepcion = 0;
  static char checksum = 0;
  static char contador_digitos = 0;

  static int Temperatura_Leida = 0;
  
  switch(estadoRecepcion)
  {
    case 0:
      if(dato == '>')
      {
        estadoRecepcion = 1; 
        checksum = '>';     
      }
      break;
      
    case 1:
      if(dato == Indice_Envio + '0')  // Chequeo si me responde el mismo equipo que consulte, aca podria poner algun mensaje de error en caso de recibir otro
      {
        estadoRecepcion = 2; 
        checksum += dato; 
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
        Temperatura_Leida = 0;
        contador_digitos = 0;
        checksum += dato;   
      }
      else
      {
        estadoRecepcion = 0; 
      }
      break;

    case 3:
      // Aca tengo q recibir el dato de temperatura q son 5 digitos
      Temperatura_Leida *= 10;
      Temperatura_Leida += dato - '0';

      checksum += dato;

      contador_digitos++;
      if(contador_digitos >= 5)
      {
        estadoRecepcion = 4;   
      }
      break;

    case 4:
      //if(dato == checksum) // Comente el checksum para un analisis mas facil
      //{
        estadoRecepcion = 5;    
      //}
      //else
      //{
      //  estadoRecepcion = 0; 
      //}
      break;

    case 5:
      if(dato == '<')
      {
        Temperaturas[Indice_Envio] = Temperatura_Leida;

        Serial.print("Temp RX: ");
        Serial.print(Temperatura_Leida);
        Serial.print(" Equipo: ");
        Serial.println((char)('0' + Indice_Envio));
        
        Estado_Envio = 0;

        // Incremento el indice para leer el proximo equipo
        Indice_Envio++;
        if(Indice_Envio >= CANTIDAD_DE_EQUIPOS)
          Indice_Envio = 0;
      }
      estadoRecepcion = 0;
      break;
  }
}

void PSerial_Enviar_Consulta(char id)
{
  // La trama a enviar es [>][id][T][?][chk][<]
  // Indices               0  1   2  3  4    5 
  
  char Buf[12];   // El tamaño del buffer depende del tamaño maximo de la trama + un extra por las dudas

  sprintf(Buf, ">%cT?", id); // Armo la trama
  
  char checksum = 0;
  for(int i = 0 ; i < 4 ; i++)
  {
    checksum += Buf[i]; 
  }
  Buf[4] = checksum;
  Buf[5] = '<';

  // Envio la trama generada
  for(int i = 0 ; i <= 5 ; i++)
  {
    Serial.write(Buf[i]); 
  }
}
