#ifndef TIEMPO_H
#define TIEMPO_H
 
#include "mbed.h"
 
class Tiempo {

public:
    Tiempo (int dia, int mes, int anio, int hora, int minuto, int segundo); 
    
    char* obtener();
 
private:
    struct tm tiempo;
};
 
#endif