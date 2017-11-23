//----------------------------------------------------------
// JAI Camera Class
// JAI SDK 3.0.1.4
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------
// Last Update : 2017-11-23 13:55
// Modified by William Kim
//----------------------------------------------------------
#pragma once

#include <jai_factory.h>
#pragma comment (lib,"Jai_Factory")

namespace JAI_SDK {

#define NODE_WIDTH				(int8_t*)"Width"
#define NODE_HEIGHT				(int8_t*)"Height"
#define NODE_PIXELFORMAT		(int8_t*)"PixelFormat"
#define NODE_USERID				(int8_t*)"DeviceUserID"
#define NODE_MODELNAME			(int8_t*)"DeviceModelName"
#define NODE_SERIALNUMBER_GIGE	(int8_t*)"DeviceSerialNumber"
#define NODE_SERIALNUMBER_USB	(int8_t*)"DeviceID"
#define NODE_OFFSETX			(int8_t*)"OffsetX"
#define NODE_OFFSETY			(int8_t*)"OffsetY"
#define NODE_ACQMODE			(int8_t*)"AcquisitionMode"
#define NODE_ACQFPS				(int8_t*)"AcquisitionFrameRate"
#define NODE_TRGMODE			(int8_t*)"TriggerMode"
#define NODE_TRGSRC				(int8_t*)"TriggerSource"
#define NODE_EXPMODE			(int8_t*)"ExposureMode"
#define NODE_EXPTIME			(int8_t*)"ExposureTimeRaw"
#define NODE_ACQSTART			(int8_t*)"AcquisitionStart"
#define NODE_ACQSTOP			(int8_t*)"AcquisitionStop"
#define NODE_ACQMMODE			(int8_t*)"AcquisitionMode"
#define NODE_ACQMFRMCNT			(int8_t*)"AcquisitionFrameCount"
#define NODE_USERSETSELECTOR	(int8_t*)"UserSetSelector"
#define NODE_USERSETSAVE		(int8_t*)"UserSetSave"
#define NODE_USERSETLOAD		(int8_t*)"UserSetLoad"

//----- enum type -----//
typedef	enum { eDefault=0, eUserSet1, eUserSet2, eUserSet3 } EUserSet;
typedef	enum { eLine5=0, eLine6, eSoftware, eOutput0, eOutput1, eOutput2, eOutput3, ePG0, ePG1, ePG2, ePG3, eNAND1, eNAND2, eAction1, eAction2, eNotConnected } ETrgSrc;
typedef	enum { eOff=0, eReadOut, ePreviousFrame } ETrgOvl;
typedef	enum { eTimed=0, eTriggerWidth } EExpMode;
typedef	enum { eContinuous=0, eSingleFrame, eMultiFrame } EAcqMode ;

class CJaiCamera
{
public:
	CJaiCamera(void);
	~CJaiCamera(void);
public :
	//******************************************************************************************************************
	/// \brief					System의 Device 개수 확인 함수.
	/// \param [out] nDvCnt		Device 개수 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceCount(int &nDvCnt);
	//******************************************************************************************************************
	/// \brief					특정 Device의 Interface Name 확인 함수.
	/// \param [in] nDvIdx		Device Index 입력.
	/// \param [out] strvalue	Interface Name 확인.
	/// \param bool				결과 반환.
	static bool GetInterfaceName(int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 Interface Type 확인 함수.
	/// \param [in] nDvIdx		Device Index 입력.
	/// \param [out] strvalue	Interface Type 확인.
	/// \param bool				결과 반환.
	static bool GetInterfaceType(int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 IP Address 확인 함수.
	/// \param [in] nDvIdx		Device Index 입력.
	/// \param [out] strvalue	IP Address 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceIPAddr(int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 Model Name 확인 함수.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device Model Name 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceName(int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 User Defined Name 확인 함수.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device User Defined Name 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceUserID(int nDvIdx, CString &strValue);
	//******************************************************************************************************************
	/// \brief					특정 Device의 Serial Number 확인 함수.
	/// \param [in] nDvIdx		Device Index.
	/// \param [out] strValue	Device Serial Number 확인.
	/// \param bool				결과 반환.
	static bool GetDeviceSN(int nDvIdx, CString &strValue);
public :
	//******************************************************************************************************************
	/// \brief					특정 Device를 연결하는 함수.
	/// \param [in] nDvIdx		Device Index.
	/// \param bool				결과 반환.
	bool OnConnect(int nDvIdx);
	//******************************************************************************************************************
	/// \brief					입력한 Device User ID와 동일한 카메라를 연결하는 함수.
	/// \param [in] strUserID	특정 Device User ID를 입력.
	/// \param bool				결과 반환.
	bool OnConnectID(CString strUserID);
	//******************************************************************************************************************
	/// \brief					입력한 IP Address와 동일한 카메라를 연결하는 함수.
	/// \param [in] strIPAddress특정 IP Address를 입력. ('.'를 포함해야 한다.)
	/// \param bool				결과 반환.
	bool OnConnectIP(CString strIPAddress);
	//******************************************************************************************************************
	/// \brief					카메라를 해제하는 함수.
	/// \param bool				결과 반환.
	bool OnDisconnect();
	//******************************************************************************************************************
	/// \brief					영상 취득 시작 함수.
	/// \param bool				결과 반환.
	bool OnStartAcquisition();
	//******************************************************************************************************************
	/// \brief					영상 취득 종료 함수.
	/// \param bool				결과 반환.
	bool OnStopAcquisition();
	//******************************************************************************************************************
	/// \brief					Continuous Mode 설정 함수.
	/// \param bool				결과 반환.
	bool SetContinuousMode();
	//******************************************************************************************************************
	/// \brief					Software Trigger Mode 설정 함수.
	/// \param bool				결과 반환.
	bool SetSoftTriggerMode();
	//******************************************************************************************************************
	/// \brief					Hardware Trigger Mode 설정 함수.
	/// \param bool				결과 반환.
	bool SetHardTriggerMode();
	//******************************************************************************************************************
	/// \brief					Software Trigger Event 발생 함수.
	/// \param bool				결과 반환.
	bool OnTriggerEvent();
	//******************************************************************************************************************
	/// \brief					Acquisition Mode 설정 함수.
	/// \param [in] Mode		Continuous / Single Frame / Multi Frame 선택 가능.
	/// \param bool				결과 반환.
	bool SetAcquisitionMode(EAcqMode eMode);
	//******************************************************************************************************************
	/// \brief					Multi Frame Count 설정 함수.
	/// \param [in] nValue		Count 입력.
	/// \param bool				결과 반환.
	bool SetMultiFrameCount(int nValue);
	//******************************************************************************************************************
	/// \brief					이미지 저장 함수.
	/// \param [in] strPath		저장 경로 입력.
	/// \param bool				결과 반환.
	bool OnSaveImage(CString strPath);
	//******************************************************************************************************************
	/// \brief					User Set 저장 함수.
	/// \param bool				결과 반환.
	bool OnUserSetSave();
	//******************************************************************************************************************
	/// \brief					User Set 불러오기 함수.
	/// \param bool				결과 반환.
	bool OnUserSetLoad();
	//******************************************************************************************************************
	/// \brief					Auto White Balance 설정 함수.
	/// \param bool				결과 반환.
	bool OnCalculateWhiteBalance();
public :
	//******************************************************************************************************************
	/// \brief					Device 연결 상태 확인 함수.
	/// \param bool				결과 반환.
	bool IsConnected() { return m_isConnected; }
	//******************************************************************************************************************
	/// \brief					영상 취득 상태 확인 함수.
	/// \param bool				결과 반환.
	bool IsActive() { return m_isActived; }
	//******************************************************************************************************************
	/// \brief					Device User ID 확인 함수.
	/// \param [out] strValue	Device User ID 확인.
	/// \param bool				결과 반환.
	bool GetDeviceUserID(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Device Model Name 확인 함수.
	/// \param [out] strValue	Device Model Name 확인.
	/// \param bool				결과 반환.
	bool GetDeviceModelName(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Device Serial Number 확인 함수.
	/// \param [in] bGigE		GigE Device인지 설정 함수.
	/// \param [out] strValue	Device Serial Number 확인.
	/// \param bool				결과 반환.
	bool GetSerialNumber(bool bGigE, CString &strValue);
	//******************************************************************************************************************
	/// \brief					Offset X 확인 함수.
	/// \param [out] nValue		Offset X 확인.
	/// \param bool				결과 반환.
	bool GetOffsetX(int &nValue);
	//******************************************************************************************************************
	/// \brief					Offset Y 확인 함수.
	/// \param [out] nValue		Offset Y 확인.
	/// \param bool				결과 반환.
	bool GetOffsetY(int &nValue);
	//******************************************************************************************************************
	/// \brief					Acquisition Mode 확인 함수.
	/// \param [out] strValue	Acquisition Mode 확인.
	/// \param bool				결과 반환.
	bool GetAcquisitionMode(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Frame Rate 확인 함수.
	/// \param [out] dValue		Frame Rate 확인.
	/// \param bool				결과 반환.
	bool GetAcquisitionFrameRate(double &dValue);
	//******************************************************************************************************************
	/// \brief					Trigger Mode 확인 함수.
	/// \param [out] strValue	Trigger Mode 확인.
	/// \param bool				결과 반환.
	bool GetTriggerMode(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Trigger Source 확인 함수.
	/// \param [out] strValue	Trigger Source 확인.
	/// \param bool				결과 반환.
	bool GetTriggerSource(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Exposure Mode 확인 함수.
	/// \param [out] strValue	Exposure Mode 확인.
	/// \param bool				결과 반환.
	bool GetExposureMode(CString &strValue);
	//******************************************************************************************************************
	/// \brief					Exposure Time 확인 함수.
	/// \param [out] nValue		Exposure Time 확인.
	/// \param bool				결과 반환.
	bool GetExposureTimeRaw(int &nValue);
	//******************************************************************************************************************
	/// \brief					Pixel Format 확인 함수.
	/// \param [out] strValue	Pixel Format 확인.
	/// \param bool				결과 반환.
	bool GetPixelFormat(CString &strValue);
	//******************************************************************************************************************
	/// \brief					마지막 에러 메시지 확인 함수.
	/// \param CString			마지막 에러 메시지 반환.
	CString GetLastErrorMessage() { return m_strErrMsg; }
	//******************************************************************************************************************
	/// \brief					Width 확인 함수.
	/// \param int				결과 반환.
	int  GetWidth()  { return m_nWidth;  }
	//******************************************************************************************************************
	/// \brief					Height 확인 함수.
	/// \param int				결과 반환.
	int  GetHeight() { return m_nHeight; }
	//******************************************************************************************************************
	/// \brief					BPP 확인 함수.
	/// \param int				결과 반환.
	int  GetBpp()	 { return m_nBpp; }
	//******************************************************************************************************************
	/// \brief					Grab Done Handle 반환 함수.
	/// \param HANDLE			결과 반환.
	HANDLE GetHandleGrabDone() { return m_hGrabDone; }
	//******************************************************************************************************************
	/// \brief					Grab Done Handle Reset 함수.
	/// \param void				반환 없음.
	void ResetHandleGrabDone() { ResetEvent(m_hGrabDone); }
	//******************************************************************************************************************
	/// \brief					Device의 Interface Type 확인 함수.
	/// \param CString			Interface Type 문자열 반환.
	CString GetInterface() { return m_strInterface; }
	//******************************************************************************************************************
	/// \brief					Image Buffer 확인 함수.
	/// \param BYTE*			Image Buffer Pointer 반환.
	BYTE* GetImageBuffer() { return m_pbyBuffer; }
	//******************************************************************************************************************
	/// \brief					Device User ID 설정 함수.
	/// \param [in] strValue	Device User ID 입력.
	/// \param bool				결과 반환.
	bool SetDeviceUserID(CString strValue);
	//******************************************************************************************************************
	/// \brief					Offset X 설정 함수.
	/// \param [in] nValue		Offset X 입력.
	/// \param bool				결과 반환.
	bool SetOffsetX(int nValue);
	//******************************************************************************************************************
	/// \brief					Offset Y 설정 함수.
	/// \param [in] nValue		Offset Y 입력.
	/// \param bool				결과 반환.
	bool SetOffsetY(int nValue);
	//******************************************************************************************************************
	/// \brief					Frame Rate 설정 함수.
	/// \param [in] dValue		Frame Rate 입력.
	/// \param bool				결과 반환.
	bool SetAcquisitionFrameRate(double dValue);
	//******************************************************************************************************************
	/// \brief					Acquisition Mode 설정 함수.
	/// \param [in] strValue	Acquisition Mode 입력.
	/// \param bool				결과 반환.
	bool SetAcquisitionMode(CString strValue);
	//******************************************************************************************************************
	/// \brief					Trigger Mode 설정 함수.
	/// \param [in] bEnable		On / Off 입력.
	/// \param bool				결과 반환.
	bool SetTriggerMode(bool bEnable);
	//******************************************************************************************************************
	/// \brief					Trigger Source 설정 함수.
	/// \param [in] Src			Soft / Hard 입력.
	/// \param bool				결과 반환.
	bool SetTriggerSource(ETrgSrc eSrc);
	//******************************************************************************************************************
	/// \brief					Trigger Overlap 설정 함수.
	/// \param [in] Ovl			Off=0 / ReadOut / Pre Frame 입력.
	/// \param bool				결과 반환.
	bool SetTriggerOverlap(ETrgOvl eOvl);
	//******************************************************************************************************************
	/// \brief					Exposure Mode 설정 함수.
	/// \param [in] Mode		Timed / Trigger Width 입력.
	/// \param bool				결과 반환.
	bool SetExposureMode(EExpMode eMode);
	//******************************************************************************************************************
	/// \brief					Exposure Time 설정 함수.
	/// \param [in] nValue		Exposure Time 입력.
	/// \param bool				결과 반환.
	bool SetExposureTime(int nValue);
	//******************************************************************************************************************
	/// \brief					User Selector 설정 함수.
	/// \param [in] Mode		Default / UserSet1 입력.
	/// \param bool				결과 반환.
	bool SetUserSetSelector(EUserSet eUser);
private :
	//FACTORY_HANDLE	m_hFactory;
	CAM_HANDLE      m_hCamera;		// Camera Handle.
	THRD_HANDLE     m_hThread;		// Thread Handle.
	J_tIMAGE_INFO   m_ImgColor;		// Bayer 변환 시 사용되는 Info.
	HANDLE			m_hGrabDone;	// Grab Done 확인 Handle.
	BYTE*			m_pbyBuffer;	// Image Buffer.
	BITMAPINFO*		m_pBitmapInfo;	// Image Bitmap Info.

	CString m_strInterface;	// Device의 Interface 확인 문자열.
	CString m_strErrMsg;	// 마지막 에러 메시지.

	int	m_nWidth;	// Image Width Size.
	int	m_nHeight;	// Image Height Size.
	int	m_nBpp;		// Image Bit Per Pixel 크기.
	int	m_nGainR;	// White Balance R Gain.
	int	m_nGainG;	// White Balance G Gain.
	int	m_nGainB;	// White Balance B Gain.

	bool m_isConnected;		// Device 연결 상태 확인.
	bool m_isActived;		// Acquisition 상태 확인.
	bool m_isColorConvert;	// Bayer Conversion 확인.
	bool m_is3CCD;			// 3CCd 확인.

private :
	CString GetErrorMsg(J_STATUS_TYPE ErrCode);
	bool OpenFactory();
	bool CloseFactory();
	bool GetWidth(int &nValue);
	bool GetHeight(int &nValue);
	bool GetBpp(int &nValue);
	void StreamCBFunc(J_tIMAGE_INFO * pAqImageInfo);
	void OnCreateBmpInfo(int nWidth, int nHeight, int nBpp);

private :
	//******************************************************************************************************************
	/// \brief					Type별로 Get/Set 하는 함수.
	/// \param [in] pNodeName	파라미터의 Node Name 입력.
	/// \param [in]  Value		파라미터의 값 입력.
	/// \param [out] Value		파라미터의 값 확인.
	/// \param bool				결과 반환.
	bool GetValueString(int8_t* pNodeName, CString &strValue);
	bool SetValueString(int8_t* pNodeName, CString strValue);
	bool GetValueInt(int8_t* pNodeName, int &nValue);
	bool SetValueInt(int8_t* pNodeName, int nValue);
	bool GetValueDouble(int8_t* pNodeName, double &dValue);
	bool SetValueDouble(int8_t* pNodeName, double dValue);
	bool OnExecuteCommand(int8_t* pNodeName);
};

}