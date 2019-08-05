# algorithm
---
## 关于find
普通find 的大致思路就是：
* 1. 遍历容器
* 2. 与查找元素 作对比

#### Qt 与STL的实现(Qt4.8.5  vs2010 STL)
```C++
// Qt
template <typename InputIterator, typename T>
inline InputIterator qFind(InputIterator first, InputIterator last, const T &val)
{
    while (first != last && !(*first == val))  //这里把遍历条件和 与元素对比的条件联合到了一起  
        ++first;
    return first;
}
```


```C++
//STL
template<class _InIt,
	class _Ty> inline
	_InIt _Find(_InIt _First, _InIt _Last, const _Ty& _Val)
	{	// find first matching _Val
	for (; _First != _Last; ++_First)
		if (*_First == _Val)
			break;
	return (_First);
	}
```

```C++
template <typename InputIterator, typename T>
inline InputIterator _Find(InputIterator First, InputIterator Last, const T& val)
{
  //method 1
  for( ; First != Last; ++First)
  {
    if (*First == Last) {
      break;
    }
  }
  return First;

  // method 2
  while(First != Last &&  *First != val)
    ++val;
}
```
