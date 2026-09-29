#include <iostream>
#include <thread>
using namespace std;

void Tarea(){
    cout << "Thread secundario" << endl;
}

void greetings(int id){
    cout << "Hello from Thread" << id << "(real id :"
    << std::this_thread::get_id() << ") \n";            
}

int main(){
    thread Hilo(Tarea);
    Hilo.join();
    cout << "Thread principal" << endl;
    return 0;
}