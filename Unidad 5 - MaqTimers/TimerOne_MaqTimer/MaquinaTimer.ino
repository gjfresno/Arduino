
#define BASEDETIEMPO      1000
#define CANTIDAD_TIMERS   16

// Genero una estructura 
typedef struct
{
  unsigned int  contador;
  char          fin;
}Struct_Timer;

// Declaro un vector de estructuras
Struct_Timer  Timer[CANTIDAD_TIMERS];

//--------------------------------------

void Timer_Inicializar(char NumeroTimer)
{
  Timer[NumeroTimer].contador = 0;
  Timer[NumeroTimer].fin = 0;
}

void Timer_Disparar(char NumeroTimer, unsigned int tiempo)
{
  // Esta funcion es la que se encarga de configurar la temporizacion
  Timer[NumeroTimer].contador = tiempo * BASEDETIEMPO;
  Timer[NumeroTimer].fin = 0;
}

void Timer_Analizar(void)
{
  // Esta se encarga del analizar que el contador haya llegado a cero y realizar la accion de fin
  // La voy a llamar dentro del loop
  
  for(int i = 0 ; i < CANTIDAD_TIMERS ; i++)
  {
    if(Timer[NumeroTimer].fin == 1)
    {
      Timer[NumeroTimer].fin = 0;
  
      // Accion a realizar
      switch(NumeroTimer)
      {
        case 0:
          //ACCION POR TIMER 0
          digitalWrite(pin_Led1, 1);
          break;
        case 1:
          //ACCION POR TIMER 1
          digitalWrite(pin_Led2, 1);
          break;
        case 2:
          //ACCION POR TIMER 2
          digitalWrite(pin_Led3, 1);
          break;
        case N:
          //ACCION POR TIMER N
          break;
      }
    }
  }
}

void Timer_Descontar(void)
{
  for(int i = 0 ; i < CANTIDAD_TIMERS ; i++)
  {
    // Esta funcion se encarga de descontar el contador, la tengo q llamar SystickHandler
    if(Timer[NumeroTimer].contador > 0)
    {
      Timer[NumeroTimer].contador--;
      if(Timer[NumeroTimer].contador == 0)
      {
        Timer[NumeroTimer].fin = 1;
      }
    }
  }
}
