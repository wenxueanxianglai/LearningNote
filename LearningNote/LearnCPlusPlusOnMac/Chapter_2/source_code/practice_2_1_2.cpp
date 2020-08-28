#include <iostream>

using namespace std;

int main()
{
    //练习2.3
    unsigned u = 10, u2 = 42;
    cout << u2 - u << endl;     //32
    cout << u - u2 << endl;     // 0x ff ff ff e0   (unsigned)

    int i = 10, i2 = 42;
    cout << i2 - i << endl;        // 32
    cout << i - i2 << endl;         // -32  0x ff ff ff e0
    cout << i - u << endl;          // 0
    cout << u - i << endl;          // 0

    return 0;
}