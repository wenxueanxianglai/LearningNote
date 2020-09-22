# 对象

---

## 什么是对象：

就是一堆键值对

## 对象的引用

```js
var obj = {
  name: "猪八戒",
};

var obj2 = obj;

obj2 = null; // 此时 obj 不影响
```

## 获取一个对象

```js
var obj = new Object();
var obj1 = {};

var obj3 = {
  name: "hhh",
  age: 22,
  test: {
    nana: dd,
  },
};
```

## 一切皆对象

### 创建一个函数对象

可以将 要封装的代码 以 **字符串** 的形式传递给构造函数

---

## 批量创建对象 --->

### 普通的工厂方法

```js
function create_persion(name, age) {
  let obj = {
    name: name,
    age: age,
    getName: function () {
      console.log(obj.name);
    },
  };

  return obj;
}
```

方法问题： 所有创建的 对象都是 object 对象

### 构造函数方法

```js
function persion(name, age) {
  this.name = name;
  this.age = age;
  this.getName = function () {
    console.log(this.name);
  };
}

// 1. 创建一个对象   --> new
// 2. 将新建的对象设为 函数中的 this， 在函数内部可以使用this
// 3. 执行 函数代码
// 4. return new出来的对象

var obj = new persion("aa", 23);
```

- 这个需要 new 关键字 才能生成对象, 否则就是 undefined
- 当前的 构造函数 每 new 出来一个 对象， 内部的属性(不管函数还是名字)都会复制一遍

### 解决上述问题

#### 前提知识

- js 规定： 每个函数都有一个 prototype
- 构造函数默认成为实例对象的原型

* 当实例对象 **没有**某个属性或者方法时，会到 原型对象找属性或者方法

**原型对象作用**

- 定义所有实例对象共享的属性和方法
- 实例对象可以视作从原型对象衍生出来的子对象

#### 构造函数的继承

##### 步骤

1. 在子类构造函数中， 调用 父类的构造函数

2. 将子类的原型指向父类的原型

---
### 语法糖
*  `var a = {}` ==> `var a = new Object()`
* `var a = []` ==> `var a = new Array()`
* `function foo(){}` ==> `var foo = new function(){}` 


### 原型原则
* 所有引用类型都有 对象特性(除了null)
* 所有引用类型都有 `__proto__` 属性， 是一个普通对象(隐式原型)
* 所有**函数** 都有一个 `prototype`（显式原型）, 也是个普通对象
* 所有引用类型： `__proto__`指向它的构造函数`prototype`
  * 当试图得到一个对象的某个属性时，如果没有， 就去它的 `__proto__` (即它的构造函数的prototype(显式原型))中寻找
* 通过对象的属性的形式来执行函数的时候，无论函数是自身的属性还是从原型中得到的属性， this 永远指向 f 自身,
* hasOwnProperty 判断是否是自身属性
  

### __proto__
#### 是什么
* 是 任何一个 引用对象的属性
* 一般指向 prototype


### prototype
#### 是什么
是 函数  对象 的 一个属性 指向 另一个对象

---
## 继承