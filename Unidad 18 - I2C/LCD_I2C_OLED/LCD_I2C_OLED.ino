#define __DEBUG__

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64

Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

void setup() {
#ifdef __DEBUG__
  Serial.begin(115200);
  delay(100);
  Serial.println("Iniciando pantalla OLED");
#endif

  // Cambiar la velocidad del bus I2C a 10 kHz
  Wire.begin();
  Wire.setClock(10000); // Ajustar a 10kHz (puedes cambiarlo según tus necesidades)

  // Iniciar pantalla OLED en la dirección 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
#ifdef __DEBUG__
    Serial.println("No se encuentra la pantalla OLED");
#endif
    while (true);
  }

  // Limpiar buffer
  display.clearDisplay();

  // Tamaño del texto
  display.setTextSize(1);
  // Color del texto
  display.setTextColor(SSD1306_WHITE);
  // Posición del texto
  display.setCursor(10, 32);
  // Escribir texto
  display.println("¡¡Hola mundo!!");

  // Enviar a pantalla
  display.display();
}

void loop() {
    // Limpiar buffer
  display.clearDisplay();

  // Tamaño del texto
  display.setTextSize(1);
  // Color del texto
  display.setTextColor(SSD1306_WHITE);
  // Posición del texto
  display.setCursor(10, 32);
  // Escribir texto
  display.println("¡¡Hola mundo!!");

  // Enviar a pantalla
  display.display();
  
  delay(1000);
  }
