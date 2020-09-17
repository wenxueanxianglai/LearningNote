# selenium
---
## link
https://blog.csdn.net/qq_37546891/article/details/79038559


---
## tasklog
### 调通远程
```
2020-9-16 14:15:47
当前： 依旧不行
任务： 尝试 统一所有的版本，看看是不是版本的问题
```


## 安装步骤：
### client 安装
就是 webdriver 安装
```
npm i selenium-webdriver@3.6.0
```

### driver 安装
与本机使用的 chrome浏览器 版本要 一致！
```
https://sites.google.com/a/chromium.org/chromedriver/
```

### grid 下载
下载 稳定版
```
https://www.selenium.dev/downloads/
```

## 运行
当前仅在单个机器上运行成功


## 连接
http://www.docin.com/p-698130153.html

https://www.cnblogs.com/hanxiaobei/p/7352794.html


http://www.voidcn.com/article/p-qtkihoyu-bvu.html

#### 已完成
调通 client端 向 grid hub节点发送脚本， grid hub 执行。

#### 尚未解决
如何 通过 js 获取所有的node节点
如果通过获取的node节点去 精准控制

#### 意外遇到的问题
当前尚未搜索到能够行之有效的方法

```
cannot reach the node for 2 tries
```
node显示：
```
01:53:39.064 INFO [SelfRegisteringRemote$1.run] - Couldn't register this node: The hub is down or not responding: Failed to connect to /192.168.0.105:4444
```
