#include <iostream>

using namespace std;

int main()
{
  int sum = 0;
  int value = 0;

  //read until end-of-file, calculating a running total of all values read
  while (cin >> value) {
    sum += value;         // equivalent to sum = sum + value
  }

  cout << "Sum is: " << sum << endl;

  return 0;
}

/*
D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>cl /Ehsc 1_4_UnknowNumber.cpp
用于 x64 的 Microsoft (R) C/C++ 优化编译器 16.00.40219.01 版
版权所有(C) Microsoft Corporation。保留所有权利。

cl: 命令行 warning D9002 :忽略未知选项“/Ehsc”
1_4_UnknowNumber.cpp
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\xlocale(323) : warning C4530: 使用了 C++ 异常处理程序，但未启用展开语义。请指定 /EHsc
Microsoft (R) Incremental Linker Version 10.00.40219.01
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:1_4_UnknowNumber.exe
1_4_UnknowNumber.obj

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>1_4_UnknowNumber.exe
3 2 4 2


Sum is: 11
*/
