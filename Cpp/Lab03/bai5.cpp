#include <iostream>
using namespace std;

class Student {
private:
    int age;

public:
    void setAge(int a) {
        if (a > 0)
        {
            age = a;
        } else {
            cout << "tuoi khong hop le!" << endl;
        }
    }

    int getAge() {
        return age;
    }
};

int main() {
    Student s;

    //s.age->loi (age: private)
    s.setAge(20);
    cout << "tuoi cua sinh vien: " << s.getAge() << endl;

    s.setAge(-10); //loi vi khong hop le
}