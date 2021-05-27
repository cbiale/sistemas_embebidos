#include "mbed.h"
#include "ControladorLuminosidad.h"
#include "arm_book_lib.h"


ControladorLuminosidad::ControladorLuminosidad(PinName const &pinLuz, PinName const &pinLuminosidad, PinName const &pinSirena, float const minimaLuz, int const lecturas) :
    luz(pinLuz), luminosidad(pinLuminosidad), sirena(pinSirena), minimaLuz(minimaLuz), lecturas(lecturas)
{}    


bool ControladorLuminosidad::actualizar() {
    // variable a devolver
    bool imprime = false;

    // cambiado para imprimir valores acumuladores en Sistema
    // si al ingresar el contador de lecturas es igual a la cantidad de lecturas a realizar
    if (contadorLecturas == lecturas) {
        // reinicio atributos para promedio siguiente
        contadorLecturas = 0;
        acumuladorLuminosidad = 0.0;
    }
    contadorLecturas++;
    acumuladorLuminosidad += luminosidad.read();
    // si se realizan las lecturas necesarias
    if (contadorLecturas == lecturas) {
        imprime = true;
        // promedio de lecturas
        valorLuminosidad = acumuladorLuminosidad / contadorLecturas;
        // si la lumninosidad es menor a la necesaria        
        if (valorLuminosidad <= minimaLuz && luz == OFF) {
            // activo led
            sirena = ON;
            printf("Activando led\n");
            luz = ON;
            sirena = OFF;
        } 
        if (valorLuminosidad > minimaLuz && luz != OFF) {
            // desactivo led
            sirena = ON;
            printf("Desactivando led\n");
            luz = OFF;
            sirena = OFF;
        }
    }
    return imprime;
}


float ControladorLuminosidad::getAcumuladorLuminosidad() {
    return acumuladorLuminosidad;
};

float ControladorLuminosidad::getValorLuminosidad() {
    return valorLuminosidad;
}

int ControladorLuminosidad::getContadorLecturas() {
    return contadorLecturas;
}

char const* ControladorLuminosidad::getEstadoLuz() {
    return luz == ON ? "ON" : "OFF";
}