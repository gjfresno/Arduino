// Arduino Display Matricial
// Author: Fresno Gustavo

#include <LedControl.h> // https://github.com/wayoda/LedControl


const int dataPin = 3;  // Pin de datos del MAX7219
const int clockPin = 4; // Pin de reloj del MAX7219
const int csPin = 5;    // Pin de selección de chip del MAX7219
const int NUM_DEVICES = 6;

LedControl lc = LedControl(dataPin, clockPin, csPin, NUM_DEVICES);  // Inicializamos la librería LedControl

// Definición de los caracteres usando mapas de bits (8x8)
const byte H[] = {
  0b01100110,
  0b01100110,
  0b01100110,
  0b01111110,
  0b01111110,
  0b01100110,
  0b01100110,
  0b01100110
};

const byte E[] = {
  0b01111110,
  0b01111110,
  0b01100000,
  0b01111110,
  0b01111110,
  0b01100000,
  0b01111110,
  0b01111110
};

const byte A[] = {
  0b00111100,
  0b01111110,
  0b01100110,
  0b01111110,
  0b01111110,
  0b01100110,
  0b01100110,
  0b01100110
};

const byte L[] = {
  0b01100000,
  0b01100000,
  0b01100000,
  0b01100000,
  0b01100000,
  0b01100000,
  0b01111110,
  0b01111110
};

const byte O[] = {
  0b00111100,
  0b01111110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01100110,
  0b01111110,
  0b00111100
};

void displayChar(int device, int position, const byte character[]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(device, position + row, reverseBits(character[row]));
  }
}

uint8_t reverseBits(uint8_t b) {
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return b;
}

void setup() {
  // Configuración del brillo de los LEDs (0-15)
  lc.setIntensity(0, 8);
  lc.setIntensity(1, 8);

  // Limpieza de los displays
  lc.clearDisplay(0);
  lc.clearDisplay(1);

  // Mostrando "HELLO" en los displays
  displayChar(5, 0, H);
  displayChar(4, 0, O);
  displayChar(3, 0, L);
  displayChar(2, 0, A);

}

void loop() {

}

