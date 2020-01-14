# 乱码问题

```C++

//为各种文字处理的地方设置支持的字符集，因为QT默认字符集不支持中文
void SetCodecByName(const char *pstrName)
{
	QTextCodec * pDefaultCodec = QTextCodec::codecForName(pstrName);
	if (!pDefaultCodec)
	{
		pDefaultCodec = QTextCodec::codecForLocale();
	}
	QTextCodec::setCodecForLocale(pDefaultCodec);
	QTextCodec::setCodecForCStrings(pDefaultCodec);
	QTextCodec::setCodecForTr(pDefaultCodec);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SetCodecByName("system");//使用本地系统语言

	TestXml w;
	w.show();
	return a.exec();
}
```
