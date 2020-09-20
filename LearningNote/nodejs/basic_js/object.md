# 对象
---
## 什么是对象：
就是一堆键值对


## 对象的引用
```js
var obj = {
  name : "猪八戒"
};

var obj2 = obj;

obj2 = null;      // 此时 obj 不影响

```

## 获取一个对象
```js
var obj = new Object();
var obj1 = {};

var obj3 = {
  name: "hhh",
  age: 22,
  test: {
    nana : dd
  }
}
```

## 一切皆对象
### 创建一个函数对象
可以将 要封装的代码 以 **字符串** 的形式传递给构造函数
