#include <TimerOne.h>

const int Pin_Led = 13;

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize(1000);  // 1ms
  Timer1.attachInterrupt( Systick_Handler );

  pinMode(Pin_Led, OUTPUT);

  Serial.begin(9600);
}

void Systick_Handler(void)
{
  // Aca vamos a entrar cada 1mseg
  GPIO_Antirebote();
}

void loop() {
  
  MaqEst_Bomba();
}

void MaqEst_Bomba(void)
{
  switch(EstadoBomba)
  {
    case 0:
      Estado_NoLlenando();
      break;
    case 1:
      Estado_Llenando();
      break; 
    default:
      Inicio();
      break;   
  }
}

void Estado_NoLlenando(void)
{
  if(TECLADO_Read() == '1')
  {
    digitalWrite(Bomba, 1);

    Serial.println("Bomba Encendida");

    EstadoBomba = 1;
  }
}

void Estado_Llenando(void)
{
  if(TECLADO_Read() == '2')
  {
    digitalWrite(Bomba, 0);
    EstadoBomba = 0;
  }  
}
