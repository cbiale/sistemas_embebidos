#include "mbed.h"
#include "arm_book_lib.h"
#include "Dht22.h"
#include "Tiempo.h"
#include "Sistema.h"

int main() {
    // imprimo mensaje de bienvenida
    printf("\nProyecto integrador\n");
    printf("-------------------\n");
    // espero se estabilice el sensor DHT
    delay(1);
    // variable de tiempo
    Tiempo tiempo(26, 5, 2021, 22, 45, 0);
    // variable del sistema
    Sistema sistema(tiempo, 0.3f, 22.0f, PA_0, D6, A0, PE_12, PE_10);
    // bucle infinito
    while (true) {}
}
