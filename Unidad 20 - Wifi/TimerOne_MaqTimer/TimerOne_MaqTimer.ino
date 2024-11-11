const int Pin_Led = 2;

void setup() {
  // Inicializacion del puerto serial
  Serial.begin(115200);
  
  pinMode(Pin_Led, OUTPUT);

  TimerInit();

  Timer_Disparar(0, 1000, 1000, Led);
}

void loop() {
  Timer_Analizar();
}

void Led()
{
    digitalWrite(Pin_Led, !digitalRead(Pin_Led));  // Invertir el estado del LED
}
