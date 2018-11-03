# Chapter 5 Utilities
---
---
This chapter describes the general utilities of C++ Standard library. These utilities are small and  
simple classes, types, or functions that perform frequently needed tasks:
* Class pair<> and class tuple<>
* Smart pointer classes (class shared_ptr<> and class unique_ptr)
* Numeric limits
* Type traits and type utilities
* Auxiliary functions(for example, min(), max(), and swap())
* Class ratio<>
* Clocks and timers
* Some important C functions

译：  
本章讲解C++标准库中的通用工具。这些通用工具是小型的简单的类，类型，或者是在任务中经常需要的函数
* Class pair<> and class tuple<>
* 智能指针类 (class shared_ptr<> and class unique_ptr)
* 数值极值
* Type traits 和 type utilities
* 辅助函数(如：min(), max(), 和 swap())
* Class ratio<>
* Clocks 和 timers
* 一些重要的C函数


Most, but not all, of these utilities are described in clause 20, "General Utilities," of the C++ standard.  
The rest are described along with more major components of the library either because they are used  
primarily with that particular component or due to historical reasons, For example, some general  
auxiliary functions are defined as part of the <algorithm\> header, although they are not algorithms  
in the sense of the STL(which is described in Chapter6).

译：  
大部分的通用工具被描述在C++标准的第20项“General Utilities”。其余的和库里的比较重要  
的组件一起描述，原因是他们经常和这些组件一起共同使用，或是由于历史原因。例如：一些  
通用辅助函数被定义在<algorithm\>头文件中，尽管不是STL意义上的算法(见第6章)
