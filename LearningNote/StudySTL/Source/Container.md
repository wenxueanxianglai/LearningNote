# **_Container_base12**
---
 当看到list的源码的时候发现顶层还有这个东东，就在这里也记录一下

 ## 文件中的位置
 ```C++
 #include <xutility>
 ```

 ## 大致结构
 ```C++
//listnod继承的类型在这里定义的
typedef _Container_base12 _Container_base;
typedef _Iterator_base12 _Iterator_base;
/*
// store pointer to _Container_proxy
struct _Container_base12
{
  _Container_proxy * _Myproxy;
};

// store head of iterator chain and back poiznter
struct _Container_proxy
{
	const _Container_base12 *_Mycont;
	_Iterator_base12 *_Myfirstiter;
};

// store links to container proxy, next iterator
struct _Iterator_base12
{
  _Container_proxy *_Myproxy;
	_Iterator_base12 *_Mynextiter;
};
*/
```
