/*
Exercises Section 2.2.1

Exercises 2.9:
    Explain the following definitions. For those that are illegal,
    explian what's wrong and how to correct it.

    (a) std::cin >> int input_value;
    // X
    (b) int i = {3.14};
    // X    list initialization has one important property:
    //The Compiler will not let us list initialize variables of built-in type
    // if the initializer might lead to loss of information

    (c) double salary = wage = 9999.99;     // X   wage undefined
    (d) int i = 3.14;           // OK


Exercise 2.10: What are the initial values, if any, of each of the following variables?


*/

#include<iostream>
#include<string>

std::string global_str;     //  ""
int global_int;             // 0

int main()
{
    int local_int;          // uninitialized
    std::string local_str;  // ""


    return 0;
}
