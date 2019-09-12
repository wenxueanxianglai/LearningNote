# 1.1.1 Compiling and Executing Our Program
---
Having written the program, we need to compile it.  
已经写好程序后，我们需要去编译它。  
How you compile a program depends on your operating system and compiler.  
你如何编译一个程序 取决于 你的 操作系统 和 编译器。  
For details on how your particular compiler works, check the reference manual or ask a knowledgeable colleague.  
有关特定的编译期如何工作的 详细信息，查参考手册 或者 询问 一个 很有知识的 同事。  

Many PC-based compilers are run from an integrated development environment(IDE) that bundles the compiler with build and analysis tools.  
很多基于PC的编译器都是从集成开发环境(简称IDE), 它 将 编译器 与  构建和分析工具 捆绑在一起。  
These environments can be a great asset in developing large programs but require a fair bit of time to learn how to use effectively.  
这些环境在开发大型程序方面是优秀的资产， 但 需要 花费大量的时间 去学习如何有效地使用  
Learning how to use such environments is well beyond the scope of this book.  
学习如何使用这些环境 大大超过了 我们这本书的范围。  

Most compilers, including those that come with an IDE, provide a command-line interface.  
大部分编译器(包括IDE附带的编译器) 都提供了 命令行界面。  
Unless you already know the IDE, you may find it easier to start with the command-line interface.  
除非你已经学会并知道了IDE， 否则你可能会发现，从命令行启动会更容易。  
Doing so will let you concentrate on learning C++ first.  
这样做可以让你首先专注于 学习C++  
Moreover, once you understand the language, the IDE is likely to be easier to learn.  
此外，一旦你学会了C++语言，IDE会很容易学习  

**Program Source File Naming Convention**  
Whether you use a command-line interface or an IDE, most compilers expect program source code to be stored in one or more files.  
不管你是用 命令行还是 IDE， 大多数编译器都希望 程序的源代码 存储在 一个或多个文件中。  
Program files are normally referred to as a source files.  
程序文件通常指的是 源文件。  
On most systems, the name of a source file end with a suffix, which is a period followed by one or more characters.  
在大部分系统中，一个源文件名的最后带有一个后缀， 后缀为在点之后的一个或者多个字符  
The suffix tells the system that the file is a C++ program.  
这个后缀告诉 系统， 这个文件是个C++程序  
Different compilers use different suffix conventions;  
不同的编译器 使用不同的 后缀约定  
the most common include .cc, .cxx, .cpp, .cp, and .C.
通常大部分包括： .cc, .cxx, .cpp, .cp, 和.C  

**Running the Compiler from the Command Line**  
If we are using a Command-line interface, we will typically compile a program in a console window(such as a shell window on a UNIX system or a Command Prompt window on Windows).  
如果我们正在使用 命令行界面， 我们通常会在 控制台窗口 编译一个程序(例如UNIX系统的shell窗口 或者 windows的命令提示符界面)  
Assuming that our main program is in a file named prog1.cc, we might compile it by using a command such as  
假设 我们的main程序 在 prog1.cc 文件里， 我们 通过使用命令 请求编译 如：  
```
$CC prog1.cc
```
where CC names the compiler and $ is the system prompt.  
其中 CC 为 编译器， $ 是系统提示符。  
The compiler generates an executable file.
编译器生成可执行文件  
On a Windows system, that executable file is named prog1.exe.  
在windows 操作系统里， 这个可执行文件名叫 prog1.exe.  
UNIX compilers tend to put their executables in files named a.out.  
UNIX 编译器 倾向于 让他们的可执行文件名叫 a.out.  

To run an executable on Windows, we supply the executable file name and can omit the .exe file extension:  
为了在Windows上运行一个可执行的文件， 我们提供 可执行文件名，我们也可以省略.exe文件扩展(就是后缀)  
```
$prog1
```
On some systems you must specify the file's location explicitly, even if the file is in the current directory or folder.  
在某些系统中，你必须明确地指定文件文件的位置，即使这个文件 在当前目录或文件夹里  
```
$.\prog1
```
The "." followed by a backslash indicates that file is in the current directory.  
.后面跟着的反斜杠 表示 这个文件在当前目录下。  

To run an executable on UNIX, we use the full file name, including the file extension.  
为了在UNIX上运行，我们使用文件名全名，包含文件名扩展部分。  
```
$a.out
```
If we need to specify the file's location, we'd use a "." followed by a forward slash to indicate that our executable is in the current directory:  
如果我们需要去指定 文件的位置， 我们可以使用 ./ (翻译是 点后面跟着正斜杠) 表示 我们的可执行文件在 当前目录。  
```
$./a.out
```
The value returned from main is accessed in a system-dependent manner.  
从 main 返回的值 是以系统相关的方式 访问  
On both UNIX and Windows systems, after executing the program, you must issue an appropriate echo command.  
在UNIX和Windows操作系统中， 在执行完程序之后， 你必须发出相应的 echo 命令  

On UNIX systems, we obtain the status by writing  
在UNIX操作系统中，我们 获取这个状态量 通过输入：
```
$echo $?
```

To see the status on a Windows system, we write  
为了在windows操作系统看到这个状态量，我们输入:  
```
$echo %ERRORLEVEL%
```


---
## Words
### particular
### reference
### manual
### integrated
### bundles
### require
### fair
### beyond
### concentrate
### Moreover
### whether
### expect
### referred
### referred to
### suffix
### period
### typically
### Prompt
### generates
### executable
### tend
### supply
### omit
### specify
### backslash
### forward
### slash
### issue
### appropriate
### obtain
