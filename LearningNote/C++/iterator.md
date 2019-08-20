# ierator
---
## 1. 线性查找(linear Search)的例子
### 1.1 线性查找的概念
从头到尾一步步依序检查某特定数值是否出现在此线性序列中
* 如果 元素值 与该特定元素值相同， 则返回目前元素在 此序列的位置
* 如果 元素值 与该特定元素值不同，则移动至下一个元素
* 如果没有下一个元素，就返回某个值表示 **查找失败**
  
### 1.2 查找分析：实现任何线性查找 所需要回答的问题
* 1. 如何指明我们想要查找的序列？
* 2. 如何表示序列中的位置？
* 3. 如何移动到下一个元素？
* 4. 如何知道我们已经到了 序列尾端？
* 5. 用来表示查找失败的返回值是什么？

### 1.3 Ranges(区间)
ranges表示first 至 last(但不包含last)的所有指针

ranges需满足下列性质
* 对于任何指针p而言，empty range[p, p) (空区间) 是有效区间
* 如果 [first, last) 有效， 而且不为空，那么[first+1， Last)也必然有效
* 如果 [first，last) 有效，mid 为满足一下条件的任何指针:
  * first出发后可达mid
  * mid出发后可达last
  * 那么[first, mid)与[mid，last)皆有效
* 反之：若[first, mid)与[mid，last)皆有效，则[first, last)亦必有效

#### 为什么要用？
虽然奇怪，但是这样有助于避免相差一个(off-by-one)的错误。
* [first, last) 的元素个数，就是 last - first
* 也能够表示空区间[0, 0) 满足 0 - 0  = 0

---
## 2 C++线性查找
```C++
template<typename Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& value)
{
    while (first != last && *first != value)
        ++first;
    return first;
} 
```

###  2.1 链表查找
#### 链表一般遍历
```C++
struct int_node
{
    int val;
    int_node* next;
};

int_node* p;
for(p = list_head; p != NULL; p = p->next)
{
    // do something
}
```

#### 如何适配到 STL里的查找
解决方法：操作符重载(operatot overloading)
* 定义一个template warpper class 
* 适用于任何具有next指针的链表节点
  ```C++
  template <typename Node>
  struct node_wrap
  {
      Node* ptr;

      node_wrap(Node* p = 0) : ptr(p){}

      Node& operator* () const { return *ptr; };
      Node* operator-> () const { reurn ptr; };
  };
  ```