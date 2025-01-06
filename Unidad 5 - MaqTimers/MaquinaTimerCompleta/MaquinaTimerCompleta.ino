#define PIN_LED   2   

void setup() {

  Timer_Inicializar();

  pinMode(PIN_LED, OUTPUT);

  Timer_Disparar(0, 1000, 1000, Led);
}

void loop() {
  // put your main code here, to run repeatedly:
  Timer_Analizar();
}

void Led(void)
{
  static char status = 0;

  if(status){
    status = 0;
    digitalWrite(PIN_LED, HIGH);
  }
  else{
    status = 1;
    digitalWrite(PIN_LED, LOW);
  }
}
