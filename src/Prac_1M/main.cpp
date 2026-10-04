#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

atomic<int> cont{0};

void million(){
        for(int i = 0; i < 1000000; i++){
            cont++;
        }     
}

int main(){
    thread t1(million);
    thread t2(million);
    thread t3(million);
    thread t4(million);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cout << "Contador final: " << cont.load() << endl;
    return 0;
}
