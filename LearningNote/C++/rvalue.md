# 右值
---
## 背景： 值类别
---
### 怎么判断值类别？
#### 1. 拥有身份(identity)
可以 确定 表达式A 与 表达式B 是否指代 同一个实体

#### 2. 可 被移动
移动构造，移动赋值， 或实现移动语义其他函数重载， 能够绑定这个表达式
---
## 通过值类别定义 右值(右值是什么)
* 拥有身份 && 不可被移动的表达式 --> 左值表达式(lvalue expressions)
* 拥有身份 &&  可被移动 --> 亡值表达式(xvalue expressions)
* 无身份 && 可被移动 --> 纯右值表达式(prvalue<"pure rvalue"> expressions)
* 无身份 && 不可被移动 --> 无法使用！

### 简单点：
* 泛左值 ：拥有身份
* 右值 ：可被移动

### 更简单点的 左右值
* 可以放在 ``` = ``` 左边 --> 左值
* 可以放在 ``` = ``` 右边 --> 右值

### 作用：
* glvalue 是 一种表达式： 求值确定一个 对象， 位域， 或函数的个体
* grvalue 是一种表达式：
  * 计算 不与对象关联的值
  * 创建临时对象 并指代它
---
## 左值有哪些
### 名字
* 变量名
* 函数名
* 数据成员名
* 模板形参对象名

只要是名字，不管类型，都是左值表达式

### 返回类型为左值的引用的
* 函数调用
* 重载运算符(也是函数)

### 内置运算符 形成的表达式
#### 1. 赋值表达式 以及 复合赋值表达式
* 赋值表达式 ``` = ```
* 复合赋值
  * ``` += ```
  * ``` -= ```
  * ``` *= ```
  * ``` /= ```
  * ``` %= ```
  * ``` &= ```
  * ``` |= ```
  * ``` ^= ```
  * ``` <<= ```
  * ``` >>= ```

#### 2. 前置 自增，自减
* ++i
* --i

#### 3. 间接寻址
* ``` *p ```

#### 4. 下标表达式
* ``` a[n] ```
* ``` n[a] ```

#### 5. 对象成员表达式(member of object expression)
* ```a.m```
  * m 不能是：  成员枚举项
  * m 不能是：  非静态成员函数
  * m 不能是：  (a为右值时) 非引用类型的非静态数据成员

#### 6. 内置的指针成员表达式
* ``` p->m ```
  * m 不能是 : 成员枚举项
  * m 不能是：  非静态成员函数

#### 7. 对象的成员指针表达式
* ``` a.*mp ```
  * a是左值 且 mp是 数据成员指针

#### 8. 内置的 逗号表达式
* ``` a,b ``` b为左值

#### 9. 某些三元表达式

### 字符串 字面量
```
"hello world"
```

### 转换为左值引用的转型表达式
```
static_cast<int&>(x)
```

### 返回类型
 是 到 函数的右值引用的 函数调用表达式 或者重载的 运算符表达式

### 转换为函数的 右值引用类型的转型表达式
```
static_cast<void(&&)(int)>(int)
```

---

## 左值 性质(可以做什么？)
* 可以用内置的```&``` 取地址：
  * ``` &++i```
  * ```&std::endl```


* 可修改的左值 可以 用作 内置赋值(=)  和 内置 复合赋值运算符的左操作数
* 左值 可用于 **初始化左值引用**
* 泛左值的性质
---
## 纯右值 有哪些
### 除了 字符串字面量之外 的 字面量
* 42
* true
* nullptr

### 返回类型是 非引用 的 函数调用 或 重载运算符

### 内置的
#### 后置自增 后置自减
* i++
* i--

#### 内置的算术表达式
* a + b
* a - b
* a % b
* a & b
* a << b
* 等等(所有)

#### 内置的逻辑表达式
* a && b
* a || b
* !a

#### 内置的表达式
* a < b
* a > b
* a == b
* 等等(所有)

#### 内置的取地址
```
&a
```

###


---
## 引用坍缩
* 左值引用的引用(...)仍为左值引用
* 右值的右值引用 为 右值引用
