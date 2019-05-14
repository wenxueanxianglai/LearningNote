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

## 怎么进行的双向绑定
* API class 继承自QObject
  * API class 中 需要多添加一个构造函数 这个在 protected
* API private class  继承自QObjectPrivate
* 定义的 API private class  在 API class 构造函数初始化的时候new出来

```C++
//QObject.h
class Q_CORE_EXPORT QObject {
public:
    Q_INVOKABLE explicit QObject(QObject * parent=0);      
    virtual ~QObject();
public:
    QT3_SUPPORT_CONSTRUCTOR QObject(QObject * parent, const char * name);

protected:
    QObject(QObjectPrivate &dd, QObject * parent = 0);

protected:
  QScopedPointer<QObjectData> d_ptr;

  static const QMetaObject staticQtMetaObject;
};

//QObject_p.h
class Q_CORE_EXPORT QObjectPrivate : public QObjectData {

};
// QObject.cpp 实现
QObject::QObject(QObjectPrivate &dd, QObject *parent)
    : d_ptr(&dd)
{
    Q_D(QObject);
    d_ptr->q_ptr = this;
    //... other operation
}

QObject::QObject(QObject *parent, const char *name)
    : d_ptr(new QObjectPrivate)
{
    Q_D(QObject);
    qt_addObject(d_ptr->q_ptr = this);
    //... other operation
}

QObject::QObject(QObject *parent)
    : d_ptr(new QObjectPrivate)
{
    Q_D(QObject);
    d_ptr->q_ptr = this;
    //... other operation
}

```
## 为什么要这样双向绑定？
* 减少不必要的 q_ptr
  * widget 子控件之类的继承层次很深，如果仅仅每个实现自己类的private 那这样的话多了相当多的父类 ptr
* 经过继承之后，绑定交给最顶层的父类，不浪费过多内存，且保持ptr的唯一性

下面是多层级的证明：
```C++
// QWidget.h
class Q_GUI_EXPORT QWidget : public QObject, public QPaintDevice
{
public:
  explicit QWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
#ifdef QT3_SUPPORT
  QT3_SUPPORT_CONSTRUCTOR QWidget(QWidget* parent, const char* name, Qt::WindowFlags f = 0);

protected:
    QWidget(QWidgetPrivate &d, QWidget* parent, Qt::WindowFlags f);
};


// QWidget.cpp
QWidget::QWidget(QWidget *parent, Qt::WindowFlags f)
    : QObject(*new QWidgetPrivate, 0), QPaintDevice()
{
    QT_TRY {
        d_func()->init(parent, f);
    } QT_CATCH(...) {
        QWidgetExceptionCleaner::cleanup(this, d_func());
        QT_RETHROW;
    }
}


QWidget::QWidget(QWidget *parent, const char *name, Qt::WindowFlags f)
    : QObject(*new QWidgetPrivate, 0), QPaintDevice()
{
    QT_TRY {
        d_func()->init(parent , f);
        setObjectName(QString::fromAscii(name));
    } QT_CATCH(...) {
        QWidgetExceptionCleaner::cleanup(this, d_func());
        QT_RETHROW;
    }
}

QWidget::QWidget(QWidgetPrivate &dd, QWidget* parent, Qt::WindowFlags f)
    : QObject(dd, 0), QPaintDevice()
{
    Q_D(QWidget);
    QT_TRY {
        d->init(parent, f);
    } QT_CATCH(...) {
        QWidgetExceptionCleaner::cleanup(this, d_func());
        QT_RETHROW;
    }
}
```
这样，子类 使用父类的 protected构造函数对父类进行初始化
