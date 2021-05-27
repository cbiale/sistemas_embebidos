#ifndef SISTEMA_H
#define SISTEMA_H
 
#include "mbed.h"
#include "Tiempo.h"
#include "ControladorLuminosidad.h"
#include "ControladorTemperatura.h"
 
class Sistema {

public:
    Sistema(Tiempo& tiempo, float minimaLuz, float maximaTemperatura, PinName const &pinLuz, PinName const &pinVentilador,
    PinName const &pinLuminosidad, PinName const &pinTemperaturaHumedad, PinName const &pinSirena);
    
    void controlar();

private:
    // temporizador y cola de mensajes
    Ticker temporizador;
    EventQueue cola;
    // hilo para manejar eventos
    Thread hiloEventos;
    // cantidad de lecturas a realizar por los controladores
    int const cantidadLecturas = 12;
    // tiempo
    Tiempo tiempo;
    // controlador de luminosidad
    ControladorLuminosidad controladorLuminosidad;
    // controlador de temperatura
    ControladorTemperatura controladorTemperatura;
};
 
#endif