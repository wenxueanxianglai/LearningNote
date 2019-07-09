# url
---
学习一个概念大致 步骤应该是：
* 1.从这个概念**是什么**
* 2.然后指着一个东西问 这东西是 这个概念吗？ **为什么是为什么不是？**
* 3.然后拿着东西去**用**
  * 用的 步骤 或者顺序
  * 用的时候注意的坑
* 4.然后不断地去深入了解，大致进入迭代，然后回到步骤1的过程
---

## 需要知道的预备知识 URL：
### url 是什么？
通用的说就是链接，点击这个url 我们就能进到其他地方

### url 由哪几部分组成？
1. protocol  Qurl里是scheme
2. hostname
3. port
4. path
5. parameters
6. query
7. fragment

---
## Qurl 组成
* scheme
* authority
  * user info
    * user
    * password
  * host
  * port
* path
* fragment
* query
```
ftp://tray:5uQQ_f@ftp.example.com:2021
scheme: ftp
authority:  tray:5uQQ_f@ftp.example.com:2021
  user info:  tray:5uQQ_f@
    user   :    tray
    password:   5uQQ_f
  host  :     ftp.example.com
  port  :     2021
```

### QUrlPrivate的属性]
```C++
class QUrlPrivate
{
  QString scheme;
  QString userName;
  QString password;
  QString host;
  QString path;
  QByteArray query;
  QString fragment;

  QByteArray encodedOriginal;
  QByteArray encodedUserName;
  QByteArray encodedPassword;
  QByteArray encodedPath;
  QByteArray encodedFragment;
};
```

## QUrl 解析
Qurl 解析有两种，一种 TolerantMode，一种StrictMode, 一般 TolerantMode
```C++
enum ParsingMode {
    TolerantMode,
    StrictMode
};
```
### TolerantMode 解析 主要代码
```C++
void QUrl::setUrl(const QString &url, ParsingMode parsingMode)
{
    // Tolerant preprocessing
    QString tmp = url;

    // Allow %20 in the QString variant
    tmp.replace(QLatin1String("%20"), QLatin1String(" "));

    // Percent-encode unsafe ASCII characters after host part
    int start = tmp.indexOf(QLatin1String("//"));
    if (start != -1) {
        // Has host part, find delimiter
        start += 2; // skip "//"
        const char delims[] = "/#?";
        const char * d = delims;
        int hostEnd = -1;
        while (*d && (hostEnd = tmp.indexOf(QLatin1Char(*d), start)) == -1)
            ++d;
        start = (hostEnd == -1) ? -1 : hostEnd + 1;
    } else {
        start = 0; // Has no host part
    }
    QByteArray encodedUrl;
    if (start != -1) {
        QString hostPart = tmp.left(start);
        QString otherPart = tmp.mid(start);
        encodedUrl = toPercentEncodingHelper(hostPart, ":/?#[]@!$&'()*+,;=")
                   + toPercentEncodingHelper(otherPart, ":/?#@!$&'()*+,;=");
    } else {
        encodedUrl = toPercentEncodingHelper(tmp, ABNF_reserved);
    }
    d->setEncodedUrl(encodedUrl, StrictMode);
}
```
