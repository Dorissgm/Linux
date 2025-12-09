#include <iostream>
using namespace std;

class Base {
private:
    int privateVar;

protected:
    int protectedVar;

public:
    int publicVar;

    Base() {
        privateVar = 1;
        protectedVar = 2;
        publicVar = 3;
    }

    void showPrivate() {
        cout << "privateVar = " << privateVar << endl;
    }
};

class Derived : public Base {
public: 
    void accessMembers() {
        //cout << privateVar; -> loi vi private khong the goi ngoai class.
        cout << "protectedVar (ngoai class co the ke thua) = " << protectedVar << endl;
        cout << "publicVar (ngoai class co the goi duoc) = " << publicVar << endl;
    }
};

int main() {
    Base b;
    Derived d;

    //----truy cap tu ben ngoai:
    //b.pivateVar = 10; -> loi vi khong the truy cap ngoai class
    //b.protectedVar = 20; -> loi vi khong the truy cap ngoai class
    b.publicVar = 30;

    cout << "publicVar (truy cap ben ngoai class) = " << b.publicVar << endl;

    //goi methob public de xem private
    b.showPrivate();

    //truy cap tu lop ke thua
    d.accessMembers();
}