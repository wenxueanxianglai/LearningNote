/*
*  Write a program to print  Hello, World on the standard output.
*
*/

#include <iostream>

int main()
{

  std::cout << "Hello, World" << std::endl;

  return 0;
}

/*
D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>cl /Ehsc practice_1_3.cpp
用于 x64 的 Microsoft (R) C/C++ 优化编译器 16.00.40219.01 版
版权所有(C) Microsoft Corporation。保留所有权利。

cl: 命令行 warning D9002 :忽略未知选项“/Ehsc”
practice_1_3.cpp
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\xlocale(323) : warning C4530: 使用了 C++ 异常处理程序，但未启用展开语义。请指定 /EHsc
Microsoft (R) Incremental Linker Version 10.00.40219.01
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:practice_1_3.exe
practice_1_3.obj

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>practice_1_3.exe
Hello, World


*/
