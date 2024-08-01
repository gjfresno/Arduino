#include <LiquidCrystal.h>

/* Display */
//LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void LCD_Display(int fila, int columna, char* cadena);

void setup() {
  // Configura el LCD para 16 columnas y 2 filas
  lcd.begin(16, 2);
  // Imprime un mensaje en la primera línea
  LCD_Display(0, 3, "Hola");
}

int temperatura = 0;
char Buf[20];

void loop() {
  temperatura++;
  if(temperatura > 200)
    temperatura = 0;

  sprintf(Buf, "La temp es: %03d", temperatura);
  LCD_Display(1, 0, Buf);

  delay(1000); // Solo a modo de ejemplo
}

void LCD_Display(int fila, int columna, char* cadena)
{
  // Coloca el cursor en la segunda línea
  lcd.setCursor(columna, fila);
  // Imprime un mensaje en la segunda línea
  lcd.print(cadena);
}


