# Debug 的一些概念， 名词

## 符号文件(symbol files)
* 调试信息的 database
* 程序调试的重要辅助信息
* 程序中所有的 运行信息 都记录在这个文件中
* 实体：PDB文件

### 信息
* 全局变量
* 局部变量
* 函数名及函数的入口地址
* FPO数据

## 静态链接库(static library)
* 本质上是一个代码集
* 通常以 lib 形式提供
* 把一些函数做成函数集合放在一起，这些函数没有经过编译器链接

## 动态链接库(dynamic link library)
* 共享函数库的可执行文件
* 进程可以调用不属于其可执行代码的函数
* 使用动态链接库有助于共享数据 和 资源
* 多个应用程序可同时访问内存中单个dll副本的内容

### 和静态链接库的区别
* 静态链接库：
  * 将需要的代码直接链接进可执行程序

* 动态链接库
  * 在需要调用其中的函数时，根据函数映射表找到该函数，然后调入堆栈执行


http://www.360doc.com/content/19/0709/20/49851048_847709368.shtml

http://www.xszydq.com/17705.html

http://itbook.top/tag/18


2.查找僵尸进程



ps -A -o stat,ppid,pid,cmd | grep -e '^[Zz]'





3.批量清理僵尸进程



ps -A -o stat,ppid,pid,cmd | grep -e '^[Zz]' | awk '{print $2}' | xargs kill -9
