#pragma once
#include <string>


// include 
# ifdef _WIN32
#include <Windows.h>
#endif

// exception
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4191)
#endif

// type
# ifdef _WIN32
using Handler = HMODULE;
using FuncPtr = FARPROC;
#endif


class CIMOSLoader
{
public:
	CIMOSLoader(const std::string& strName);
	virtual ~CIMOSLoader();

	bool Load();
	bool UnLoad();

	bool GetFunctionPtr(const std::string& strFunc, FuncPtr& ptrFuc);
	bool GetFunctionPtr(const char* strFunc, FuncPtr& ptrFuc);

	inline bool IsLoad() const { return (m_handler != nullptr); }
private:
	bool loadLibrary();
	bool unloadLibrary();

private:
	std::string m_Name;
	Handler m_handler;
	unsigned int m_error;
};
//
//m_pFunQueryResourceList = (IMOSQueryResourceList)GetProcAddress(m_hImosSdkModule, "IMOS_QueryResourceList");
//if (NULL == m_pFunQueryResourceList)
//{
//	printf("CImosManager.Init: ªÒ»°IMOS_QueryResourceListµÿ÷∑ ß∞‹.\n");
//	break;
//} 