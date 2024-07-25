
#include "Arduino.h"
#include "GPIO_DriverSalida.h"

GPIO_Salida::GPIO_Salida(void)
{
  for(int i = 0 ; i < CANTIDAD_MAXIMA_SALIDAS ; i++)
  {
    numPin[i] = -1;
    estado[i] = 0;
  }
}

int GPIO_Salida::Config(char _numPin)
{
  int index = Find(_numPin);
  if(index >= 0)
    return index;

  // El pin no esta configurado previamente
  for(int i = 0 ; i < CANTIDAD_MAXIMA_SALIDAS ; i++)
  {
    if(-1 == numPin[i])
    {
      numPin[i] = _numPin; 
      pinMode(_numPin, OUTPUT);
      return i;
    }
  }

  return -1;
}

int GPIO_Salida::Find(char _numPin)
{
  for(int i = 0 ; i < CANTIDAD_MAXIMA_SALIDAS ; i++)
  {
    if(numPin[i] == _numPin)
      return i;
  }

  return -1;
}

int GPIO_Salida::Delete(char _numPin)
{
  int index = Find(_numPin);
  if(index >= 0)
  {
    numPin[index] = -1;
    estado[index] = 0;
  }

  return -1;
}

int GPIO_Salida::Set(char _numPin, char _estado)
{
  int index = Find(_numPin);
  if(index >= 0)
  {
    estado[index] = _estado;
  }

  return -1;
}


int GPIO_Salida::Get(char _numPin)
{
  int index = Find(_numPin);
  if(index >= 0)
  {
      return estado[index];
  }

  return -1;
}

void GPIO_Salida::Barrido(void)
{
  for(int i = 0 ; i < CANTIDAD_MAXIMA_SALIDAS ; i++)
  {
    if(numPin[i] >= 0)
    {
      if(0 == estado[i])
        digitalWrite(numPin[i], LOW);
      else
        digitalWrite(numPin[i], HIGH);
    }
      
  }
}
