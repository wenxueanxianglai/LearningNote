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

### 5.2.3 误用Shared Pointer
shared_ptr 由于对象的相应资源往往被自动释放，当对象不再被使用时有可能出现问题

#### 确保某对象只被一组 shared pointer 拥有

### 5.2.4 细究 shared_ptr 和 weak_ptr
#### 线程安全(Thread-Safe)的Shared Pointer接口
* 一般而言 shared pointer 并非线程安全

### 5.2.5 Class unique_ptr
* C++11起开始有
* 他是异常发生时可帮助避免资源泄露的 smart pointer
* **独占式拥有** ： 他只确保一个对象和其相应资源只被一个pointer拥有
* 资源释放情形：
  * 一旦拥有者被销毁或变成empty
  * 开始拥有另一个对象

#### 函数的运作
* 获得某些资源
* 执行某些操作
* 将取得的资源释放掉

```C++
void f()
{
  ClassA* ptr = new ClassA; //creat an object explicitly
  ...                       //perform some operations
  delete ptr;               //clean up(destroy the object explicitly)
}
```

#### Class unique_ptr 的目的
* unique_ptr 是 **其所指向对象** 的唯一拥有者
* unique_ptr 的必要条件：它指向的对象只有一个拥有者

#### 使用 unique_ptr
* 不提供 pointer 的算术运算
* 初始化要求：不允许以赋值语法将一个普通的pointer当做初值，只能直接 **初始化**
* unique_ptr可为空
* 使用release(), 获取 unique_ptr拥有的对象，并让 unique_ptr 放弃拥有权

#### 转移 unique_ptr 的拥有权
* 不能使用拷贝构造，必须要触发移动构造

#### 源头和去处(Source and Sink)
拥有权可转移意味着 unique_ptr 的一个用途: 函数可利用他们讲拥有前转移给其他函数
* 函数是接收端
  * unique_ptr 以 rvalue reference 作为函数实参传递
  * 函数会取得 unique_ptr 的拥有权


* 函数是供应端
  * 当函数返回一个unique_ptr，其拥有权会转移至被调用端
  * 在函数末尾时， 编译器应自动尝试加上move

#### 对Array
* 需要主动在之前面加数组符号
* 但是不再提供 `*` 和 `->`操作符，提供[]
* 不接受派生类型的Array

#### 其他资源的deleter
* 如果是个函数或者lambda 必须声明deleter类型为 `void(*)(*)`或`std::function<void(T*)>`,或者使用decltype

---
---
# Chapter 6 标准模板库
STL 的一个根本特性：所有组件都可以针对任意类型运作

从程序员的角度看：
* 可使用不同需求的集合类(collection class)
* 能够在这些集合类上运作的算法

## 6.1 组件(Component)
* Container 容器
  * 用来管理某对象的集合
* Iterator 迭代器
  * 用来在一个对象集合(collection of objects)内便利元素
  * 好处： 为所有各式各样的容器提供了一组很小的共同接口
* Algorithm 算法
  * 用来处理集合内的元素

adapter 适配器

## 6.2 容器(Container)
分类：
* Sequence container 序列式容器
  * 是一种有序(ordered)集合，
  * 其元素均有确凿的位置--取决于插入时机和地点，与元素值无关
  * array、vector、deque、list 和 forward_list
* Associative container 关联式容器
  * 是一种已排序(sorted)集合，元素位置取决于其value(或key)和给定的排序准则， 与插入次序无关
  * set、multiset、map 和 multimap
* Unordered (associative) container 无序容器
  * 这是一种无序集合(unordered collection)
  * 每个元素的位置无关紧要， **唯一重要的是其特定元素是否位于此集合内**
  * 元素值或其安插顺序，都不影响元素的位置，而且元素位置可能随时间而改变
  * unordered_set、unordered_multiset、unordered_map 和 unordered_multimap

### 6.2.1 序列式容器(Sequence Container)
* vector
  * 将元素置于一个dynamic array中管理
    * 在array尾部 **插入** 和 **移除** 元素都很快，插入中间，删除中间费时
    * 可利用索引直接访问任何一个元素


* Deque
  * dynamic array
    * 可 **向两端发展**
    * 头尾安插元素都十分迅速


* Array
  * 在某个固定大小的array内管理元素
    * 不可改变元素个数
    * 建立时就指明其大小
    * 支持随机访问


* List
  * 双向链表实现而成
    * 不提供随机访问
    * 在任意位置上执行安插或删除都非常迅速


### 6.2.2 序列式容器(associative Container)
通常由二叉树(binary tree)实现。  
关联式容器主要差别在于：
* 元素种类
* 处理重复元素时的方式

主要优点
* 它能够找出一个具有特定value的元素。因为它具备对数复杂度  

主要缺点：
* 不能直接改动元素的value，因为会破坏元素的自动排序

## 6.3 迭代器(Iterator)
迭代器是一个“可遍历STL容器全部或部分元素”的 对象。迭代器用来表现容器中的某一个位置
* Operator * 返回当前位置上的元素值。
  * 如果元素拥有成员，可以通过操作符->直接使用
* Operator ++ 前进至下一个元素。
  * 大多数迭代器还可以使用Operator--退至前一元素
* Operator == 和 != 判断两个迭代器是否指向同一位置
* Operator = 对迭代器赋值(也就是指明迭代器所指向的元素 的 位置)  


迭代器中重要的两个成员函数
* begin() 返回一个迭代器，指向容器起点
  * 就是指向第一个元素(如果有)的位置
* end() 返回一个迭代器，指向容器终点
  * 终点位于最末元素的下一个位置
  * 这样的迭代器又称作"逾尾(past-the-end)"迭代器  


begin() 和 end()形成半开区间(half-open range),有两个优点。
* 为"遍历元素时的loop结束时机"提供了一个简单的判断依据。
  * 只要尚未到达end()， loop就可以继续进行
* 不必对空区间(empty range)采取特殊处理
  * 空区间的begin()就等于end()































0
