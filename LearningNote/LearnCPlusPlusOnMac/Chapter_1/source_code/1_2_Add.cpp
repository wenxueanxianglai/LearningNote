#include <iostream>     

int main()
{
  std::cout << "Enter two numbers:" << std::endl;

  int v1 = 0;
  int v2 = 0;

  std::cin >> v1 >> v2;

  std::cout << "The sum of " << v1 << " and " << v2
            << " is " << v1 + v2 << std::endl;

  return 0;
}

/* run result
D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>cl /Ehsc 1_2_Add.cpp
用于 x64 的 Microsoft (R) C/C++ 优化编译器 16.00.40219.01 版
版权所有(C) Microsoft Corporation。保留所有权利。

cl: 命令行 warning D9002 :忽略未知选项“/Ehsc”
1_2_Add.cpp
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\xlocale(323) : warning C4530: 使用了 C++ 异常处理程序，但未启用展开语义。请指定 /EHsc
Microsoft (R) Incremental Linker Version 10.00.40219.01
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:1_2_Add.exe
1_2_Add.obj

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>1_2_Add.exe
Enter two numbers:
3 2
The sum of 3 and 2 is 5

*/
