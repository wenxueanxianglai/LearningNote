/*
*  Compile a program that has incorrectly nested comments.
*/

/*
 * comment pairs /* */ connot nest
 *
 */

int main()
{
  return 0;
}


/*
D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>cl /Ehsc practice_1_7.cpp
用于 x64 的 Microsoft (R) C/C++ 优化编译器 16.00.40219.01 版
版权所有(C) Microsoft Corporation。保留所有权利。

cl: 命令行 warning D9002 :忽略未知选项“/Ehsc”
practice_1_7.cpp
practice_1_7.cpp(3) : error C2146: 语法错误: 缺少“;”(在标识符“nest”的前面)
practice_1_7.cpp(3) : error C4430: 缺少类型说明符 - 假定为 int。注意: C++ 不支持默认 int
practice_1_7.cpp(3) : error C2143: 语法错误 : 缺少“;”(在“*”的前面)
practice_1_7.cpp(3) : error C4430: 缺少类型说明符 - 假定为 int。注意: C++ 不支持默认 int
practice_1_7.cpp(4) : warning C4138: 在注释外找到“*/”
practice_1_7.cpp(4) : error C2059: 语法错误:“/”
practice_1_7.cpp(7) : error C2143: 语法错误 : 缺少“;”(在“{”的前面)
practice_1_7.cpp(7) : error C2447: “{”: 缺少函数标题(是否是老式的形式表?)

D:\ZxpFiles\learngit\LearningNote\LearnCPlusPlusOnMac\Chapter_1\source_code>
*/
