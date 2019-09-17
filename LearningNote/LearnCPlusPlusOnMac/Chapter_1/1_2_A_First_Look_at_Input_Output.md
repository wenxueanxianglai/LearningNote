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
For output, we use an the standard output.  
对于输出， 我们使用 标准输出。  




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
