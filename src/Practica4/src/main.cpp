#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

const int PRUEBAS = 5;
long long contador = 0;
atomic<long long> contadorAtomico(0);

void incrementar(int iteraciones) {
    for (int i = 0; i < iteraciones; i++) {
        contador++;
    }
}

void incrementarAtomico(int iteraciones) {
    for (int i = 0; i < iteraciones; i++) {
        contadorAtomico++;
    }
}

void realizarPruebas(int iteraciones, bool usarAtomico) {
    long long esperado = 4LL * iteraciones;
    cout << "Iteraciones por hilo: " << iteraciones << endl;
    if (usarAtomico) {
        cout << "Contador atomico" << endl;
    } else {
        cout << "Contador sin proteccion" << endl;
    }
    for (int prueba = 1; prueba <= PRUEBAS; prueba++) {
        contador = 0;
        contadorAtomico = 0;
        thread hilos[4];
        for (int i = 0; i < 4; i++) {
            if (usarAtomico) {
                hilos[i] = thread(incrementarAtomico, iteraciones);
            } else {
                hilos[i] = thread(incrementar, iteraciones);
            }
        }
        for (int i = 0; i < 4; i++) {
            hilos[i].join();
        }
        long long resultado;
        if (usarAtomico) {
            resultado = contadorAtomico.load();
        } else {
            resultado = contador;
        }
        cout << "Prueba " << prueba << endl;
        cout << "Resultado esperado: " << esperado << endl;
        cout << "Resultado obtenido: " << resultado << endl;
        if (resultado == esperado) {
            cout << "El resultado coincide con el esperado." << endl;
        } else {
            cout << "El resultado no coincide con el esperado." << endl;
        }
        cout << endl;
    }
}

int main() {
    realizarPruebas(1000000, false);
    realizarPruebas(10, false);
    realizarPruebas(1000000, true);
    realizarPruebas(10, true);
    return 0;
}