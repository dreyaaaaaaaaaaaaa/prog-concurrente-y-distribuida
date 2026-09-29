#include <iostream>
#include <thread>
using namespace std;

void Tarea(){
    cout << "Thread secundario" << endl;
}

int main(){
    thread Hilo(Tarea);
    Hilo.join();
    cout << "Thread principal" << endl;
    return 0;
}