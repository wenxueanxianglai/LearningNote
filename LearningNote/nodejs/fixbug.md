# 有些注意的问题
---
## 1. 安装 nodejs之后， cmd可使用node命令， ps不行
#### 场景
安装完node之后，在命令行使用node 命令 都可以，在 vscode中的powershell中不可以

#### 原因
powershell的默认执行策略 为Restricted， 这样就没办法加载并运行脚本等外部文件


#### 解决
```ps
 Set-ExecutionPolicy RemoteSigned
```

---
## 2. 安装 puppeteer 出现 saveError
#### 详情
```
 punpm WARN saveError ENOENT: no such file or directory, open 'C:\Users\butel987\package.json'
```

#### 解决
```
https://blog.csdn.net/qq_32068809/article/details/79512709
```
按照提示创建这个 json文件