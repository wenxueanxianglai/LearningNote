# allocator
---
## vs的 allocator 位置
```C++
#include <xmemory>
```

## vs 中的实现：
大概vs认为如果是内部封装的，都会在前面加下划线。所以，在xmemory头文件有个define
```C++
#define _ALLOCATOR	allocator
```

然后，当前文件的下面就有了 ```_ALLOCATOR```  的类模板.
这里有两个版本，一个是普通版本，一个是特化版本。
```C++
/*
template<class _Ty>
	class _ALLOCATOR : public _Allocator_base< _Ty>
    {
      //...
    };

template<> class _ALLOCATOR<void>
{
  //...
};
*/
```

---
## 稍微分析一下：
由于我不是太喜欢开头加各种下划线，所以我就自己修改下命名了。。

#### Allocator_base 类
```C++
template<class Ty>
	struct Allocator_base
	{	// base class for generic allocators
	typedef Ty value_type;
	};

// TEMPLATE CLASS _Allocator_base<const _Ty>
template<class Ty>
	struct Allocator_base<const Ty>
	{
      //base class for generic allocators for const Ty
	   typedef Ty value_type;
	};
```
**注：**
* 我把 **_Ty** 写成了 **Ty**
* 我把 **_Allocator_base** 写成了 **Allocator_base**

其实上面写得很清楚，只是定义了模板 **传入参数的类型**， 以后 咱们传入的类型就在模板里面就是这个。


#### allocator
其实这个类并不是太难理解，不过我是一边看类，一边向上翻那几个函数的,这里有几个需要记录下:
* **_FARQ** 这个宏
  * 后面注释：specify standard memory model 翻译就是指定标准内存模型
  * 由于后面是空的，大概应该是给编译器，或者其他的使用，至少不是我
  * (这里我是忽略的，因为我认为学习应该先分层？主要目的是想看看allocator)
* **_Allocate** 又是带下划线的，这是个模板函数
  ```C++
  /*  这里是源码 ，但是我不是太会直接阅读这样的源码，所以我进行了替换
  template<class Ty> inline
	Ty _FARQ *_Allocate(_SIZT _Count, Ty _FARQ *)
	{	// allocate storage for _Count elements of type _Ty
	void *_Ptr = 0;

	if (_Count <= 0)
		_Count = 0;
	else if (((_SIZT)(-1) / sizeof (_Ty) < _Count)
		|| (_Ptr = ::operator new(_Count * sizeof (_Ty))) == 0)
		_THROW_NCEE(bad_alloc, 0);

	return ((_Ty _FARQ *)_Ptr);
	}
  */
  //替换后  这个就是获取一段内存的函数
  template< typename Ty >
  Ty* Func_Allocate(size_t Count, Ty*)
  {
    void* ptr = nullptr;
    if (Count <= 0)   //其实这里size_t 就是unsigned..但是我也不知道他为啥这样写，俺也不敢问...
    {   
      Count = 0;
    }
    else if(
              ((size_t)(-1) / sizeof(Ty) < Count)                       // 定义了边界，-1转换成unsigned 就是unsigned的最大值。最多获取元素个数，还小于这个个数，就返回bad allocat
              || (ptr = ::operator new(Count* sizeof(Ty)) == nullptr)   //这里做了获取内存的操作~如果没new成功，就返回 bad allocat
            )
    {
      throw bad_alloc(0);
    }  

    return ( (Ty*)ptr);
  }

  ```
* **_Construct** 也是个带下划线的模板函数，和上面一样
	```C++
	/* 同上，这是他的源码
	template<class _Ty1,
	class _Ty2> inline
	void _Construct(_Ty1 _FARQ *_Ptr, _Ty2&& _Val)
	{	// construct object at _Ptr with value _Val
	void _FARQ *_Vptr = _Ptr;
	::new (_Vptr) _Ty1(_STD forward<_Ty2>(_Val));
	}

	template<class _Ty1> inline
	void _Construct(_Ty1 _FARQ *_Ptr)
	{	// construct object at _Ptr with default value
	void _FARQ *_Vptr = _Ptr;

	::new (_Vptr) _Ty1();
	}
	*/

	template<typename Ty1, typename Ty2>
	void Func_Construct(Ty1 Ptr, Ty2 Val)
	{
		void* Vptr = Ptr;
		::new(Vptr) Ty1(::std::forward<Ty2>(Val));		//这里进行了初始化，Ptr指向的对象进行了初始化
	}

	```

* **_Destroy** 调用析构的函数
```C++
	/* 源码大概就长这样，很好懂
	template<class _Ty> inline
	void _Destroy(_Ty _FARQ *_Ptr)
	{	// destroy object at _Ptr
	_Ptr->~_Ty();
	}
	*/
template<typename Ty> inline
void Func_Destroy(Ty* Ptr)
{
	Ptr->~Ty();
}

```

```C++
/* 同理 这里是源码
template<class _Ty>
	class _ALLOCATOR
		: public _Allocator_base<_Ty>
	{	// generic allocator for objects of class _Ty
public:
	typedef _Allocator_base<_Ty> _Mybase;
	typedef typename _Mybase::value_type value_type;

	typedef value_type _FARQ *pointer;
	typedef value_type _FARQ& reference;
	typedef const value_type _FARQ *const_pointer;
	typedef const value_type _FARQ& const_reference;

	typedef _SIZT size_type;
	typedef _PDFT difference_type;

	template<class _Other>
		struct rebind
		{	// convert this type to _ALLOCATOR<_Other>
		typedef _ALLOCATOR<_Other> other;
		};

	pointer address(reference _Val) const
		{	// return address of mutable _Val
		return ((pointer) &(char&)_Val);
		}

	const_pointer address(const_reference _Val) const
		{	// return address of nonmutable _Val
		return ((const_pointer) &(char&)_Val);
		}

	_ALLOCATOR() _THROW0()
		{	// construct default allocator (do nothing)
		}

	_ALLOCATOR(const _ALLOCATOR<_Ty>&) _THROW0()
		{	// construct by copying (do nothing)
		}

	template<class _Other>
		_ALLOCATOR(const _ALLOCATOR<_Other>&) _THROW0()
		{	// construct from a related allocator (do nothing)
		}

	template<class _Other>
		_ALLOCATOR<_Ty>& operator=(const _ALLOCATOR<_Other>&)
		{	// assign from a related allocator (do nothing)
		return (*this);
		}

	void deallocate(pointer _Ptr, size_type)
		{	// deallocate object at _Ptr, ignore size
		::operator delete(_Ptr);
		}

	pointer allocate(size_type _Count)
		{	// allocate array of _Count elements
		return (_Allocate(_Count, (pointer)0));
		}

	pointer allocate(size_type _Count, const void _FARQ *)
		{	// allocate array of _Count elements, ignore hint
		return (allocate(_Count));
		}

	void construct(pointer _Ptr, const _Ty& _Val)
		{	// construct object at _Ptr with value _Val
		_Construct(_Ptr, _Val);
		}

	void construct(pointer _Ptr, _Ty&& _Val)
		{	// construct object at _Ptr with value _Val
		::new ((void _FARQ *)_Ptr) _Ty(_STD forward<_Ty>(_Val));
		}

	template<class _Other>
		void construct(pointer _Ptr, _Other&& _Val)
		{	// construct object at _Ptr with value _Val
		::new ((void _FARQ *)_Ptr) _Ty(_STD forward<_Other>(_Val));
		}

	void destroy(pointer _Ptr)
		{	// destroy object at _Ptr
		_Destroy(_Ptr);
		}

	_SIZT max_size() const _THROW0()
		{	// estimate maximum array size
		_SIZT _Count = (_SIZT)(-1) / sizeof (_Ty);
		return (0 < _Count ? _Count : 1);
		}
	};
*/

// 这里是我替换后的版本
template < typename Ty >
class allocator : public Allocator_base< Ty >
{
public:
  typedef Allocator_base<Ty> Mybase;
  typedef typename Mybase::value_type value_type;     //这两行，是拿到了父类定义的value_type

  typedef value_type* pointer;                        //定义了Ty的指针 在这里叫 pointer
  typedef value_type& reference;                      //定义了Ty的引用 在这里叫 reference
  typedef const value_type* const_pointer;            // const 指针
  typedef const value_type& const_reference;          // const 引用

  typedef size_t size_type;     
  typedef ptrdiff_t difference_type;

  template < typename Other >
  struct rebind
  {
    //将 allocator< Other > 定义为 other 类型
    typedef allocator< Other > other;
  };

  //---------- 这里开始算是 alocator 的各种method -----
  //--begin: 这里是获取指针的函数
  pointer address(reference Val) const
	{	// return address of mutable Val
	   return ((pointer) &(char&)Val);     //这里猜测使用char作为类型转换的中介，大概是因为char是基本类型中最小的，谁都可以转换，且都能读取到东西
	}

  const_pointer address(const_reference Val) const
  {	// return address of nonmutable Val
    return ((const_pointer) &(char&)Val);
  }
  //--end

  //--begin: 构造函数，拷贝构造，赋值操作符
  allocator() throw()
  {	// construct default allocator (do nothing)
  }

  allocator(const allocator<Ty>&) throw()
  {	// construct by copying (do nothing)
  }

  template<typename Other>
  allocator(const allocator<Other>&) throw()
  {	// construct from a related allocator (do nothing)
  }

  template<typename Other>
  allocator<Ty>& operator=(const allocator<Other>&)
  {	// assign from a related allocator (do nothing)
    return (*this);
  }
  //--end.

	//-- begin: 这里是最重要的功能函数获取内存，以及释放内存
	void deallocate(pointer Ptr, size_type)
	{
		::operator delete(Ptr);
	}

	pointer allocate(size_type Count)
	{
		return (Func_Allocate(Count, (pointer)0));			//这里调用之前的一个全局函数
	}

	pointer allocate(size_type Count, const void*)
	{
		return allocate(Count);											//这里调用了上面的函数 allocate
	}
	//--end

	//-- begin: 这里进行初始化和销毁~
	void construct(pointer Ptr, const Ty& Val)
	{	// construct object at Ptr with value Val
	  Func_Construct(Ptr, Val);
	}

	void construct(pointer Ptr, Ty&& Val)
	{	// construct object at Ptr with value Val
		::new ((void*)Ptr) Ty(::std::forward<Ty>(Val));
	}

	template<class Other>
	void construct(pointer Ptr, Other&& Val)
	{	// construct object at Ptr with value Val
		::new ((void* )Ptr) Ty(::std::forward<Other>(Val));
	}

	void destroy(pointer Ptr)
	{	// destroy object at Ptr
			Destroy(Ptr);
	}
	//-- end


	//-- begin: 获取能够存储的最大个数
	size_t max_size() const throw()
	{
		size_t Count = (size_t)(-1) / sizeof(Ty);
		return (0 < Count ? Count : 1);
	}
};


```
