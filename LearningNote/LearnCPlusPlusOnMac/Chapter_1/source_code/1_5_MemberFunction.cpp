#include <iostream>
#include "Sales_item.h"

int main()
{
  Sales_item item1, item2;
  std::cin >> item1 >> item2;

  // first check that item1 and item2 represent the same book
  if (item1.isbn() == item2.isbn()) {
    std::cout << item1 + item2 << std::endl;
    return 0;
  } else {
    std::cerr << "Data must refer to same ISBN" << '\n';
    return -1;
  }

  return 0;
}

/*

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>cl /Ehsc 1_5_MemberFunction.cpp
用于 x64 的 Microsoft (R) C/C++ 优化编译器 16.00.40219.01 版
版权所有(C) Microsoft Corporation。保留所有权利。

cl: 命令行 warning D9002 :忽略未知选项“/Ehsc”
1_5_MemberFunction.cpp
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\xlocale(323) : warning C4530: 使用了 C++ 异常处理程序，但未启用展开语义。请指定 /EHsc
Microsoft (R) Incremental Linker Version 10.00.40219.01
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:1_5_MemberFunction.exe
1_5_MemberFunction.obj

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>1_5_MemberFunction.exe
eee-222-sasas 32 32.22
sxx-aaa-22222 32 32.22
Data must refer to same ISBN

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>1_5_MemberFunction.exe
eee-222-sasas 2 32.22
eee-222-sasas 4 4.2
eee-222-sasas 6 81.24 13.54


*/
