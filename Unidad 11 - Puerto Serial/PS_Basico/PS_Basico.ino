void setup() {
  Serial.begin(9600);
}


void loop() {
  if (Serial.available() > 0) 
  { // Comprueba si hay datos disponibles en el buffer del puerto serial
    char receivedChar = Serial.read(); // Lee el primer byte de datos del buffer
    Serial.print("Caracter recibido: ");
    Serial.println(receivedChar); // Muestra el carácter recibido en el puerto serial
  }
}
