#include <iostream>
using namespace std;

class Animal {
protected: //dong goi
    string name;
    int age;

public:
    Animal(string n, int a) : name(n), age(a) { }
    
    //ham ao
    virtual void sound() = 0;

    //getter (dong goi du lieu)
    string getName() {
        return name;
    }

    int getAge() {
        return age;
    }
};

//ke thua
class Dog : public Animal {
public:
    Dog(string n, int a) : Animal(n ,a) {}
    
    void sound() override { //ghi de ham ao -> da hinh
        cout << "CHO - sua gau gau." << endl;
    }
};

//ke thua
class Cat : public Animal {
public:
    Cat(string n , int a) : Animal(n , a) {}

    void sound() override {
        cout << "MEO - keu meo meo." << endl;
    }
};

int main() {
    //tao cac doi tuong tu lop con 
    Dog d("Milu", 3);
    Cat c("MiuMiu" , 2);

    //the hien dong goi 
    cout << d.getName() << " nam nay " << d.getAge() << " tuoi." << endl;
    cout << c.getName() << " nam nay " << c.getAge() << " tuoi." << endl;

    //the hien da hinh
    Animal* d1 = &d;
    Animal* c1 = &c;
    cout << "Tieng ke cua cac dong vat:" << endl;
    d1->sound();
    c1->sound();

    return 0;
}