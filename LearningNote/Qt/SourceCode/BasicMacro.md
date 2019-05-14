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
```C++
#define Q_DECLARE_PRIVATE(Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private * >(qGetPtrHelper(d_ptr)); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private * >(qGetPtrHelper(d_ptr)); } \
    friend class Class##Private;
```
### What is this
这是一个

## Q_DECLARE_PRIVATE_D
```C++
#define Q_DECLARE_PRIVATE_D(Dptr, Class) \
    inline Class##Private* d_func() { return reinterpret_cast<Class##Private * >(Dptr); } \
    inline const Class##Private* d_func() const { return reinterpret_cast<const Class##Private * >(Dptr); } \
    friend class Class##Private;
```

## Q_DECLARE_PUBLIC
```C++
#define Q_DECLARE_PUBLIC(Class)                                    \
    inline Class* q_func() { return static_cast<Class * >(q_ptr); } \
    inline const Class* q_func() const { return static_cast<const Class * >(q_ptr); } \
    friend class Class;
```

## Q_D
```C++
#define Q_D(Class) Class##Private * const d = d_func()
```
#### 为了什么？
* 主要为了不改变导出的 C++ 类的大小
* 信息隐藏
* 保持头文件干净


## Q_Q
```C++
#define Q_Q(Class) Class * const q = q_func()
```
#### 为了什么？
* 访问父类的公共接口


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



##
