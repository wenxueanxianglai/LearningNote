# QEvent
---
## Qt的 事件 是什么
Qt事件将windows的消息 封装 成了事件

## 为什么是？ (特征)
* Qt事件是一个QEvent对象
* 描述程序内部或外部发生的 **动作**
* 任何QObject对象都有具备事件处理能力

### QEvent 与 signal-slot 区别
* 信号的触发不会对程序行为造成影响
* 重写事件处理函数可能改变程序行为
* 事件由QObject对象进行处理
* 信号是主动产生的
* 信号则是QObject对象触发
  * 一般，信号在具体的时间处理函数 中产生

## 事件处理顺序
### 一般 组件事件处理与信号 顺序
* user做出行为
* OS转化成 Message
* QApplication 封装 Message 成 QEvent
* QApplication 发送 QEvent
* 相应组件 处理 QEvent ，发送相应signal
* QObject Slot

### 父子组件一般顺序
* OS转化成 Message
* QApplication 封装 Message 成 QEvent
* QApplication 发送 QEvent
* Child QWidget 处理 QEvent

### 使用 事件过滤器
类似于家长先看看是不是给小孩儿买东西，再买完给小孩
* QApplication 封装 Message 成 QEvent
* QApplication 发送 QEvent
* 过滤器对象 处理并决定 是否继续 发送
* 如果决定发送 则 相应组件接收

```C++
TestEvent::TestEvent(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
    , m_Edit(this)
{
   m_Edit.installEventFilter(this);
}

bool TestEvent::eventFilter(QObject * obj, QEvent * e)
{
   // false  表示未处理， 可以传递给原有对象， true表示 已处理
    bool ret = true;
    if ( obj == &m_Edit && e->type() == QEvent::KeyPress)
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
