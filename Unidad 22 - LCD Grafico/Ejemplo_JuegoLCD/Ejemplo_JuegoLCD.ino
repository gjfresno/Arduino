#include <Adafruit_GFX.h>    // Biblioteca GFX de Adafruit
#include <Adafruit_ST7789.h> // Biblioteca ST7789 de Adafruit
#include <SPI.h>             // Para comunicación SPI
#include "TFT_Defines.h"

extern const tImage fondo;
extern const tImage sonic;
extern tImage bufDisplay;

// Definir pines
#define TFT_SCK 18   // Pin SCK (CLK)
#define TFT_MOSI 23  // Pin SDA (MOSI)
#define TFT_RST 4    // Pin Reset
#define TFT_DC 2     // Pin DC (Data/Command)
#define TFT_CS  -1

// Tamaño de la pantalla (en píxeles)
#define TFT_WIDTH 240
#define TFT_HEIGHT 240

#define SPI_FREQUENCY 80000000  // 80 MHz

// Inicializar el objeto Adafruit_ST7789
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


void setup() {
  // Configurar SPI con pines personalizados
  SPI.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS);  // SCK, MISO, MOSI, CS

  // Iniciar la pantalla ST7789
  tft.init(240, 240, SPI_MODE3);  // Iniciar pantalla con resolución 240x240
  tft.setSPISpeed(80000000);
  //tft.setRotation(1);  // Ajustar rotación si es necesario
  //tft.fillScreen(ST77XX_BLACK);  // Limpiar pantalla
  tft.setAddrWindow( 0,0, 320, 240 );

  mostrarImagen((tImage*)&fondo);
}

unsigned int posSonicPrevX = 20;
unsigned int posSonicPrevY = 180;
char  refrescar = 1;

void loop() {

  char Buf[20];

  uint32_t controlX = analogRead(12);
  uint32_t controlY = analogRead(14);

  if(controlX > 3000){
    refrescar = 1;

    posSonicPrevX++;
    posSonicPrevX %= TFT_WIDTH;
  }
  if(controlX < 1000){
    refrescar = 1;

    if(posSonicPrevX > 0)
      posSonicPrevX--;
  }
  if(controlY > 3000){
    refrescar = 1;

    posSonicPrevY++;
    posSonicPrevY %= TFT_HEIGHT;
  }
  if(controlY < 1000){
    refrescar = 1;

    if(posSonicPrevY > 0)
      posSonicPrevY--;
  }

  if(refrescar){
    refrescar = 0;

    redibujarFondo(posSonicPrevX, posSonicPrevY, 50, 50, (tImage*)&fondo);

    pasteImage((tImage*)&sonic, posSonicPrevX, posSonicPrevY);

    tft.fillRect(10, 10, 180, 15, ST77XX_BLACK);
    sprintf(Buf, "X=%d Y=%d", posSonicPrevX, posSonicPrevY);
    tft.setCursor(10, 10);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.println(Buf);
  }
  // Lógica del programa
}
