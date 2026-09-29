#include <iostream>
#include <thread>
using namespace std;

void greetings(int id){
    cout << "Hello from Thread " << id << "(real id :"
    << std::this_thread::get_id() << ") \n";            
}

int main(){
    thread t1(greetings, 1);
    thread t2(greetings, 2);
    thread t3(greetings, 3);
    thread t4(greetings, 4);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cout << "Thread principal" << endl;
    return 0;
}