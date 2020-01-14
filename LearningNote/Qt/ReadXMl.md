# 检测翻译
---
## 原因：
由于拿过来的翻译在手动随意检测中发现一些和原来翻译不一致的地方。
所以想要检测究竟有几个翻译出现了问题。

## 大致需求：
能够导出具体的对比日志，能够让人看这个对比的日志

## 大致步骤：
1. 读取两个文件
2. 进行对比
3. 导出日志

---
## 详细步骤
### 读取文件
#### 文件类型 ：xml
#### 文件结构
1. 原翻译 文件结构
```xml
<translate>
	<contents>
		<chinese>删除通道</chinese>
		<english>Delete Channel</english>
		<laos>ລົບສັນຍານ</laos>
	</contents>
</translate>
其中 contents 有很多
```
所以读取的节点
```
translate
  |_contents   -->  loop
    |_chinese english laos
```

2. 翻译后要使用的 结构
```xml
<TS version="2.0" language="uk_UA">
	<defaultcodec>System</defaultcodec>
	<context>
		<name>AlarmComboBoxItem</name>
		<message>
			<location filename="../../../src/calarmcomboboxitem.cpp" line="24"/>
			<source>删除通道</source>
			<translation>ລົບສັນຍານ</translation>
		</message>
	</context>
</TS>
这里的content有很多， 而且 message也有很多
```
所以这里的需要读取的节点
```
TS
|_ context   -->  loop
  |_message  -->  loop
    |_ source translation
```

### 进行对比
对比起来还是很有难度的， 原因：
* 原翻译文件，对于之前要使用的翻译文件进行筛选
* 有的翻译词条进行了修改
* 翻译文件中的中文进行了修改
* 有的应该也没有进行填写

##### 总结归纳下，词条对于原有的修改
* 翻译词条中的中文 会与 要使用的文件 不一致
* 翻译词条中的英文 出现缺失

##### 对于上述处理
需要进行分层：
1. 处理中文完全匹配的词条  --> 进行对比输出  
  * set of Chinese
2. 剩余中文无法完全匹配的，  对其进行英文匹配  --> 进行对比输出
  * set of All - set of Chinese
    * set of English
3. 剩余无法进行的 看看能不能进行模糊匹配吧？ --> 这个可以先不做直接输出
  * set of All - set of Chinese - set of English
    * set of other

---
## 导出日志
### 导出几种日志
#### 第一层处理： 日志导出
已经匹配的 翻译词条 一个日志， 未匹配的词条一个日志
```
已经匹配的：
--------------------------------------------------
词条   翻译     翻译行数          应用行数（应用位置）
--------------------------------------------------
```
