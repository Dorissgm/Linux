#include <iostream>
using namespace std;

// Biến toàn cục (global) -> tồn tại suốt chương trình
int globalVar = 100;

void demoStatic() {
    static int staticVar = 0; // chỉ khởi tạo 1 lần, giữ giá trị qua các lần gọi
    staticVar++;
    cout << "staticVar trong ham demoStatic: " << staticVar << endl;
}

int main() {
    cout << "=== Bien toan cuc (global) ===" << endl;
    cout << "globalVar = " << globalVar << endl;

    cout << "\n=== Bien cuc bo (local) ===" << endl;
    int localVar = 10;  // chỉ sống trong hàm main
    cout << "localVar = " << localVar << endl;

    cout << "\n=== Bien tinh (static) ===" << endl;
    demoStatic();
    demoStatic();
    demoStatic();  // gọi nhiều lần -> giá trị staticVar được nhớ

    cout << "\n=== Bien hang (const) ===" << endl;
    const double PI = 3.14159; // không thay đổi được
    cout << "PI = " << PI << endl;
    // PI = 3.2;  // ❌ lỗi nếu bỏ comment

    cout << "\n=== Bien cap phat dong (dynamic) ===" << endl;
    int* dynamicVar = new int(50); // cấp phát trên heap
    cout << "Gia tri dynamicVar = " << *dynamicVar << endl;
    delete dynamicVar; // giải phóng bộ nhớ

    return 0;
}
