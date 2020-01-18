# template
---
## 编译时期
#### 1. 第一阶段： 发生模板的定义点(point of definition)
#### 2. 第二阶段： 发生它的每一个实例化的点(points of instantiation)

## Function template
一个函数模板就是一个公式，用来生成针对于特定类型的函数版本

### 如何定义
#### template 关键字
#### template paramter list 模板参数列表
  * 一个或多个模板参数
  * 模板类型参数
    * 一般看做类型说明符
  * 非模板类型参数
    * 通过一个 **特定的类型名来指定**
    * 这些值必须是 **常量表达式**
  * **定义时，模板参数列表不能为空**


### 如何使用
#### 指定模板实参(template argument)，绑定到模板参数上
* 显示或隐式指定都可以

### 实例化函数模板
* 使用实际的模板实参代替对应的模板参数
* 创建一个新实例

---
## class template
### 如何定义：和函数模板一样

### 在模板作用域中引用模板类型
```C++
template < typename T>
class Blob
{
  std::shared_ptr< std::vector<T> > data;
};
```
---
## 模板的可计算对象
* 编译期常量
* 可计算对象

###  模板内部定义类型
* 定义嵌套类 --- C++11 之后最好用using

// C++标准要求使用推导类型前面必须使用typename关键字显示指明这是一个类型
//using Result = typename PointerOf<typename PointerOf<T>::Result>::Result;

C++标准不允许在类或者模板的内部定义模板的特化

编译器对模板的特化版本选择相当于是在做模式匹配

元函数转发的概念，也就是通过已有的元函数组合，来定义新的元函数

不同于类型模板形参声明，模板模板形参只能用关键词 class 而不能用 typename。
	(C++17 前)
---
# 对于模板 栈的排列
对于参数的排列，模板是从 左->右 依次读取，从这里认为的栈则是，左边为栈顶，右边为栈底

## 如何验证
可用减法验证，减法无结合律，则减法的操作顺序变化，就会引起结果的变化

## 验证具体步骤
#### 1. 声明 减法：
V1 - V2 : 可写为 **__sub(v1, v2)**

```C++
template<typename T1, typename T2>
struct Sub;

template<int V1, int V2>
struct Sub<IntType<V1>, IntType<V2>>
{
	using Result = IntType<V1 - V2>;
};


#define __sub(...)    typename Sub<__VA_ARGS__>::Result
```

#### 2. 使用连续相减
使用递归的方式，不断地去相减，从结果去判断出递归的方向

```C++
template<typename ...Numbers>
struct SumSub;

template<typename Number, typename ...leftNumbers>
struct SumSub<Number, leftNumbers...>
{
	using Result = typename Sub<Number, typename SumSub<leftNumbers...>::Result>::Result;
};

template<>
struct SumSub<>
{
	using Result = IntType<0>;
};

#define __sumsub(...) typename SumSub<__VA_ARGS__>::Result
```
