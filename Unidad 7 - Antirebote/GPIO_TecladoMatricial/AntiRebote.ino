#define CANTIDAD_ESTADOS_ESTABLES 20

char estadoEstable = 0;

#define CODIGO_TECLA_1        1
#define CODIGO_TECLA_2        2
#define CODIGO_TECLA_3        3
#define CODIGO_TECLA_4        4
#define CODIGO_TECLA_5        5
#define CODIGO_TECLA_6        6
#define CODIGO_TECLA_7        7
#define CODIGO_TECLA_8        8
#define CODIGO_TECLA_9        9

#define PRESIONADA            0

#define PIN_TECLA_FILA_1      13
#define PIN_TECLA_FILA_2      14
#define PIN_TECLA_FILA_3      15

#define PIN_TECLA_COL_1       7
#define PIN_TECLA_COL_2       5
#define PIN_TECLA_COL_3       6

#define NO_TECLA_PRESIONADA   256//0xff

// Lee HW
int TECLADO_Lectura_HW(void)
{
  // Selecciono la columna 1
  
  digitalWrite(PIN_TECLA_COL_1, 0);
  digitalWrite(PIN_TECLA_COL_2, 1);
  digitalWrite(PIN_TECLA_COL_3, 1);
    
  if(digitalRead(PIN_TECLA_FILA_1) == PRESIONADA)}
    return CODIGO_TECLA_1;

  if(digitalRead(PIN_TECLA_FILA_2) == PRESIONADA)}
    return CODIGO_TECLA_2;

  if(digitalRead(PIN_TECLA_FILA_3) == PRESIONADA)}
    return CODIGO_TECLA_3;

  // Selecciono la columna 2
  
  digitalWrite(PIN_TECLA_COL_1, 1);
  digitalWrite(PIN_TECLA_COL_2, 0);
  digitalWrite(PIN_TECLA_COL_3, 1);
    
  if(digitalRead(PIN_TECLA_FILA_1) == PRESIONADA)}
    return CODIGO_TECLA_4;

  if(digitalRead(PIN_TECLA_FILA_2) == PRESIONADA)}
    return CODIGO_TECLA_5;

  if(digitalRead(PIN_TECLA_FILA_3) == PRESIONADA)}
    return CODIGO_TECLA_6;

  // Selecciono la columna 3
  
  digitalWrite(PIN_TECLA_COL_1, 1);
  digitalWrite(PIN_TECLA_COL_2, 1);
  digitalWrite(PIN_TECLA_COL_3, 0);
    
  if(digitalRead(PIN_TECLA_FILA_1) == PRESIONADA)}
    return CODIGO_TECLA_7;

  if(digitalRead(PIN_TECLA_FILA_2) == PRESIONADA)}
    return CODIGO_TECLA_8;

  if(digitalRead(PIN_TECLA_FILA_3) == PRESIONADA)}
    return CODIGO_TECLA_9;

  return NO_TECLA_PRESIONADA;
}

// Antirebote
// Antirebote
void TECLADO_Antirebote(void)
{   
  static char contador = 0;
  static int codigoTeclaAnterior = 0;

  int codigoTeclaActual = TECLADO_Lectura_HW();
  if(codigoTeclaActual == NO_TECLA_PRESIONADA)
  {
    contador = 0;
    codigoTeclaAnterior = NO_TECLA_PRESIONADA;
    return;
  }

  if(codigoTeclaActual == codigoTeclaAnterior)
  {
    if(contador < CANTIDAD_ESTADOS_ESTABLES)
    {
      contador++;
      if(contador >= CANTIDAD_ESTADOS_ESTABLES)
      {
        codigoTeclaEstable = codigoTeclaActual;
    
      }
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
