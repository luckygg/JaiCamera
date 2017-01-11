#include "StdAfx.h"
#include "JaiCamera.h"

using namespace JAI_STANDARD;

CString g_strErrMsg=_T("");
CString GetErrorMsg(J_STATUS_TYPE ErrCode)
{
	CString strErrMsg=_T("");
	switch(ErrCode)
	{
	case J_ST_SUCCESS             :	strErrMsg = _T("OK."								); break; 
	case J_ST_INVALID_BUFFER_SIZE :	strErrMsg = _T("Invalid buffer size."				); break; 
	case J_ST_INVALID_HANDLE      :	strErrMsg = _T("Invalid handle."					); break; 
	case J_ST_INVALID_ID          :	strErrMsg = _T("Invalid ID."						); break; 
	case J_ST_ACCESS_DENIED       :	strErrMsg = _T("Access denied."						); break; 
	case J_ST_NO_DATA             :	strErrMsg = _T("No data."							); break; 
	case J_ST_ERROR               :	strErrMsg = _T("Generic error code."				); break; 
	case J_ST_INVALID_PARAMETER   :	strErrMsg = _T("Invalid parameter."					); break; 
	case J_ST_TIMEOUT             :	strErrMsg = _T("Timeout."							); break; 
	case J_ST_INVALID_FILENAME    :	strErrMsg = _T("Invalid file name."					); break; 
	case J_ST_INVALID_ADDRESS     :	strErrMsg = _T("Invalid address."					); break; 
	case J_ST_FILE_IO             :	strErrMsg = _T("File IO error."						); break; 
	case J_ST_GC_ERROR            :	strErrMsg = _T("GenICam error."						); break; 
	case J_ST_VALIDATION_ERROR    :	strErrMsg = _T("Settings File Validation Error."	); break; 
	case J_ST_VALIDATION_WARNING  :	strErrMsg = _T("Settings File Validation Warning."	); break; 
	}

	return strErrMsg;
}

CJaiSystem::CJaiSystem(void)
{
	m_hFactory = NULL;

	J_Factory_Open((int8_t*)"", &m_hFactory);
}

CJaiSystem::~CJaiSystem(void)
{
	J_Factory_Close(m_hFactory);
}

bool CJaiSystem::SearchDevices(int &nValue)
{
	J_STATUS_TYPE status = J_ST_SUCCESS;
	uint32_t iNumDev=0;
	bool8_t bHasChange=0;
	
	status = J_Factory_UpdateCameraList(m_hFactory, &bHasChange);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	status = J_Factory_GetNumOfCameras(m_hFactory, &iNumDev);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	nValue = (int)iNumDev;

	return true;
}

bool CJaiSystem::GetManufacture(int nIdx, CString &strVendor)
{
	if (m_hFactory == NULL) return false;

	J_STATUS_TYPE status = J_ST_SUCCESS;
	uint32_t iSize=0;
	int8_t Value[J_CAMERA_INFO_SIZE] = {0,};
	int8_t sCameraId[J_CAMERA_ID_SIZE];

	iSize = sizeof(sCameraId);
	status = J_Factory_GetCameraIDByIndex(m_hFactory, nIdx, sCameraId, &iSize);
	iSize = sizeof(Value);
	status = J_Factory_GetCameraInfo(m_hFactory, sCameraId, CAM_INFO_MANUFACTURER, Value, &iSize);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	char* pTmp = (char*)Value;
	strVendor = pTmp;

	return true;
}
bool CJaiSystem::GetInterface(int nIdx, CString &strInterface)
{
	if (m_hFactory == NULL) return false;

	J_STATUS_TYPE status = J_ST_SUCCESS;
	uint32_t iSize=0;
	int8_t Value[J_CAMERA_INFO_SIZE] = {0,};
	int8_t sCameraId[J_CAMERA_ID_SIZE];

	iSize = sizeof(sCameraId);
	status = J_Factory_GetCameraIDByIndex(m_hFactory, nIdx, sCameraId, &iSize);
	iSize = sizeof(Value);
	status = J_Factory_GetCameraInfo(m_hFactory, sCameraId, CAM_INFO_INTERFACE_ID, Value, &iSize);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	char* pTmp = (char*)Value;
	strInterface = pTmp;

	return true;
}
bool CJaiSystem::GetModelName(int nIdx, CString &strModel)
{
	if (m_hFactory == NULL) return false;

	J_STATUS_TYPE status = J_ST_SUCCESS;
	uint32_t iSize=0;
	int8_t Value[J_CAMERA_INFO_SIZE] = {0,};
	int8_t sCameraId[J_CAMERA_ID_SIZE];

	iSize = sizeof(sCameraId);
	status = J_Factory_GetCameraIDByIndex(m_hFactory, nIdx, sCameraId, &iSize);
	iSize = sizeof(Value);
	status = J_Factory_GetCameraInfo(m_hFactory, sCameraId, CAM_INFO_MODELNAME, Value, &iSize);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	char* pTmp = (char*)Value;
	strModel = pTmp;

	return true;
}
bool CJaiSystem::GetSerialNumber(int nIdx, CString &strSerial)
{
	if (m_hFactory == NULL) return false;

	J_STATUS_TYPE status = J_ST_SUCCESS;
	uint32_t iSize=0;
	int8_t Value[J_CAMERA_INFO_SIZE] = {0,};
	int8_t sCameraId[J_CAMERA_ID_SIZE];

	iSize = sizeof(sCameraId);
	status = J_Factory_GetCameraIDByIndex(m_hFactory, nIdx, sCameraId, &iSize);
	iSize = sizeof(Value);
	status = J_Factory_GetCameraInfo(m_hFactory, sCameraId, CAM_INFO_SERIALNUMBER, Value, &iSize);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	char* pTmp = (char*)Value;
	strSerial = pTmp;

	return true;
}
bool CJaiSystem::GetIPAddress(int nIdx, CString &strIP)
{
	if (m_hFactory == NULL) return false;

	J_STATUS_TYPE status = J_ST_SUCCESS;
	uint32_t iSize=0;
	int8_t Value[J_CAMERA_INFO_SIZE] = {0,};
	int8_t sCameraId[J_CAMERA_ID_SIZE];

	iSize = sizeof(sCameraId);
	status = J_Factory_GetCameraIDByIndex(m_hFactory, nIdx, sCameraId, &iSize);
	iSize = sizeof(Value);
	status = J_Factory_GetCameraInfo(m_hFactory, sCameraId, CAM_INFO_IP, Value, &iSize);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	char* pTmp = (char*)Value;
	strIP = pTmp;

	return true;
}

CJaiCamera::CJaiCamera(void)
{
	m_hFactory		= NULL;
	m_hCamera		= NULL;
	m_hThread		= NULL;
	m_pbyBuffer		= NULL;
	m_pBitmapInfo	= NULL;
	m_ImgColor.pImageBuffer = NULL;

	m_nWidth	= 0;
	m_nHeight	= 0;
	m_nBpp		= 0;
	m_nGainR	= 4096;
	m_nGainG	= 4096;
	m_nGainB	= 4096;

	m_isConnected	= false;
	m_isActived		= false;
	m_isColorConvert= false;
	m_is3CCD		= false;

	m_hGrabDone = CreateEvent(NULL,TRUE,FALSE,NULL);
	ResetEvent(m_hGrabDone);
	
	OpenFactory();
}


CJaiCamera::~CJaiCamera(void)
{
	if (m_isActived == true)
		OnStopAcquisition();

	if (m_isConnected == true)
		OnDisconnect();

	if (m_ImgColor.pImageBuffer != NULL)
	{
		J_Image_Free(&m_ImgColor);
		m_ImgColor.pImageBuffer = NULL;
	}

	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (m_pbyBuffer != NULL)
	{
		delete []m_pbyBuffer;
		m_pbyBuffer = NULL;
	}

	CloseFactory();
}

bool CJaiCamera::OpenFactory()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;

	status = J_Factory_Open((int8_t*)"", &m_hFactory);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	return true;
}

bool CJaiCamera::CloseFactory()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;

	if(m_hFactory != NULL)
	{
		status = J_Factory_Close(m_hFactory);
		if(status != J_ST_SUCCESS)
		{
			g_strErrMsg = GetErrorMsg(status);
			return false;
		}

		m_hFactory = NULL;
	}

	return true;
}

bool CJaiCamera::OnConnect(int nIdx, bool bColorConvert)
{
	J_STATUS_TYPE status = J_ST_SUCCESS;
	uint32_t iNumDev=0;
	uint32_t iSize=0;
	bool8_t bHasChange=0;
	int8_t sCameraId[J_CAMERA_ID_SIZE] = {0,};
	
	status = J_Factory_UpdateCameraList(m_hFactory, &bHasChange);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	status = J_Factory_GetNumOfCameras(m_hFactory, &iNumDev);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	if (iNumDev == 0)
	{
		g_strErrMsg = _T("There are no devices on the system.");
		return false;
	}
	
	iSize = sizeof(sCameraId);
	status = J_Factory_GetCameraIDByIndex(m_hFactory, nIdx, sCameraId, &iSize);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	status = J_Camera_Open(m_hFactory, sCameraId, &m_hCamera);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	CString model=_T("");
	GetDeviceModelName(model);
	if (model.Find(_T("AT")) != -1) m_is3CCD = true;

	int value=0;
	bool ret=false;
	ret = GetWidth(value);
	if(ret != true) return false;
	m_nWidth = value;

	ret = GetHeight(value);
	if(ret != true) return false;
	m_nHeight = value;

	ret = GetBpp(value);
	if(ret != true) return false;
	m_nBpp = value;

	m_isColorConvert = bColorConvert;
	m_isColorConvert && (m_nBpp == 8)? m_nBpp *= 3 : m_nBpp;

	m_pbyBuffer = new BYTE[m_nWidth * m_nHeight * m_nBpp / 8];
	memset(m_pbyBuffer, 0, m_nWidth * m_nHeight * m_nBpp / 8);

	OnCreateBmpInfo(m_nWidth, m_nHeight, m_nBpp);

	m_isConnected = true;
	return true;
}

void CJaiCamera::OnCreateBmpInfo(int nWidth, int nHeight, int nBpp)
{
	if (m_pBitmapInfo != NULL)
	{
		delete []m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (nBpp == 8)
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255*sizeof(RGBQUAD)];
	else if (nBpp == 24)
		m_pBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBitmapInfo->bmiHeader.biPlanes = 1;
	m_pBitmapInfo->bmiHeader.biBitCount = nBpp;
	m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;

	if (nBpp == 8)
		m_pBitmapInfo->bmiHeader.biSizeImage = 0;
	else if (nBpp == 24)
		m_pBitmapInfo->bmiHeader.biSizeImage = (((nWidth * 24 + 31) & ~31) >> 3) * nHeight;

	m_pBitmapInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBitmapInfo->bmiHeader.biClrUsed = 0;
	m_pBitmapInfo->bmiHeader.biClrImportant = 0;

	if (nBpp == 8)
	{
		for (int i = 0 ; i < 256 ; i++)
		{
			m_pBitmapInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBitmapInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBitmapInfo->bmiHeader.biWidth = nWidth;
	m_pBitmapInfo->bmiHeader.biHeight = -nHeight;
}

bool CJaiCamera::OnDisconnect()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;

	if(m_hCamera != NULL)
	{
		status = J_Camera_Close(m_hCamera);
		if(status != J_ST_SUCCESS)
		{
			g_strErrMsg = GetErrorMsg(status);
			return false;
		}

		m_hCamera = NULL;
	}

	if (m_pBitmapInfo != NULL)
	{
		delete m_pBitmapInfo;
		m_pBitmapInfo = NULL;
	}

	if (m_pbyBuffer != NULL)
	{
		delete []m_pbyBuffer;
		m_pbyBuffer = NULL;
	}

	return true;
}

bool CJaiCamera::OnStartAcquisition()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;

	status = J_Image_OpenStream(m_hCamera, 0, reinterpret_cast<J_IMG_CALLBACK_OBJECT>(this), reinterpret_cast<J_IMG_CALLBACK_FUNCTION>(&CJaiCamera::StreamCBFunc), &m_hThread, (m_nWidth*m_nHeight*m_nBpp)/8);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	status = J_Camera_ExecuteCommand(m_hCamera, NODE_ACQSTART);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}
	
	m_isActived = true;

	return true;
}

void CJaiCamera::StreamCBFunc(J_tIMAGE_INFO * pAqImageInfo)
{
	if (m_isColorConvert == true || m_is3CCD == true) 
	{
		if(m_ImgColor.pImageBuffer != NULL)
		{
			if((m_ImgColor.iSizeX != pAqImageInfo->iSizeX) || (m_ImgColor.iSizeY != pAqImageInfo->iSizeY))
			{
				J_Image_Free(&m_ImgColor);
				m_ImgColor.pImageBuffer = NULL;
			}
		}

		if(m_ImgColor.pImageBuffer == NULL)
			J_Image_Malloc(pAqImageInfo, &m_ImgColor);

		J_Image_FromRawToImageEx(pAqImageInfo, &m_ImgColor, BAYER_STANDARD_MULTI,m_nGainR,m_nGainG,m_nGainB); //BAYER_STANDARD

		memcpy(m_pbyBuffer, m_ImgColor.pImageBuffer, m_ImgColor.iImageSize);
	}
	else
	{
		memcpy(m_pbyBuffer, pAqImageInfo->pImageBuffer, pAqImageInfo->iImageSize);
	}

	SetEvent(m_hGrabDone);
}

bool CJaiCamera::SetHardTriggerMode()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;
	
	if(m_hCamera != NULL)
	{
		NODE_HANDLE hNode;
		uint32_t iNumOfEnumEntries = 0;
		int64_t int64Val = 0;

		hNode = NULL;
		status = J_Camera_GetNodeByName(m_hCamera, (int8_t*)"TriggerSelector", &hNode);
		if ((status == J_ST_SUCCESS) && (hNode != NULL))
		{
			status = J_Camera_SetValueString(m_hCamera, (int8_t*)"TriggerSelector", (int8_t*)"FrameStart");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

			status = J_Camera_SetValueString(m_hCamera, (int8_t*)"TriggerMode", (int8_t*)"On");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

			status = J_Camera_SetValueString(m_hCamera,(int8_t*)"TriggerSource", (int8_t*)"Line5");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

			status = J_Camera_SetValueString(m_hCamera,(int8_t*)"SequenceMode", (int8_t*)"Off");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }
		}
		else
		{
			g_strErrMsg = GetErrorMsg(status);
			return false;
		}
	}
	return true;
}

bool CJaiCamera::SetSoftTriggerMode()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;

	if(m_hCamera != NULL)
	{
		NODE_HANDLE hNode;
		uint32_t iNumOfEnumEntries = 0;
		int64_t int64Val = 0;

		hNode = NULL;
		status = J_Camera_GetNodeByName(m_hCamera, (int8_t*)"TriggerSelector", &hNode);
		if ((status == J_ST_SUCCESS) && (hNode != NULL))
		{
			status = J_Camera_SetValueString(m_hCamera, (int8_t*)"TriggerSelector", (int8_t*)"FrameStart");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

			status = J_Camera_SetValueString(m_hCamera, (int8_t*)"TriggerMode", (int8_t*)"On");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

			status = J_Camera_SetValueString(m_hCamera,(int8_t*)"TriggerSource", (int8_t*)"Software");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

			status = J_Camera_SetValueString(m_hCamera,(int8_t*)"SequenceMode", (int8_t*)"Off");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }
		}
		else
		{
			status = J_Camera_SetValueString(m_hCamera,(int8_t*)"ExposureMode", (int8_t*)"EdgePreSelect");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

			status = J_Camera_SetValueString(m_hCamera,(int8_t*)"LineSelector", (int8_t*)"CameraTrigger0");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

			status = J_Camera_SetValueString(m_hCamera,(int8_t*)"LineSource", (int8_t*)"SoftwareTrigger0");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }
		}
	} 

	return true;
}

bool CJaiCamera::SetContinuousMode()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;

	if(m_hCamera != NULL)
	{
		NODE_HANDLE hNode = NULL;
		status = J_Camera_GetNodeByName(m_hCamera, (int8_t*)"TriggerSelector", &hNode);

		if ((status == J_ST_SUCCESS) && (hNode != NULL))
		{
			status = J_Camera_SetValueString(m_hCamera, (int8_t*)"TriggerSelector", (int8_t*)"FrameStart");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

			status = J_Camera_SetValueString(m_hCamera, (int8_t*)"TriggerMode", (int8_t*)"Off");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }
		}
		else
		{
			status = J_Camera_SetValueString(m_hCamera,(int8_t*)"ExposureMode", (int8_t*)"Continuous");
			if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }
		}
	} 

	return true;
}

bool CJaiCamera::OnTriggerEvent()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;

	NODE_HANDLE hNode = NULL;
	status = J_Camera_GetNodeByName(m_hCamera, (int8_t*)"TriggerSoftware", &hNode);
	if ((status == J_ST_SUCCESS) && (hNode != NULL))
	{
		status = J_Camera_SetValueString(m_hCamera, (int8_t*)"TriggerSelector", (int8_t*)"FrameStart");
		if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

		status = J_Camera_ExecuteCommand(m_hCamera, (int8_t*)"TriggerSoftware");
		if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }
	}
	else
	{
		status = J_Camera_SetValueInt64(m_hCamera, (int8_t*)"SoftwareTrigger0", 1);
		if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }

		status = J_Camera_SetValueInt64(m_hCamera, (int8_t*)"SoftwareTrigger0", 0);
		if(status != J_ST_SUCCESS) { g_strErrMsg = GetErrorMsg(status); return false; }
	}

	return true;
}

bool CJaiCamera::OnCalculateWhiteBalance()
{
	J_STATUS_TYPE	status = J_ST_SUCCESS;
	J_tBGR48		resultcolor;
	RECT			pMeasureRect;
	int64_t			int64Val;
	int				iWidth, iHeight;

	status = J_Camera_GetValueInt64(m_hCamera, (int8_t*)"Width", &int64Val);
	if (status != J_ST_SUCCESS) 
	{ 
		g_strErrMsg = GetErrorMsg(status); 
		return false; 
	}
	iWidth = (int)int64Val;

	status = J_Camera_GetValueInt64(m_hCamera, (int8_t*)"Height", &int64Val);
	if (status != J_ST_SUCCESS) 
	{ 
		g_strErrMsg = GetErrorMsg(status); 
		return false; 
	}
	iHeight = (int)int64Val;

	pMeasureRect.top = (long)abs(2* iWidth / 5);
	pMeasureRect.left = (long)abs(2* iHeight / 5);
	pMeasureRect.right = (long)abs(3 * iWidth / 5);
	pMeasureRect.bottom = (long)abs(3 * iHeight / 5);

	status = J_Image_GetAverage(&m_ImgColor, &pMeasureRect, &resultcolor);
	if (status != J_ST_SUCCESS) 
	{ 
		g_strErrMsg = GetErrorMsg(status); 
		return false; 
	}

	m_nGainR = 4096 * resultcolor.G16 / resultcolor.R16;
	m_nGainB = 4096 * resultcolor.G16 / resultcolor.B16;
	m_nGainG = 4096;

	return true;
}

bool CJaiCamera::OnSaveImage(CString strPath)
{
	if (strPath.IsEmpty()) return false;

	if (m_pbyBuffer == NULL) return false;

	BITMAPFILEHEADER dib_format_layout;
	ZeroMemory(&dib_format_layout, sizeof(BITMAPFILEHEADER));
	dib_format_layout.bfType = 0x4D42;//*(WORD*)"BM";
	if (m_nBpp == 8)
		dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + sizeof(m_pBitmapInfo->bmiColors) * 256;
	else
		dib_format_layout.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	
	dib_format_layout.bfSize = dib_format_layout.bfOffBits + m_pBitmapInfo->bmiHeader.biSizeImage;

	wchar_t* wchar_str;     
	char*    char_str;      
	int      char_str_len;  
	wchar_str = strPath.GetBuffer(strPath.GetLength());

	char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL);
	char_str = new char[char_str_len];
	WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, char_str, char_str_len, 0,0);  

	FILE *p_file;
	fopen_s(&p_file,char_str, "wb");
	if(p_file != NULL)
	{
		fwrite(&dib_format_layout, 1, sizeof(BITMAPFILEHEADER), p_file);
		fwrite(m_pBitmapInfo, 1, sizeof(BITMAPINFOHEADER), p_file);
		if (m_nBpp == 8)
			fwrite(m_pBitmapInfo->bmiColors, sizeof(m_pBitmapInfo->bmiColors), 256, p_file);

		fwrite(m_pbyBuffer, 1, m_nWidth * m_nHeight * m_nBpp/8, p_file);
		fclose(p_file);
	}

	delete char_str;

	return true;
}

bool CJaiCamera::OnStopAcquisition()
{
	J_STATUS_TYPE status = J_ST_SUCCESS;

	// Stop Acquisition
	if (m_hCamera != NULL) 
	{
		status = J_Camera_ExecuteCommand(m_hCamera, NODE_ACQSTOP);
		if(status != J_ST_SUCCESS)
		{
			g_strErrMsg = GetErrorMsg(status);
			return false;
		}
	}

	if(m_hThread != NULL)
	{
		// Close stream
		status = J_Image_CloseStream(m_hThread);
		if(status != J_ST_SUCCESS)
		{
			g_strErrMsg = GetErrorMsg(status);
			return false;
		}

		m_hThread = NULL;
	}

	m_isActived = false;

	return true;
}

bool CJaiCamera::GetDeviceUserID(CString &strValue)
{
	return GetValueString(NODE_USERID, strValue);
}

bool CJaiCamera::GetDeviceModelName(CString &strValue)
{
	return GetValueString(NODE_MODELNAME, strValue);
}

bool CJaiCamera::GetSerialNumber(CString &strValue)
{
	return GetValueString(NODE_DEVICEID, strValue);
}

bool CJaiCamera::GetOffsetX(int &nValue)
{
	return GetValueInt(NODE_OFFSETX, nValue);
}

bool CJaiCamera::GetOffsetY(int &nValue)
{
	return GetValueInt(NODE_OFFSETY, nValue);
}

bool CJaiCamera::GetAcquisitionMode(CString &strValue)
{
	return GetValueString(NODE_ACQMODE, strValue);
}

bool CJaiCamera::GetAcquisitionFrameRate(double &dValue)
{
	return GetValueDouble(NODE_ACQFPS, dValue);
}

bool CJaiCamera::GetTriggerMode(CString &strValue)
{
	return GetValueString(NODE_TRGMODE, strValue);
}

bool CJaiCamera::GetTriggerSource(CString &strValue)
{
	return GetValueString(NODE_TRGSRC, strValue);
}

bool CJaiCamera::GetExposureMode(CString &strValue)
{
	return GetValueString(NODE_EXPMODE, strValue);
}

bool CJaiCamera::GetExposureTimeRaw(int &nValue)
{
	return GetValueInt(NODE_EXPTIME, nValue);
}

bool CJaiCamera::GetPixelFormat(CString &strValue)
{
	return GetValueString(NODE_PIXELFORMAT, strValue);
}

bool CJaiCamera::GetWidth(int &nValue)
{
	return GetValueInt(NODE_WIDTH, nValue);
}

bool CJaiCamera::GetHeight(int &nValue)
{
	return GetValueInt(NODE_HEIGHT, nValue);
}

bool CJaiCamera::GetBpp(int &nValue)
{
	int value=0;
	bool ret=false;
	ret = GetValueInt(NODE_PIXELFORMAT, value);
	nValue = J_BitsPerPixel(value);
	return ret;
}

bool CJaiCamera::SetDeviceUserID(CString strValue)
{
	return SetValueString(NODE_USERID, strValue);
}

bool CJaiCamera::SetOffsetX(int nValue)
{
	return SetValueInt(NODE_OFFSETX, nValue);
}

bool CJaiCamera::SetOffsetY(int nValue)
{
	return SetValueInt(NODE_OFFSETY, nValue);
}

bool CJaiCamera::SetAcquisitionFrameRate(double dValue)
{
	return SetValueDouble(NODE_ACQFPS, dValue);
}

bool CJaiCamera::SetAcquisitionMode(CString strValue)
{
	return SetValueString(NODE_ACQMODE, strValue);
}

bool CJaiCamera::SetTriggerMode(TRGMODE Mode)
{
	char value[MAX_PATH] = {0,};
	switch(Mode)
	{
	case TRG_Off : sprintf_s(value,"%s","Off"); break;
	case TRG_On  : sprintf_s(value,"%s","On"); break;
	}
	return SetValueString(NODE_TRGMODE, CString(value));
}

bool CJaiCamera::SetTriggerSource(TRGSRC Src)
{
	char value[MAX_PATH] = {0,};
	switch(Src)
	{
	case SRC_Line5			: sprintf_s(value,"%s","Line5"			); break;
	case SRC_Line6			: sprintf_s(value,"%s","Line6"			); break;
	case SRC_SW				: sprintf_s(value,"%s","Software"		); break;
	case SRC_Output0		: sprintf_s(value,"%s","UserOutput0"	); break;
	case SRC_Output1		: sprintf_s(value,"%s","UserOutput1"	); break;
	case SRC_Output2		: sprintf_s(value,"%s","UserOutput2"	); break;
	case SRC_Output3		: sprintf_s(value,"%s","UserOutput3"	); break;
	case SRC_PG0			: sprintf_s(value,"%s","PulseGenerator0"); break;
	case SRC_PG1			: sprintf_s(value,"%s","PulseGenerator1"); break;
	case SRC_PG2			: sprintf_s(value,"%s","PulseGenerator2"); break;
	case SRC_PG3			: sprintf_s(value,"%s","PulseGenerator3"); break;
	case SRC_NAND1			: sprintf_s(value,"%s","NAND1Output"	); break;
	case SRC_NAND2			: sprintf_s(value,"%s","NAND2Output"	); break;
	case SRC_ACTION1		: sprintf_s(value,"%s","Action1"		); break;
	case SRC_ACTION2		: sprintf_s(value,"%s","Action2"		); break;
	case SRC_NOTCONNECTED	: sprintf_s(value,"%s","NotConnected"	); break;
	}
	return SetValueString(NODE_TRGSRC, CString(value));
}

bool CJaiCamera::SetExposureMode(EXPMODE Mode)
{
	char value[MAX_PATH] = {0,};
	switch(Mode)
	{
	case EXP_Timed	: sprintf_s(value,"%s","Timed"); break;
	case EXP_PWC	: sprintf_s(value,"%s","TriggerWidth"); break;
	}
	return SetValueString(NODE_EXPMODE, CString(value));
}

bool CJaiCamera::SetExposureTime(int nValue)
{
	return SetValueInt(NODE_EXPTIME, nValue);
}

bool CJaiCamera::GetValueString(int8_t* pNodeName, CString &strValue)
{
	if(m_hCamera == NULL)
	{
		g_strErrMsg = _T("Device is not connected.");
		return false;
	}

	J_STATUS_TYPE status = J_ST_SUCCESS;

	char value[MAX_PATH] = {0,};
	uint32_t size=sizeof(value);
	status = J_Camera_GetValueString(m_hCamera, pNodeName, (int8_t*)value, &size);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}	

	strValue = (CString)value;

	return true;
}

bool CJaiCamera::SetValueString(int8_t* pNodeName, CString strValue)
{
	if(m_hCamera == NULL)
	{
		g_strErrMsg = _T("Device is not connected.");
		return false;
	}

	J_STATUS_TYPE status = J_ST_SUCCESS;

	char path[MAX_PATH] = {0,};
	CStringToChar(strValue,path);

	status = J_Camera_SetValueString(m_hCamera, pNodeName, (int8_t*)path);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}

	return true;
}

bool CJaiCamera::GetValueInt(int8_t* pNodeName, int &nValue)
{
	if(m_hCamera == NULL)
	{
		g_strErrMsg = _T("Device is not connected.");
		return false;
	}

	J_STATUS_TYPE status = J_ST_SUCCESS;
	int64_t value=0;
	status = J_Camera_GetValueInt64(m_hCamera, pNodeName, &value);
	if (status != J_ST_SUCCESS) 
	{ 
		g_strErrMsg = GetErrorMsg(status); 
		return false; 
	}

	nValue = (int)value;

	return true;
}

bool CJaiCamera::SetValueInt(int8_t* pNodeName, int nValue)
{
	if(m_hCamera == NULL)
	{
		g_strErrMsg = _T("Device is not connected.");
		return false;
	}

	J_STATUS_TYPE status = J_ST_SUCCESS;

	status = J_Camera_SetValueInt64(m_hCamera, pNodeName, nValue);
	if (status != J_ST_SUCCESS) 
	{ 
		g_strErrMsg = GetErrorMsg(status); 
		return false; 
	}

	return true;
}

bool CJaiCamera::GetValueDouble(int8_t* pNodeName, double &dValue)
{
	if(m_hCamera == NULL)
	{
		g_strErrMsg = _T("Device is not connected.");
		return false;
	}

	J_STATUS_TYPE status = J_ST_SUCCESS;
	double value=0;
	status = J_Camera_GetValueDouble(m_hCamera, pNodeName, &value);
	if (status != J_ST_SUCCESS) 
	{ 
		g_strErrMsg = GetErrorMsg(status); 
		return false; 
	}

	dValue = value;

	return true;
}

bool CJaiCamera::SetValueDouble(int8_t* pNodeName, double dValue)
{
	if(m_hCamera == NULL)
	{
		g_strErrMsg = _T("Device is not connected.");
		return false;
	}

	J_STATUS_TYPE status = J_ST_SUCCESS;

	status = J_Camera_SetValueDouble(m_hCamera, pNodeName, dValue);
	if (status != J_ST_SUCCESS) 
	{ 
		g_strErrMsg = GetErrorMsg(status); 
		return false; 
	}

	return true;
}

bool CJaiCamera::OnExecuteCommand(int8_t* pNodeName)
{
	if(m_hCamera == NULL)
	{
		g_strErrMsg = _T("Device is not connected.");
		return false;
	}

	J_STATUS_TYPE status = J_ST_SUCCESS;

	status = J_Camera_ExecuteCommand(m_hCamera, pNodeName);
	if(status != J_ST_SUCCESS)
	{
		g_strErrMsg = GetErrorMsg(status);
		return false;
	}	

	return true;
}