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
