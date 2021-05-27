#include "mbed.h"
#include "ControladorTemperatura.h"
#include "arm_book_lib.h"
#include "Dht22.h"

ControladorTemperatura::ControladorTemperatura (PinName const &pinVentilador, PinName const &pinTemperaturaHumedad, PinName const &pinSirena, float const maximaTemperatura, int const lecturas) :
    ventilador(pinVentilador), temperaturaHumedad(pinTemperaturaHumedad), sirena(pinSirena), maximaTemperatura(maximaTemperatura), lecturas(lecturas)
{}

bool ControladorTemperatura::actualizar() {
    // variable a devolver
    bool imprime = false;

    // cambiado para imprimir valores acumuladores en Sistema
    // si al ingresar el contador de lecturas es igual a la cantidad de lecturas a realizar
    if (contadorLecturas == lecturas) {
        // reinicio atributos para promedio siguiente
        contadorLecturas = 0;
        contadorLecturasValidas = 0;
        acumuladorTemperatura= 0.0;
        acumuladorHumedad = 0.0;
    }
    
    contadorLecturas++;
    if (temperaturaHumedad.read() == 0) {
        contadorLecturasValidas++;
        acumuladorTemperatura = acumuladorTemperatura + temperaturaHumedad.getCelsius();
        acumuladorHumedad = acumuladorHumedad + temperaturaHumedad.getHumidity();
    } else {
        printf("Error al leer DHT22 \n");
    }
    if (contadorLecturas == lecturas) {
        imprime = true;
        // promedio de lecturas
        valorTemperatura = acumuladorTemperatura / contadorLecturasValidas;
        valorHumedad = acumuladorHumedad / contadorLecturasValidas;
        // control de ventilador
        if (valorTemperatura >= maximaTemperatura && ventilador == 0){
            // activo ventilador
            sirena = ON;
            printf("Activando ventilador\n");
            ventilador = 1;
            sirena = OFF;
        } 
        if (valorTemperatura < maximaTemperatura && ventilador != 0){
            // desactivo ventilador
            sirena = ON;
            printf("Desactivando ventilador\n");
            ventilador = 0;
            sirena = OFF;
        }
    }
    return imprime;
}

float ControladorTemperatura::getAcumuladorTemperatura() {
    return acumuladorTemperatura;
}

float ControladorTemperatura::getValorTemperatura() {
    return valorTemperatura;
}

float ControladorTemperatura::getAcumuladorHumedad() {
    return acumuladorHumedad;    
}

float ControladorTemperatura::getValorHumedad() {
    return valorHumedad;
}

int ControladorTemperatura::getContadorLecturasValidas() {
    return contadorLecturasValidas;
}

int ControladorTemperatura::getContadorLecturas() {
    return contadorLecturas;
}

char const* ControladorTemperatura::getEstadoVentilador() {
    return ventilador == ON ? "ON" : "OFF";
}
