# 关于递归的一些思考：
## 递归：调用自己
* 这个定义是从运行状态来定义的。

## 仅从做的事情的角度看下递归：
* 所有做的事情的步骤都是一样的。
* 有个初始步骤，这样可以有个出口
* 从这里看的话，我们往往建模都会向数列方向去靠。
  * 数列有一个初始值
  * 数列有个针对于 An -> An+1的一个关系表达式
* 遍历看起来也是这样，里面做的事情的步骤是一样的，有一个初始步骤
* 所以，如果从做事的角度来看的话，遍历和递归是一样的。

## 关于递归思考转换成代码
* 如果当前已经建模成最简单的数学表达式。诸如递推，斐波那契之类的。直接就能成为代码
* 如果是稍微复杂点的步骤，看到学弟已经晕了，这时候一定要分而治之，找到每次做事情不变的地方
  * 最简单直观的 ，相对于当前这一件事情不变的， 如果是for循环，就是那个i
  * 如果是递归，那就是那个栈是不变的，我们去看怎么返回的，就能知道哪个往往是不变的。

## 小栗子：
输出某个自然数之前的所有排列顺序。  
诸如N = 1, 输出： 1
N = 2, 输出： 1 2； 2 1
N = 3, 输出： 1 2 3； 1 3 2； 213； 231； 312； 321；

#### 分析
* 对于上述例子，我们很容易想到最简单的高中排列组合学到的排列。   

回想下：当时我们学习排列的时候怎么学习的？ 我当时学习的是：有一堆小球在地上,小球有编号，  
这边有槽，我们把球放到槽里，有多少种放的方式？   

当时并没有学公式，只是自己依次试出来，然后统计。   
尝试的步骤：
* 步骤 1：把一个球 拿过来，放到左边第一个槽，（一般都会拿编号1的球，至于为什么放左边，我是左撇子）
* 重复步骤1：放到下一个槽，直到放完
* 写出这个排列
* 我一般从最尾巴交换两个球。
* 写出这个排列   


但是从另一种角度去看：
* 我们只看槽
* 对于 **当前槽** 来说，每次动作：
* 从剩下的球中，挑选一个球， 然后放到槽里
* 然后进入下一个槽。
* 然后拿出这个球
* 重复上面的操作

这样看的好处是，横向看而不是顺序看，每个槽都遍历了这些球。

```C++
int ball = 50;    //假设球有50个
int flag[50];     //设置50个更好理解点
int slot[100];    //放置的槽
//一次槽的放置球
void SetBall(int OneSlot)
{
  for (size_t i = 0; i < ball; i++) {
    // 如果当前这个球没有被使用，则放到槽里
    if (flag[i] == 0) {     
      flag[i] = 1;              //我们使用了这个球    
      slot[OneSlot] = i + 1;    //把这个球放到槽里
    }
  }
}
```
```C++
int ball = 50;    //假设球有50个
int flag[50];     //设置50个更好理解点
int slot[100];    //放置的槽
//放置到下一个槽
void SetBall(int OneSlot)
{
  for (size_t i = 0; i < ball; i++) {
    // 如果当前这个球没有被使用，则放到槽里
    if (flag[i] == 0) {     
      flag[i] = 1;              //我们使用了这个球    
      slot[OneSlot] = i + 1;    //把这个球放到槽里

      SetBall(OneSlot + 1);     //这里放置到了下一个槽
      flag[i] = 0;              //拿出球
    }
  }
}
```

开始确定输出：
```C++
//从槽的观点去写
int flag[50];
int slot[100];
int ball = 50;


void SetBall(int OneSlot) {
  if (OneSlot == ball) {
    //print array of slot
  }
  else
  {
    for (size_t i = 0; i < ball; i++) {
       if (flag[i] == 0) {
         flag[i] = 1;
         slot[OneSlot] = i + 1;

         SetBall(OneSlot);
         flag[i] = 0;       
       }
    }
  }
}
```