# QBasicTimer
---
学习一个概念大致 步骤应该是：
* 1.从这个概念**是什么**
* 2.然后指着一个东西问 这东西是 这个概念吗？ **为什么是为什么不是？**
* 3.然后拿着东西去**用**
  * 用的 步骤 或者顺序
  * 用的时候注意的坑
* 4.然后不断地去深入了解，大致进入迭代，然后回到步骤1的过程

当前环境：**Qt 4.8**

---
## 是什么？
* QBasicTimer 是一个基础的定时器。

## 有什么？
```C++
class Q_CORE_EXPORT QBasicTimer
{
    int id;     //当前保存的是id 或者叫 handle ，就是唯一指定的当前这个timer的
public:
    inline QBasicTimer() : id(0) {}
    inline ~QBasicTimer() { if (id) stop(); }

    inline bool isActive() const { return id != 0; }
    inline int timerId() const { return id; }

    void start(int msec, QObject *obj);
    void stop();
};
```
从代码上看，QBasicTimer具有基本的使用接口
* isActive 是否在活动  
* timerId  返回当前id
* start    开始启动timer
* stop    停止timer

## 如何用？
看下说明文档：
* QBasicTimer 给对象提供 定时器事件 ()
 ```
 The QBasicTimer class provides timer events for objects.
 ```
* 除非调用stop，否则会一直触发QTimerEvent事件

## 源码
```C++
/*!
    \fn void QBasicTimer::start(int msec, QObject *object)

    Starts (or restarts) the timer with a \a msec milliseconds
    timeout.

    The given \a object will receive timer events.

    \sa stop() isActive() QObject::timerEvent()
 */
void QBasicTimer::start(int msec, QObject *obj)
{
   stop();
   if (obj)
       id = obj->startTimer(msec);
}

/*!
    Stops the timer.

    \sa start() isActive()
*/
void QBasicTimer::stop()
{
    if (id) {
        QAbstractEventDispatcher* eventDispatcher = QAbstractEventDispatcher::instance();
        if (eventDispatcher)
            eventDispatcher->unregisterTimer(id);
    }
    id = 0;
}
```
### start 代码说明
* 代码看起来很简单，
  * 就是 先停止
  * 判断对象的指针是否为真
    * 为真，则启动 并设置当前的启动id
* 这看起来就是简单的命令模式
  * 我们对QObject发送开始命令，并告诉他每隔多久启动timerevent事件
  * 但真正的代码执行不在timer这里
* 这样也就意味着，我们可以在Object对象内部调用Starttimer

### stop 代码说明
* 这里代码 主要逻辑
  * 判断id是否为真
  * 如果为真
    * 获取事件队列管理
    * 取消注册当前id
  * 最终不管怎样，id设置为0.
