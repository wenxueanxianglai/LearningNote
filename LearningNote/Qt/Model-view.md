# model/view
## 重写view
### 1. pure virtual functions of QAbstractItemView
after public key word:
```C++
  virtual QRect visualRect(const QModelIndex &index) const = 0;
  virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) = 0;
  virtual QModelIndex indexAt(const QPoint &point) const = 0;
```
#### 1.1 visualRect：
返回index占据的视图的范围
* 如果您的项目显示在多个区域中，则visualRect应返回包含索引的**主要区域**，而不是索引可能包含，触摸或导致绘图的完整区域。
* 这里model 开始与 view 关联

#### 1.2 scrollTo:
滚动到index处，让index可见
* if necessary： 所以这个有时候**根据自己需要空实现也行**

#### 1.3 indexAt：
返回 窗口点 属于model 的 哪个index


after protect key word:
```C++
  virtual QModelIndex moveCursor(CursorAction cursorAction,
                                 Qt::KeyboardModifiers modifiers) = 0;

  virtual int horizontalOffset() const = 0;
  virtual int verticalOffset() const = 0;

  virtual bool isIndexHidden(const QModelIndex &index) const = 0;

  virtual void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) = 0;
  virtual QRegion visualRegionForSelection(const QItemSelection &selection) const = 0;
```
#### 1.4 moveCursor
这里处理的是**键盘事件**
* CursorAction 的enum在源码上就在这个纯虚函数上面(qt 4.8是这样)

#### 1.5 horizontalOffset
返回视图的水平偏移量

#### 1.6 verticalOffset
同理：返回视图的垂直偏移量

#### 1.7 isIndexHidden
判断当前index项是否隐藏，true隐藏，false不隐藏

#### 1.8 setSelection
处理用户命令，最初不太理解的话，处理鼠标点击之类的 选中命令。。。
* SelectionFlags 这里定义的enum 大部分选中行，当前什么的
* 传递过来的区域，可通过 index的 视图区域是不是包含当前该区域 判断
  ```C++
  if (index.Rect().contains(rect)) {
    // do something...
  }

  ```

### 2. 需要重载的 虚函数
```C++
void paintEvent(QPaintEvent *event)
```
#### 2.1 paintEvent
毕竟绘制事件
* 这里值得注意的也就是 painter 传入的指针不是原来自定义painter时候的 this指针 而是viewport, 下面是我的证据？

``` C++
// QTableView 的 paintEvent
void QTableView::paintEvent(QPaintEvent *event)
{
    Q_D(QTableView);
    // setup temp variables for the painting
    //        ...
    const bool rightToLeft = isRightToLeft();

    QPainter painter(d->viewport);
    //        ...
}

// QListView 的 paintEvent
void QListView::paintEvent(QPaintEvent *e)
{
    Q_D(QListView);
    if (!d->itemDelegate)
        return;
    QStyleOptionViewItemV4 option = d->viewOptionsV4();
    QPainter painter(d->viewport);
}
```
