# 过滤
#### xml contains "内容"

#### 根据ip过滤
* ip.dst eq 172.111.111.1   


#### 打包
```bash
tcpdump -i any -w ug3.cap tcp port 80 or udp portrange 1-7000
-i any: -i 监视接口    -i any 监视所有的网路接口
-w ug3.cap: -w 输出到文件    ug3.cap  输出到这个文件中

```

#### 根据端口过滤
```bash
udp.srcport>= 30001 && udp.srcport <= 30100
```
