# A First Look at Input/Output
---
The C++ language does not define any statements to do input or output(IO).  
C++语言没有定义任何 用作输入输出的 语句。  
Instead, C++ includes an extensive standard library that provides IO (and many other facilities).  
取而代之， C++ 包含的 标准库 提供了IO(还有其他工具)  
For many purposes, including the examples in this book, one needs to know only a few basic concepts and operations from the IO library.  
出于许多目的，包括书里的例子， 我们只需要知道基础的IO概念和操作  

Most of the examples in this book use the iostream library.  
这本书的大多数例子 使用 iostream 库  
Fundamental to the iostream library are two types named istream and ostream, which represent input and output streams, respectively.  
基本的iostream库是由 istream 和 ostream 这两种类型组成， 分别代表了输入和输出流.  
A stream is a squence of characters read from or written to an IO device.  
流是 从 IO设备 读取或者写入 有顺序的 字符串。  
The term stream is intended to suggest that the characters are generated, or consumed, sequentially over time.  
流 这个术语 指的是 随着时间推移 顺序生成 或消耗字符。  

**Standard Input and Output Objects**  
The library defines four IO objects.  
标准库定义了四种IO对象。  
To handle input, we use an object of type istream named cin(pronounced see-in).  
为了处理输入， 我们使用一个 输入流 cin 对象  
This object is also referred to as the standard input.  
这个对象也提供一个标准输入。  
For output, we use an ostream object named cout(pronounced see-out).  
对于输出， 我们使用 名字叫 cout 的 ostream 对象  
This object is also known as the standard output.
这个对象我们也叫 标准输出。  
The library also defines two other ostream objects, named cerr and clog(pronounced see-err and see-log, respectively).  
这个库还定义了两个其他的标准输出对象， cerr 和 clog。  
We typically use cerr, referred to as the standard error, for warning and error messages and clog for general information about the executiong of the program.  
我们通常使用cerr 作为一个标准输出错误， 为了 警示 和错误信息， clog 作为运行这个程序时 普通信息  

Ordinarily, the system associates each of these objects with the window in which the program is executed.
通常， 系统将 这些对象 的 每一个 与 执行程序的窗口相关联。  
So, when we read from cin, data are read from the window in which the program is executing and when we write to cout , cerr, or clog, the output is written to the same window.    
所以，当我们从cin 读取时， 数据从正在运行程序的窗口 读取。 当我们写入到cout,cerr 或者clog，输出被写入这些窗口中  

**A Program That Uses the IO Library**  
In our bookstore problem, we'll have several records that we'll want to combine into a single total.  
在我们的书店程序中，我们将有几条 可以合并成一条总计的 记录  
As a simpler, related problem, let's  look first at how we might add two numbers.  
座位了更简单的相关问题，让我们首先看一下如何将两个数字相加。  
Using the IO library, we can extend our main program to prompt the user to give us two numbers and then print their sum:  
使用IO库，我们扩展我们的main程序 使得使用者 给我们两个数 然后打印他们的和  
```C++
#include <iostream>
int main()
{
  std::cout << "Enter two numbers:" << std::endl;
  int v1 = 0, v2 = 0;
  std::cin >> v1 >> v2;
  std::cout << "The sum of " << v1 << " and " << v2
            << " is " << v1 + v2 << std:: endl;

  return 0;
}
```
This program starts by printing  
程序开始于打印：  
**Enter two numbers:**  
on the user's screen and then waits for input from the user.  
在用户屏幕上“Enter two numbers:”然后等待用户输入  
If the user enters  
如果用户输入：  
**3 7**  
followed by newline, then the program produces the following output:



---
## Words
### extensive
### facilities
### purposes
### concepts
### Fundamental
### respectively
### term
### generated
### consumed
### sequentially
### referred
### typically
### Ordinarily
### associates
### in which
