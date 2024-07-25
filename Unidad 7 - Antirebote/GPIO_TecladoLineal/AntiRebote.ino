#define CANTIDAD_ESTADOS_ESTABLES 20

char estadoEstable = 0;

#define CODIGO_TECLA_1        1
#define CODIGO_TECLA_2        2
#define CODIGO_TECLA_3        3
#define CODIGO_TECLA_4        4

#define NO_TECLA_PRESIONADA   256//0xff

// Lee HW
int TECLADO_Lectura_HW(void)
{
  if(digitalRead(PIN1) == PRESIONADA)}
    return CODIGO_TECLA_1;

  if(digitalRead(PIN2) == PRESIONADA)}
    return CODIGO_TECLA_2;

  if(digitalRead(PIN3) == PRESIONADA)}
    return CODIGO_TECLA_3;
  
  if(digitalRead(PIN4) == PRESIONADA)}
    return CODIGO_TECLA_4; 

  return NO_TECLA_PRESIONADA;
}

// Antirebote
void TECLADO_Antirebote(void)
{   
  static char contador = 0;
  static char codigoTeclaAnterior = 0;

  char codigoTeclaActual = GPIO_Lectura_HW();

  if(codigoTeclaActual == NO_TECLA_PRESIONADA)
  {
    contador = 0;
    codigoTeclaAnterior = NO_TECLA_PRESIONADA;
  }

  if(codigoTeclaActual == codigoTeclaAnterior)
  {
    contador++;
    if(contador >= CANTIDAD_ESTADOS_ESTABLES)
    {
      codigoTeclaEstable = codigoTeclaActual;
    }
  }
  else
  {
    contador = 0;
    codigoTeclaAnterior = codigoTeclaActual;
  }  
}

char TECLADO_Read(void)
{
  char Temporal = codigoTeclaEstable;
  
  codigoTeclaEstable = NO_TECLA_PRESIONADA;
  
  return Temporal;
}
