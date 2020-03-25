#include "common.h"
#include "unidef.h"
#include "gat669proxy.h"
#include "Font2Bmp.h"
#include "UniLock.h"



s32	CGat669Proxy::s_nPort[MAX_GAT669_PORT] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
static CUniLock    g_tLock; //使接口调用同步

////////////////////////////////////////////////////////////////////////////
// BOOL ParseFileName( LPCTSTR szFileName, CString &strPath, CString &strName )
// {
// 	CString strFullName = szFileName;
// 	if ( strFullName.IsEmpty() )
// 	{
// 		return FALSE;
// 	}
// 
// 	strPath = strFullName.Left( strFullName.ReverseFind( '\\' ) );
// 	if ( strPath.IsEmpty() )
// 	{
// 		return FALSE;
// 	}
// // 	CString strAdapter = strFullName.Right( strFullName.GetLength() - 1 - strFullName.ReverseFind( '\\' ) );
// // 	if ( strAdapter.IsEmpty() )
// // 	{
// // 		return FALSE;
// // 	}
// // 	strName = strAdapter.Left( strAdapter.ReverseFind( '_' ) );
// // 	if ( strName.IsEmpty() )
// // 	{
// // 		return FALSE;
// // 	}
// 	return TRUE;
// }
// 
// BOOL APIENTRY DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpReserved)
// {
// 	if ( dwReason == DLL_PROCESS_ATTACH )
// 	{
// 		TCHAR szBuf[MAX_PATH] = { 0 };
// 		DWORD dwSize = sizeof( szBuf ) / sizeof( TCHAR );
// /*		CCommonDecoder::s_hModule = (HMODULE)hDllHandle;*/
// 		::GetModuleFileName( (HMODULE)hDllHandle, szBuf, dwSize );
// 		CString strFullName = szBuf;
// 		CGat669Proxy::s_strDllPath = strFullName.Left( strFullName.ReverseFind( '\\' ));
// 
// 		::WritePrivateProfileString( "adapter", "Path", CGat669Proxy::s_strDllPath, ".\\config.ini" );
// 	}
// 	return TRUE;
// }

static void CALLBACK  DecCBFun(s32 nPort, const s8* pBuf, s32 nSize, const FRAME_INFO& tFrameCB, s32 nUser)
{
    UNILOGD("[%d]recv gat669 callback, buf:%u size:%u,type:%d video[keyframe:%d width:%d height:%d rate:%d stamp:%d] audio[rate:%d bitwidth:%d chn:%d]",
        nPort, pBuf, nSize,tFrameCB.m_nType, tFrameCB.m_tVideo.m_bKeyFrame,tFrameCB.m_tVideo.m_nWidth, 
        tFrameCB.m_tVideo.m_nHeight,tFrameCB.m_tVideo.m_nFrameRate, tFrameCB.m_tVideo.m_nStamp,
        tFrameCB.m_tAudio.m_nSampleRate,tFrameCB.m_tAudio.m_nBitWidth,tFrameCB.m_tAudio.m_nChnNum);

	CGat669Proxy *pcGat669 = (CGat669Proxy *)nUser;
	if (pcGat669 == NULL)
	{
        UNILOGE("[%d]in gat669 proxy,nUser = NULL",nPort);
		return;
	}

	if (pcGat669->m_nPort != nPort)
	{
        UNILOGE("[%d]in gat669 proxy,port error nport:%d", pcGat669->m_nPort, nPort);
		return;
	}
		
	// 音频数据
	if(tFrameCB.m_nType == em_AUDIO16)
	{
		KDFrameInfo tFrameInfo;
		tFrameInfo.dwMediaType = KD_FRAME_AUDIO;
		tFrameInfo.dwFrameIndex = 0;		//没有回调帧序号
		tFrameInfo.pbyRawBuf = (u8 *)pBuf;
		tFrameInfo.dwRawlen = nSize;
		tFrameInfo.u.tAudio.dwSampleRate = tFrameCB.m_tAudio.m_nSampleRate;
		tFrameInfo.u.tAudio.wBitWidth = tFrameCB.m_tAudio.m_nBitWidth;
		tFrameInfo.u.tAudio.wChannels = tFrameCB.m_tAudio.m_nChnNum;
		PDECCALLBACK cbPcm = pcGat669->m_pfPCMDataCB;
		if (cbPcm)
		{
			cbPcm(nPort,&tFrameInfo, pcGat669->m_pPCMParam);
		}
	}
	else //视频数据
	{
		KDFrameInfo tFrameInfo;
		tFrameInfo.dwMediaType = KD_FRAME_VIDEO;
		tFrameInfo.dwFrameIndex = 0;		////没有回调帧序号
		tFrameInfo.pbyRawBuf = (u8 *)pBuf;
		tFrameInfo.dwRawlen = nSize;
		tFrameInfo.dwMediaTimeStamp = tFrameCB.m_tVideo.m_nStamp;
		tFrameInfo.u.tVideo.dwWidth = tFrameCB.m_tVideo.m_nWidth;
		tFrameInfo.u.tVideo.dwHeight = tFrameCB.m_tVideo.m_nHeight;
		tFrameInfo.u.tVideo.dwFrameRate	 = tFrameCB.m_tVideo.m_nFrameRate;

		switch(tFrameCB.m_nType)
		{
		case em_YUV420:
			tFrameInfo.dwMediaEncode = FRAME_DATA_I420;
			break;
		case em_RGB32:
			tFrameInfo.dwMediaEncode = FRAME_DATA_RGBA32;
			break;
		case em_YV12:
			tFrameInfo.dwMediaEncode = FRAME_DATA_YV12;
			break;
		default:
			break;
		}

		PDECCALLBACK cbYuv = pcGat669->m_pfYUVDataCB;
		if (cbYuv != NULL)
		{
			cbYuv(nPort,&tFrameInfo, pcGat669->m_pYUVParam);
		}

		PDECCALLBACK cbDecInfo = pcGat669->m_pfDecInfoCB;
		if (cbDecInfo != NULL)
		{
			tFrameInfo.pbyRawBuf = NULL;//置为NULL，避免上层使用
			tFrameInfo.dwRawlen = 0;
			cbDecInfo(nPort,&tFrameInfo, pcGat669->m_pDecInfoParam);
		}

	}
}
////////////////////////////////////////////////////////////////////////////////////

CGat669Proxy::CGat669Proxy(void)
{
#ifdef _UNIDEBUG_
    char filename[MAX_PATH] = {0};
    char filepath[MAX_PATH] = {0};
#ifdef _WINDOW
    strcpy(filepath,"D:\\");
#elif defined _ANDROID_
    strcpy(filepath,"/sdcard/");
#else
    strcpy(filepath, sCurDir);
#endif

    strcpy(filename,filepath);
    strcat(filename, "GAT669PSData.dat");
    m_fpStreamData = fopen(filename,"wb");
    strcpy(filename,filepath);
    strcat(filename, "GAT669PSFrameInfo.txt");
    m_fpStreamInfo = fopen(filename,"wt");
    strcpy(filename,filepath);
#endif

}
s32 CGat669Proxy::FoundAPort()
{
    int i;
    for( i=0;i<MAX_GAT669_PORT;i++ )
    {
        if ( 0 == s_nPort[i] )
            return i;
    }

    return -1;
}
CGat669Proxy::CGat669Proxy(const char *szCompany,void * hDll)
{//gat669_mobotix.dll

    int iPort;
	SetCreateDecoder(FALSE);
	m_bPlaying = FALSE;
	m_bFilePlaying = FALSE;
    m_bSetOsdRender = 0;
	m_dwLastError = KDPLAY_NOERROR;
	m_pfYUVDataCB = NULL;
	m_pfPCMDataCB = NULL;
	m_pfDecInfoCB = NULL;
    m_nPort       = 0;
    CAutoLock tLock(&g_tLock);

    iPort = FoundAPort();
	if ( iPort != -1 && init(szCompany,hDll) == TRUE)
	{
		m_nPort = iPort;
        s_nPort[m_nPort] = 1;
        UNILOGW("[%d]gat669:found a gat669 port", m_nPort);
		SetCreateDecoder(TRUE);
	}
	m_pOsdBuf = NULL;
	memset(&m_tOsdParam, 0, sizeof(KDOsdParam));
    memset(&m_tOsdMode, 0, sizeof(KD_OSD_MODECONFIG));
	m_bOsd = FALSE;
	InitOpenStreamParam();

#ifdef _UNIDEBUG_
    char filename[MAX_PATH] = {0};
    char filepath[MAX_PATH] = {0};
#ifdef _WINDOW
    strcpy(filepath,"D:\\");
#elif defined _ANDROID_
    strcpy(filepath,"/sdcard/");
#else
    strcpy(filepath, sCurDir);
#endif

    strcpy(filename,filepath);
    strcat(filename, "GAT669PSData.dat");
    m_fpStreamData = fopen(filename,"wb");
    strcpy(filename,filepath);
    strcat(filename, "GAT669PSFrameInfo.txt");
    m_fpStreamInfo = fopen(filename,"wt");
    strcpy(filename,filepath);
#endif
}

int	CGat669Proxy::InitOpenStreamParam()
{
	if (TRUE == m_bOsd)
	{
        m_bSetOsdRender = 0;
        m_tOsdMode.bOsd = FALSE;
        m_tOsdMode.eOsdMode = PLAYKD_OSD_MODE_RENDER | PLAYKD_OSD_MODE_SNAP | PLAYKD_OSD_MODE_RECORD;
		m_bOsd = FALSE;
		m_cGat669.GAT669_SetOsdParam(m_nPort, m_hWnd,NULL,m_bOsd);
        m_cGat669.GAT669_SetOsdParamEx(m_nPort, m_hWnd, &m_tOsdMode);
	}
	m_hWnd			= NULL;

	return KDPLAY_NOERROR;
}

CGat669Proxy::~CGat669Proxy(void)
{
	m_dwLastError = KDPLAY_NOERROR;
	uninit();
	SAFE_FREE(m_pOsdBuf);

#ifdef _UNIDEBUG_
    if (m_fpStreamData)
    {
        fclose(m_fpStreamData);
        m_fpStreamData = NULL;
    }
    if( m_fpStreamInfo )
    {
        fclose(m_fpStreamInfo);
        m_fpStreamInfo = NULL;
    }
#endif

    UNILOGW("[%d]gat669:free a gat669 port", m_nPort);
}

BOOL32 CGat669Proxy::init(const char *szCompany,void * hDll)
{
	TCHAR achDllName[MAX_PATH] = {0};
	TCHAR tmp[MAX_PATH] = {0};
    CMultiToWide change(szCompany);
    m_dwLastError = 0;
    uni_char szCurrentPath[FILE_NAME_LEN] = {0};
    kd_getcwd(szCurrentPath,SIZE_OF_ARRAY(szCurrentPath));

    //该外厂商插件为加载过，需要LOAD LIBRARY动态加载
    int iPos = rfind(szCompany,"\\");
    if( iPos >= 0 ) // 厂商名带全路径
    {
        char strPath[1024];
        memset(strPath,0x0,sizeof(strPath));
        memcpy(strPath,szCompany,iPos);
        CMultiToWide path(strPath);
        kd_setcwd(path.get_ptr(),sizeof(path));
        UNILOGW("gat669:set cwd path:%s",strPath);
        uni_sprintf(achDllName,_T("%s"),change.get_ptr());
    }
    else
    {
	    kd_getModulePath(kd_getCurrentModule((void*)DecCBFun),(TCHAR*)tmp,MAX_PATH);
        TCHAR achPath[MAX_PATH] = {0};
        uni_sprintf(achPath,_T("%s\\gat669\\%s\\"),tmp,change.get_ptr());
        kd_setcwd(achPath,sizeof(achPath));
        UNILOGW("gat669:set cwd path:%S",achPath);
	    uni_sprintf(achDllName,_T("%s\\gat669\\%s\\gat669_%s.dll"),tmp,change.get_ptr(),change.get_ptr());
    }

	if (m_cGat669.LoadDecDll(achDllName,hDll) == FALSE)
	{
        UNILOGE("[%d]gat669: load dll:%s failed", m_nPort, szCompany);
		return FALSE;
	}
    //设置回原来的目录
    kd_setcwd(szCurrentPath,sizeof(szCurrentPath));

	if (m_cGat669.GAT669_Init() == FALSE)
	{
        UNILOGE("[%d]gat669: init failed", m_nPort);
		return FALSE;
	}

	m_playspeed = PlaySpeed_1;

	return TRUE;
}

void CGat669Proxy::uninit()		//资源的反初始化
{
	UNILOGI("[%d]gat669:start uninit", m_nPort);
	if (IsCreateDecoder() == FALSE)
	{
		return;
	}

 	if (m_bPlaying == TRUE )
	{
		m_cGat669.GAT669_Stop(m_nPort);
		m_cGat669.GAT669_CloseStream(m_nPort);
	}

	if (m_bFilePlaying == TRUE)
	{
		m_cGat669.GAT669_CloseFile(m_nPort);
	}


	m_cGat669.GAT669_Clear();
	UNILOGI("[%d]gat669:start UnloadDecDll", m_nPort);
	m_cGat669.UnloadDecDll();

	m_bPlaying = FALSE;
	m_bFilePlaying = FALSE;
	SetCreateDecoder(FALSE);

    CAutoLock tLock(&g_tLock);
    s_nPort[m_nPort] = 0;
}

/******************************************************************************
函 数 名：	PLAYKD_GetVersion
功	  能：	版本信息
算法实现：
全局变量：	
参	  数： 
返 回 值：	int32_t,成功返回版本信息
-------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人    修改内容
2014/06/19	1.0			nick					创建
******************************************************************************/
int CGat669Proxy::GetVersion()
{
	if (IsCreateDecoder() == FALSE)
	{
		return FALSE;
	}
	return m_cGat669.GAT669_GetSdkVersion();
}


int CGat669Proxy::GetVersionEx(char* szVersion,int* pVerLen)
{
	m_dwLastError = KDPLAY_ERR_RETURN;
	return FALSE;
}

/******************************************************************************
函 数 名：	PLAYKD_GetFileHeadLen
功	  能：	获取头信息长度
算法实现：
全局变量：	
参	  数：	
返 回 值：	int32_t,头信息长度
-------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人    修改内容
2014/06/19	1.0			nick					创建
******************************************************************************/
int CGat669Proxy::GetFileHeadLen()
{
	m_dwLastError = KDPLAY_ERR_RETURN;
	return FALSE;
}

int CGat669Proxy::GetLastError()
{
	if (m_dwLastError != KDPLAY_NOERROR)
	{
		s32 nTempError = m_dwLastError;
		m_dwLastError = KDPLAY_NOERROR;
		return nTempError;
	}
	else
	{
		UNILOGE("[%d]m_cGat669.GAT669_GetLastError():%s\n", m_nPort, m_cGat669.GAT669_GetLastError());
	}
}
BOOL32  CGat669Proxy::StartStream(int8_t* pHead,int nHeadLen,int nbufferlen)
{
	if (IsCreateDecoder() == FALSE)
	{
        UNILOGE("[%d]gat669:not created", m_nPort);
		return FALSE;
	}
#ifdef _UNIDEBUG_
    if (m_fpStreamData)
    {
        fwrite((unsigned char*)pHead, 1,nHeadLen,m_fpStreamData);
        fflush(m_fpStreamData);
    }
    if( m_fpStreamInfo )
    {
        int len;
        char strInfo[1024];
        memset(strInfo,0x0,sizeof(strInfo));
        sprintf(strInfo,"head-framelen:%u\n",nHeadLen);
        len = strlen(strInfo);
        len = fwrite(strInfo, 1,len,m_fpStreamInfo);
        fflush(m_fpStreamInfo);
        len = 0;
    }
#endif
	BOOL32 bRet = FALSE;
	bRet = m_cGat669.GAT669_OpenStream(m_nPort,(u8*)pHead,nHeadLen,nbufferlen);
	if (bRet == TRUE)
	{
		m_bPlaying = TRUE;
	}
    UNILOGE("[%d]gat669:open stream ret:%d",m_nPort,bRet);

	return bRet;
}

BOOL32  CGat669Proxy::SetStreamMode(int nmode)
{
	if( nmode != 1 && nmode != 2 )
	{
		m_dwLastError = KDPLAY_PARA_OVER;
		return FALSE;
	}
	
    return m_cGat669.GAT669_SetStreamOpenMode(m_nPort,nmode);
}

BOOL32  CGat669Proxy::StopStream()
{
	if(m_bPlaying == FALSE)
	{
		return TRUE;
	}
	m_bPlaying = FALSE;

#ifdef _UNIDEBUG_
    if (m_fpStreamData)
    {
        fclose(m_fpStreamData);
        m_fpStreamData = NULL;
    }
    if( m_fpStreamInfo )
    {
        fclose(m_fpStreamInfo);
        m_fpStreamInfo = NULL;
    }
#endif
	InitOpenStreamParam();

	return m_cGat669.GAT669_CloseStream(m_nPort);
}

BOOL32  CGat669Proxy::PlaySound()
{
	BOOL32 bRet = FALSE;
	//m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;

	bRet =  m_cGat669.GAT669_SetAudioMute(m_nPort,FALSE) ;

	return bRet;
}

BOOL  CGat669Proxy::PlaySoundEx(char* pszID[KD_MAX_KDAP_DEVICENUM], int nCount)
{
	BOOL32 bRet = FALSE;

	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return bRet;
}

BOOL32  CGat669Proxy::StopSound()
{
	BOOL32 bRet = FALSE;
	//m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	bRet =  m_cGat669.GAT669_SetAudioMute(m_nPort,TRUE) ;
	return bRet;
}

BOOL32  CGat669Proxy::StartFile(const char* szfile)
{
	int info = 0;
	if (IsCreateDecoder() == FALSE)
	{
        UNILOGE("[%d]gat669:not created", m_nPort);
		return FALSE;
	}
	BOOL32 bRet = FALSE;
	bRet = m_cGat669.GAT669_OpenFile(m_nPort,(s8*)szfile);
	if (bRet == TRUE)
	{
		m_bFilePlaying = TRUE;
	}
	else
	{
//		info = m_cGat669.GAT669_GetLastError()
	}
	return bRet;
}

BOOL32  CGat669Proxy::StopFile()
{
	if (m_bFilePlaying == FALSE)
	{
		return TRUE;
	}
	m_bFilePlaying = FALSE;

	InitOpenStreamParam();

	return m_cGat669.GAT669_CloseFile(m_nPort);
}

BOOL32  CGat669Proxy::PlayWndStart(void* hwnd)
{
	BOOL bRet = FALSE;
	int dwRet = KDPLAY_NOERROR;
	if (m_bFilePlaying== FALSE && m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
	//在play之前设置osd，需要记录状态信息;窗口句柄发生变化先关闭先前句柄
	if (m_bOsd == TRUE)
	{
		if (m_hWnd != NULL && hwnd != m_hWnd)
		{
			//hWnd change, reopen osd hook
			dwRet = m_cGat669.GAT669_SetOsdParam(m_nPort, m_hWnd,NULL,FALSE);
			if (KDPLAY_NOERROR != dwRet)
			{
				UNILOGE("[%d]<%s> GAT669_SetOsdParam ret: %d", m_nPort, __FUNCTION__, dwRet);
			}
            KD_OSD_MODECONFIG tOsdMode = {0};
            tOsdMode.wStructSize = sizeof(KD_OSD_MODECONFIG);
            tOsdMode.bOsd = FALSE;
            tOsdMode.eOsdMode = PLAYKD_OSD_MODE_RENDER | PLAYKD_OSD_MODE_SNAP | PLAYKD_OSD_MODE_RECORD;
            m_cGat669.GAT669_SetOsdParamEx(m_nPort, m_hWnd, &tOsdMode);
			if (KDPLAY_NOERROR != dwRet)
			{
				UNILOGE("[%d]<%s> GAT669_SetOsdParamEx ret: %d", m_nPort, __FUNCTION__, dwRet);
			}
		}
		if (m_hWnd == NULL && hwnd != NULL)
		{
			//osd hook was called beford play
            if (m_bSetOsdRender == 1)
            {
                dwRet = m_cGat669.GAT669_SetOsdParam(m_nPort,hwnd,&m_tOsdParam,m_bOsd);
                if (KDPLAY_NOERROR != dwRet)
                {
                    UNILOGE("[%d]<%s> GAT669_SetOsdParam ret: %d", m_nPort, __FUNCTION__, dwRet);
                }
            }
            else if (m_bSetOsdRender == 2)
            {
                dwRet = m_cGat669.GAT669_SetOsdParamEx(m_nPort,hwnd,&m_tOsdMode);
                if (KDPLAY_NOERROR != dwRet)
                {
                    UNILOGE("[%d]<%s> GAT669_SetOsdParamEx ret: %d", m_nPort, __FUNCTION__, dwRet);
                }
            }
		}
	}
	bRet = m_cGat669.GAT669_Play(m_nPort,(u32)hwnd);
	if (TRUE == bRet)
	{
		m_hWnd = hwnd;
	}
	return bRet;
}

BOOL32  CGat669Proxy::PlayWndStop()
{
	if (m_bFilePlaying== FALSE && m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
	return m_cGat669.GAT669_Stop(m_nPort);
}

BOOL32  CGat669Proxy::SetPlayTime(int ntime)
{
	if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
	return m_cGat669.GAT669_SetReplayPos(m_nPort,ntime/1000);
}

BOOL32  CGat669Proxy::SetPlayPos(float fpos)
{
	if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
	s32 nTime = m_cGat669.GAT669_GetRecordTime(m_nPort) * fpos;
	return m_cGat669.GAT669_SetReplayPos(m_nPort,nTime);
}

uint32_t	CGat669Proxy::GetTotalFrameNum()
{
	if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return KDPLAY_ERR_RETURN;
	}
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return KDPLAY_ERR_RETURN;
}

uint32_t	CGat669Proxy::GetTotalTime()
{
	if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return KDPLAY_ERR_RETURN;
	}
	return m_cGat669.GAT669_GetRecordTime(m_nPort) * 1000;
}

BOOL32  CGat669Proxy::SetFileEndCallBack(PFILEENDCALLBACK cb,void* context)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::SetRunTimeInfoCallBack( PRunTimeInfoCBFun pPRunTimeInfoCBFun, void *pContext)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::GetKeyFramePos(int	nValue, int nType, PKD_FRAME_POS pFramePos)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}
BOOL32  CGat669Proxy::GetNextKeyFramePos(int	nValue, int nType, PKD_FRAME_POS pFramePos)
{	
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}
uint32_t	CGat669Proxy::GetCurrentFrameRate()
{ 
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return KDPLAY_ERR_RETURN;
}
float CGat669Proxy::GetPlayPos()
{
	if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return -1;
	}
	s32 nTotalTime = m_cGat669.GAT669_GetRecordTime(m_nPort);
	if (nTotalTime == 0)
	{
		OspPrintf(TRUE,FALSE,"CGat669Proxy.GetPlayPos nTotalTime is 0,error:%s\n",
			m_cGat669.GAT669_GetLastError());
		return 0;
	}
	return (float)m_cGat669.GAT669_GetReplayPos(m_nPort) / nTotalTime;
}
uint32_t CGat669Proxy::GetPlayTime()
{
	if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return KDPLAY_ERR_RETURN;
	}
	return m_cGat669.GAT669_GetReplayPos(m_nPort) * 1000;
}

uint32_t	CGat669Proxy::GetPlayedFrames()
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return KDPLAY_ERR_RETURN;
}

BOOL  CGat669Proxy::StartLocalRecordExt(const char* szRecFileName,int nRecordType,int iStreamType,int iFileLen,BOOL bFirstVideoFrame)
{
    /*
	if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
    */
    //GAT669支持文件和流的录像。
	return m_cGat669.GAT669_StartDataRecord(m_nPort,(s8*)szRecFileName);
}

BOOL32  CGat669Proxy::StartLocalRecord(const char* szRecFileName)
{
    /*
	if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
    */
    //GAT669支持文件和流的录像。
	return m_cGat669.GAT669_StartDataRecord(m_nPort,(s8*)szRecFileName);
}

BOOL32  CGat669Proxy::StopLocalRecord()
{
    /*
	if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
    */
	return m_cGat669.GAT669_StopDataRecord(m_nPort);
}
BOOL32  CGat669Proxy::SetAudioVolume(int wVolume)
{
	if (m_bFilePlaying == FALSE && m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
	return m_cGat669.GAT669_SetAudioVolume(m_nPort,wVolume);
}
uint32_t	CGat669Proxy::GetAudioVolume()
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return KDPLAY_ERR_RETURN;
}

BOOL32  CGat669Proxy::SetAudioMutex(bool bmutex)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return KDPLAY_ERR_RETURN;
}

BOOL32  CGat669Proxy::AdjustWaveAudio(int ncoffient)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::Snapshot(void* hWnd)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL	CGat669Proxy::GetBmp(char* pBitmap, int nBufSize, int* pBmpSize)
{
	BOOL32 bRes = FALSE;
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;

	return bRes;
}

BOOL32  CGat669Proxy::SaveSnapshot(const char *szPicFileName, EImageType ePicType)
{
	if (m_bFilePlaying == FALSE && m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
	return m_cGat669.GAT669_SnapShot(m_nPort,(s8*)szPicFileName,ePicType);
}

BOOL32  CGat669Proxy::CatchResizePic(const int8_t *sFileName, int lTargetWidth, int lTargetHeight, EImageType ePicfomat)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}
BOOL32  CGat669Proxy::SetDrawCallBack(PDRAWCALLBACK pFunc, void *pParam)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::SetPlaySpeed(emPlaySpeed ePlayRate)
{
	/*if (m_bFilePlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}*/
	enum em_GAT669_PlaySpeed eSpeed = em_NORMAL;
	switch( ePlayRate )
	{
	case PlaySpeed_1:
		{
			eSpeed = em_NORMAL; 
			break;
		}
	case PlaySpeed_2:
		{
			eSpeed = em_FAST_2;
			break;
		}
	case PlaySpeed_1_div_2:
		{
			eSpeed = em_SLOW_2;
			break;
		}
	case PlaySpeed_4:
		{
			eSpeed = em_FAST_4;
			break;
		}
	case PlaySpeed_1_div_4:
		{
			eSpeed = em_SLOW_4;
			break;
		}
	case PlaySpeed_8:
		{
			eSpeed = em_FAST_8;
			break;
		}
	case PlaySpeed_1_div_8:
		{
			eSpeed = em_SLOW_8;
			break;
		}
    case PlaySpeed_1_div_16:
		{
			eSpeed = em_SLOW_16;
			break;
		}
	case PlaySpeed_16:
		{
			eSpeed = em_FAST_16;
			break;
		}
	default:
		m_dwLastError = KDPLAY_PARA_OVER;
		return FALSE;
	}
	return m_cGat669.GAT669_ReplaySpeed(m_nPort,eSpeed);
}

BOOL32	CGat669Proxy::Fast()
{
	if (m_playspeed >= PlaySpeed_16)
	{
		m_dwLastError = KDPLAY_PARA_OVER;
		return FALSE;
	}
	m_playspeed = (int)m_playspeed+1;
	
	return SetPlaySpeed((emPlaySpeed)m_playspeed);
}

BOOL32	CGat669Proxy::Slow()
{
	if (m_playspeed < PlaySpeed_1_div_16)
	{
		m_dwLastError = KDPLAY_PARA_OVER;
		return FALSE;
	}
	m_playspeed = (int)m_playspeed-1;

	return SetPlaySpeed((emPlaySpeed)m_playspeed);
}

BOOL32  CGat669Proxy::SetPlayPause(BOOL32 bPause)
{
	if (m_bFilePlaying == FALSE && m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
	return m_cGat669.GAT669_Pause(m_nPort,bPause);
}

BOOL32  CGat669Proxy::OneByOne()
{
	/*
	if (m_bFilePlaying == FALSE && m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
	*/
	return m_cGat669.GAT669_OneByOne(m_nPort);
}

BOOL32  CGat669Proxy::PlayOneBack()
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::RevertPlay()
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::SetYUVDataCallback(PDECCALLBACK pFun, void *pParam,bool bRender)
{
	BOOL32 bRes = FALSE;
	if(NULL == pFun)
	{
        if ( NULL == m_pfDecInfoCB)
        {
            bRes =  m_cGat669.GAT669_SetDecCallBack(m_nPort, NULL, NULL);
        }
        else
        {
            bRes = TRUE;
        }
	}
	else
	{
		bRes = m_cGat669.GAT669_SetDecCallBack(m_nPort, DecCBFun, (s32)this);
	}

    if(TRUE == bRes)
    {
        m_pfYUVDataCB = pFun;
        m_pYUVParam = pParam;
    }

	return bRes;
}

BOOL32  CGat669Proxy::SetDecInfoCallback(PDECCALLBACK pFun, void *pParam)
{
	BOOL32 bRes = FALSE;
	if(NULL == pFun)
	{
        if ( NULL == m_pfYUVDataCB)
        {
            bRes =  m_cGat669.GAT669_SetDecCallBack(m_nPort, NULL, NULL);
        }
        else
        {
            bRes = TRUE;
        }
	}
	else
	{
		bRes = m_cGat669.GAT669_SetDecCallBack(m_nPort, DecCBFun, (s32)this);
	}

    if(TRUE == bRes)
    {
        m_pfDecInfoCB = pFun;
        m_pDecInfoParam = pParam;

    }
	return bRes;
}

BOOL32  CGat669Proxy::SetPCMDataCallback(PDECCALLBACK pFun, void *pParam,bool bRender)
{
	BOOL32 bRes = FALSE;
	if(NULL == pFun)
	{
		bRes =  m_cGat669.GAT669_SetDecCallBack(m_nPort, NULL, NULL);
	}
	else
	{
		bRes = m_cGat669.GAT669_SetDecCallBack(m_nPort, DecCBFun, (s32)this);
	}

	m_pfPCMDataCB = pFun;
	m_pPCMParam = pParam;

	return bRes;
}

BOOL32  CGat669Proxy::SetRawDataCallback(PRAWDATACALLBACK pFun, void *pParam)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::SetEncTypeChangeCallBack(PENCCALLBACK pFun,void *pParam)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::InputStreamData(void *pData, int dwDataSize,uint32_t dwFrameID)
{
#ifdef _UNIDEBUG_
    if (m_fpStreamData)
    {
        fwrite((unsigned char*)pData, 1,dwDataSize,m_fpStreamData);
        fflush(m_fpStreamData);
    }
    if( m_fpStreamInfo )
    {
        int len;
        char strInfo[1024];
        memset(strInfo,0x0,sizeof(strInfo));
        sprintf(strInfo,"framelen:%u\n",dwDataSize);
        len = strlen(strInfo);
        len = fwrite(strInfo, 1,len,m_fpStreamInfo);
        fflush(m_fpStreamInfo);
        len = 0;
    }
#endif

	if (m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}

	return m_cGat669.GAT669_InputVideoData(m_nPort,(u8*)pData,dwDataSize);
}

BOOL32  CGat669Proxy::InputVideoData(KDTRawData *pVData)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::InputAudioData(KDTRawData *pAData)
{
	if ( m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
	return m_cGat669.GAT669_InputAudioData(m_nPort,(u8*)pAData->pData,pAData->dwDataSize);
}

BOOL32  CGat669Proxy::GetColor(uint32_t nRegionNum, uint32_t* pBrightness,uint32_t* pContrast,uint32_t* pSaturation,uint32_t* pHue)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::SetColor(int nRegionNum,int nBrightness,int nContrast,int nSaturation, int nHue)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::SetDisplayRegion(int nRegionNum, KDRECT* pSrcRect, void* hDestWnd, BOOL32 bEnable)
{

	//m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;

	return m_cGat669.GAT669_SetZoomWnd(m_nPort,(u32)hDestWnd,(u32*)pSrcRect,nRegionNum,bEnable);
}

BOOL32  CGat669Proxy::RefreshPlay (int nRegionNum)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::VerticalSyncEnable(BOOL32 bEnable)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::GetPictureSize(uint32_t* pWidth, uint32_t* pHeight)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::SetRotateAngle(int nrotateType)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::GetDecoderStatis(TDecStatis* pKdvDecStatis)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;
}

BOOL32  CGat669Proxy::DenoiseFilter( BOOL32  bEnable, int dwLevel)
{
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
	return FALSE;;
}

BOOL32  CGat669Proxy::ResetBuffer(int buffertype)
{
    return m_cGat669.GAT669_ReSetBuffer(m_nPort);
}

BOOL32 CGat669Proxy::GetSourceBufferRemain(int iType)
{
	return m_cGat669.GAT669_GetBuffValue(m_nPort,iType);
}

BOOL32  CGat669Proxy::SetDecoderMode(int cDecoderMode)
{
	if( cDecoderMode != 1 && cDecoderMode != 3 )
	{
		m_dwLastError = KDPLAY_PARA_OVER;
		return FALSE;
	}
	if( cDecoderMode == 3 )
		cDecoderMode = 1;

    return m_cGat669.GAT669_SetStreamOpenMode(m_nPort,cDecoderMode);
}

BOOL CGat669Proxy::SetOsdParam( KDOsdParam* ptOsdParam, BOOL bOsd)
{
	BOOL bRet = TRUE;
	int dwRet = KDPLAY_NOERROR;

	if (m_bFilePlaying== FALSE && m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
    if (m_bSetOsdRender == 2)
    {
        UNILOGE("[%d]<%s> already set osd", m_nPort, __FUNCTION__);
        return KDPLAY_ORDER_ERROR;
    }

	if (NULL == ptOsdParam && TRUE == bOsd)
	{
		m_dwLastError = KDPLAY_PARA_OVER;
		return FALSE;
	}

	if ((NULL != m_hWnd && TRUE == ::IsWindow((HWND)m_hWnd)) || FALSE == bOsd)
	{
		dwRet = m_cGat669.GAT669_SetOsdParam( m_nPort, m_hWnd,ptOsdParam,bOsd);
		if (KDPLAY_NOERROR != dwRet)
		{
			m_dwLastError = dwRet;
			return FALSE;
		}
	}
	if (KDPLAY_NOERROR == dwRet)
	{ 
        if ( TRUE == bOsd)
        {
            if ((NULL == ptOsdParam->pOsdBuf || 0 >= ptOsdParam->nOsdBuf) &&
                (NULL == m_tOsdParam.pOsdBuf || 0 >= m_tOsdParam.nOsdBuf))
            {
                UNILOGE("[%d]<CVidPlyer::SetOsd> set buf:%p,len:%d; osd buf: %p, len:%d",m_nPort, ptOsdParam->pOsdBuf , ptOsdParam->nOsdBuf,
                    m_tOsdParam.pOsdBuf, m_tOsdParam.nOsdBuf);
                m_dwLastError = KDPLAY_PARA_POINT_NULL;
                return FALSE;
            }

            if (m_tOsdParam.nOsdBuf < ptOsdParam->nOsdBuf)
            {
                SAFE_FREE(m_pOsdBuf);
            }
            if (NULL == m_pOsdBuf && ptOsdParam->nOsdBuf != 0)
            {
                m_pOsdBuf = (char*)malloc(ptOsdParam->nOsdBuf);
                m_tOsdParam.pOsdBuf = m_pOsdBuf;
                m_tOsdParam.nOsdBuf = ptOsdParam->nOsdBuf;
            }
            if (NULL != m_pOsdBuf && ptOsdParam->nOsdBuf != 0)
            {
                memcpy(m_pOsdBuf, ptOsdParam->pOsdBuf, ptOsdParam->nOsdBuf);
            }
            //else
            //{
            //	memset(&m_tOsdParam.tOsdParam, 0, sizeof(KDRECT));
            //}
            memcpy(&m_tOsdParam.tOsdParam, &ptOsdParam->tOsdParam, sizeof(KDRECT));
        }
       
		m_bOsd = bOsd;
        if (bOsd == TRUE)
        {
            m_bSetOsdRender = 1;
        }
        else
            m_bSetOsdRender = 0;
	}
	return bRet;
}

BOOL CGat669Proxy::SetOsdParamEx( KD_OSD_MODECONFIG* pMode)
{
	BOOL bRet = TRUE;
	int dwRet = KDPLAY_NOERROR;

	if (m_bFilePlaying== FALSE && m_bPlaying == FALSE)
	{
		m_dwLastError = KDPLAY_ORDER_ERROR;
		return FALSE;
	}
    if (m_bSetOsdRender == 1)
    {
        UNILOGE("[%d]<%s> already set osd", m_nPort, __FUNCTION__);
        return KDPLAY_ORDER_ERROR;
    }

	if (NULL == pMode)
	{
		m_dwLastError = KDPLAY_PARA_OVER;
		return FALSE;
	}

    if (TRUE == pMode->bOsd)
    {
        if ( pMode->uiFontSize < 16 || pMode->uiFontSize > 2000 ||
            pMode->uiFontRotate < 0 || pMode->uiFontRotate > 360 ||
            pMode->uiLayerMode != 1 || (NULL != pMode->pstrFontPath && (strlen(pMode->pstrFontPath) > 512)))
        {
            UNILOGE("[%d]<%s> param fail: size:%d[16,2000]; rote:%d[0,360);layer:%d[1]; %s", m_nPort, __FUNCTION__,
                pMode->uiFontSize, pMode->uiFontRotate, pMode->uiLayerMode, pMode->pstrFontPath);
            m_dwLastError = KDPLAY_PARA_OVER;
            return FALSE;
        }

        if ((pMode->eOsdMode & PLAYKD_OSD_MODE_SNAP) == PLAYKD_OSD_MODE_RENDER ||
            (pMode->eOsdMode & PLAYKD_OSD_MODE_RECORD) == PLAYKD_OSD_MODE_RECORD)
        {
            UNILOGE("[%d]<%s> param fail: mode:%d size:%d[16,2000]; rote:%d[0,360);layer:%d[1]; %s", m_nPort, __FUNCTION__,
                pMode->eOsdMode, pMode->uiFontSize, pMode->uiFontRotate, pMode->uiLayerMode, pMode->pstrFontPath);
            m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;
            return FALSE;
        }
        IMAGE tImagedate        = {0};
        dwRet = Font2Bmp(pMode->pstrFontPath,pMode->strText,pMode->uiARGB,pMode->uiFontSize,pMode->uiFontRotate,0,&tImagedate);
        if (KDPLAY_NOERROR != dwRet)
        {
            m_dwLastError = dwRet;
            UNILOGE("[%d]<%s> create osd bmp fail: %d", m_nPort, __FUNCTION__, dwRet);
            return FALSE;
        }
        FreeBmp((char *)tImagedate.imgdata);

    }

	if ((NULL != m_hWnd && TRUE == ::IsWindow((HWND)m_hWnd)) || FALSE == pMode->bOsd)
	{
		dwRet = m_cGat669.GAT669_SetOsdParamEx( m_nPort, m_hWnd, pMode);
		if (KDPLAY_NOERROR != dwRet)
		{
			m_dwLastError = dwRet;
			return FALSE;
		}
	}
	if (KDPLAY_NOERROR == dwRet)
    { 
        if (sizeof(KD_OSD_MODECONFIG) != pMode->wStructSize)
        {
            UNILOGE("[%d]<%s> KD_OSD_MODECONFIG struct not cmp", m_nPort, __FUNCTION__);
            return KDPLAY_ERR_VERSION_CMP;
        }
        if ((pMode->eOsdMode & PLAYKD_OSD_MODE_RENDER) != PLAYKD_OSD_MODE_RENDER)
        {
            UNILOGE("[%d]<%s> this mode:%d not support", m_nPort, __FUNCTION__,pMode->eOsdMode);
            return KDPLAY_PARA_OVER;
        }
        memcpy(&m_tOsdMode, pMode, sizeof(KD_OSD_MODECONFIG));
        if (pMode->pstrFontPath != NULL)
        {
            if (strlen(pMode->pstrFontPath) > 512)
            {
                return KDPLAY_BUF_OVER;
            }
            strcpy(m_strOsdFontPath, pMode->pstrFontPath);
            m_tOsdMode.pstrFontPath = m_strOsdFontPath;
        }

        if (pMode->bOsd == TRUE)
        {
            m_bSetOsdRender = 2;
        }
        else
            m_bSetOsdRender = 0;
	}
	return bRet;
}

BOOL CGat669Proxy::SetModuConfig( int nModuFlag, PKD_VIE_MODUCONFIG pModu, BOOL bEnable)
{
	BOOL bRet = FALSE;
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;

	return bRet;
}

BOOL CGat669Proxy::SetModuRegion( uint32_t nRegionNum,	KDRECT *pRect)
{
	BOOL bRet = FALSE;
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;

	return bRet;
}

BOOL CGat669Proxy::GetModuConfig( int *dwModuFlag, PKD_VIE_MODUCONFIG pParaConfig)
{
	BOOL bRet = FALSE;
	m_dwLastError = KDPLAY_OPERTION_NOTALLOWED;

	return bRet;
}

BOOL CGat669Proxy::GetOsdParam( int nID, char* pPath, int& hwnd, BOOL& bOsd, int& eStatus)
{
    int dwRet = 0;
    BOOL bRet = TRUE;
    dwRet = m_cGat669.GAT669_GetOsdParam(nID, pPath, hwnd, bOsd, eStatus);
    if (KDPLAY_NOERROR != dwRet)
    {
        m_dwLastError = dwRet;
        bRet = FALSE;
    }
    return bRet;
}

API void gat669ver()
{
	OspPrintf(TRUE,FALSE,"大华解码库 ver:compile time:%s %s\n", __DATE__, __TIME__);
}

API void gat669help()
{
	::OspPrintf( TRUE, FALSE, "gat669ver()\n");
}