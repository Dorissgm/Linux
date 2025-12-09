#include <iostream>
using namespace std;

// Hàm truyền tham trị (copy giá trị sang tham số)
void increaseByValue(int x) {
    x = x + 10; // chỉ thay đổi bản sao, không ảnh hưởng biến gốc
    cout << "Trong increaseByValue, x = " << x << endl;
}

// Hàm truyền tham chiếu (tham số là bí danh của biến gốc)
void increaseByReference(int &x) {
    x = x + 10; // thay đổi trực tiếp biến gốc
    cout << "Trong increaseByReference, x = " << x << endl;
}

int main() {
    int a = 5, b = 5;

    cout << "Ban dau: a = " << a << ", b = " << b << endl;

    increaseByValue(a);    // truyền tham trị
    cout << "Sau khi goi increaseByValue(a), a = " << a << endl;

    increaseByReference(b); // truyền tham chiếu
    cout << "Sau khi goi increaseByReference(b), b = " << b << endl;

    return 0;
}
