#define TAMANIO_DISPLAY_HEIGHT  240
#define TAMANIO_DISPLAY_WIDTH   240

void mostrarImagen( tImage *dataImage) {
  int index = 0;
  for (int y = 0; y < dataImage->height; y++) {
    for (int x = 0; x < dataImage->width; x++) {
      tft.drawPixel(x, y, dataImage->data[index++]);  // Dibujar cada píxel desde el array
    }
  }
}

void redibujarFondo(int posX, int posY, int width, int height, tImage *dataImage) {
  int index = 0;
  char graficar = 0;
  for (int y = 0; y < dataImage->height; y++) {
    for (int x = 0; x < dataImage->width; x++) {

      graficar = 1;

      if(y < posY)
        graficar = 0;

      if(y > posY + height)
        graficar = 0;

      if(x < posX)
        graficar = 0;

      if(x > posX + width)
        graficar = 0;

      if(graficar)
        tft.drawPixel(x, y, dataImage->data[index]);  // Dibujar cada píxel desde el array

      index++;
    }
  }
}

void pasteImage( tImage *imagen, unsigned int posX, unsigned int posY)
{
  int index = 0;
  
  for (int y = 0; y < imagen->height; y++) {
    for (int x = 0; x < imagen->width; x++) {
      
      if(imagen->data[index] != 0xf81f)
        tft.drawPixel(posX + x, posY + y, imagen->data[index]);
      
      index++;
    }
  }   
}
