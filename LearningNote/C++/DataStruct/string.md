# 字符串
---
## C++中的string
C++里面的字符串是标准库的string

## 自定义实现
```c++
class String : public Object
{
public:
  void init(const char* s);

  String();
  String(const char* s);
  String(const String& s);
  int length() const;
  const char* str() const;

  ~String();

private:
  char* m_string;
  int m_length;
};

```
---
## 实现时的注意事项
* 无缝实现String对象与 ```char*```字符串的互操作
* 操作符重载函数需要考虑是否支持 const 版本
* 通过 C语言中的字符串函数 实现String的成员函数

---
## 其他的常用功能函数

成员函数 | 功能描述
-|-
operator[](i) | 操作符重载函数，访问指定下标的字符
startWith(s) | 判断字符串是否以`s`开头
endOf(s) | 判断字符串是否以 `s`结束
insert(i, s) | 在字符串的位置 `i`处 插入 s
trim() | 去掉字符串两端的空

---
### 重载数组访问操作符[] 注意
当 i 的取值不合法时，抛出异常
* 合法范围: (0 <= i) && (i < m_length)

---
## KMP
### 伟大的发现
* 匹配失败时的右移位数与子串本身相关， 与目标串无关
* **移动位数** = 已匹配的字符数 - **对应的部分匹配值**
* 任意子串都存在一个**唯一**的部分匹配表


### 部分匹配表
#### 前缀
除了 **最后一个字符以外**， 一个字符串的全部头部组合
* 例子：
```
abcd 的前缀 ： a ab abc  (bc 不是)
```

####  后缀
除了**第一个字符以外**， 一个字符串的全部尾部组合
* 例子：
```
abcd 的后缀 ：d cd bcd  (bc 不是)
```

#### 部分匹配值
前缀 和 后缀 最长共有的元素 最长的长度
* 例子：
```
abcd 的部分匹配值： 0（求 前缀 与 后缀 的交集）
ABCDAB 的 部分匹配值: 2
  前缀： A AB ABC ABCD ABCDA
  后缀： B AB DAB CDAB BCDAB
  交集： AB
  部分匹配值: 2 (AB的长度 为2)
```

#### 实现：
* PMT[1] = 0;（ 下标为 0 的 元素匹配值 为 0）
* 从2个字符开始递推
* * *假设** PMT[n] = PMT[n-1] + 1 (最长共有元素的长度)
* 当假设不成立， PMT[n]在PMT[n-1]的基础上减小


### 使用部分匹配表
* 若 下标 j 处匹配失败
* 前 j 位匹配成功
* 查表PMT[j-1]
* 右移位数 j - PMT[j-1]
