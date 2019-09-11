# Traits
---
## 元数据 (metadata)
#### 有什么？
* 类型
* 非类型

#### 非类型
大致就是编译期知道的任何其他值
* 常量整数值
* 枚举
* 函数
* 全局对象的指针 和 引用
* 指向成员的指针

## 类型关联

#### iterator_traits
traits 为我们提供了一种非侵入的方式，将信息与类型进行关联
* value_type  值的类型
* reference
* pointer
* difference_type
* iterator_category

```C++
template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::value_type value_type;
};
```

## 元函数
* traits 的特化
