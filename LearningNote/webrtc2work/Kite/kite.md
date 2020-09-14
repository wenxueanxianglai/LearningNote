# kite
---
## 需求
通过 某种工具  在一台机子上 控制 多台机子 启动一个脚本

## 目标
* 进行压测
* 压测对象： 跑在demo端的 

## 目标分解

如何使用Kite
* 阅读 文献
  * 了解是 什么
  * 怎么用
* 跑demo
  * 安装好环境 （优先）
  * 尝试跑demo
  * 修改demo
  
尝试编写

---
## 替代方案
如果Kite，这两天安装失败，则使用puppeteer

## puppeteer目标
* 一台机子控制多台机子（通过网络， 启动puppeteer）
* puppeteer 抓取元素
* puppeteer 通过网络 传输 抓取效果

## 目标分解
* 编写拉起来 另外一台node的脚本
* 编写puppeteer 抓取元素
  * 抓取元素
  * 监听
  
*  编写发送

---
## tasklog

### 链接
#### 控制 chrome 和 火狐的
* http://chromedriver.chromium.org/downloads
* https://github.com/mozilla/geckodriver/releases

备注： 这里放在 ```\KITE\localGrid```

#### selenium.jar 
https://www.seleniumhq.org/download/ 

这里最容易失败

### 优先： 安装好环境



```
2020-9-14 14:10:41
当前： 花了一上午安装完成，但是目前demo没办法跑起来

```

```
2020-9-14 15:57:19
任务： 优先阅读基本知识，然后尝试查看 demo为什么没有跑起来

```

```
2020-9-14 17:10:50
当前： demo可以跑起来，但是日志不知道从哪里找
任务： 上面应该是配置问题，如果仅仅是配置的问题，那就可以先阅读下文档
```

```

```

