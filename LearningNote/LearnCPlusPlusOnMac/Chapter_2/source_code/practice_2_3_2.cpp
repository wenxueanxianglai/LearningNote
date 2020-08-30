 /*
 Exercise 2.18: Write code to change the value of a pointer. Write code to change the
                value to which the pointer points.
 */
#include<iostream>

void test_func_1()
{
    int i = 10;
    int j = 20;
    int* pi = &i;

    std::cout << *pi << " " << pi << std::endl;

    i = 222;
    std::cout << *pi << " " << pi << std::endl;

    pi = &j;
    std::cout << *pi << " " << pi << std::endl;
}


/*
Exercise 2.19: Explain the key differences between pointers and references.
pointer is object. 
reference is not object.
*/


/*
Exercise 2.20: What does the following program do?
*/
void test_func_2()
{
    int i = 42;
    int *pi = &i;       // a pointer named pi point i
    *pi = *pi * *pi;    // 42 * 42
}

/*
Exercise 2.21: Explain each of the following definitions. Indicate whether any
                are illegal, if so, why.
*/
void test_func_3()
{
    int i = 0;
    double* dp = &i;        // illegal.    in initialization can not convert int* to double*    
    int * ip = i;           // illegal      invalid conversion from int to int*;
    int *p = &i;
}


/*
Exercise 2.22: Assuming p is a pointer to int, explain the following code:
*/

void test_func_4()
{
    int i = 10;
    int*p = &i;
    if (p)      // a value of p
    {
        /* code */
    }
    
    if (*p)     // avalue of i
    {
        /* code */
    }
    

}

/*
Exercise 2.23: Given a pointer p, can determine whether p points to a valid object?
                If so, how? If not, why not?

        Yes.   Using p to access an object.
*/


/*
Exercise 2.24: Why is the initialization of p legal but that of lp illegal?
*/

void test_func_5()
{
    int i = 42;
    void* p = &i;
    long * lp = &i;  //invalid conversion from int* to  long int*;
}


int main()
{
    test_func_1();

    return 0;
}