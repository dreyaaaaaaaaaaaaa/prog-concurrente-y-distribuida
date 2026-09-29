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

int maint(){
    thread t1(factorial, 1);
    thread t2(factorial, 2);
    thread t3(factorial, 3);
    thread t4(factorial, 4);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cout << "" << endl;
    return 0;
}