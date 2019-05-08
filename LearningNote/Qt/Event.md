# QEvent
---
学习一个概念大致 步骤应该是：
* 1.从这个概念**是什么**
* 2.然后指着一个东西问 这东西是 这个概念吗？ **为什么是为什么不是？**
* 3.然后拿着东西去**用**
  * 用的 步骤 或者顺序
  * 用的时候注意的坑
* 4.然后不断地去深入了解，大致进入迭代，然后回到步骤1的过程
---
## 1. Qt的事件 是什么？
Qt事件将windows的消息 封装 成了事件

## 2. 为什么是？ (特征)
* Qt事件是一个QEvent对象
* 描述程序内部或外部发生的 **动作**
* 任何QObject对象都有具备事件处理能力

#### 2.1 QEvent 与 signal-slot 区别
* 信号的触发不会对程序行为造成影响
* 重写事件处理函数可能改变程序行为
* 事件由QObject对象进行处理
* 信号是主动产生的
* 信号则是QObject对象触发
  * 一般，信号在具体的时间处理函数 中产生
---
## 3. 使用的大致步骤
#### 3.1 大致原理步骤 (通用~)
* 在自己的类中重新实现event
* 根据event类型判断 自己想修改的事件
* 然后去做相应的事情
```C++

  //上述步骤转成差不多的伪码
  // 源码中的 event：virtual bool event(QEvent *); ----我在QObject类中找到的
  bool event(QEvent * e)
  {
    if (e->type() == (自己想要的类型))
    {
       // 处理的代码
    }
    return QWidget::event(e);   
  }
  //这里的QWidget 是因为 我写的继承自QWidget
  // 至于为什么要返回QEvent，是因为其他的事件处理，父类里面已经有很多了
```
#### 3.1.1 使用中对于当前事件的处理
处理的代码写完之后，我们可以将这个事件 进行忽略 或者 继续传递下去

  ```C++
  inline void accept() { m_accept = true; }
  inline void ignore() { m_accept = false; }

  //套入上面框架
  bool event(QEvent * e)
  {
    if (e->type() == (自己想要的类型))
    {
       //
       e->ignore();
    }
    else
    {
        return QWidget::event(e);  
    }
  }
  ```

#### 3.1 事件处理顺序
##### 3.1.1一般 组件事件处理与信号 顺序
* user做出行为
* OS转化成 Message
* QApplication 封装 Message 成 QEvent
* QApplication 发送 QEvent
* 相应组件 处理 QEvent ，发送相应signal
* QObject Slot

#### 3.1.2父子组件一般顺序
* OS转化成 Message
* QApplication 封装 Message 成 QEvent
* QApplication 发送 QEvent
* Child QWidget 处理 QEvent

#### 使用 事件过滤器 改变处理顺序
类似于家长先看看是不是给小孩儿买东西，再买完给小孩
* QApplication 封装 Message 成 QEvent
* QApplication 发送 QEvent
* 过滤器对象 处理并决定 是否继续 发送
* 如果决定发送 则 相应组件接收

```C++
TestEvent::TestEvent(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
    , m_testLineEdit(this)
{
   m_testLineEdit.installEventFilter(this);
}

bool TestEvent::eventFilter(QObject * obj, QEvent * e)
{
   // false  表示未处理， 继续传递下去， true表示 已处理
    bool ret = true;
    if ( obj == &m_testLineEdit && e->type() == QEvent::KeyPress)
    {
        qDebug() << "Widget::eventFilter";
        ret = false;
    }
    else
    {
       ret = QWidget::eventFilter(obj, e);
    }

   // return __super::eventFilter(obj, e);
    return ret;
}
```
---
## 其他使用注意的地方
#### 一个组件显示的事件顺序

```C++
        Polish = 75,                            // widget is polished
        Move = 13,                              // move widget
        Resize = 14,                            // resize widget
        Show = 17,                              // widget is shown
        ShowToParent = 26,                      // widget is shown to parent
        WindowActivate = 24,                    // window was activated
        FocusIn = 8,                            // keyboard focus received
        PolishRequest = 74,                     // widget should be polished
        MetaCall =  43,                         // meta call event
        Paint = 12,                             // paint widget
```
上述值得我们注意的几个顺序：
```
Move = 13,                              // move widget
Resize = 14,                            // resize widget
Show = 17,                              // widget is shown
ShowToParent = 26,                      // widget is shown to parent
Paint = 12,                             // paint widget
```
* 为什么要注意显示顺序？
  * 有些操作是在显示后做的，例如：某些组件的显示隐藏，需要记录之前的状态，这时候在show之后做，就行了
