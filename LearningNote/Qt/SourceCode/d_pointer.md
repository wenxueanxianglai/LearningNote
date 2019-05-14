# d_ptr & q_ptr
## d_ptr 在哪里？
```C++
class QObject {
  // ...
  protected:
      QScopedPointer<QObjectData> d_ptr;
  //...
};
```
#### 为什么要用d_ptr
* 主要为了不改变导出的 C++ 类的大小
* 信息隐藏 这个应该也是主要
* 保持头文件干净?

## q_ptr 在哪里
```C++
struct QObjectData {
public:
    virtual ~QObjectData() = 0;

    QObject * q_ptr;    //Here! Here! Here! Here!

    QObject * parent;
    QObjectList children;

    uint isWidget : 1;
    uint pendTimer : 1;
    uint blockSig : 1;
    uint wasDeleted : 1;
    uint ownObjectName : 1;
    uint sendChildEvents : 1;
    uint receiveChildEvents : 1;
    uint inEventHandler : 1; //only used if QT_JAMBI_BUILD
    uint inThreadChangeEvent : 1;
    uint hasGuards : 1; //true iff there is one or more QPointer attached to this object
    uint unused : 22;
    int postedEvents;
    QMetaObject * metaObject; // assert dynamic
};
```

#### 为什么要用q_ptr
* 访问当前API的公共接口
* 换个意思说 就是 api class 与 api private class 进行绑定
* 这样 与 d_ptr 形成了双向绑定
