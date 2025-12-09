//Viết chương trình C++ đơn giản để có thể phân biết được thế nào là Class, thế nào là Object.

#include <iostream>
using namespace std;

//class
class student {
public:
    string name;
    int age;

    void introduce() {
        cout << "xin chao, toi ten la " << name << ", nam nay toi " << age << " tuoi" << endl;
    }
};

int main() {
    student s1; //object 1
    s1.name = "Quang";
    s1.age = 20;

    student s2; //object 2
    s2.name = "Minh";
    s2.age = 20;

    s1.introduce();
    s2.introduce();
}