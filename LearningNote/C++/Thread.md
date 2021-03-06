# Thread
---
---
## 为什么使用并发？
* 关注点分离(SOC)
* 性能

## 什么时候不使用并发
* 收益比不上成本


---
# 线程管理
## 线程管理基础
* 每个程序至少有一个线程
  * main()函数的线程


* 线程执行完入口函数后，线程也会退出

* 切记：当为一个线程创建一个线程对象后，一定要 **等待线程结束，它才能结束**。

---
# 线程间共享数据

## 共享数据带来的问题
* 共享数据修改，可能会导致某些问题的产生

## 竞态条件 --> 条件竞争
* 1. 两个process 共享变量       --> 数量上
* 2. 至少有一个 process 对 变量 进行 **修改** -> 写操作
* 3. 一个 process 未完成，另外一个 介入    ---> 时序上

## 解决 上述条件竞争方法：
### 1.
#### lock
* 将 时序上的条件破坏
* 这样，另一个 process 在介入的时候， 变量已经修改完成，要么就根本没有修改

#### 事务
* 一个 process 所有的操作合为一步，提交，这个叫事务
*  当一个 process 对 变量进行修改时，提交无法完成

#### 对数据结构进行 无锁设计 --> 无锁的数据结构

---
# condition_variable
## 限制
* 只能和 unique_lock<std::mutex>
* 执行wait,wait_for, wait_until会释放互斥量，并使线程**阻塞**
* condition_variable被通知，线程被唤醒，且自动获得互斥

---
### 序列化(serialzation)
#### 是什么
对数据进行串行的访问

# 提高 对数据结构进行并发访问 的 思路
* 减少保护区域
* 减少序列化操作

## 线程安全
### 是什么
* 确保 没有 线程 能够看到， 数据结构的 “不变量” 破坏时的状态
* 注意会引起 条件竞争的 接口， 提供完整操作 而非操作步骤
* 注意数据结构的行为 是否
