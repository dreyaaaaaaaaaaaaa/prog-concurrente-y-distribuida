#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <functional>
using namespace std;

int numThreads = 4;
vector<long long> parciales(numThreads);

void sumarTramo(const vector<int>& datos, int inicio, int fin, int idx) {
    long long suma = 0;

    for (int i = inicio; i < fin; ++i)
        suma += datos[i];

    parciales[idx] = suma;
}

int main(){
    vector<int> datos(1000000);
    iota(datos.begin(), datos.end(), 1);
    vector<thread> threads;
    for (int idx = 0; idx < numThreads; ++idx) {
        int inicio = static_cast<int>(datos.size()) * idx / numThreads;   // Calcular el inicio del tramo para cada hilo
        int fin = static_cast<int>(datos.size()) * (idx + 1) / numThreads;  // Calcular el fin del tramo para cada hilo
        threads.emplace_back(sumarTramo, cref(datos), inicio, fin, idx);  // Crear un hilo para cada tramo y pasar los argumentos necesarios
    }
    for (auto& t : threads) t.join();      // puntero a cada hilo y esperar a que terminen
    long long total = accumulate(parciales.begin(), parciales.end(), 0LL);   // Sumar los resultados parciales de cada hilo para obtener la suma total
    cout << "Suma total: " << total << endl;
    return 0;
}
