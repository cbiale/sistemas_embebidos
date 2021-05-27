#include "Tiempo.h"
#include "mbed.h"
 
Tiempo::Tiempo(int dia, int mes, int anio, int hora, int minuto, int segundo) {
    tiempo.tm_year = anio - 1900;
    tiempo.tm_mon  = mes - 1;
    tiempo.tm_mday = dia;
    tiempo.tm_hour = hora;
    tiempo.tm_min  = minuto;
    tiempo.tm_sec  = segundo;
    tiempo.tm_isdst = -1;
    set_time( mktime(&tiempo)); 
}
 
char* Tiempo::obtener() {
    time_t tiempoActual = time(NULL);
    return ctime(&tiempoActual);    
}
