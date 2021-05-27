#ifndef CONTROLADOR_LUMINOSIDAD_H
#define CONTROLADOR_LUMINOSIDAD_H
 
#include "mbed.h"
#include "arm_book_lib.h"

class ControladorLuminosidad {

public:
    ControladorLuminosidad(PinName const &pinLuz, PinName const &pinLuminosidad, PinName const &pinSirena, float const minimaLuz, int const lecturas);    
    bool actualizar();
    float getAcumuladorLuminosidad();
    float getValorLuminosidad();
    int getContadorLecturas();
    char const* getEstadoLuz();

private:
    // dispositivos
    PwmOut luz;
    AnalogIn luminosidad;
    DigitalOut sirena;
    // atributo de minima luz
    float const minimaLuz;
    // atributos usados para control de lecturas
    int contadorLecturas = 0;
    int const lecturas;
    // atributos usados para luminosidad
    float acumuladorLuminosidad = 0.0;
    float valorLuminosidad = 0.0;
};

#endif