#include "Sistema.h"
#include "mbed.h"
#include "Tiempo.h"
#include "ControladorLuminosidad.h"
#include "ControladorTemperatura.h"
 
Sistema::Sistema(Tiempo& tiempo, float minimaLuz, float maximaTemperatura, PinName const &pinLuz, PinName const &pinVentilador,
    PinName const &pinLuminosidad, PinName const &pinTemperaturaHumedad, PinName const &pinSirena )
    : 
    tiempo(tiempo),
    controladorLuminosidad(pinLuz, pinLuminosidad, pinSirena, minimaLuz, cantidadLecturas),
    controladorTemperatura(pinVentilador, pinTemperaturaHumedad, pinSirena, maximaTemperatura, cantidadLecturas) 
{

    // inicio hilo para manejar eventos
    hiloEventos.start(callback(&cola, &EventQueue::dispatch_forever));
    // temporizador cada 5 segundos
    temporizador.attach(cola.event(this, &Sistema::controlar), 5.0);
}
 
void Sistema::controlar() {
    bool imprimirLuminosidad = false, imprimirTemperatura = false;    
    printf("Controlando en tiempo: %s\n", tiempo.obtener());
    imprimirLuminosidad = controladorLuminosidad.actualizar();
    imprimirTemperatura = controladorTemperatura.actualizar();

    // si se llega a la cantidad de lecturas se imprimen los datos
    if (imprimirLuminosidad) {
        printf("Luminosidad: %.2f (%.2f / %d)\n", controladorLuminosidad.getValorLuminosidad(), controladorLuminosidad.getAcumuladorLuminosidad(), controladorLuminosidad.getContadorLecturas());
        printf("Estado luz: %s \n", controladorLuminosidad.getEstadoLuz());
    }
    
    if (imprimirTemperatura) {
        printf("Temperatura: %.2f (%.2f / %d)\n", controladorTemperatura.getValorTemperatura(), controladorTemperatura.getAcumuladorTemperatura(), controladorTemperatura.getContadorLecturasValidas());
        printf("Humedad:     %.2f (%.2f / %d)\n", controladorTemperatura.getValorHumedad(), controladorTemperatura.getAcumuladorHumedad(), controladorTemperatura.getContadorLecturasValidas());
        printf("Estado ventilador: %s \n", controladorTemperatura.getEstadoVentilador());
    }
}
