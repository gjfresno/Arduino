#define CANTIDAD_ESTADOS_ESTABLES 20

char estadoEstable = 0;

void GPIO_Antirebote(void)
{   
  static char contador = 0;
  static char estadoAnterior = 0;

  char estadoActual = digitalRead(ENTRADA);

  if(estadoAnterior == estadoActual)
  {
    contador++;
    if(contador >= CANTIDAD_ESTADOS_ESTABLES)
    {
      estadoEstable = estadoActual;
    }
  }
  else
  {
    contador = 0;
    estadoAnterior = estadoActual;
  }  
}

char digitalRead_Debounce(void)
{
  return estadoEstable;
}
