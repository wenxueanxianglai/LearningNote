# Qt4.8的某些问题

## 字符串的某些问题

## 信号关联的某些问题
* 如果某些关联不上的时候，可以尝试singal中取消形参变量，仅保留形参声明
```C++
connect(m_Display->getTreeView(), SIGNAL(clicked(const QModelIndex & index)), this, SLOT(onItemClicked(const QModelIndex & index)));
改为
connect(m_Display->getTreeView(), SIGNAL(clicked(const QModelIndex &)), this, SLOT(onItemClicked(const QModelIndex &)));
```

## 借助Qt原生的modelview完成系统架构

* 数据显示层(view)
* 数据组织层(Model)
* 数据表示层(DataObject)
* 数据层(Data Source)

## 关于Qt网络接口使用的问题
* Qt的网络接口是异步的
* 所以这时候要考虑Qt接口异步的信号是否传输成功，通过接收的信号才能算真正的成功

## 文件或目录创建的时候，如果创建路径没有权限会崩溃
* 此时，需要修改权限。
* 如果不修改权限，那么，就只能崩溃了
* Win 10 默认C盘不可写
