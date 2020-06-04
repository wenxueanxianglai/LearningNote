# rest
---
## 预备
### URI
### 是什么
是资源的唯一标识(地址，名称) URI(Uniform Resource Identifier)

#### 资源是什么
* 各种数据都可以是资源
* 例子： C中的 数据结构 的 数据。 图片，等等等，就是数据

#### 一般上的小技巧
* 使用 `_`或 `-` 可以让uri更具可读性
```
http://www.oschina.net/news/38119/oschina-translate-reward-plan
```
* 使用`/`标识资源的 层级
```
https://github.com/git/git
https://github.com/git/git/blob/master/block-sha1/sha1.h
```
* 使用 `?` 过滤资源
```
https://github.com/git/git/pulls?state=closed
http://172.16.119.91:80/cdevice-manage/device/ext?f_eq_deviceAttr.ipc.devmsUrl=172.16.64.101&&f_eq_devmsProtocol=5&&pageNo=0
```
* `,` 或 `;` 可表示同级资源

## rest 是什么
是对 资源的 一种 规范(标准，协议). 有固定格式.

## 有什么
### 无状态
通过相应的(uri)就能获取到固定的资源，不需要相应的流程
