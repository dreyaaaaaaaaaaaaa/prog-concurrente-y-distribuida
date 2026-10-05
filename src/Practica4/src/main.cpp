#include <iostream>
#include <thread>
using namespace std;

const int PRUEBAS = 5;
long long contador = 0;

void incrementar(int iteraciones) {
    for (int i = 0; i < iteraciones; i++) {
        contador++;
    }
}

void realizarPruebas(int iteraciones) {
    long long esperado = 4LL * iteraciones;
    cout << "Iteraciones por hilo: " << iteraciones << endl;
    for (int prueba = 1; prueba <= PRUEBAS; prueba++) {
        contador = 0;
        thread hilo1(incrementar, iteraciones);
        thread hilo2(incrementar, iteraciones);
        thread hilo3(incrementar, iteraciones);
        thread hilo4(incrementar, iteraciones);
        hilo1.join();
        hilo2.join();
        hilo3.join();
        hilo4.join();
        cout << "Prueba " << prueba << endl;
        cout << "Resultado esperado: " << esperado << endl;
        cout << "Resultado obtenido: " << contador << endl;
        if (contador == esperado) {
            cout << "El resultado coincide con el esperado." << endl;
        } else {
            cout << "El resultado no coincide con el esperado." << endl;
        }
        cout << endl;
    }
}

int main() {
    realizarPruebas(1000000);
    realizarPruebas(10);
    return 0;
}