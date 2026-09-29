#include <iostream>
#include <thread>
#include <vector>
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
    vector<int> datos = {1, 2, 3, 4, 5, 6, 7, 8};
    thread t1(sumarTramo, ref(datos), 0, 2, 0);
    thread t2(sumarTramo, ref(datos), 2, 4, 1);
    thread t3(sumarTramo, ref(datos), 4, 6, 2);
    thread t4(sumarTramo, ref(datos), 6, 8, 3);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cout << "thread principal" << endl;
    return 0;
}