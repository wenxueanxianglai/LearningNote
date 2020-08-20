# python
## 在哪里下载？
https://www.python.org/downloads/

## 如何安装？
勾选上所有选项 ：
1. Install launcher for all users
2. Add Python   to  PATH

## 验证是否成功
1. 进入命令行
2. 输入 python
![](./pic/python_commmand.png)

----
## 对 上面解释
### 输入 python：
就是进入了 python 的环境， 这里可以做python的事

### 如何退出
输入  ```exit()```

---
## 输入 和 输出
### 为什么要知道
每个语言 或者工程 都需要知道我们做的东西(或者叫 计算) 是否会成功，这时候 就需要输出  
每个工程 都是有输入的 只是输入的东西不一样

### 最简单的输出
```py
>>> 100 + 200
300
```
上面我们敲入  100 + 200  然后 回车 ， 就能看到结果


### 一般使用的输出： print()
程序员最喜欢输出的一句话 ： hello world！
```py
print("hello world!")
```

#### 复杂点的输出
多个 string 的 输出
```py
print("hello world!", "I am zxp")
```
上面输出：```hello world! I am zxp```

输出计算结果
```py
print("100 + 200 = ", 100 + 200)
```

### 输入： input()
通过键盘，我们可以输入很多东西 到 python
```py
x = input()
```
这时候 键盘键入  300， x 就是 300了
