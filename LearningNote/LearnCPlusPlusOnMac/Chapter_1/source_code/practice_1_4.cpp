/*
*   Our program used the addition operator, + , to add two numbers.
*   Write a program that uses the multiplication operator, * , to print the product instead.
*/

#include <iostream>

using namespace std;

int main()
{
  cout << "Enter two numbers:" << endl;

  int v1 = 0;
  int v2 = 0;

  cin >> v1 >> v2;

  cout << "The product of " << v1 << " and " << v2
       << " is " << v1 * v2 << endl;

  return 0;
}


/*
D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>cl /Ehsc practice_1_4.cpp
用于 x64 的 Microsoft (R) C/C++ 优化编译器 16.00.40219.01 版
版权所有(C) Microsoft Corporation。保留所有权利。

cl: 命令行 warning D9002 :忽略未知选项“/Ehsc”
practice_1_4.cpp
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\xlocale(323) : warning C4530: 使用了 C++ 异常处理程序，但未启用展开语义。请指定 /EHsc
Microsoft (R) Incremental Linker Version 10.00.40219.01
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:practice_1_4.exe
practice_1_4.obj

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>practice_1_4.exe
Enter two numbers:
3 4
The product of 3 and 4 is 12

*/
