#ifndef CONTROLADOR_TEMPERATURA_H
#define CONTROLADOR_TEMPERATURA_H
 
#include "mbed.h"
#include "arm_book_lib.h"
#include "Dht22.h"

class ControladorTemperatura {

public:
    ControladorTemperatura(PinName const &pinVentilador, PinName const &pinTemperaturaHumedad, PinName const &pinSirena, float const maximaTemperatura, int const lecturas);    
    bool actualizar();
    float getAcumuladorTemperatura();
    float getValorTemperatura();
    float getAcumuladorHumedad();
    float getValorHumedad();
    int getContadorLecturasValidas();
    int getContadorLecturas();
    char const* getEstadoVentilador();

private:
    // dispositivos
    PwmOut ventilador;
    Dht22 temperaturaHumedad;
    DigitalOut sirena;
    // atributo de minima luz
    float const maximaTemperatura;
    // atributos usados para control de lecturas
    int contadorLecturas = 0;
    int const lecturas;
    // atributos usados para temperatura y humedad
    int contadorLecturasValidas = 0;
    float acumuladorTemperatura = 0.0;
    float acumuladorHumedad = 0.0;
    float valorTemperatura = 0.0;
    float valorHumedad = 0.0;
};

#endif