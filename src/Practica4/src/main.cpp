#include <iostream>
#include <thread>
using namespace std;

const int ITERACIONES = 1000000;
long long contador = 0;

void incrementar() {
    for (int i = 0; i < ITERACIONES; i++) {
        contador++;
    }
}

int main() {
    thread hilo1(incrementar);
    thread hilo2(incrementar);
    thread hilo3(incrementar);
    thread hilo4(incrementar);
    hilo1.join();
    hilo2.join();
    hilo3.join();
    hilo4.join();
    cout << "Resultado esperado: " << 4LL * ITERACIONES << endl;
    cout << "Resultado obtenido: " << contador << endl;
    return 0;
}
