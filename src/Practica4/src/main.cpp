#include <iostream>
#include <thread>
using namespace std;

const int ITERACIONES = 1000000;
const int PRUEBAS = 5;
long long contador = 0;

void incrementar() {
    for (int i = 0; i < ITERACIONES; i++) {
        contador++;
    }
}

int main() {
    long long esperado = 4LL * ITERACIONES;
    for (int prueba = 1; prueba <= PRUEBAS; prueba++) {
        contador = 0;
        thread hilo1(incrementar);
        thread hilo2(incrementar);
        thread hilo3(incrementar);
        thread hilo4(incrementar);
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
    return 0;
}