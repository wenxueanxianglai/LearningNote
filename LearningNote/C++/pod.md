# pod
---
## pod 是什么？
之前有看了一堆，依然不是太懂，还是应该结合着标准库中的`is_pod` 去理解 这样好点

**pod 就是 平凡的(类型) 且 又是标准布局(类型) 的类型**

POD ： Plain Old Data 缩写

### 什么是平凡类型(TrivialType)
* 可平凡复制
* 默认构造

## 标准布局(StandardLayoutType)
标准中并没有定义具有这个名字的具名要求

### 要求
* 所有 非静态数据成员 具有 相同的访问控制
* 没有引用类型的非静态数据成员
* 所有非静态成员和基类自身也是标准布局
* 没有虚函数，虚基类



http://cseweb.ucsd.edu/~ricko/rt_lt.rule.html
