#include <iostream>

using namespace std;

int main()
{
  int sum = 0;

  //sum values from 1 through 10 inclusive
  for (int val = 1; val < 10; val++) {
    sum += val;       //equivalent to sum = sum + val
  }

  cout << "Sum of 1 to 10 inclusive is "
       << sum << endl;

  return 0;
}
/* code result
D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>cl /Ehsc 1_4_For.cpp
用于 x64 的 Microsoft (R) C/C++ 优化编译器 16.00.40219.01 版
版权所有(C) Microsoft Corporation。保留所有权利。

cl: 命令行 warning D9002 :忽略未知选项“/Ehsc”
1_4_For.cpp
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\xlocale(323) : warning C4530: 使用了 C++ 异常处理程序，但未启用展开语义。请指定 /EHsc
Microsoft (R) Incremental Linker Version 10.00.40219.01
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:1_4_For.exe
1_4_For.obj

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>1_4_For.exe
Sum of 1 to 10 inclusive is 45

*/
