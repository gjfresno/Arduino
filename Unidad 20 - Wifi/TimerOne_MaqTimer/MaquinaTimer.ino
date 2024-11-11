
#define BASEDETIEMPO      1000
#define CANTIDAD_TIMERS   16

// Genero una estructura 
typedef struct
{
  unsigned int  contador;
  unsigned int  recarga;
  char          fin;
  void (*func) (void);
}Struct_Timer;

// Declaro un vector de estructuras
Struct_Timer  Timer[CANTIDAD_TIMERS];

hw_timer_t *My_timer = NULL;  // Crear un puntero de tipo hw_timer_t

void IRAM_ATTR Systick_Handler();

//--------------------------------------

void TimerInit(void)
{
    // Inicializar el temporizador: 
  // - timer 0 
  // - prescaler 80 (frecuencia de 1 MHz)
  // - contador ascendente
  My_timer = timerBegin(0, 80, true);

  // Vincular la función de interrupción al temporizador
  timerAttachInterrupt(My_timer, Systick_Handler, true);

  // Configurar el temporizador para que dispare la interrupción cada 1 segundo (1,000,000 microsegundos)
  timerAlarmWrite(My_timer, 1000, true);

  // Habilitar la alarma del temporizador para que empiece a funcionar
  timerAlarmEnable(My_timer);

  Serial.println("Timer inicializado..");
}

void IRAM_ATTR Systick_Handler()
{
  // Aca entro cada 1ms = 1000Hz
  Timer_Descontar();
}

void Timer_Inicializar(char NumeroTimer)
{
  Timer[NumeroTimer].contador = 0;
  Timer[NumeroTimer].recarga = 0;
  Timer[NumeroTimer].fin = 0;
  Timer[NumeroTimer].func = 0;
}

void Timer_Disparar(char NumeroTimer, unsigned int tiempo, unsigned int tiempoRecarga, void (*func)(void))
{
  // Esta funcion es la que se encarga de configurar la temporizacion
  Timer[NumeroTimer].contador = tiempo;
  Timer[NumeroTimer].fin = 0;
  Timer[NumeroTimer].recarga = tiempoRecarga;
  Timer[NumeroTimer].func = func;
}

void Timer_Analizar(void)
{
  // Esta se encarga del analizar que el contador haya llegado a cero y realizar la accion de fin
  // La voy a llamar dentro del loop
  
  for(int i = 0 ; i < CANTIDAD_TIMERS ; i++)
  {
    if(Timer[i].fin == 1)
    {
      Timer[i].fin = 0;

      if(Timer[i].func != 0)
        Timer[i].func();
    }
  }
}

void Timer_Descontar(void)
{
  for(int i = 0 ; i < CANTIDAD_TIMERS ; i++)
  {
    // Esta funcion se encarga de descontar el contador, la tengo q llamar SystickHandler
    if(Timer[i].contador > 0)
    {
      Timer[i].contador--;
      if(Timer[i].contador == 0)
      {
        Timer[i].fin = 1;

        Timer[i].contador = Timer[i].recarga;
      }
    }
  }
}
