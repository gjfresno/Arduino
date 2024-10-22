#include <Adafruit_GFX.h>    // Biblioteca GFX de Adafruit
#include <Adafruit_ST7789.h> // Biblioteca ST7789 de Adafruit
#include <SPI.h>             // Para comunicación SPI

// Definir pines
#define TFT_SCK 18   // Pin SCK (CLK)
#define TFT_MOSI 23  // Pin SDA (MOSI)
#define TFT_RST 4    // Pin Reset
#define TFT_DC 2     // Pin DC (Data/Command)
#define TFT_CS  -1

// Tamaño de la pantalla (en píxeles)
#define TFT_WIDTH 240
#define TFT_HEIGHT 240

// Inicializar el objeto Adafruit_ST7789
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Configurar SPI con pines personalizados
  SPI.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS);  // SCK, MISO, MOSI, CS

  // Iniciar la pantalla ST7789
  tft.init(240, 240, SPI_MODE3);  // Iniciar pantalla con resolución 240x240
  tft.setRotation(1);  // Ajustar rotación si es necesario
  tft.fillScreen(ST77XX_BLACK);  // Limpiar pantalla
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("Hola Mundo!");
}

void loop() {
  // Lógica del programa
}
