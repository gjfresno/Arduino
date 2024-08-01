#include <Wire.h> 
#include <LiquidCrystal_I2C.h>     // if you don´t have I2C version of the display, use LiquidCrystal.h library instead

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x3f,16,2);    // set the LCD address to 0x3f for a 16 chars and 2 line display
// if you don´t know the I2C address of the display, use I2C scanner first (https://playground.arduino.cc/Main/I2cScanner/)

void setup() {
  // Inicializa el LCD
  lcd.begin(16, 2);
  // Enciende la retroiluminación
  lcd.backlight();
  // Imprime un mensaje en la primera línea
  lcd.print("Hello, World!");
  // Coloca el cursor en la segunda línea
  lcd.setCursor(0, 1);
  // Imprime un mensaje en la segunda línea
  lcd.print("Arduino I2C LCD");
}

void loop() {
  // El loop está vacío porque solo necesitamos configurar la pantalla una vez
}