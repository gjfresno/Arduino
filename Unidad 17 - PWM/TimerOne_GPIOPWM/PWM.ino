#define PINPWM  13

unsigned char duty = 0;

void PWM_Init(unsigned char duty_init)
{
  pinMode(PINPWM, OUTPUT);

  duty = duty_init;
}

void PWM_Set(unsigned char duty_conf)
{
  if(duty_conf > 10)
    duty_conf = 10;
  
  duty = duty_conf;

  Serial.print("PWM: ");
  Serial.println((int)duty); // Muestra el carácter recibido en el puerto serial
}

void PWM_Work(void)
{
  // 0 1 2 3 4 5 6 7 8 9
  //       d   
  // 11111110000000000000
  
  static char div = 0;

  div++;
  
  if(div > duty)
  {
    digitalWrite(PINPWM, 0);
  }
  else
  {
    digitalWrite(PINPWM, 1);
  }

  if(div >= 10)
    div = 0;
}
