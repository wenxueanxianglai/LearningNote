#include <iostream>
#include <Windows.h>
#include <array>
#include <stdio.h>
#include "MyLoader.h"
#include "IMOSFuntor.h"
#include <string>
#include <map>
#include <utility>

//#include <winbase.h>

void importDLL(const char* ss)
{
	//std::array<char, 128> aDll{ss};
	char Dll[128]{ 0 };

	strcpy_s(Dll, ss);

#ifdef WIN32
	//备份当前工作目录
	char szCurDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(sizeof(szCurDir), szCurDir);
	//设置当前工作目录为外厂商接入模块所在目录
	char szBuf[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szBuf, sizeof(szBuf));
	int nLen = strlen(szBuf) - 1;
	while ('\\' != szBuf[nLen]) { nLen -= 1; }
	szBuf[nLen + 1] = '\0';
	//strcat(szBuf, m_szDeviceName);
	SetCurrentDirectory(szBuf);
	auto hand = LoadLibrary(Dll);
	//恢复当前工作目录
	SetCurrentDirectory(szCurDir);

	if (NULL == hand)
	{
		//CLASSLOGEX(ERROR_LEV, "load[%s] failed, code=%d\n", szDeviceDllPath, GetLastError());
		return;
	}
#endif // WIN32

	
}

typedef void (*fibonacci_init)(
	const unsigned long long a,
	const unsigned long long b);

typedef bool (*fibonacci_next)();
typedef unsigned long long (*fibonacci_current)();
typedef unsigned (*fibonacci_index)();



int testImport()
{
	//importDLL("TestIMOS.dll");
//设置当前工作目录为外厂商接入模块所在目录
	char szBuf[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szBuf, sizeof(szBuf));
	int nLen = strlen(szBuf) - 1;
	while ('\\' != szBuf[nLen]) { nLen -= 1; }
	szBuf[nLen + 1] = '\0';
	std::string str{ szBuf };
	str += "TestIMOS.dll";

	CIMOSLoader load(str);
	load.Load();

	if (!load.IsLoad())
	{
		return -1;
	}


	//class Test
	//{
	//public:
	//	Test() {}
	//	~Test() {}

	//public:
	fibonacci_init _p_fibonacci_init{nullptr};
	fibonacci_next _p_fibonacci_next{ nullptr };
	fibonacci_current _p_fibonacci_current{ nullptr };
	fibonacci_index _p_fibonacci_index{ nullptr };
	//};

	//Test tt;

	std::map<std::string, FuncPtr*> mapFun;
//	FuncPtr ptr = reinterpret_cast<FuncPtr>(_p_fibonacci_init);
	mapFun.insert(std::make_pair("fibonacci_init", reinterpret_cast<FuncPtr*>(&_p_fibonacci_init)));
	mapFun.insert(std::make_pair("fibonacci_next", reinterpret_cast<FuncPtr*>(&_p_fibonacci_next)));
	mapFun.insert(std::make_pair("fibonacci_current", reinterpret_cast<FuncPtr*>(&_p_fibonacci_current)));
	mapFun.insert(std::make_pair("fibonacci_index", reinterpret_cast<FuncPtr*>(&_p_fibonacci_index)));

	for (auto iter = mapFun.begin(); iter != mapFun.end(); ++iter)
	{
		if (!load.GetFunctionPtr(iter->first, *(iter->second)))
			return -1;
	}

	/*
	FuncPtr func;
	bool ret = load.GetFunctionPtr("fibonacci_init", func);
	if (!ret)
		return -1;

	auto i_init = reinterpret_cast<decltypefibonacci_init>(func);



	ret = load.GetFunctionPtr("fibonacci_next", func);
	if (!ret)
		return -1;

	auto i_next = reinterpret_cast<decltype(fibonacci_next)*>(func);


	ret = load.GetFunctionPtr("fibonacci_current", func);
	if (!ret)
		return -1;

	auto i_current = reinterpret_cast<decltype(fibonacci_current)*>(func);


	ret = load.GetFunctionPtr("fibonacci_index", func);
	if (!ret)
		return -1;

	auto i_index = reinterpret_cast<decltype(fibonacci_index)*>(func);

	*/

	

	_p_fibonacci_init(1, 1);
	// Write out the sequence values until overflow.
	do {
		std::cout << _p_fibonacci_index() << ": "
			<< _p_fibonacci_current() << std::endl;
	} while (_p_fibonacci_next());
	// Report count of values written before overflow.
	std::cout << _p_fibonacci_index() + 1 <<
		" Fibonacci sequence values fit in an " <<
		"unsigned 64-bit integer." << std::endl;

			
	return 0;

}

int main()
{
	testImport();

	//设置当前工作目录为外厂商接入模块所在目录
	char szBuf[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, szBuf, sizeof(szBuf));
	int nLen = strlen(szBuf) - 1;
	while ('\\' != szBuf[nLen]) { nLen -= 1; }
	szBuf[nLen + 1] = '\0';
	std::string str{ szBuf };
	std::string strsdk  = str + "redist\\imos_sdk.dll";
	std::string strxp = str + "redist\\xp_frame.dll";

	//CIMOSLoader load(str);
	//load.Load();

	//if (!load.IsLoad())
	//{
	//	return -1;
	//}

	IMOSFuntor fot(strsdk, strxp);
	fot.Init();

	return 0;
}