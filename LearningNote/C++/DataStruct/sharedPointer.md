# sharedPointer
---
## 需求
* 多个指针指向同一片堆空间
* 能够自动释放堆空间

---
## 设计
* 通过计数机制 标识堆内存
  * 堆内存被指向时，ref++
  * 指针被置空时， ref--
  * ref == 0时， 释放堆内存


## 其他
智能指针可比较
