# 1.1 Writing a Simple C++ Program
---
Every C++ program contains one or more functions, one of which must be named main.  
每个C++程序有一个或多个函数， 其中有一个 函数 必须叫 main.  
The operating system runs a C++ program by calling main.  
操作系统运行 通过 调用 main 函数 调用 C++ 程序.  
Here is simple version of main that does nothing but return  a value to the operating system:  
这里有一个main函数的简单版本， 它除了 返回一个值给 操作系统 其他的什么都没有。  
```C++
int main()
{
  return 0;
}
```
A function definition has four elements: a return type, a function name, a(possibly empty)parameter list enclosed in parentheses, and a function body.  
一个函数定义 有 4 个元素： 返回值， 函数名， 带着括号的参数列表， 和 函数体。  
Although main is special in some ways, we define main the same way we define any other function.  
尽管在某些方面 main函数是 特别的， 但是，我们定义main 和我们定义任何其他函数 是一样的。  

In this example, main has an empty list of parameters(shown by the () with nothing inside).  
在这个例子中，main 有一个空的 参数列表(()里没有任何显示).  
$6.2.5(p.218) will discuss the other parameter types that we can define for main.  
$6.2.5(p.218)节 将会讨论  我们能为main函数定义 其他的参数。  

The main function is required to have a return type of int, which is a type that represents integers.  
main 函数 被要求 有一个 int 类型的 返回值，  int 是一个 表示整数的类型。  
The int type is a built-in type, which means that it is one of the types the language defines.  
int leixing 是一个 内置类型， 内置类型 是 编程语言定义的一种类型。  

The final part of a function definition, the function body, is a block of statements starting with an open curly brace and ending with a close curly:  
函数定义的最后一部分, 函数体, 是一个语句块 有左花括号开始 结束于右花括号。  
```C++
{
  return 0;
}

```
The only statement in this block is a return, which is a statement that terminates a function.  
在这个语句块中唯一的语句 是一个 return， return是 结束一个函数 的语句。  
As is the case here, a return can also send a value back to the function's caller.  
在这里发生的情况(在这个example 这样翻译？)， return 还能 返回一个值 给 函数的调用者。  
When a return statement includes a value, the value returned must have a type that is compatible with the return type of the function.  
当 return 语句 包含一个值的时候， 这个值的类型  必须 和 函数返回值类型  兼容（匹配）。  
In this case, the return type of main is int and the return value is 0, which is an int.  
在本例中， main的返回值 是 int， return 的值为 0， 0 是 int 类型。  





---
## Words
### one or more
### one of which
### definition
### parameter
### enclosed
### parentheses
### in some ways
### the same way
### shown by
### discuss
### the other
### required
### represents
### curly brace
### terminates
### compatible
