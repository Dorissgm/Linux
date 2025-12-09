#include <iostream>
using namespace std;

class Person {
public: 
    string name;
    int age;

    void introduce() {
        cout << "Xin chao, toi ten la " << name << ", nam nay toi " << age << " tuoi." << endl;
    }
};

class Student : public Person{
public:
    string school;

    void study() {
        cout << "Toi dang hoc tai truong " << school << endl;
    }
};

class Teacher : public Person {
public:
    string subject;

    void teach() {
        cout << "Toi day mon " << subject << endl;
    }
};

int main() {
    Student a;
    a.name = "Quang";
    a.age = 21;
    a.school = "VKU";
    
    a.introduce();
    a.study();

    cout << endl;

    Teacher b;
    b.name = "Peter";
    b.age = 36;
    b.subject = "C++";
    
    b.introduce();
    b.teach();
}