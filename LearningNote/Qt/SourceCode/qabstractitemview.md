#QAbstractItemView
---
## 数据： QAbstractItemViewPrivate
```C++
class Q_AUTOTEST_EXPORT QAbstractItemViewPrivate : public QAbstractScrollAreaPrivate{
    QAbstractItemModel* model;
    QPointer<QAbstractItemDelegate> itemDelegate;
    QMap<int, QPointer<QAbstractItemDelegate> > rowDelegates;
    QMap<int, QPointer<QAbstractItemDelegate> > columnDelegates;
    QPointer<QItemSelectionModel> selectionModel;
    QItemSelectionModel::SelectionFlag ctrlDragSelectionFlag;
    bool noSelectionOnMousePress;

    QAbstractItemView::SelectionMode selectionMode;
    QAbstractItemView::SelectionBehavior selectionBehavior;

     QEditorIndexHash editorIndexHash;
     QIndexEditorHash indexEditorHash;
     QSet<QWidget*> persistent;
     QWidget * currentlyCommittingEditor;

     QPersistentModelIndex enteredIndex;
     QPersistentModelIndex pressedIndex;
     Qt::KeyboardModifiers pressedModifiers;
     QPoint pressedPosition;
     bool pressedAlreadySelected;

     //forces the next mouseMoveEvent to send the viewportEntered signal
     //if the mouse is over the viewport and not over an item
     bool viewportEnteredNeeded;

     QAbstractItemView::State state;
     QAbstractItemView::State stateBeforeAnimation;
     QAbstractItemView::EditTriggers editTriggers;
     QAbstractItemView::EditTrigger lastTrigger;

     QPersistentModelIndex root;
     QPersistentModelIndex hover;

     bool tabKeyNavigation;

 #ifndef QT_NO_DRAGANDDROP
     bool showDropIndicator;
     QRect dropIndicatorRect;
     bool dragEnabled;
     QAbstractItemView::DragDropMode dragDropMode;
     bool overwrite;
     QAbstractItemView::DropIndicatorPosition dropIndicatorPosition;
     Qt::DropAction defaultDropAction;
 #endif

 #ifdef QT_SOFTKEYS_ENABLED
     QAction* doneSoftKey;
 #endif

     QString keyboardInput;
     QElapsedTimer keyboardInputTime;

     bool autoScroll;
     QBasicTimer autoScrollTimer;
     int autoScrollMargin;
     int autoScrollCount;
     bool shouldScrollToCurrentOnShow; //used to know if we should scroll to current on show event
     bool shouldClearStatusTip; //if there is a statustip currently shown that need to be cleared when leaving.

     bool alternatingColors;

     QSize iconSize;
     Qt::TextElideMode textElideMode;

     QRegion updateRegion; // used for the internal update system
     QPoint scrollDelayOffset;

     QBasicTimer updateTimer;
     QBasicTimer delayedEditing;
     QBasicTimer delayedAutoScroll; //used when an item is clicked
     QBasicTimer delayedReset;

     QAbstractItemView::ScrollMode verticalScrollMode;
     QAbstractItemView::ScrollMode horizontalScrollMode;

     bool currentIndexSet;

     bool wrapItemText;
     mutable bool delayedPendingLayout;
     bool moveCursorUpdatedView;

 private:
     mutable QBasicTimer delayedLayout;
     mutable QBasicTimer fetchMoreTimer;
};
```

## setModel
#### 声明
```C++
virtual void setModel(QAbstractItemModel *model);
  QAbstractItemModel *model() const;
```

#### 实现
```C++
/*!
    Sets the \a model for the view to present.

    This function will create and set a new selection model, replacing any
    model that was previously set with setSelectionModel(). However, the old
    selection model will not be deleted as it may be shared between several
    views. We recommend that you delete the old selection model if it is no
    longer required. This is done with the following code:

    \snippet doc/src/snippets/code/src_gui_itemviews_qabstractitemview.cpp 2

    If both the old model and the old selection model do not have parents, or
    if their parents are long-lived objects, it may be preferable to call their
    deleteLater() functions to explicitly delete them.

    The view \e{does not} take ownership of the model unless it is the model's
    parent object because the model may be shared between many different views.

    \sa selectionModel(), setSelectionModel()
*/
void QAbstractItemView::setModel(QAbstractItemModel *model)
{
    Q_D(QAbstractItemView);   //  Get d_pointer

    if (model == d->model)    // 如果model相同，返回
        return;

    // 优先 判断 d->model 是否为空  且不是空model
    if (d->model && d->model != QAbstractItemModelPrivate::staticEmptyModel()) {
        disconnect(d->model, SIGNAL(destroyed()),
                   this, SLOT(_q_modelDestroyed()));
        disconnect(d->model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                   this, SLOT(dataChanged(QModelIndex,QModelIndex)));
        disconnect(d->model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)),
                   this, SLOT(_q_headerDataChanged()));
        disconnect(d->model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this, SLOT(rowsInserted(QModelIndex,int,int)));
        disconnect(d->model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                   this, SLOT(rowsAboutToBeRemoved(QModelIndex,int,int)));
        disconnect(d->model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                   this, SLOT(_q_rowsRemoved(QModelIndex,int,int)));
        disconnect(d->model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this, SLOT(_q_rowsInserted(QModelIndex,int,int)));
        disconnect(d->model, SIGNAL(columnsAboutToBeRemoved(QModelIndex,int,int)),
                   this, SLOT(_q_columnsAboutToBeRemoved(QModelIndex,int,int)));
        disconnect(d->model, SIGNAL(columnsRemoved(QModelIndex,int,int)),
                   this, SLOT(_q_columnsRemoved(QModelIndex,int,int)));
        disconnect(d->model, SIGNAL(columnsInserted(QModelIndex,int,int)),
                   this, SLOT(_q_columnsInserted(QModelIndex,int,int)));

        disconnect(d->model, SIGNAL(modelReset()), this, SLOT(reset()));
        disconnect(d->model, SIGNAL(layoutChanged()), this, SLOT(_q_layoutChanged()));
    }

    d->model = (model ? model : QAbstractItemModelPrivate::staticEmptyModel());

    // These asserts do basic sanity checking of the model
    Q_ASSERT_X(d->model->index(0,0) == d->model->index(0,0),
               "QAbstractItemView::setModel",
               "A model should return the exact same index "
               "(including its internal id/pointer) when asked for it twice in a row.");
    Q_ASSERT_X(!d->model->index(0,0).parent().isValid(),
               "QAbstractItemView::setModel",
               "The parent of a top level index should be invalid");

    if (d->model != QAbstractItemModelPrivate::staticEmptyModel()) {
        connect(d->model, SIGNAL(destroyed()),
                this, SLOT(_q_modelDestroyed()));
        connect(d->model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                this, SLOT(dataChanged(QModelIndex,QModelIndex)));
        connect(d->model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)),
                this, SLOT(_q_headerDataChanged()));
        connect(d->model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                this, SLOT(rowsInserted(QModelIndex,int,int)));
        connect(d->model, SIGNAL(rowsInserted(QModelIndex,int,int)),
                this, SLOT(_q_rowsInserted(QModelIndex,int,int)));
        connect(d->model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
                this, SLOT(rowsAboutToBeRemoved(QModelIndex,int,int)));
        connect(d->model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this, SLOT(_q_rowsRemoved(QModelIndex,int,int)));
        connect(d->model, SIGNAL(columnsAboutToBeRemoved(QModelIndex,int,int)),
                this, SLOT(_q_columnsAboutToBeRemoved(QModelIndex,int,int)));
        connect(d->model, SIGNAL(columnsRemoved(QModelIndex,int,int)),
                this, SLOT(_q_columnsRemoved(QModelIndex,int,int)));
        connect(d->model, SIGNAL(columnsInserted(QModelIndex,int,int)),
                this, SLOT(_q_columnsInserted(QModelIndex,int,int)));

        connect(d->model, SIGNAL(modelReset()), this, SLOT(reset()));
        connect(d->model, SIGNAL(layoutChanged()), this, SLOT(_q_layoutChanged()));
    }

    QItemSelectionModel * selection_model = new QItemSelectionModel(d->model, this);
    connect(d->model, SIGNAL(destroyed()), selection_model, SLOT(deleteLater()));
    setSelectionModel(selection_model);

    reset(); // kill editors, set new root and do layout
}
```
## visualRect 
* 这里只是个虚函数
* 返回index占据的视图的范围
