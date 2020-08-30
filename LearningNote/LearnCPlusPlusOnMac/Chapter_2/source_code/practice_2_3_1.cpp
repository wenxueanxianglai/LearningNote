/*
Exercise 2.15: Which of the following definitions, if any, are invalid?Why?
*/
void test_func_1()
{
    int ival= 1.01;
    //int &rval1 = 1.01;  // invalid,  reference must be a lvalue   
    int & rval2 = ival;
  //  int &rval3;         // reference need initialize;
}

/*
Exercise 2.16: Which, if any, of the following assignments are invalid? If they are
                valid, explain what they do.
*/

void test_func_2()
{
    int i = 0, &r1 = i;
    double d = 0, &r2 = d;

    {
        r2 = 3.1415926; // d is 3.1415926
    }

    {
        r2 = r1;    // assign value of i to d
    }

    {
        i = r2;     // assign  value of d to i
    }

    {
        r1 = d;     // // assign  value of d to i
    }

}

/*
Exercise 2.17: What does the following code print?
*/
#include <iostream>

void test_func_3()
{
    int i, &ri = i;
    i = 5;
    ri = 10;
    
    std::cout << i << " " << ri << std::endl;       // print : 10 10
}

int main()
{
test_func_3();
}