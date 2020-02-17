# lambda
---
## 是什么
* 匿名函数

## 有什么
```C++
auto a_alias = [capture](parameters) -> return_type {...};
```

### 捕捉
* [=] 按照值传递的方法捕捉父作用域的所有变量
* [&] 按照引用传递的方法捕捉父作用域的所有变量


### 如何递归 调用一个 lambda
