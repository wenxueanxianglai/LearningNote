#include <iostream>
#include "Sales_item.h"

int main()
{
  Sales_item item1, item2;

  std::cin >> item1 >> item2;                     // read a pair of transactions
  std::cout << item1 + item2 << std::endl;        // print their sum

  return 0;
}
/*
D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>cl /Ehsc 1_5_Sales_item_add.cpp
用于 x64 的 Microsoft (R) C/C++ 优化编译器 16.00.40219.01 版
版权所有(C) Microsoft Corporation。保留所有权利。

cl: 命令行 warning D9002 :忽略未知选项“/Ehsc”
1_5_Sales_item_add.cpp
C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\INCLUDE\xlocale(323) : warning C4530: 使用了 C++ 异常处理程序，但未启用展开语义。请指定 /EHsc
Microsoft (R) Incremental Linker Version 10.00.40219.01
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:1_5_Sales_item_add.exe
1_5_Sales_item_add.obj

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>1_5_Sales_item_add.exe
0-123-xxxx-44 2 10.00
0-123-xxxx-44 5 20.00
0-123-xxxx-44 7 120 17.1429

*/
