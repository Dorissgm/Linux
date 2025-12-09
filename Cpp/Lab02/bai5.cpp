#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b +c;
}

int main() {
    cout << "add(3, 4) = " << add(3, 4) << endl;
    cout << "add(2.5, 4.98) = " << add(2.5, 4.89) << endl;
    cout << "add(2, 4, 5) = " << add(2, 4, 5) << endl;

}
