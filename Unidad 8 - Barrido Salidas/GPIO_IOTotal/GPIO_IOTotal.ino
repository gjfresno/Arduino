#include <TimerOne.h>

#define ENTRADA0  4
#define Bomba  13   //led rojo indicando la bomba cargando
#define LApagado  8   //led azul indica que la maquina esta lista para arrancar

int BOMBA = 0;     // estados de las salidas
int LAPAGADO = 0;

enum Estados   { 
   Estado_0,
   Estado_1
}; 
Estados estado = Estado_0;

char flag_mostrar_info = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando...");
  pinMode(ENTRADA0, INPUT_PULLUP);
  GPIO_Antirebote_Init();
  
  pinMode(Bomba, OUTPUT);
  pinMode(LApagado, OUTPUT);
  GPIO_BarridoSalidasInit();
  
  Timer_Inicializacion();
}

void Timer_Inicializacion(void){
  Timer1.initialize(1000); //1ms
  Timer1.attachInterrupt(Systick_Handler);
 } 

char Buf[20];

void loop() {
  
  ME_Control_Nivel();
  
//  if(flag_mostrar_info)
//  {
//    flag_mostrar_info = 0;
//
//    sprintf(Buf, "E:%d B:%d L:%d", estado, BOMBA, LAPAGADO);
//    Serial.println(Buf);
//  }
}

void Systick_Handler(void){

    GPIO_Antirebote();
    GPIO_BarridoSalidas();

    static int divisor = 0;
    divisor++;
    if(divisor > 1000)
    {
      divisor = 0;
      flag_mostrar_info = 1; 
    }
} 


void ME_Control_Nivel(void) {
 switch(estado){
  case Estado_0:  
    APAGADO();
    break;
    
  case Estado_1:     
    ENCENDIDO();
    break;

  default:     
    estado = Estado_0;
    break;

  }
}
 
void APAGADO(void) {
//  BOMBA =0;
//  LAPAGADO=1;
    if(digitalRead_Debounce(0)==1){
          estado = Estado_1;  
            digitalWrite_OUT(Bomba,1);   //ordenes
  digitalWrite_OUT(LApagado,0);
      }
}

void ENCENDIDO() {
//  BOMBA =1;
//  LAPAGADO=0;
    if(digitalRead_Debounce(0)==0){
          estado = Estado_0;  
           digitalWrite_OUT(Bomba,0);   //ordenes
          digitalWrite_OUT(LApagado,1);
      }
}  
