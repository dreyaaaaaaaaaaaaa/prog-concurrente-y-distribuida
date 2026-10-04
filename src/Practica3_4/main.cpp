#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void longTask() {
    cout << "[hilo de fondo] Empezando tarea larga en segundo plano...\n";
    this_thread::sleep_for(chrono::seconds(2));
    cout << "[hilo de fondo] tarea larga completada.\n";
}

int main() {
    cout << "[main] Arrancando la aplicacion...\n";
    thread workerLongTask(longTask);
    workerLongTask.detach();            // Ya no podemos hacer join() sobre este objeto.
    cout << "[main] Haciendo otras cosas mientras la tarea se ejecuta...\n"; 
    const int esperaPrincipalMs = 500;            // Experimento: cambiar 500 por 3000 y volver a compilar y ejecutar.
    this_thread::sleep_for(chrono::milliseconds(esperaPrincipalMs));
    cout << "[main] Terminando el programa.\n";
    return 0;
}
