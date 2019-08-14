# list
---
## 1. list 在vs的位置
```C++
#include <list>
```

## 2. list大致结构
```C++
/*
//这个在xutility文件里定义
typedef _Container_base12 _Container_base;    
class _List_nod : public _Container_base
class _List_val	: public _List_nod<_Ty, _Alloc>
class list  : public _List_val<_Ty, _Ax> {};
*/

// 这样看起来舒服点
typedef Container_base12 Container_base;    
class List_nod : public Container_base {};          //nod 继承的 是 Container_base12        
class List_val	: public List_nod<Ty, Alloc> {};
class list  : public List_val<Ty, Ax> {};

```

## 3. **_List_nod**
```C++
/* 这里就是源码，由于我不是太习惯读开头加各种下划线，所以就自己修改下了
template<class _Ty,
	class _Alloc>
	class _List_nod
		: public _Container_base
	{	// base class for _List_val to hold storage
public:
	typedef typename _Alloc::template rebind<_Ty>::other _Alty;
	typedef typename _Alty::size_type size_type;

	struct _Node;
	typedef _Node *_Nodeptr;	// _Node allocator must have ordinary pointers
	typedef _Nodeptr& _Nodepref;

	struct _Node
		{	// list node
		_Nodeptr _Next;	// successor node, or first element if head
		_Nodeptr _Prev;	// predecessor node, or last element if head
		_Ty _Myval;	// the stored value, unused if head

	private:
		_Node& operator=(const _Node&);
		};

 #if _ITERATOR_DEBUG_LEVEL == 0
	_List_nod(_Alloc _Al)
		: _Alnod(_Al), _Alval(_Al)
		{	// construct allocators from _Al
		}

 #else    // _ITERATOR_DEBUG_LEVEL == 0
	_List_nod(_Alloc _Al)
		: _Alnod(_Al), _Alval(_Al)
		{	// construct allocators and proxy from _Al
		typename _Alloc::template rebind<_Container_proxy>::other
			_Alproxy(_Alnod);
		this->_Myproxy = _Alproxy.allocate(1);
		_Cons_val(_Alproxy, this->_Myproxy, _Container_proxy());
		this->_Myproxy->_Mycont = this;
		}

	~_List_nod()
		{	// destroy proxy
		typename _Alloc::template rebind<_Container_proxy>::other
			_Alproxy(_Alnod);
		this->_Orphan_all();
		_Dest_val(_Alproxy, this->_Myproxy);
		_Alproxy.deallocate(this->_Myproxy, 1);
		this->_Myproxy = 0;
		}
 #endif   // _ITERATOR_DEBUG_LEVEL == 0

	_Nodeptr _Myhead;	// pointer to head node
	size_type _Mysize;	// number of elements

	typename _Alloc::template rebind<_Node>::other
		_Alnod;	// allocator object for nodes
	_Alty _Alval;	// allocator object for element values
	};
*/

//------------------------- 这里是自己加的注释版 ------------------------------------------
//其实源码中有句注释这个基础类为 list_val 提供 存储
template <typename Ty, typename Alloc>
class List_nod : public Containter_base
{
public:
  //这个rebind 在 allocator 定义了
  typedef typename Alloc::template rebind<Ty>::other  Alty;
  typedef typename Alty::size_type  size_type;

  //---- begin 定义Node ----
  struct Node;                    //在这里先声明，真正定义在下面
  typedef Node* Nodeptr;          //声明了Node的指针    PS：我习惯把*放在前面
  typedef Nodeptr& Nodepref;      //声明 Node指针的 引用

  struct Node      //这里源码也有翻译， list Node
  {
    Nodeptr Next;     //successor node后继指针，或者如果是头 指向第一个元素
    Nodeptr Prev;     //predecessor node 前驱指针，或者如果是头 指向最后一个元素
    Ty Myval;         // 存储 值， 如果是头 就不能用

  private:
    Node& operator = (const Node&);
  }
  //---- end. ----

  // 重点
  // ---- begin 这里记录下node 类中存储的属性 ----
  Nodeptr Myhead;	// pointer to head nod
  size_type Mysize;	// number of elements

  //这里实际上引用的类型allocator< Node >
  typename Alloc::template rebind<Node>::other    
		Alnod;	// allocator object for nodes
	Alty Alval;	// allocator object for element values
  // ---- end. ----

  //---- begin 构造函数 和 析构函数 ----
  List_nod(Alloc Al) : Alnod(Al), Alval(Al)
  {
    //创建 Alloc<Container_proxy> Alproxy变量
    typename Alloc::template rebind<Container_proxy>::other Alproxy(Alnod);

    this->MyProxy = Alproxy.allocate(1);

    Cons_val(Alproxy, this->MyProxy, Container_proxy());  //初始化~ 这个函数在 xmemory

    this->MyProxy->Mycont = this;

  };
  //---- end. ----

}

```
