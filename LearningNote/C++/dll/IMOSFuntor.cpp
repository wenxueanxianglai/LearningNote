#include "IMOSFuntor.h"
#include <map>
#include <vector>
#include <utility>


IMOSFuntor::IMOSFuntor(const std::string& strSDKName, const std::string& strXPName)
	: m_pImosSdk(std::make_unique<CIMOSLoader>(strSDKName))
	, m_pImosXP(std::make_unique<CIMOSLoader>(strXPName))
{

}

IMOSFuntor::~IMOSFuntor()
{

}

bool IMOSFuntor::Init()
{
	bool ret = false;

	int ss = sizeof FuncPtr;
	int ssa = sizeof(m_pInitiate);

	ret = InitSDK_Func();
	ret = ret && InitXP_Func();


	return ret;
}

bool IMOSFuntor::InitSDK_Func()
{
	m_pImosSdk->Load();
	if (!m_pImosSdk->IsLoad())
	{
		return false;
	}

	std::map<std::string, FuncPtr*> mapFunc;
	{
		mapFunc.insert(std::make_pair("IMOS_Initiate", reinterpret_cast<FuncPtr*>(&m_pInitiate)));
		mapFunc.insert(std::make_pair("IMOS_SetOption", reinterpret_cast<FuncPtr*>(&m_pSetOption)));
		mapFunc.insert(std::make_pair("IMOS_CleanUp", reinterpret_cast<FuncPtr*>(&m_pCleanUp)));
		mapFunc.insert(std::make_pair("IMOS_Encrypt", reinterpret_cast<FuncPtr*>(&m_pEncrypt)));

		mapFunc.insert(std::make_pair("IMOS_Login", reinterpret_cast<FuncPtr*>(&m_pLogin)));

		mapFunc.insert(std::make_pair("IMOS_Logout", reinterpret_cast<FuncPtr*>(&m_pLogout)));
		mapFunc.insert(std::make_pair("IMOS_SubscribePushInfo", reinterpret_cast<FuncPtr*>(&m_pSubscribePushInfo)));
		mapFunc.insert(std::make_pair("IMOS_RegCallBackPrcFunc", reinterpret_cast<FuncPtr*>(&m_pRegCallBackPrcFunc)));
		mapFunc.insert(std::make_pair("IMOS_StartPlayer", reinterpret_cast<FuncPtr*>(&m_pStartPlayer)));

		mapFunc.insert(std::make_pair("IMOS_StopPlayer", reinterpret_cast<FuncPtr*>(&m_pStopPlayer)));

		mapFunc.insert(std::make_pair("IMOS_StartMonitor", reinterpret_cast<FuncPtr*>(&m_pStartMonitor)));
		mapFunc.insert(std::make_pair("IMOS_StopMonitor", reinterpret_cast<FuncPtr*>(&m_pStopMonitor)));
		mapFunc.insert(std::make_pair("IMOS_StartPtzCtrl", reinterpret_cast<FuncPtr*>(&m_pStartPtzCtrl)));
		mapFunc.insert(std::make_pair("IMOS_PtzCtrlCommand", reinterpret_cast<FuncPtr*>(&m_pPtzCtrlCommand)));

		mapFunc.insert(std::make_pair("IMOS_ReleasePtzCtrl", reinterpret_cast<FuncPtr*>(&m_pReleasePtzCtrl)));
		mapFunc.insert(std::make_pair("IMOS_RecordRetrieval", reinterpret_cast<FuncPtr*>(&m_pRecordRetrieval)));
		mapFunc.insert(std::make_pair("IMOS_GetRecordFileURL", reinterpret_cast<FuncPtr*>(&m_pGetRecordFileURL)));

		mapFunc.insert(std::make_pair("IMOS_UserKeepAlive", reinterpret_cast<FuncPtr*>(&m_pUserKeepAlive)));
		mapFunc.insert(std::make_pair("IMOS_QueryResourceList", reinterpret_cast<FuncPtr*>(&m_pQueryResourceList)));
	}



	for (auto it = mapFunc.begin(); it != mapFunc.end(); ++it)
	{
		if (!m_pImosSdk->GetFunctionPtr(it->first, *(it->second)))
		{
			printf("IMOSFuntor.Init: 获取 %s 地址失败.\n", it->first.c_str());
			return false;
		}
	}

	return true;
}

/*
bool IMOSFuntor::InitSDK_Func()
{
	m_pImosSdk->Load();
	if (!m_pImosSdk->IsLoad())
	{
		return false;
	}

	std::map<std::string, FuncPtr> mapFunc;
	{
		mapFunc.insert(std::make_pair("IMOS_Initiate", nullptr));
		mapFunc.insert(std::make_pair("IMOS_SetOption", nullptr));
		mapFunc.insert(std::make_pair("IMOS_CleanUp", nullptr));
		mapFunc.insert(std::make_pair("IMOS_Encrypt", nullptr));

		mapFunc.insert(std::make_pair("IMOS_Login", nullptr));

		mapFunc.insert(std::make_pair("IMOS_Logout", nullptr));
		mapFunc.insert(std::make_pair("IMOS_SubscribePushInfo", nullptr));
		mapFunc.insert(std::make_pair("IMOS_RegCallBackPrcFunc", nullptr));
		mapFunc.insert(std::make_pair("IMOS_StartPlayer", nullptr));

		mapFunc.insert(std::make_pair("IMOS_StopPlayer", nullptr));

		mapFunc.insert(std::make_pair("IMOS_StartMonitor", nullptr));
		mapFunc.insert(std::make_pair("IMOS_StopMonitor", nullptr));
		mapFunc.insert(std::make_pair("IMOS_StartPtzCtrl", nullptr));
		mapFunc.insert(std::make_pair("IMOS_PtzCtrlCommand", nullptr));

		mapFunc.insert(std::make_pair("IMOS_ReleasePtzCtrl", nullptr));
		mapFunc.insert(std::make_pair("IMOS_RecordRetrieval", nullptr));
		mapFunc.insert(std::make_pair("IMOS_GetRecordFileURL", nullptr));

		mapFunc.insert(std::make_pair("IMOS_UserKeepAlive", nullptr));
		mapFunc.insert(std::make_pair("IMOS_QueryResourceList", nullptr));
	}



	for (auto it = mapFunc.begin(); it != mapFunc.end(); ++it)
	{
		if (!m_pImosSdk->GetFunctionPtr(it->first, it->second))
		{
			printf("IMOSFuntor.Init: 获取 %s 地址失败.\n", it->first.c_str());
			return false;
		}
	}


	m_pInitiate = reinterpret_cast<decltype(m_pInitiate)>(mapFunc.find("IMOS_Initiate")->second);
	m_pInitiate = reinterpret_cast<decltype(m_pInitiate)>(mapFunc.find("IMOS_Initiate")->second);
	m_pSetOption = reinterpret_cast<decltype(m_pSetOption)>(mapFunc.find("IMOS_SetOption")->second);
	m_pCleanUp = reinterpret_cast<decltype(m_pCleanUp)>(mapFunc.find("IMOS_CleanUp")->second);
	m_pEncrypt = reinterpret_cast<decltype(m_pEncrypt)>(mapFunc.find("IMOS_Encrypt")->second);

	m_pLogin = reinterpret_cast<decltype(m_pLogin)>(mapFunc.find("IMOS_Login")->second);

	m_pLogout = reinterpret_cast<decltype(m_pLogout)>(mapFunc.find("IMOS_Logout")->second);
	m_pSubscribePushInfo = reinterpret_cast<decltype(m_pSubscribePushInfo)>(mapFunc.find("IMOS_SubscribePushInfo")->second);
	m_pRegCallBackPrcFunc = reinterpret_cast<decltype(m_pRegCallBackPrcFunc)>(mapFunc.find("IMOS_RegCallBackPrcFunc")->second);
	m_pStartPlayer = reinterpret_cast<decltype(m_pStartPlayer)>(mapFunc.find("IMOS_StartPlayer")->second);

	m_pStopPlayer = reinterpret_cast<decltype(m_pStopPlayer)>(mapFunc.find("IMOS_StopPlayer")->second);

	m_pStartMonitor = reinterpret_cast<decltype(m_pStartMonitor)>(mapFunc.find("IMOS_StartMonitor")->second);
	m_pStopMonitor = reinterpret_cast<decltype(m_pStopMonitor)>(mapFunc.find("IMOS_StopMonitor")->second);
	m_pStartPtzCtrl = reinterpret_cast<decltype(m_pStartPtzCtrl)>(mapFunc.find("IMOS_StartPtzCtrl")->second);
	m_pPtzCtrlCommand = reinterpret_cast<decltype(m_pPtzCtrlCommand)>(mapFunc.find("IMOS_PtzCtrlCommand")->second);

	m_pReleasePtzCtrl = reinterpret_cast<decltype(m_pReleasePtzCtrl)>(mapFunc.find("IMOS_ReleasePtzCtrl")->second);
	m_pRecordRetrieval = reinterpret_cast<decltype(m_pRecordRetrieval)>(mapFunc.find("IMOS_RecordRetrieval")->second);
	m_pGetRecordFileURL = reinterpret_cast<decltype(m_pGetRecordFileURL)>(mapFunc.find("IMOS_GetRecordFileURL")->second);

	m_pUserKeepAlive = reinterpret_cast<decltype(m_pUserKeepAlive)>(mapFunc.find("IMOS_UserKeepAlive")->second);
	m_pQueryResourceList = reinterpret_cast<decltype(m_pQueryResourceList)>(mapFunc.find("IMOS_QueryResourceList")->second);

	return true;
}

*/

bool IMOSFuntor::InitXP_Func()
{
	m_pImosXP->Load();
	if (!m_pImosXP->IsLoad())
	{
		return false;
	}

	std::map<std::string, FuncPtr*> mapFunc;
	{
		mapFunc.insert(std::make_pair("IMOS_SetRealtimeFluency", reinterpret_cast<FuncPtr*>(&m_pSetRealtimeFluency)));

		mapFunc.insert(std::make_pair("IMOS_SetSourceMediaDataCB", reinterpret_cast<FuncPtr*>(&m_pSetSourceMediaDataCB)));
		mapFunc.insert(std::make_pair("IMOS_SetParseVideoDataCB", reinterpret_cast<FuncPtr*>(&m_pSetParseVideoDataCB)));
		mapFunc.insert(std::make_pair("IMOS_SetParseAudioDataCB", reinterpret_cast<FuncPtr*>(&m_pSetParseAudioDataCB)));
		mapFunc.insert(std::make_pair("IMOS_SetDecodeVideoDataCB", reinterpret_cast<FuncPtr*>(&m_pSetDecodeVideoDataCB)));
		mapFunc.insert(std::make_pair("IMOS_SetDecodeAudioDataCB", reinterpret_cast<FuncPtr*>(&m_pSetDecodeAudioDataCB)));

		mapFunc.insert(std::make_pair("IMOS_IsInNat", reinterpret_cast<FuncPtr*>(&m_pIsInNat)));
		mapFunc.insert(std::make_pair("IMOS_OpenVodStream", reinterpret_cast<FuncPtr*>(&m_pOpenVodStream)));
		mapFunc.insert(std::make_pair("IMOS_StartPlay", reinterpret_cast<FuncPtr*>(&m_pStartPlay)));
		mapFunc.insert(std::make_pair("IMOS_SetDecoderTag", reinterpret_cast<FuncPtr*>(&m_pSetDecoderTag)));
		mapFunc.insert(std::make_pair("IMOS_StopPlay", reinterpret_cast<FuncPtr*>(&m_pStopPlay)));
		mapFunc.insert(std::make_pair("IMOS_PausePlay", reinterpret_cast<FuncPtr*>(&m_pPausePlay)));
		mapFunc.insert(std::make_pair("IMOS_ResumePlay", reinterpret_cast<FuncPtr*>(&m_pResumePlay)));
		mapFunc.insert(std::make_pair("IMOS_SetPlaySpeed", reinterpret_cast<FuncPtr*>(&m_pSetPlaySpeed)));
		mapFunc.insert(std::make_pair("IMOS_SetPlayedTimeEx", reinterpret_cast<FuncPtr*>(&m_pSetPlayedTimeEx)));
		mapFunc.insert(std::make_pair("IMOS_OneByOne", reinterpret_cast<FuncPtr*>(&m_pOneByOne)));

		mapFunc.insert(std::make_pair("IMOS_SetRunMsgCB", reinterpret_cast<FuncPtr*>(&m_pSetRunMsgCB)));
		mapFunc.insert(std::make_pair("IMOS_OpenDownloadCallback", reinterpret_cast<FuncPtr*>(&m_pOpenDownloadCallback)));
		mapFunc.insert(std::make_pair("IMOS_StartDownloadCallback", reinterpret_cast<FuncPtr*>(&m_pStartDownloadCallback)));
		mapFunc.insert(std::make_pair("IMOS_StopDownloadCallback", reinterpret_cast<FuncPtr*>(&m_pStopDownloadCallback)));
		mapFunc.insert(std::make_pair("IMOS_GetDownloadTime", reinterpret_cast<FuncPtr*>(&m_pGetDownloadTime)));
	}


	for (auto it = mapFunc.begin(); it != mapFunc.end(); ++it)
	{
		if (!m_pImosXP->GetFunctionPtr(it->first, *(it->second)))
		{
			printf("IMOSFuntor.Init: 获取 %s 地址失败.\n", it->first.c_str());
			return false;
		}
	}
	
	return true;
}

/*
bool IMOSFuntor::InitXP_Func()
{
	m_pImosXP->Load();
	if (!m_pImosXP->IsLoad())
	{
		return false;
	}

	std::map<std::string, FuncPtr> mapFunc;
	mapFunc.insert(std::make_pair("IMOS_SetRealtimeFluency", nullptr));

	mapFunc.insert(std::make_pair("IMOS_SetSourceMediaDataCB", nullptr));
	mapFunc.insert(std::make_pair("IMOS_SetParseVideoDataCB", nullptr));
	mapFunc.insert(std::make_pair("IMOS_SetParseAudioDataCB", nullptr));
	mapFunc.insert(std::make_pair("IMOS_SetDecodeVideoDataCB", nullptr));
	mapFunc.insert(std::make_pair("IMOS_SetDecodeAudioDataCB", nullptr));

	mapFunc.insert(std::make_pair("IMOS_IsInNat", nullptr));
	mapFunc.insert(std::make_pair("IMOS_OpenVodStream", nullptr));
	mapFunc.insert(std::make_pair("IMOS_StartPlay", nullptr));
	mapFunc.insert(std::make_pair("IMOS_SetDecoderTag", nullptr));
	mapFunc.insert(std::make_pair("IMOS_StopPlay", nullptr));
	mapFunc.insert(std::make_pair("IMOS_PausePlay", nullptr));
	mapFunc.insert(std::make_pair("IMOS_ResumePlay", nullptr));
	mapFunc.insert(std::make_pair("IMOS_SetPlaySpeed", nullptr));
	mapFunc.insert(std::make_pair("IMOS_SetPlayedTimeEx", nullptr));
	mapFunc.insert(std::make_pair("IMOS_OneByOne", nullptr));

	mapFunc.insert(std::make_pair("IMOS_SetRunMsgCB", nullptr));
	mapFunc.insert(std::make_pair("IMOS_OpenDownloadCallback", nullptr));
	mapFunc.insert(std::make_pair("IMOS_StartDownloadCallback", nullptr));
	mapFunc.insert(std::make_pair("IMOS_StopDownloadCallback", nullptr));
	mapFunc.insert(std::make_pair("IMOS_GetDownloadTime", nullptr));

	for (auto it = mapFunc.begin(); it != mapFunc.end(); ++it)
	{
		if (!m_pImosXP->GetFunctionPtr(it->first, it->second))
		{
			printf("IMOSFuntor.Init: 获取 %s 地址失败.\n", it->first.c_str());
			return false;
		}
	}

	m_pSetRealtimeFluency = reinterpret_cast<decltype(m_pSetRealtimeFluency)>(mapFunc.find("IMOS_SetRealtimeFluency")->second);

	m_pSetSourceMediaDataCB = reinterpret_cast<decltype(m_pSetSourceMediaDataCB)>(mapFunc.find("IMOS_SetSourceMediaDataCB")->second);
	m_pSetParseVideoDataCB = reinterpret_cast<decltype(m_pSetParseVideoDataCB)>(mapFunc.find("IMOS_SetParseVideoDataCB")->second);
	m_pSetParseAudioDataCB = reinterpret_cast<decltype(m_pSetParseAudioDataCB)>(mapFunc.find("IMOS_SetParseAudioDataCB")->second);
	m_pSetDecodeVideoDataCB = reinterpret_cast<decltype(m_pSetDecodeVideoDataCB)>(mapFunc.find("IMOS_SetDecodeVideoDataCB")->second);
	m_pSetDecodeAudioDataCB = reinterpret_cast<decltype(m_pSetDecodeAudioDataCB)>(mapFunc.find("IMOS_SetDecodeAudioDataCB")->second);

	m_pIsInNat = reinterpret_cast<decltype(m_pIsInNat)>(mapFunc.find("IMOS_IsInNat")->second);
	m_pOpenVodStream = reinterpret_cast<decltype(m_pOpenVodStream)>(mapFunc.find("IMOS_OpenVodStream")->second);
	m_pStartPlay = reinterpret_cast<decltype(m_pStartPlay)>(mapFunc.find("IMOS_StartPlay")->second);
	m_pSetDecoderTag = reinterpret_cast<decltype(m_pSetDecoderTag)>(mapFunc.find("IMOS_SetDecoderTag")->second);
	m_pStopPlay = reinterpret_cast<decltype(m_pStopPlay)>(mapFunc.find("IMOS_StopPlay")->second);
	m_pPausePlay = reinterpret_cast<decltype(m_pPausePlay)>(mapFunc.find("IMOS_PausePlay")->second);
	m_pResumePlay = reinterpret_cast<decltype(m_pResumePlay)>(mapFunc.find("IMOS_ResumePlay")->second);
	m_pSetPlaySpeed = reinterpret_cast<decltype(m_pSetPlaySpeed)>(mapFunc.find("IMOS_SetPlaySpeed")->second);
	m_pSetPlayedTimeEx = reinterpret_cast<decltype(m_pSetPlayedTimeEx)>(mapFunc.find("IMOS_SetPlayedTimeEx")->second);
	m_pOneByOne = reinterpret_cast<decltype(m_pOneByOne)>(mapFunc.find("IMOS_OneByOne")->second);

	m_pSetRunMsgCB = reinterpret_cast<decltype(m_pSetRunMsgCB)>(mapFunc.find("IMOS_SetRunMsgCB")->second);
	m_pOpenDownloadCallback = reinterpret_cast<decltype(m_pOpenDownloadCallback)>(mapFunc.find("IMOS_OpenDownloadCallback")->second);
	m_pStartDownloadCallback = reinterpret_cast<decltype(m_pStartDownloadCallback)>(mapFunc.find("IMOS_StartDownloadCallback")->second);
	m_pStopDownloadCallback = reinterpret_cast<decltype(m_pStopDownloadCallback)>(mapFunc.find("IMOS_StopDownloadCallback")->second);
	m_pGetDownloadTime = reinterpret_cast<decltype(m_pGetDownloadTime)>(mapFunc.find("IMOS_GetDownloadTime")->second);

	return true;
}

*/