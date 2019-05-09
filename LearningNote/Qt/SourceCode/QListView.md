# QListView
---
阅读以下：
```C++
virtual QRect visualRect(const QModelIndex &index) const = 0;
virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) = 0;
virtual QModelIndex indexAt(const QPoint &point) const = 0;

virtual QModelIndex moveCursor(CursorAction cursorAction,
                               Qt::KeyboardModifiers modifiers) = 0;

virtual int horizontalOffset() const = 0;
virtual int verticalOffset() const = 0;

virtual bool isIndexHidden(const QModelIndex &index) const = 0;

virtual void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) = 0;
virtual QRegion visualRegionForSelection(const QItemSelection &selection) const = 0;

void paintEvent(QPaintEvent *event)
```
---

## visualRect
```C++
QRect QListView::visualRect(const QModelIndex &index) const
{
    Q_D(const QListView);
    return d->mapToViewport(rectForIndex(index));
}

```
