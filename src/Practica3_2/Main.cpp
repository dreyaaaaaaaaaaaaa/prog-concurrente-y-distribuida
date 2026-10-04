#include <iostream>
#include <thread>
using namespace std;

void factorial(int number) {
    int factorial_value = 1;
    for (int i = 1; i <= number; i++) {
        factorial_value *= i;
    }
    cout << "Factorial of " << number
         << " is " << factorial_value << "\n";
}

int main(){
    thread t1(factorial, 5);
    thread t2(factorial, 6);
    thread t3(factorial, 7);
    thread t4(factorial, 8);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cout << "thread principal" << endl;
    return 0;
}