/*
Exercise 2.13: What is the value of j in the following program?
*/
// int i = 42;
// int main()
// {
//     int i = 100;
//     int j = i;          // 100;

// }

/*
Exercise 2.14: Is the following program legal? If so, what values are printed?
*/

#include <iostream>

int main()
{
    int i = 100, sum = 0;
    for (int i = 0; i != 10; ++i)
    {
        sum += i;
    }

    std::cout << i << " " << sum << std::endl;      // i = 100, 1+2+.. 9 = sum = 45
    
}


