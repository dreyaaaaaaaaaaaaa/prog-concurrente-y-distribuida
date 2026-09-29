#include <iostream>
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
    
}