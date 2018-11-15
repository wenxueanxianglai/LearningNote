# Chapter 5
---
## 5.1 Pair 和 Tuple
* 标准库实现保证可一直的范围是：允许tuple带有最多10个类型不同的元素

### 5.1.1 Pair
#### 概念
*  Class Pair 可将两个value视为一个单元
* 本质是一个struct，所以所有成员都是public

#### 操作
* 构造
* 赋值
* 比较
* 取值
* 交换

#### 构造函数和赋值
* 逐块式构造 (目前不太懂，需要回家编码测试)

#### 便捷函数make_pair
* C++11之后，如果可能的话，使用move语义，否则使用copy语义
* 此外它会蛀蚀(decay)实参(目前不懂)
* 使用make_pair产生出来的pair有绝对明确的类型

### 5.1.2 Tuple(不定数的值组)
Tuple扩展了pair的概念，拥有任意数量的元素

#### 操作
* 构造
* 比较
* 赋值
* 交换
* 引用

#### 注意
* Tuple不允许迭代元素
* 必须在编译期知道你打算处理的索引值

#### 便捷函数make_tuple()和tie()
* 使用tie时可以忽略tuple的某些元素

#### Tuple和初值列
* tuple接受不定个数的实参时被声明为explicit，避免隐式转换
* 由于explicit，不可以使用赋值语法(初值列)，对tuple进行初始化
* 一定要用make_tuple
---
---
## 5.2 Smart Pointer
* 使用pointer的理由之一是 作用于边界之外拥有reference语义
* 使用容易出现的问题：
  * 确保"pointer的寿命"和"其所指向的对象的寿命一致"很难


* 解决方案：使用smartpointer
  * Class shared_ptr 实现共享式拥有(shared ownership) 概念
    * 多个smart pointer 可以指向相同的对象，该对象和相关资源会在"最后一个reference被销毁"时释放
    * 提供了weak_ptr、bad_weak_ptr和enable_shared_from_this等辅助类


  * Class unique_ptr 实现独占式拥有(exclusive ownership)或严格拥有(strict ownership)概念
    * 保证同一时间内只有一个smart pointer可以指向该对象
    * 可以移交拥有权，对于避免资源泄露(resource leak)特别有用

### Class shared_ptr
shared_ptr目标就是：在其所指向的对象不再被需要之后(而非之前)，自动释放与对象相关资源

#### 使用 shared_ptr
