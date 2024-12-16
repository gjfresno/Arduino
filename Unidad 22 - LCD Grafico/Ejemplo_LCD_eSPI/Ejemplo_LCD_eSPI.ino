//#include <Adafruit_GFX.h>    // Biblioteca GFX de Adafruit
#include <TFT_eSPI.h>       // Librería TFT_eSPI
#include "TFT_Defines.h"

extern const tImage fondo;
extern const tImage sonic;
extern tImage bufDisplay;

TFT_eSPI tft = TFT_eSPI();  // Inicializar el objeto TFT

void setup() {
  // Configurar SPI con pines personalizados
  tft.init();               // Inicializar pantalla
  tft.setRotation(1);       // Ajustar la rotación
  tft.fillScreen(TFT_BLACK); // Limpiar pantalla

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

    tft.fillRect(10, 10, 180, 15, TFT_BLACK);
    sprintf(Buf, "X=%d Y=%d", posSonicPrevX, posSonicPrevY);
    tft.setCursor(10, 10);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.println(Buf);
  }
  // Lógica del programa
}
