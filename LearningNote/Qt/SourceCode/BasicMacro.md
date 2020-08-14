# Macro
```
#define  定义某个宏
\ 延伸下一行
## 连接两个字符
```
---
## 当前分页 大多都是 d_ptr q_ptr 相关

## 两个基础的模板
```C++
template <typename T> static inline T *qGetPtrHelper(T *ptr) { return ptr; }
template <typename Wrapper> static inline typename Wrapper::pointer qGetPtrHelper(const Wrapper &p) { return p.data(); }
```

## Q_DECLARE_PRIVATE
* 提供了一组 d_func() 函数，这样 不管是 const 对象 还是非const对象 都可以使用
* 这个一般在 API类中 使用， 这样构成了 class -> private class 的使用关系

```C++
#define Q_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private * >(qGetPtrHelper(d_ptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private * >(qGetPtrHelper(d_ptr)); } \
    friend class Class##Private;
```

#### 展开示例
```C++
Q_DECLARE_PRIVATE(QListView)
//-->  展开成：
// d_ptr 在QObject中： QScopedPointer<QObjectData> d_ptr;
inline QListViewPrivate* d_func() {
  return reinterpret_cast<QListViewPrivate* > qGetPtrHelper(d_ptr);
}

inline const QListViewPrivate* d_func() const {
  return reinterpret_cast<QListViewPrivate* > qGetPtrHelper(d_ptr);
}

friend class QListViewPrivate;
```


## Q_DECLARE_PRIVATE_D
```C++
#define Q_DECLARE_PRIVATE_D(Dptr, Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private * >(Dptr); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private * >(Dptr); } \
    friend class Class##Private;
```


## Q_DECLARE_PUBLIC
* 和上面的一样
* 不同的是，这个在 private class 中使用, 构成了private class --> class 的使用关系

```C++
#define #define Q_DECLARE_PUBLIC(Class)      \
    inline Class* q_func() { return static_cast<Class * >(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class * >(q_ptr); } \
    friend class Class;
```
#### 展开示例
```C++
Q_DECLARE_PUBLIC(QListView)
//-->  展开成：
//QObjectData 中有 q_ptr: QObject * q_ptr;
inline QListView* q_func() {
  return static_cast<QListView* >(q_ptr);
}

inline const QListView* q_func() const{
  return static_cast<QListView* >(q_ptr);
}

friend class QListView;
```

## Q_D
简化使用 d_ptr
```C++
#define Q_D(Class) Class##Private * const d = d_func()
```
####


## Q_Q
```C++
#define Q_Q(Class) Class * const q = q_func()
```
#### 简化使用 q_ptr
---

## Q_ENUM

## Q_PROPERTY

## QT_REQUIRE_CONFIG
```C++
/*
    The QT_CONFIG macro implements a safe compile time check for features of Qt.
    Features can be in three states:
        0 or undefined: This will lead to a compile error when testing for it
        -1: The feature is not available
        1: The feature is available
*/
#define QT_CONFIG(feature) (1/QT_FEATURE_##feature == 1)
#define QT_REQUIRE_CONFIG(feature) Q_STATIC_ASSERT_X(QT_FEATURE_##feature == 1, "Required feature " #feature " for file " __FILE__ " not available.")
```

##

## QT_BEGIN_NAMESPACE
直接可以使用 namespace
```C++
# define QT_BEGIN_NAMESPACE namespace QT_NAMESPACE {
# define QT_END_NAMESPACE }
```


---
## 简单的 set get
```cpp
#define _Set_Get_Func( keyType , KeyWord )	\
void Set##KeyWord ( keyType const& o##KeyWord ) {	\
	KeyWord = o##KeyWord; \
} \
keyType& Get##KeyWord() { \
	return KeyWord;\
}\
keyType const& Get##KeyWord() const { \
	return KeyWord;\
}\



#define Set_Get_Func(KeyWord) \
template <typename T>\
void Set##KeyWord(T const& o##KeyWord)\
{\
	KeyWord = o##KeyWord;\
}\
decltype(KeyWord)&  Get##KeyWord() { \
	return KeyWord;\
}\
const decltype(KeyWord)&  Get##KeyWord() const {	\
		return KeyWord; \
}\

```
