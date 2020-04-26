#include "MyLoader.h"

CIMOSLoader::CIMOSLoader(const std::string& strName)
	: m_Name(strName)
	, m_handler(nullptr)
{

}

CIMOSLoader::~CIMOSLoader()
{
	UnLoad();
}

bool CIMOSLoader::Load()
{
	if (IsLoad())
	{
		UnLoad();
	}

	if (m_Name.empty())
	{
		return false;
	}

	return loadLibrary();


}

bool CIMOSLoader::UnLoad()
{
	bool ret = true;
	if (IsLoad())
	{
		ret = unloadLibrary();
		if (ret)
		{
			m_handler = nullptr;
		}
	}

	return ret;
}

bool CIMOSLoader::GetFunctionPtr(const char* strFunc, FuncPtr& ptrFuc)
{
	if (!IsLoad())
	{
		return false;
	}

	FuncPtr pFun = GetProcAddress(m_handler, strFunc);
	if (pFun == nullptr)
	{
		return false;
	}

	ptrFuc = pFun;
	return true;
}

bool CIMOSLoader::GetFunctionPtr(const std::string& strFunc, FuncPtr& ptrFuc)
{
	return GetFunctionPtr(strFunc.c_str(), ptrFuc);
}

bool CIMOSLoader::loadLibrary()
{
	std::string str = m_Name;

	//备份当前工作目录
	char szCurDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(sizeof(szCurDir), szCurDir);

	int nLen = str.length();
	auto pos = str.find_last_of('\\');
	std::string substr = str.substr(0, pos+1);
	//while ('\\' != szBuf[nLen]) { nLen -= 1; }
	//szBuf[nLen + 1] = '\0';
	SetCurrentDirectory(substr.c_str());
	m_handler = LoadLibrary(str.c_str());
	if (nullptr == m_handler)
	{
		auto Error = GetLastError();
		m_error = Error;
	}

	//恢复当前工作目录
	SetCurrentDirectory(szCurDir);

	return m_handler != nullptr;
}

bool CIMOSLoader::unloadLibrary()
{
	return FreeLibrary((HMODULE)m_handler) != 0;
}


