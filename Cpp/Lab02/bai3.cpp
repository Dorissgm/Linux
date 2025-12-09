#include <iostream>
using namespace std;

struct MyStruct {
    int x;      // 4 byte
    char y;     // 1 byte
    double z;   // 8 byte
};

union MyUnion {
    int x;      // 4 byte
    char y;     // 1 byte
    double z;   // 8 byte
};

int main() {
    cout << "===== Struct =====" << endl;
    MyStruct s;
    s.x = 10;
    s.y = 'A';
    s.z = 3.14;

    cout << "Struct size: " << sizeof(MyStruct) << " bytes" << endl;
    cout << "s.x = " << s.x << endl;
    cout << "s.y = " << s.y << endl;
    cout << "s.z = " << s.z << endl;

    cout << "\n===== Union =====" << endl;
    MyUnion u;
    u.x = 10;
    cout << "After u.x=10 -> u.x=" << u.x << endl;

    u.y = 'A';
    cout << "After u.y='A' -> u.y=" << u.y << ", u.x=" << u.x << endl;

    u.z = 3.14;
    cout << "After u.z=3.14 -> u.z=" << u.z 
         << ", u.x=" << u.x 
         << ", u.y=" << u.y << endl;

    cout << "Union size: " << sizeof(MyUnion) << " bytes" << endl;

    return 0;
}
