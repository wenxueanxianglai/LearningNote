#include<iostream>
#include <string>

using namespace std;
class b
{
    static int a;
    public:
    void func()
    {

    }
};

int b::a = 0;

enum color;
enum color : unsigned char;
class test;
class test : public b
{
    using b::func;

};

int main()
{
    using std::string;

    string   dddd;
    ;

    unsigned int d= 12;
    float a = -111;

    cout << a + d << endl;

    enum color;

    return 0;
}