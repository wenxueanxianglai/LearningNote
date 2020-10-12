## 任务记录
---
## 验证性测试：
```
目的： 测试 同一个 metrics 如何发到 pushgateway

 jobName: 'test', groupings: { instance: 'xxxvalue' }           // xxxvalue 是instance
```

## 数学命令行

### 函数
---
#### increase()
针对 counter这种持续增长的数值， 截取 其中 一段时间的 增量
```
increase( node_cpu[1m])

获取 cpu 一分钟内 的 增量

```
---
#### sum()
起到 加和 作用
```
sum(increase(node_cpu[1m]))
把所有的cpu的 核 加在一起
```
