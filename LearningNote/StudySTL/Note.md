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

### 5.2.1 Class shared_ptr
shared_ptr目标就是：在其所指向的对象不再被需要之后(而非之前)，自动释放与对象相关资源

#### 使用 shared_ptr
* 接收单一pointer作为唯一实参的构造函数是explicit,所以对于字符串不能够使用赋值符号。
* 使用便捷函数
* 注意：**但凡容器，总是为传入的元素创建属于容器自己的拷贝**

#### 定义一个deleter
可以声明属于自己的deleter

#### 对Array
* 默认的shared_ptr提供的deleter调用的是delete，不是delete[]
* 这时候 **必须定义自己的deleter
* 也可使用unique_ptr提供的辅助函数作为deleter，期内调用delete[]**
* 注意：unique_ptr允许只传递对应元素类型作为template实参，但shared_ptr不行

#### 其他析构策略
* 如果清理工作不仅仅删除内存，就必须明确给出自己的deleter
* 注意：shared_ptr只提供`operator *`和 `operator ->`
* 如果想访问内存必须使用get()

### 5.2.2 Class bad_weak_ptr
#### 不期望使用shared_ptr的情况
* cyclic reference
* 想明确共享但不愿拥有某对象

#### 功能
* 这个class建立起一个shared pointer，
* 一旦最末一个该对象的shared pointer失去了拥有权
* 任何weak pointer 都会自动成空

#### 使用建议
* weak_ptr只提供小量操作，
  * 只能够用来创建、复制、赋值 weak pointer,
  * 转换一个shared pointer
  * 检查自己是否指向某对象
* 不能使用* 和->访问 weak_ptr 指向的对象，而是必须另外建立一个 shared_ptr
  * 这样可因此检查是否存在一个相应对象，如果不，操作抛出异常或者建立一个 empty shared pointer
  * 当指向的对象正在被处理时，shared pointer无法被释放
