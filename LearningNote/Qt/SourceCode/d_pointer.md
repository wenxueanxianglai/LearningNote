# d_pointer

## 不使用d_pointer
```C++
class Widget {
//…
private:
Rect m_geometry;
String m_stylesheet; // New in WidgetLib 1.1
};

class Label : public Widget {
///…
String text() const { return m_text; }
private:
String m_text;
};
/*
| Label 对象在 WidgetLib 1.0的布局| Label 对象在 WidgetLib 1.1的布局 |
| m_geometry <偏移量 0> | m_geometry <偏移量 0>	|
| —————- 		      | m_stylesheet <偏移量 1>	|
| m_text <偏移量 1>    | —————-  					|
| —————- 			 | m_text <偏移量 2>		|  
 */
```
## 使用 d_pointer
```C++
//----->>>>>>>>>>>>> 使用 d_pointer    begin >>>>>>>>>>>>>>>>>>>
//前置声明
// Widget.h
class WidgetPrivate;
class Widget {
 Rect geometry() const;

private:
 WidgetPrivate * d_ptr;
};

//widget_p.h
struct WidgetPrivate {
 Rect geometry;
 String stylesheet;
};

//Widget.cpp
#include "widget_p.h"
Widget::Widget() : d_ptr(new WidgetPrivate) {
  //创建私有数据
}

Rect Widget::geoemtry() const {
// d-ptr 仅仅被类库代码访问
return d_ptr->geometry;
}

/* label.h */
class Label : public Widget {
…
String text();
private:
// 每个类维护自己的 d-pointer
LabelPrivate '''d_ptr;
};

/* label.cpp */
// 和 WidgetPrivate 不同, 我们在它自己的源文件里定义 LabelPrivate
struct LabelPrivate {
String text;
};

Label::Label()
: d_ptr(new LabelPrivate) {
}

String Label::text() {
return d_ptr->text;
}

//-----<<<<<<<<<<<<< 使用 d_pointer    end   <<<<<<<<<<<<<<<<<<
```

## d_pointer 保存 q_pointer 用来使用API的某些公用接口
```C++
//----->>>>>>>>>>>>> 使用 q_pointer    begin >>>>>>>>>>>>>>>>>>>
/* widget.h */
// 前置声明. 定义在 widget.cpp
// 或者单独的一个文件，比如 widget_p.h
class WidgetPrivate;

class Widget {
…
Rect geometry() const;
…
private:
// d-pointer 从来不在头文件被引用
// 因为WidgetPrivate没有在头文件里定义,
// 所有对它的访问都会带来编译错误
WidgetPrivate* d_ptr;
};

/* widget_p.h */ 				//(_p意味着私有)
struct WidgetPrivate {
// constructor that initializes the q-ptr
WidgetPrivate(Widget * q) : q_ptr(q) { }
Widget* q_ptr; // q-ptr that points to the API class
Rect geometry;
String stylesheet;
};

/* widget.cpp */
#include "widget_p.h"
// create private data. pass the 'this' pointer to initialize the q-ptr
Widget::Widget()
: d_ptr(new WidgetPrivate(this)) {
}

Rect Widget::geoemtry() const {
// the d-ptr is only accessed in the library code
return d_ptr->geometry;
}


/* label.h */
class Label : public Widget {
…
String text() const;
private:
LabelPrivate * d_ptr;  // each class maitains it's own d-pointer
};


// label.cpp
// Unlike WidgetPrivate, we define LabelPrivate in the source file
struct LabelPrivate {
LabelPrivate(Label * q) : q_ptr(q) { }
Label * q_ptr;
String text;
};

Label::Label()
: d_ptr(new LabelPrivate(this)) {
}

String Label::text() {
return d_ptr->text;
}
//-----<<<<<<<<<<<<< 使用 q_pointer    end   <<<<<<<<<<<<<<<<<<
```

## 修改private class 可以少一些继承层次
```C++
//----->>>>>>>>>>>>> 修改 private   begin >>>>>>>>>>>>>>>>>>>
/* widget.h */
class Widget {
public:
Widget();
…
protected:
// only sublasses may access the below
Widget(WidgetPrivate &d); // 允许子类通过他们自己的实体私有对象来初始化
WidgetPrivate * d_ptr;
};

/* widget_p.h */  // (_p means private)
struct WidgetPrivate {
WidgetPrivate(Widget * q) : q_ptr(q) { } // 构造函数初始化 q-ptr
Widget * q_ptr; // 指向API类的
Rect geometry;
String stylesheet;
};

/* widget.cpp */
Widget::Widget()
: d_ptr(new WidgetPrivate(this)) {
}

Widget::Widget(WidgetPrivate &d)
: d_ptr(&d) {
}

/* label.h */
class Label : public Widget {
public:
Label();
…
protected:
Label(LabelPrivate &d); // 允许Label的子类传递自己的私有数据
//注意 Label 没有 d_ptr！它用了父类 Widget 的 d_ptr。
};

/* label.cpp */
#include "widget_p.h" // 所以我们能够访问 WidgetPrivate

class LabelPrivate : public WidgetPrivate {
public:
String text;
};

Label::Label()
: Widget(new LabelPrivate) {
// 用我们自己的私有对象来初始化 d-pointer
}

Label::Label(LabelPrivate &d)
: Widget(d) {
}
//-----<<<<<<<<<<<<< 修改 private   end   <<<<<<<<<<<<<<<<<<
```

## 使用 Q_D 宏 来使用 private Class 
