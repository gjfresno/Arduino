#define CANTIDAD_MAXIMA_SALIDAS   14    // Es el numero de pin mas alto que tenga Arduino
#define SALIDA_SIN_CONFIGURAR     0xff

char salidasEstado[CANTIDAD_MAXIMA_SALIDAS];

// Funcion que se encarga de inicializar la salida
void GPIO_BarridoSalidasInit(void)
{
  for(int i = 0 ; i < CANTIDAD_MAXIMA_SALIDAS ; i++)
  {
    salidasEstado[i] = SALIDA_SIN_CONFIGURAR;
  }
}

// Funcion que setea el estado de una salida
void digitalWrite_OUT(int numPin, int estado)
{
  salidasEstado[numPin] = estado;
}

// Funcion que se debe llamar cada 1ms para realizar el barrido
void GPIO_BarridoSalidas(void)
{
  for(int i = 0 ; i < CANTIDAD_MAXIMA_SALIDAS ; i++)
  {
    GPIO_BarridoSalida(i);
  }
}

void GPIO_BarridoSalida(int index)
{
    switch(salidasEstado[index])
    {
      case 0:
        digitalWrite(index, LOW);
        break;
      case 1:
        digitalWrite(index, HIGH);
        break;
      default:
        break;        
    }
}
