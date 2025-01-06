// Autor: Fresno Gustavo

#include <TimerOne.h>

#define BASEDETIEMPO      1000
#define CANTIDAD_TIMERS   16

// Genero una estructura 
typedef struct
{
  unsigned int  contador;
  unsigned int  recarga;
  char          fin;
  void          (*func)(void);
}Struct_Timer;

unsigned int divisor = 0;
unsigned char flag_Led = 0;

// Declaro un vector de estructuras
Struct_Timer  Timer[CANTIDAD_TIMERS];

void Timer_Inicializar(void){
  Timer1.initialize(1000);  // Internamente trabaja a 1us, por eso pongo 1000 para contar 1ms
  Timer1.attachInterrupt( Systick_Handler );
}

void Systick_Handler(void)
{
  // Voy a entrar cada 1000us = 1ms = 0,001seg  

  // Base de tiempo es de 1milisegundo
  Timer_Descontar();

  divisor++;
  if(divisor >= 1000)
  {
    divisor = 0;

    // Base de tiempo es de 1segundo
    //Timer_Descontar();
  }
}

//--------------------------------------

void Timer_Inicializar(char NumeroTimer)
{
  Timer[NumeroTimer].contador = 0;
  Timer[NumeroTimer].fin = 0;
  Timer[NumeroTimer].func = 0;
  Timer[NumeroTimer].recarga = 0;
  
}

void Timer_Disparar(char NumeroTimer, unsigned int tiempo, unsigned int tiempoRecarga, void (*funcion)(void))
{
  // Esta funcion es la que se encarga de configurar la temporizacion
  Timer[NumeroTimer].contador = tiempo;
  Timer[NumeroTimer].fin = 0;
  Timer[NumeroTimer].func = funcion;
  Timer[NumeroTimer].recarga = tiempoRecarga;
}

void Timer_Analizar(void)
{
  // Esta se encarga del analizar que el contador haya llegado a cero y realizar la accion de fin
  // La voy a llamar dentro del loop
  
  for(int NumeroTimer = 0 ; NumeroTimer < CANTIDAD_TIMERS ; NumeroTimer++)
  {
    if(Timer[NumeroTimer].fin == 1)
    {
      Timer[NumeroTimer].fin = 0;

      Timer[NumeroTimer].func();
    }
  }
}

void Timer_Descontar(void)
{
  for(int NumeroTimer = 0 ; NumeroTimer < CANTIDAD_TIMERS ; NumeroTimer++)
  {
    // Esta funcion se encarga de descontar el contador, la tengo q llamar SystickHandler
    if(Timer[NumeroTimer].contador > 0)
    {
      Timer[NumeroTimer].contador--;
      if(Timer[NumeroTimer].contador == 0)
      {
        Timer[NumeroTimer].fin = 1;
        Timer[NumeroTimer].contador = Timer[NumeroTimer].recarga;
      }
    }
  }
}
