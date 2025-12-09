//Viết chương trình C++, tạo ra các Class tùy ý, thể hiện được đặc  trưng mang tính trừu tượng. 

#include <iostream>
using namespace std;

//lop truu tuong
class Animal {
public: 
    virtual void sound() = 0; // ham ao thuan tuy
};

//lop ke thua
class Dog : public Animal {
public:
    void sound() override {
        cout << "cho sua: gau gau" << endl;
    }
};

//lop ke thua
class Cat : public Animal {
public: 
    void sound() override {
        cout << "Meo keu: meow meow" << endl;
    }
};

int main() {
    Dog A;
    Cat B;

    A.sound();
    B.sound();
}