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

与本机使用的 chrome 浏览器 版本要 一致！

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

调通 client 端 向 grid hub 节点发送脚本， grid hub 执行。

#### 尚未解决

如何 通过 js 获取所有的 node 节点
如果通过获取的 node 节点去 精准控制

#### 意外遇到的问题

当前尚未搜索到能够行之有效的方法

```
cannot reach the node for 2 tries
```

node 显示：

```
01:53:39.064 INFO [SelfRegisteringRemote$1.run] - Couldn't register this node: The hub is down or not responding: Failed to connect to /192.168.0.105:4444
```

https://github.com/SeleniumHQ/selenium/blob/selenium-3.141.59/java/server/src/org/openqa/grid/common/defaults/DefaultNodeWebDriver.json

https://github.com/SeleniumHQ/selenium/tree/selenium-3.141.59/java/server/src/org/openqa/grid/common/defaults

---

## test

使用 usingServer 可以直接控制 driver

"http://"

setInitParameter

http://192.168.0.101:4444/grid/api/hub
http://192.168.0.101:4444/grid/api/proxy
http://192.168.0.101:4444/grid/console

---

## 任务

搜索：如何 通过 selenium 的库 获取具体的 node 节点
搜索结果： 目前没有接口

```
原因：
selenium 每实例化一个 driver 实际上 对应的就是一个真实的浏览器

而 selenuim - grid 的主要功能是 向下方 node 分发 这些请求。
 但并未对外暴露接口
```

## 解决方案

#### 解决 1：

1.  在开始部署的时候： 在 client 端保存 node 节点的 ip

#### 解决 2：

2.  直接把远端所有的当成原始服务器

## 考虑场景

##### 如果仅针对 **随机的用户** 发言来说：

可以不需要获取特定的 node

- 原因： 因为 每个 driver 对应一个 浏览器，当每个用户对应一个 driver 的时候，这里就是很明显的一对一

##### 如果 一组用户都在同一台测试机上

selenium-driver 可以直接 指定 当前测试机器的 ip，作为远端 server


---
## 任务
已完成： 部署多台node 测试 控制不同的driver

正在学习： driver 尝试控制 页面元素

待研究： 尝试不同方式启动 selenium 是否能够让 driver 同时启动快一点

## 参数
---
```
disable-infobars
```
