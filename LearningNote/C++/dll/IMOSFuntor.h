#pragma once
#include <string>
#include "MyLoader.h"

#include "include/sdk_func.h"
#include "include/xp_func.h"

using PFunc_Initiate = decltype(IMOS_Initiate)*;
using PFunc_SetOption = decltype(IMOS_SetOption)*;
using PFunc_CleanUp = decltype(IMOS_CleanUp)*;
using PFunc_Encrypt = decltype(IMOS_Encrypt)*;

using PFunc_Login = decltype(IMOS_Login)*;
using PFunc_Logout = decltype(IMOS_Logout)*;
using PFunc_SubscribePushInfo = decltype(IMOS_SubscribePushInfo)*;
using PFunc_RegCallBackPrcFunc = decltype(IMOS_RegCallBackPrcFunc)*;
using PFunc_StartPlayer = decltype(IMOS_StartPlayer)*;

using PFunc_StopPlayer = decltype(IMOS_StopPlayer)*;

using PFunc_StartMonitor = decltype(IMOS_StartMonitor)*;
using PFunc_StopMonitor = decltype(IMOS_StopMonitor)*;
using PFunc_StartPtzCtrl = decltype(IMOS_StartPtzCtrl)*;
using PFunc_PtzCtrlCommand = decltype(IMOS_PtzCtrlCommand)*;
	
using PFunc_ReleasePtzCtrl = decltype(IMOS_ReleasePtzCtrl)*;
using PFunc_RecordRetrieval = decltype(IMOS_RecordRetrieval)*;
using PFunc_GetRecordFileURL = decltype(IMOS_GetRecordFileURL)*;

using PFunc_UserKeepAlive = decltype(IMOS_UserKeepAlive)*;
using PFunc_QueryResourceList = decltype(IMOS_QueryResourceList)*;


//xp_func.h
using PFunc_SetRealtimeFluency = decltype(IMOS_SetRealtimeFluency)*;

using PFunc_SetSourceMediaDataCB = decltype(IMOS_SetSourceMediaDataCB)*;
using PFunc_SetParseVideoDataCB = decltype(IMOS_SetParseVideoDataCB)*;
using PFunc_SetParseAudioDataCB = decltype(IMOS_SetParseAudioDataCB)*;
using PFunc_SetDecodeVideoDataCB = decltype(IMOS_SetDecodeVideoDataCB)*;
using PFunc_SetDecodeAudioDataCB = decltype(IMOS_SetDecodeAudioDataCB)*;

using PFunc_IsInNat = decltype(IMOS_IsInNat)*;
using PFunc_OpenVodStream = decltype(IMOS_OpenVodStream)*;
using PFunc_StartPlay = decltype(IMOS_StartPlay)*;
using PFunc_SetDecoderTag = decltype(IMOS_SetDecoderTag)*;
using PFunc_StopPlay = decltype(IMOS_StopPlay)*;
using PFunc_PausePlay = decltype(IMOS_PausePlay)*;
using PFunc_ResumePlay = decltype(IMOS_ResumePlay)*;
using PFunc_SetPlaySpeed = decltype(IMOS_SetPlaySpeed)*;
using PFunc_SetPlayedTimeEx = decltype(IMOS_SetPlayedTimeEx)*;
using PFunc_OneByOne = decltype(IMOS_OneByOne)*;

using PFunc_SetRunMsgCB = decltype(IMOS_SetRunMsgCB)*;
using PFunc_OpenDownloadCallback = decltype(IMOS_OpenDownloadCallback)*;
using PFunc_StartDownloadCallback = decltype(IMOS_StartDownloadCallback)*;
using PFunc_StopDownloadCallback = decltype(IMOS_StopDownloadCallback)*;
using PFunc_GetDownloadTime = decltype(IMOS_GetDownloadTime)*;


class IMOSFuntor
{
public:
	IMOSFuntor(const std::string& strSDKName, const std::string& strXPName);
	~IMOSFuntor();

	bool Init();

	bool InitSDK_Func();
	bool InitXP_Func();

private:
	std::unique_ptr<CIMOSLoader> m_pImosSdk;
	std::unique_ptr<CIMOSLoader> m_pImosXP;

public:
	PFunc_Initiate m_pInitiate{ nullptr };
	PFunc_SetOption m_pSetOption{ nullptr };
	PFunc_CleanUp m_pCleanUp{ nullptr };
	PFunc_Encrypt m_pEncrypt{ nullptr };

	PFunc_Login m_pLogin{ nullptr };

	PFunc_Logout m_pLogout{ nullptr };
	PFunc_SubscribePushInfo m_pSubscribePushInfo{ nullptr };
	PFunc_RegCallBackPrcFunc m_pRegCallBackPrcFunc{ nullptr };
	PFunc_StartPlayer m_pStartPlayer{ nullptr };

	PFunc_StopPlayer m_pStopPlayer{ nullptr };

	PFunc_StartMonitor m_pStartMonitor{ nullptr };
	PFunc_StopMonitor m_pStopMonitor{ nullptr };
	PFunc_StartPtzCtrl m_pStartPtzCtrl{ nullptr };
	PFunc_PtzCtrlCommand m_pPtzCtrlCommand{ nullptr };

	PFunc_ReleasePtzCtrl m_pReleasePtzCtrl{ nullptr };
	PFunc_RecordRetrieval m_pRecordRetrieval{ nullptr };
	PFunc_GetRecordFileURL m_pGetRecordFileURL{ nullptr };

	PFunc_UserKeepAlive m_pUserKeepAlive{ nullptr };


	//xp
	PFunc_SetRealtimeFluency m_pSetRealtimeFluency{ nullptr };
	PFunc_QueryResourceList m_pQueryResourceList{ nullptr };
	PFunc_SetSourceMediaDataCB m_pSetSourceMediaDataCB{ nullptr };
	PFunc_SetParseVideoDataCB m_pSetParseVideoDataCB{ nullptr };
	PFunc_SetParseAudioDataCB m_pSetParseAudioDataCB{ nullptr };
	PFunc_SetDecodeVideoDataCB m_pSetDecodeVideoDataCB{ nullptr };
	PFunc_SetDecodeAudioDataCB m_pSetDecodeAudioDataCB{ nullptr };

	PFunc_IsInNat m_pIsInNat{ nullptr };
	PFunc_OpenVodStream m_pOpenVodStream{ nullptr };
	PFunc_StartPlay m_pStartPlay{ nullptr };
	PFunc_SetDecoderTag m_pSetDecoderTag{ nullptr };
	PFunc_StopPlay m_pStopPlay{ nullptr };
	PFunc_PausePlay m_pPausePlay{ nullptr };
	PFunc_ResumePlay m_pResumePlay{ nullptr };
	PFunc_SetPlaySpeed m_pSetPlaySpeed{ nullptr };
	PFunc_SetPlayedTimeEx m_pSetPlayedTimeEx{ nullptr };
	PFunc_OneByOne m_pOneByOne{ nullptr };

	PFunc_SetRunMsgCB m_pSetRunMsgCB{ nullptr };
	PFunc_OpenDownloadCallback m_pOpenDownloadCallback{ nullptr };
	PFunc_StartDownloadCallback m_pStartDownloadCallback{ nullptr };
	PFunc_StopDownloadCallback m_pStopDownloadCallback{ nullptr };
	PFunc_GetDownloadTime m_pGetDownloadTime{ nullptr };
};

