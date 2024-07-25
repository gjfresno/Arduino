#define CANTIDAD_ESTADOS_ESTABLES 20
#define CANTIDAD_ENTRADAS   1

// Genero una estructura para cada una de las entradas a filtrar
typedef struct
{
  char contador;
  char estadoAnterior;
  char estadoEstable;
}Struct_AntiRebote;

// Declaro un vector de estructuras
Struct_AntiRebote  EntFiltrada[CANTIDAD_ENTRADAS];

// Declaro un vector con las entradas q voy a filtrar
int ENTRADAS_Vector[] = {ENTRADA0};

// Funcion de inicializacion
void GPIO_Antirebote_Init(void)
{
  for(int i = 0 ; i < CANTIDAD_ENTRADAS ; i++)
  {
    EntFiltrada[i].estadoAnterior = 0;
    EntFiltrada[i].contador = 0;
    EntFiltrada[i].estadoEstable = 0;
  }
}

// Funcion de antirebote con multiple entradas
void GPIO_Antirebote(void)
{   
  char estadoActual;

  for(int i = 0 ; i < CANTIDAD_ENTRADAS ; i++)
  {
    // Por cada analizo una entrada distinta 
    estadoActual = digitalRead(ENTRADAS_Vector[i]);

    // La logica es similar al simple antirebote
    if(EntFiltrada[i].estadoAnterior == estadoActual)
    {
      EntFiltrada[i].contador++;
      if(EntFiltrada[i].contador >= CANTIDAD_ESTADOS_ESTABLES)
      {
        EntFiltrada[i].estadoEstable = estadoActual;
      }
    }
    else
    {
      EntFiltrada[i].contador = 0;
      EntFiltrada[i].estadoAnterior = estadoActual;
    }  
  }
}

// Funcion para la lectura del valor estable de cada una de las entradas
char digitalRead_Debounce(int Nro_Entrada)
{
  return EntFiltrada[Nro_Entrada].estadoEstable;
}
