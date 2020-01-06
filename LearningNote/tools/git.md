### 创建版本库
commands:
#### 1. 创建空目录
```bash
mkdir learngit
cd learngit
pwd
```

#### 2. 在当前目录建立仓库
```bash
git init
```

---
### 添加版本库
```bash
git add readme.txt
```

### 提交到仓库

```bash
git commit -m "wrote a readme file"
```
git add 可以有很多次， git commit 相当于一次性把之前所有的add 打包提交到仓库
---
### 查看仓库当前状态
```bash
git status
```
如果本地仓库的文件有某些变动没有 commit 则会提示

###  与仓库已经存储的内容 进行对比
```bash
git diff readme.txt
```
---

### 版本回退
#### 1. 查看版本
```bash
git log
git log --pretty=oneline    #简单地变成一行，只有 id和message
```
#### 2. 版本回退
```bash
git reset --hard HEAD^     # 回退至上个版本
git reset --hard HEAD^^    # 回退至上上个版本
git reset --hard HEAD~100  # 回退至上100个版本
git reset --hard c083459   # 跳转至这个版本
```

### 查看使用过得命令
```bash
git reflog
```
---
