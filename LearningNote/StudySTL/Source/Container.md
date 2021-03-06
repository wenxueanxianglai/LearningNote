# **_Container_base12**
---
 当看到list的源码的时候发现顶层还有这个东东，就在这里也记录一下

 ## 文件中的位置
 ```C++
 #include <xutility>
 ```

 ## 1 大致结构
 ```C++
//listnod继承的类型在这里定义的
typedef _Container_base12 _Container_base;
typedef _Iterator_base12 _Iterator_base;

// store pointer to _Container_proxy
struct Container_base12
{
  Container_proxy * Myproxy;
};

// store head of iterator chain and back poiznter
struct Container_proxy
{
	const Container_base12* Mycont;
	Iterator_base12* Myfirstiter;
};

// store links to container proxy, next iterator
struct Iterator_base12
{
  Container_proxy* Myproxy;
	Iterator_base12* Mynextiter;
};

```
![container类图](./pic/Container.png)

---
## 2 **_Container_base12**
这个类的解释很清楚，存储Container_proxy的指针
```C++
//这里我还是把头的下划线给去掉，
struct Container_base12
{  
public:
  // construct childless container
  // 初始化一个无儿女的容器？额，还是翻译成初始化一个空的容器吧0.0
  Container_base12() : Myproxy(0)
  {
  }

  //拷贝函数，因为就一个指针，就简单地拷贝个指针？
  Container_base12(const Container_base12) : Myproxy(0)
  {
  }

  //assign a container
  Container_base12& operator= (const Container_base12&)
  {
    return (*this);
  }

  //destory the container
  ~Container_base12()
  {
    Orphan_all();  
  }

  //--
  // get address of iterator chain 获取迭代器链的地址  
  Iterator_base12** Getpfirst() const
  {
    return (Myproxy == 0 ? 0 : Myproxy->Myfirstiter;)
  }

  // orphan all iterators
  void Orphan_all();  
  // swap all iterators
  void Swap_all(Container_base12&);

  Container_proxy* Myproxy;   //主要就是存的他
}
```

#### Orphan_all

```C++
/* 这一段是源码
//这里只有debug等级为2的才做下面代码
#if _ITERATOR_DEBUG_LEVEL == 2  
if (_Myproxy != 0)
  {	// proxy allocated, drain it
  _Lockit _Lock(_LOCK_DEBUG);

  for (_Iterator_base12 **_Pnext = &_Myproxy->_Myfirstiter;
    *_Pnext != 0; *_Pnext = (*_Pnext)->_Mynextiter)
    (*_Pnext)->_Myproxy = 0;
  _Myproxy->_Myfirstiter = 0;
}
*/

inline void Container_base12::Orphan_all()
{
  if (Myproxy)
  {
    Lockit Lock(Lock_DEBUG);

    for( Iterator_base12** Pnext = &Myproxy->Myfirstiter;  // 获取指针的 地址,  
         *Pnext != 0;                                      // 判断地址存储的指针不为空
         *Pnext = (*Pnext)->Mynextiter                     // 将下一个指针赋值给当前这个指针
       )                     
    {
      (* Pnex)->Myproxy = 0;       //循环体里就是置空这个proxy
    }

    Myproxy->Myfirstiter = 0;         //最后把当前的指针置空
  }

}

```

#### Swap_all
```C++
inline void Container_base12::Swap_all(Container_base12& Right)
{
  // 这三行，就是两个container的proxy指针
  Container_proxy* Temp = Myproxy;    
  Myproxy = Right.Myproxy;            
  Right.Myproxy = Temp;

  //重新赋值当前对象的proxy
  if (Myproxy != 0) {
    Myproxy->MyCont = (Container_base12*)this;
  }
  if (Right.Myproxy != 0) {
    Right.Myproxy->Mycont = (Container_base12* )&Right;
  }

}
```
---
## 3 Container_proxy
Container_proxy 很简单，仅仅存储了两个指针
```C++
//store head of iterator chain and back pointer
struct Container_proxy
{
    Container_proxy() : Mycont(0), Myfirstiter(0)
    {
    }

    const Container_base12* MyCont;
    Iterator_base12* Myfirstiter;
};

```

---
## 4 Iterator_base12
```C++
// store links to container proxy, next iterator
// 存储 proxy的关联  ，下一个iterator
struct Iterator_base12
{

  //-begin 这俩属性  一个是proxy 一个是iterator
  Container_proxy* Myproxy;
  Iterator_base12* Mynextiter;
  //-end

public:
  // -begin 构造析构等相关
  // construct orphaned iterator  初始化一个孤儿？iterator 初始化一个单独的iterator
  Iterator_base12() : Myproxy(0), Mynextiter(0)
  {
  }

  Iterator_base12(const Iterator_base12& Right) : Myproxy(0), Mynextiter(0)
  { //copy an iterator
    * this = Right;
  }

  Iterator_base12& operator= (const Iterator_base12& Right)
  { // assign an iterator
    if(Myproxy != Right.Myproxy)
      Adopt(Right.Myproxy->MyCont);

    return (*this);
  }

  ~Iterator_base12()
  {
    //destroy the iterator
    Lockit Lock();

    Orphan_me();
  }
  // -end

  //-- begin
  void Clrcont()
  {//disown owning container
    Myproxy = 0;
  }

  const Container_base12* Getcont() const
  {// get owning container
    return (Myproxy == 0 ? 0 : Myproxy->MyCont);
  }

  Iterator_base12** Getpnext()
  {
    // get address of remaining iterator chain
    return (&Mynextiter);
  }
  //-- end

  // -- begin
  void Adopt(const Container_base12* Parent)
  {// adopt this iterator by parent
    if (Parent != 0)
    {
      Container_proxy* Parent_proxy = Parent->Myproxy;
      if (Myproxy != Parent_proxy)
      {
        Lockit Lock();
        Orphan_me();

        Mynextiter = Parent_proxy->Myfirstiter;
        Parent_proxy->Myfirstiter = this;
        Myproxy = Parent_proxy;
      }  
    }
  }

  void Orphan_me()
  {
    if (Myproxy != 0)
    {
      //单链表找到存放自己的指针，或者可以叫找到自己的上一个对象
      Iterator_base12** Pnext = Myproxy->Myfirstiter;
      while (*Pnext != 0 && *Pnext != this)
      {
        Pnext = &(* Pnext)->Mynextiter;
      }

      if(*Pnext == 0)
      {
        //出错了嘛~
        DEBUG_ERROR;
      }

      * Pnext = Mynextiter;   //将自己的下一个指针赋值给自己的前驱
      Mynextiter = 0;         // 自己的下一个设置为空，这时候 自己就孤立了~

    }
  }
  // -- end
};
```
