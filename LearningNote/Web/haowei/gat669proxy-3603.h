/*========================================================================================
ģ����    ��dhadapter
�ļ���    ��dhproxy.h
����ļ�  ��
ʵ�ֹ���  ���󻪶�Ӧ��IDevProxy������
����      ��tl
��Ȩ      ��<Copyright(C) 2003-2011 Suzhou Keda Technology Co., Ltd. All rights reserved.>
-------------------------------------------------------------------------------------------
�޸ļ�¼��
����               �汾              �޸���             �߶���              �޸ļ�¼
2014/07/09         V1.0              tl	                                    �½��ļ�
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

	BOOL32 init(const char *szCompany,void * hDll);		//һЩ��Դ�ĳ�ʼ��
	void uninit();		//��Դ�ķ���ʼ��
    void *GetHandle(){return m_cGat669.GetHandle();};

	BOOL32 IsCreateDecoder(){return m_bCreated;};

	void  SetCreateDecoder(BOOL32 bInit)
	{
		m_bCreated = bInit;
	}

// 
// 	static void*  CALLBACK Read2DecTask( void* pParam );
// 
// 	//�Ƿ�ͨ���ļ���ʽ������
// 	//������>=8���ٷ���ʱ����Ҫͨ���ļ���ʽ������
// 	BOOL32 IsPlayByFile( void );
// 	BOOL32 StartPlayByFile();
// 	BOOL32 StopPlayByFile();
// 	BOOL32 Input2File( void *pData, int dwDataSize );
// 
public:
	PDECCALLBACK  m_pfYUVDataCB;      //YUV���ݻص�
	void*        m_pYUVParam;

	PDECCALLBACK  m_pfDecInfoCB;      //����֡��Ϣ�ص�
	void*        m_pDecInfoParam;

	PDECCALLBACK  m_pfPCMDataCB;		//PCM���ݻص�
	void*        m_pPCMParam;

	//s32		m_nPort;	//ͨ����

private:
    s32 FoundAPort();

	int			InitOpenStreamParam();
	KDOsdParam	m_tOsdParam;
	BOOL		m_bOsd;
	char*		m_pOsdBuf;

	static s32  s_nPort[MAX_GAT669_PORT];			
	BOOL32      m_bCreated;             //�������Ƿ��ʼ��
	s32         m_dwLastError;			//��¼����
	void*       m_hWnd;		            //��ʾ���ھ��
	BOOL32      m_bPlaying;				//����������
	BOOL32      m_bFilePlaying;			//�����ļ�����
	int         m_playspeed;
    int         m_bSetOsdRender;        //����PLAYKD_SetOsdParamEx��Renderģʽ��=2����PLAYKD_SetOsdParam��=1���ӿڲ���ͬʱ����
    KD_OSD_MODECONFIG   m_tOsdMode;
    char                m_strOsdFontPath[512];

#ifdef _UNIDEBUG_
    FILE                    *m_fpStreamData;
    FILE                    *m_fpStreamInfo;
#endif

	//BOOL32	m_bLocalRecing;			//�Ƿ����ڱ���¼����

// 	PRAWDATACALLBACK  m_pfRawDataCB;		//δ�������ݻص�
// 	void*        m_pRawParam;
// 
// 	PDRAWCALLBACK	m_pfDrawCB;			//��ͼ�ص�
// 	void *		m_pDrawParam;		//��ͼ�ص�������
// 
// 	PENCCALLBACK m_pfEncChange;		//�ֱ��ʸı�ص�
// 	void*		 m_pEncChangeParam;
// 
// 	PFILEENDCALLBACK m_pfFileEndCB;	//�ļ������ص�
// 	void*			 m_pFileEndParam;
// 	
// 	BOOL32  m_bGetFileRef;			//����ļ�����

// 	emPlaySpeed m_eCurPlaySpeed;	//�����ٶ�
// 	u8		m_byDecoderMode;		//����ģʽ
// 	BOOL32	m_bIsMute;				//�Ƿ��ռ����
// 	s32		m_ncoffient;			//�ı��������ε���WAVE����
// 

/* 	s32		m_nTotalTime;			//�ļ��ܳ���  ��λ����*/
// 	s8		m_achCPlayingFile[MAX_PATH];	//��ǰ���ڲ��ŵ��ļ�
// 	float	m_fLocalRecPlayPos;		//��ǰ¼���ļ����ŵ�λ��
// 
// 
// 	//----��ȡ�ļ���ʽ������------
// 	TASKHANDLE m_hReadThread; //��ȡ�ļ������߳�
// 	FILE*  m_pFileWrite;  //д���ļ�
// 	FILE*  m_pFileRead;   //�����ļ�
// 	s8 m_achFile[MAX_PATH]; //���浱ǰ�ļ���
// 	BOOL32   m_bReadThreadFinish;
// 	BOOL32   m_bReadThreadExit;
};

#endif  //_GAT669PROXY_H
