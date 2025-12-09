#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() {
        cout << "Am thanh chung cua dong vat." << endl;
    }
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Con cho keu: gau gau." << endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        cout << "Con meo keu: miu miu." << endl;
    }
};

int main() {
    Animal* s1 = new Dog(); // con trỏ kiểu Animal nhưng trỏ tới Dog
    Animal* s2 = new Cat(); // con trỏ kiểu Animal nhưng trỏ tới Cat

    s1->speak(); //da hinh
    s2->speak(); //da hinh
}