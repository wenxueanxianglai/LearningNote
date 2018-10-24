```
约定：
# 类名
## 接口
```
---
---
# QObject

## bool QObject::blockSignals(bool block)
If block is true, signals emitted by this object are blocked (i.e., emitting a signal will not invoke anything connected to it). If block is false, no such blocking will occur.
如果block为真，那这个对象发射的信号被阻塞。(发射信号并不会调用连接到它的任何东西)
如果block为假，任何阻塞会恢复。

The return value is the previous value of signalsBlocked().
返回值为 signalsBlocked() 之前的值

Note that the destroyed() signal will be emitted even if the signals for this object have been blocked.
注意：哪怕这个对象的信号已经被阻塞， destroyed()信号都会被发出。
