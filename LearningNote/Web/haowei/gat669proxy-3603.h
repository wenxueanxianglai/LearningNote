/*========================================================================================
模块名    ：dhadapter
文件名    ：dhproxy.h
相关文件  ：
实现功能  ：大华对应的IDevProxy派生类
作者      ：tl
版权      ：<Copyright(C) 2003-2011 Suzhou Keda Technology Co., Ltd. All rights reserved.>
-------------------------------------------------------------------------------------------
修改记录：
日期               版本              修改人             走读人              修改记录
2014/07/09         V1.0              tl	                                    新建文件
=========================================================================================*/
#ifndef _GAT669PROXY_H
#define _GAT669PROXY_H

#include "DevProxy.h"
#include "kdvtype.h"
#include "osp_c.h"
#include "commongat669.h"

#define MAX_GAT669_PORT   60
class CGat669Proxy : public IDevProxy
{
public:
	CGat669Proxy(void);
	CGat669Proxy(const char *szCompany,void * hDll);
	virtual ~CGat669Proxy(void);
	virtual 	int		GetVersion();
	virtual 	int		GetVersionEx(char* szVersion,int* pVerLen);
	virtual		int		GetFileHeadLen();
	virtual		int		GetLastError();
	virtual		BOOL32	StartStream(int8_t* pHead,int nHeadLen,int nbufferlen);
	virtual		BOOL32	SetStreamMode(int nmode);
	virtual		BOOL32	StopStream();
	virtual		BOOL	PlaySound();
	virtual		BOOL	PlaySoundEx(char* pszID[KD_MAX_KDAP_DEVICENUM], int nCount);
	virtual		BOOL	StopSound();

	virtual		BOOL32	StartFile(const char* szfile);
	virtual		BOOL32	StopFile();
	virtual		BOOL32	PlayWndStart(void* hwnd);
	virtual		BOOL	PlayWndStop();
	virtual		BOOL32	SetPlayTime(int ntime);
	virtual		BOOL32	SetPlayPos(float fpos);
	virtual		uint32_t	GetTotalFrameNum();
	virtual		uint32_t	GetTotalTime();
	virtual     BOOL32  GetSourceBufferRemain(int iType);
	virtual		BOOL32		SetFileEndCallBack(PFILEENDCALLBACK cb,void* context);
	virtual		BOOL	SetRunTimeInfoCallBack( PRunTimeInfoCBFun pPRunTimeInfoCBFun, void *pContext);
	virtual		BOOL32	GetKeyFramePos(int	nValue, int nType, PKD_FRAME_POS pFramePos);
	virtual		BOOL32	GetNextKeyFramePos(int	nValue, int nType, PKD_FRAME_POS pFramePos);
	virtual		uint32_t	GetCurrentFrameRate();
	virtual		float	GetPlayPos();
	virtual		uint32_t	GetPlayTime();
	virtual		uint32_t	GetPlayedFrames();
	virtual		BOOL32	StartLocalRecord(const char* szRecFileName);
    virtual		BOOL	StartLocalRecordExt(const char* szRecFileName,int nRecordType,int iStreamType,int iFileLen,BOOL bFirstVideoFrame);
	virtual		BOOL32	StopLocalRecord();
	virtual		BOOL32	SetAudioVolume(int wVolume);
	virtual		uint32_t	GetAudioVolume();
	virtual		BOOL32	SetAudioMutex(bool bmutex);
	virtual		BOOL32	AdjustWaveAudio(int ncoffient);
	virtual		BOOL32	Snapshot(void* hWnd);
	virtual		BOOL32	SaveSnapshot(const char *szPicFileName, EImageType ePicType);
	virtual		BOOL	GetBmp(char* pBitmap, int nBufSize, int* pBmpSize);
	virtual		BOOL32	CatchResizePic(const int8_t *sFileName, int lTargetWidth, int lTargetHeight, EImageType ePicfomat);
	virtual		BOOL32	SetDrawCallBack(PDRAWCALLBACK pFunc, void *pParam);
	virtual		BOOL32	SetPlaySpeed(emPlaySpeed ePlayRate);
	virtual		BOOL32	Fast();
	virtual		BOOL32	Slow();
	virtual		BOOL32	SetPlayPause(BOOL32 bPause);
	virtual		BOOL32	OneByOne();
	virtual		BOOL32	PlayOneBack();
	virtual		BOOL32	RevertPlay();
	virtual		BOOL32	SetYUVDataCallback(PDECCALLBACK pFun, void *pParam,bool bRender = true);
	virtual		BOOL32	SetDecInfoCallback(PDECCALLBACK pFun, void *pParam);
	virtual		BOOL32	SetPCMDataCallback(PDECCALLBACK pFun, void *pParam,bool bRender = true);
	virtual		BOOL32	SetRawDataCallback(PRAWDATACALLBACK pFun, void *pParam);
	virtual		BOOL32	SetEncTypeChangeCallBack(PENCCALLBACK pFun,void *pParam);
	virtual		BOOL32	InputStreamData(void *pData, int dwDataSize,uint32_t dwFrameID);
	virtual		BOOL32	InputVideoData(KDTRawData *pVData);
	virtual		BOOL32	InputAudioData(KDTRawData *pAData);
	virtual		BOOL32	GetColor(uint32_t nRegionNum, uint32_t* pBrightness,uint32_t* pContrast,uint32_t* pSaturation,uint32_t* pHue);
	virtual		BOOL32	SetColor(int nRegionNum,int nBrightness,int nContrast,int nSaturation, int nHue);
	virtual		BOOL32	SetDisplayRegion(int nRegionNum, KDRECT* pSrcRect, void* hDestWnd, BOOL32 bEnable);
	virtual		BOOL32	RefreshPlay (int nRegionNum);
	virtual		BOOL32	VerticalSyncEnable(BOOL32 bEnable);
	virtual		BOOL32	GetPictureSize(uint32_t* pWidth, uint32_t* pHeight);
	virtual		BOOL32	SetRotateAngle(int nrotateType);
	virtual		BOOL32	GetDecoderStatis(TDecStatis* pKdvDecStatis);
	virtual		BOOL32	DenoiseFilter( BOOL32  bEnable, int dwLevel);
	virtual		BOOL32	ResetBuffer(int buffertype);
	virtual		BOOL32	SetDecoderMode(int cDecoderMode);
	virtual		BOOL	SetOsdParam( KDOsdParam* ptOsdParam, BOOL bOsd);
	virtual		BOOL	SetOsdParamEx( KD_OSD_MODECONFIG* pMode);
	virtual     BOOL    SetModuConfig( int nModuFlag, PKD_VIE_MODUCONFIG pModu, BOOL bEnable);
	virtual     BOOL    SetModuRegion( uint32_t nRegionNum,	KDRECT *pRect);
	virtual     BOOL	GetModuConfig( int *dwModuFlag, PKD_VIE_MODUCONFIG pParaConfig);
    virtual     BOOL    GetOsdParam( int nID, char* pPath, int& hwnd, BOOL& bOsd, int& eStatus);


public:
	CGat669 m_cGat669;

	BOOL32 init(const char *szCompany,void * hDll);		//一些资源的初始化
	void uninit();		//资源的反初始化
    void *GetHandle(){return m_cGat669.GetHandle();};

	BOOL32 IsCreateDecoder(){return m_bCreated;};

	void  SetCreateDecoder(BOOL32 bInit)
	{
		m_bCreated = bInit;
	}

// 
// 	static void*  CALLBACK Read2DecTask( void* pParam );
// 
// 	//是否通过文件方式来播放
// 	//当大华以>=8倍速放像时，需要通过文件方式来播放
// 	BOOL32 IsPlayByFile( void );
// 	BOOL32 StartPlayByFile();
// 	BOOL32 StopPlayByFile();
// 	BOOL32 Input2File( void *pData, int dwDataSize );
// 
public:
	PDECCALLBACK  m_pfYUVDataCB;      //YUV数据回调
	void*        m_pYUVParam;

	PDECCALLBACK  m_pfDecInfoCB;      //解码帧信息回调
	void*        m_pDecInfoParam;

	PDECCALLBACK  m_pfPCMDataCB;		//PCM数据回调
	void*        m_pPCMParam;

	//s32		m_nPort;	//通道号

private:
    s32 FoundAPort();

	int			InitOpenStreamParam();
	KDOsdParam	m_tOsdParam;
	BOOL		m_bOsd;
	char*		m_pOsdBuf;

	static s32  s_nPort[MAX_GAT669_PORT];			
	BOOL32      m_bCreated;             //解码器是否初始化
	s32         m_dwLastError;			//记录错误
	void*       m_hWnd;		            //显示窗口句柄
	BOOL32      m_bPlaying;				//正在流播放
	BOOL32      m_bFilePlaying;			//正在文件播放
	int         m_playspeed;
    int         m_bSetOsdRender;        //控制PLAYKD_SetOsdParamEx的Render模式（=2）与PLAYKD_SetOsdParam（=1）接口不能同时调用
    KD_OSD_MODECONFIG   m_tOsdMode;
    char                m_strOsdFontPath[512];

#ifdef _UNIDEBUG_
    FILE                    *m_fpStreamData;
    FILE                    *m_fpStreamInfo;
#endif

	//BOOL32	m_bLocalRecing;			//是否正在本地录像中

// 	PRAWDATACALLBACK  m_pfRawDataCB;		//未解码数据回调
// 	void*        m_pRawParam;
// 
// 	PDRAWCALLBACK	m_pfDrawCB;			//绘图回调
// 	void *		m_pDrawParam;		//绘图回调上下文
// 
// 	PENCCALLBACK m_pfEncChange;		//分辨率改变回调
// 	void*		 m_pEncChangeParam;
// 
// 	PFILEENDCALLBACK m_pfFileEndCB;	//文件结束回调
// 	void*			 m_pFileEndParam;
// 	
// 	BOOL32  m_bGetFileRef;			//获得文件索引

// 	emPlaySpeed m_eCurPlaySpeed;	//播放速度
// 	u8		m_byDecoderMode;		//解码模式
// 	BOOL32	m_bIsMute;				//是否独占声卡
// 	s32		m_ncoffient;			//改变声音波形调整WAVE波形
// 

/* 	s32		m_nTotalTime;			//文件总长度  单位毫秒*/
// 	s8		m_achCPlayingFile[MAX_PATH];	//当前正在播放的文件
// 	float	m_fLocalRecPlayPos;		//当前录像文件播放的位置
// 
// 
// 	//----读取文件方式来解码------
// 	TASKHANDLE m_hReadThread; //读取文件解码线程
// 	FILE*  m_pFileWrite;  //写的文件
// 	FILE*  m_pFileRead;   //读的文件
// 	s8 m_achFile[MAX_PATH]; //保存当前文件名
// 	BOOL32   m_bReadThreadFinish;
// 	BOOL32   m_bReadThreadExit;
};

#endif  //_GAT669PROXY_H
