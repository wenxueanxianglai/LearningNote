#小栗子
---
---
## 1. 场景：
在excel中制作好表单，想要复制成文本时，发现，一级二级某个字段会混淆。

* 导出前：![](./pic/excel_before.png)

* 导出后：![](./pic/text_after.png)


## 2. 解决：
在notepad中使用正则进行替换即可
```
查找目标： (^[\u4e00-\u9fa5]+)
替换为： \1\n
```
其中：
```
[\u4e00-\u9fa5] 匹配的是任意一个中文
^ 匹配行首
+ 匹配1个或多个
() 捕获这个组

则 上面的意思就是： 匹配行首第一个中文，之后重复匹配中文，如果有不是中文的字符，则终止匹配；更表面的意思就是如果行首一个中文的词，那就匹配它


\1 获取匹配的第一个捕获的组
意思是在 匹配的词后面换行
```
结果呈现：
![](./pic/Regular_after.png)


# 删除日志中的不必要项
## 1. 场景
```
18148.03/24 17:02:51.049 \I [tid:21472][CStreamRecver::OnInputStream] handle=034D14C0,dwPlayID=1,nUniplayId=0,encode=106,frameid=1262,timestamp=226800,ssrc=14172,datesize=151,video[w704,h576,type1,rate244]
```
类似于上述格式的日志有一堆，但只想要datesize(这里应该是data)

## 2. 解决
介于notepad正则有长度限制， 可以分多段操作
### 2.1
先匹配"18148.03/24 17:02:51.049 \\I"
```
"^\d+\.\d+/\d+ \d+:\d+:\d+\.\d+ \\I "
```

### 2.2
在匹配 ```[tid:21472][CStreamRecver::OnInputStream]```
```
"^\d+\.\d+/\d+ \d+:\d+:\d+\.\d+ \\I \[tid:\d+\]\[CStreamRecver::OnInputStream\] "
```

### 2.3

```
"(\w+=[0-9A-Z]+,){7}"
```

### 2.4
```
^.+(\w+=[0-9A-Z]+,){7}(datesize=\d+).+
```


```
"^.+(datesize=\d+).+"
\1
```
