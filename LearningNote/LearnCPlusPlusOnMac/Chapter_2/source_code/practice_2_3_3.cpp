#include <iostream>

int main()
{
    int* ip, i, &r = i;
    // ip : pointer
    // i : var
    // r : ref of i

    {
        int i, *p = 0;
        // i : var
        // p : pointer to null
    }   

    {
        int* ip, ip2;
        // ip : pointer
        // ip2 : var
    }

 
    return 0;
}