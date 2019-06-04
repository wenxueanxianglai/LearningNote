# Qt的图形绘制
---
学习一个概念大致 步骤应该是：
* 1.从这个概念**是什么**
* 2.然后指着一个东西问 这东西是 这个概念吗？ **为什么是为什么不是？**
* 3.然后拿着东西去**用**
  * 用的 步骤 或者顺序
  * 用的时候注意的坑
* 4.然后不断地去深入了解，大致进入迭代，然后回到步骤1的过程
---
---
## QPainter
### 是什么
Qt中的画家，能够绘制各种基础图形

### 有什么
拥有绘图所需的画笔，画刷，字体

#### QPen
* 用于绘制几何图形的边缘
* 由颜色，宽度，线风格等参数组成

#### QBrush
* 用于填充几何图形的调色板
* 由颜色和填充风格组成

#### QFont
* 用于文本绘制
* 由字体组成

### 使用
#### 主要功能成员函数
* drawPoint() 绘制点
* drawLine()  绘制直线
* drawRect()  绘制矩形
* drawArc() 绘制圆弧
* drawEllipse() 绘制椭圆
* drawPie() 绘制扇形
* drawChord() 绘制弦
* drawPolygon() 绘制多边形
* drawRoundedRect() 绘制圆角矩形
* drawPolyline()  绘制折线
* drawConvexPolygon() 绘制凸多边形

#### 使用步骤
只能在 **QWidget::paintEvent** 中绘制图形
```C++
void paintEvent(QPaintEvent* e)
{
  QPainter painter(this);

  //do .....
}
```

#### 动态绘制需要的图形
* 根据需要确定参数对象
* 将参数对象保存在数据集合中
* 在paintEvent函数中遍历数据集合
* 根据参数对象绘制图形

## QPaintDevice
* Qt中的画布，QPainter的绘图板
* 所有的QWidget都继承自QPaintDevice

---
## Qt的 坐标系
### 物理坐标系
* 原点(0, 0)在左上角，单位: 像素点
* x 向右增长 ， y 向下增长

### 逻辑坐标系
* 数学模型中的抽象坐标系，单位由具体问题决定
* 坐标轴增长方向有具体问题决定

## 一些Qt的事实
* QPainter 使用逻辑坐标系绘制图形
* 逻辑坐标系中图形的大小和位置经由转换后开始 绘制到 具体设备
* 默认情况下， 逻辑坐标系和物理坐标系完全一致

## 视口与窗口
#### 视口(view port)
物理坐标系中一个任意指定的矩形

#### 窗口(window)
逻辑坐标系下对应到物理坐标系中相同矩形

#### 视口与窗口
* 视口与窗口是 不同坐标系中的 同一个矩形
* 视口与窗口中的坐标点 一一映射
* 视口与窗口能够 通过坐标变换而相互转换