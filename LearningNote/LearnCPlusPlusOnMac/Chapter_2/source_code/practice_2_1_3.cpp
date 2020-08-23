#include <iostream>

using namespace std;

int main()
{
    auto cha = 'a';     // 字符
    auto cha1 = L'a';    // 宽字符 
    auto cha2 = "a";       //字符串
    auto cha3 = L"a";       //宽字符串

    auto na = 10;           //int
    auto na1 = 10u;            // unsigned int
    auto na2 = 10L;             // long
    auto na3 = 10uL;            // unsigned long
    auto na4 = 012;             // int      
    auto na5 = 0xC;             // int

    auto fa = 3.14;         // double
    auto fa1 = 3.14f;       // float
    auto fa2 = 3.14L;       // long double

    auto x = 10;            // int
    auto x1 = 10u;          // unsigned
    auto x2 = 10.;          // double
    auto x3 = 10e-2;        // double


    cout << "2M\n";
    cout << 2 << '\t' << "M\n";

    return 0;
}