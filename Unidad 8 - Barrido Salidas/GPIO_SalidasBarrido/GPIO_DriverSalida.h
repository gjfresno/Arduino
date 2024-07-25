#ifndef GPIO_DriverSalida
#define GPIO_DriverSalida

#define CANTIDAD_MAXIMA_SALIDAS   10

class GPIO_Salida
{
  public:
 
    int Config(char numPin);
    int Delete(char numPin);
    int Set(char numPin, char estado);
    int Get(char numPin);
    int Find(char numPin);
    GPIO_Salida();
    void Barrido(void);

  private:
    int numPin[CANTIDAD_MAXIMA_SALIDAS];
    char estado[CANTIDAD_MAXIMA_SALIDAS];

};

#endif
