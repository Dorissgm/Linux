#include <iostream>
using namespace std;

struct A
{
    char x;
    int y;
    double z;
};

struct B
{
    int y;
    double z;
    char x;
};

struct C 
{
    double z;
    char x;
    int y;
};

struct D {
    double z;
    int y;
    char x;
};

int main() {
    cout << "Size of A: " << sizeof(A) << " byte" << endl;
    cout << "Size of B: " << sizeof(B) << " byte" << endl;
    cout << "Size of C: " << sizeof(C) << " byte" << endl;
    cout << "Size of D: " << sizeof(D) << " byte" << endl;
}


