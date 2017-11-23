
// FTech_JaiCameraDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTech_JaiCamera.h"
#include "FTech_JaiCameraDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFTech_JaiCameraDlg dialog


UINT DisplayThread1(LPVOID param)
{
	CFTech_JaiCameraDlg* pMain = (CFTech_JaiCameraDlg*)param;

	DWORD dwResult=0;
	while(pMain->m_bThDspWork[0])
	{
		Sleep(0);

		dwResult = WaitForSingleObject(pMain->m_Camera[0].GetHandleGrabDone(),1000);
		if (dwResult == WAIT_OBJECT_0)
		{
			pMain->OnDisplayCam1();
			pMain->m_Camera[0].ResetHandleGrabDone();
		}
	}

	return 0;
}

UINT DisplayThread2(LPVOID param)
{
	CFTech_JaiCameraDlg* pMain = (CFTech_JaiCameraDlg*)param;

	DWORD dwResult=0;
	while(pMain->m_bThDspWork[1])
	{
		Sleep(0);

		dwResult = WaitForSingleObject(pMain->m_Camera[1].GetHandleGrabDone(),1000);
		if (dwResult == WAIT_OBJECT_0)
		{
			pMain->OnDisplayCam2();
			pMain->m_Camera[1].ResetHandleGrabDone();
		}
	}

	return 0;
}

CFTech_JaiCameraDlg::CFTech_JaiCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTech_JaiCameraDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int i=0; i<MAX_CAMERA; i++)
	{
		m_pBmpInfo[i]	= NULL;
		m_pThDsp[i]		= NULL;
		m_bThDspWork[i] = false;
	}
}

void CFTech_JaiCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFTech_JaiCameraDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CFTech_JaiCameraDlg::OnBnClickedBtnRefresh)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_CONNECTION1, &CFTech_JaiCameraDlg::OnBnClickedBtnConnection1)
	ON_BN_CLICKED(IDC_BTN_ACQ1, &CFTech_JaiCameraDlg::OnBnClickedBtnAcq1)
	ON_BN_CLICKED(IDC_BTN_CONNECTION2, &CFTech_JaiCameraDlg::OnBnClickedBtnConnection2)
	ON_BN_CLICKED(IDC_BTN_ACQ2, &CFTech_JaiCameraDlg::OnBnClickedBtnAcq2)
END_MESSAGE_MAP()


// CFTech_JaiCameraDlg message handlers

BOOL CFTech_JaiCameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LTC_LIST);
	pList->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	pList->DeleteAllItems();
	pList->InsertColumn(0, _T(""), LVCFMT_LEFT, 0, -1);
	pList->InsertColumn(1, _T("Model"), LVCFMT_CENTER, 70, -1);
	pList->InsertColumn(2, _T("Interface"), LVCFMT_CENTER, 90, -1);
	pList->InsertColumn(3, _T("SN"), LVCFMT_CENTER, 60, -1); 
	pList->InsertColumn(4, _T("ETC"), LVCFMT_CENTER, 40, -1); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTech_JaiCameraDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFTech_JaiCameraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFTech_JaiCameraDlg::OnBnClickedBtnRefresh()
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LTC_LIST);
	pList->DeleteAllItems();

	int devices=0;
	bool ret=false;

	BeginWaitCursor();
	
	ret = JAI_SDK::CJaiCamera::GetDeviceCount(devices);
	if (ret == true)
	{
		for (int i=0; i<devices; i++)
		{
			CString list=_T(""), model=_T(""), sn=_T(""), lf=_T(""), type=_T("");
			JAI_SDK::CJaiCamera::GetDeviceName(i,model);
			JAI_SDK::CJaiCamera::GetInterfaceType(i, lf);
			JAI_SDK::CJaiCamera::GetDeviceSN(i,sn);
			if (lf == _T("GevTL"))
			{
				CString tmp=_T("");
				JAI_SDK::CJaiCamera::GetInterfaceName(i, tmp);
				
				(tmp.Find(_T("FD")) != -1) ? type=_T("FD") : type=_T("SD");
			}
			else
				type = lf;
			pList->InsertItem(i, _T(""));
			pList->SetItem(i, 1, LVIF_TEXT, model, 0, 0, 0, NULL ); 
			pList->SetItem(i, 2, LVIF_TEXT, lf, 0, 0, 0, NULL ); 
			pList->SetItem(i, 3, LVIF_TEXT, sn, 0, 0, 0, NULL ); 
			pList->SetItem(i, 4, LVIF_TEXT, type, 0, 0, 0, NULL ); 
		}
	}

	EndWaitCursor();
}

void CFTech_JaiCameraDlg::CreateBmpInfo(int nIdx, int nWidth, int nHeight, int nBpp)
{
	if (m_pBmpInfo[nIdx] != NULL) 
	{
		delete []m_pBmpInfo[nIdx];
		m_pBmpInfo[nIdx] = NULL;
	}

	if (nBpp == 8)
		m_pBmpInfo[nIdx] = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255*sizeof(RGBQUAD)];
	else if (nBpp == 24)
		m_pBmpInfo[nIdx] = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	m_pBmpInfo[nIdx]->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfo[nIdx]->bmiHeader.biPlanes = 1;
	m_pBmpInfo[nIdx]->bmiHeader.biBitCount = nBpp;
	m_pBmpInfo[nIdx]->bmiHeader.biCompression = BI_RGB;

	if (nBpp == 8)
		m_pBmpInfo[nIdx]->bmiHeader.biSizeImage = 0;
	else if (nBpp == 24)
		m_pBmpInfo[nIdx]->bmiHeader.biSizeImage = (((nWidth * 24 + 31) & ~31) >> 3) * nHeight;

	m_pBmpInfo[nIdx]->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpInfo[nIdx]->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpInfo[nIdx]->bmiHeader.biClrUsed = 0;
	m_pBmpInfo[nIdx]->bmiHeader.biClrImportant = 0;

	if (nBpp == 8)
	{
		for (int i = 0 ; i < 256 ; i++)
		{
			m_pBmpInfo[nIdx]->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBmpInfo[nIdx]->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBmpInfo[nIdx]->bmiColors[i].rgbRed = (BYTE)i;
			m_pBmpInfo[nIdx]->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBmpInfo[nIdx]->bmiHeader.biWidth = nWidth;
	m_pBmpInfo[nIdx]->bmiHeader.biHeight = -nHeight;
}

void CFTech_JaiCameraDlg::OnDisplayCam1()
{
	CClientDC dc(GetDlgItem(IDC_VIEW_CAMERA1));
	CRect rect;
	GetDlgItem(IDC_VIEW_CAMERA1)->GetClientRect(&rect);

	dc.SetStretchBltMode(COLORONCOLOR); 

	BYTE *pBuffer = m_Camera[0].GetImageBuffer();
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_nWidth[0], m_nHeight[0], pBuffer, m_pBmpInfo[0], DIB_RGB_COLORS, SRCCOPY);
}

void CFTech_JaiCameraDlg::OnDisplayCam2()
{
	CClientDC dc(GetDlgItem(IDC_VIEW_CAMERA2));
	CRect rect;
	GetDlgItem(IDC_VIEW_CAMERA2)->GetClientRect(&rect);

	dc.SetStretchBltMode(COLORONCOLOR); 

	BYTE *pBuffer = m_Camera[1].GetImageBuffer();
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_nWidth[1], m_nHeight[1], pBuffer, m_pBmpInfo[1], DIB_RGB_COLORS, SRCCOPY);
}

void CFTech_JaiCameraDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	for (int i=0; i<MAX_CAMERA; i++)
	{
		if (m_pThDsp[i] != NULL)
		{
			m_bThDspWork[i] = false;

			DWORD dwResult=0;
			dwResult = WaitForSingleObject(m_pThDsp[i]->m_hThread, 5000);
		}

		if (m_pBmpInfo[i] != NULL)
		{
			delete []m_pBmpInfo[i];
			m_pBmpInfo[i] = NULL;
		}

		if (m_Camera[i].IsConnected() == true)
		{
			if (m_Camera[i].IsActive() == true)
				m_Camera[i].OnStopAcquisition();

			m_Camera[i].OnDisconnect();
		}
	}
}


void CFTech_JaiCameraDlg::OnBnClickedBtnConnection1()
{
	CString caption = _T("");
	GetDlgItemText(IDC_BTN_CONNECTION1, caption);
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LTC_LIST);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	int nItem=-1;
	bool ret = false;
	while (pos)
	{
		nItem = pList->GetNextSelectedItem(pos);
	}
	if (nItem == -1) return;

	if (caption == _T("Connect"))
	{
		ret = m_Camera[0].OnConnect(nItem);	
		if (ret == true)
		{
			m_Camera[0].SetAcquisitionMode(JAI_SDK::eContinuous);
			CString value=_T("");
			m_Camera[0].GetDeviceModelName(value);
			SetDlgItemText(IDC_LB_MODEL1, value);
			
			value = m_Camera[0].GetInterface();
			if (value.Find(_T("GIGE")) != -1)
				m_Camera[0].GetSerialNumber(true,value);
			else if (value.Find(_T("USB")) != -1)
				m_Camera[0].GetSerialNumber(false,value);

			SetDlgItemText(IDC_LB_SN1, value);

			int w=0,h=0,bpp=0;
			w = m_Camera[0].GetWidth();
			h = m_Camera[0].GetHeight();
			bpp =m_Camera[0].GetBpp();

			m_nWidth[0] = w;
			m_nHeight[0] = h;
			m_nBpp[0] = bpp;

			CreateBmpInfo(0,m_nWidth[0],m_nHeight[0],m_nBpp[0]);

			SetDlgItemText(IDC_BTN_CONNECTION1, _T("Disconnect"));
		}

	}
	else
	{
		m_Camera[0].OnDisconnect();

		SetDlgItemText(IDC_LB_MODEL1, _T(""));
		SetDlgItemText(IDC_LB_SN1, _T(""));

		SetDlgItemText(IDC_BTN_CONNECTION1, _T("Connect"));
	}
}


void CFTech_JaiCameraDlg::OnBnClickedBtnAcq1()
{
	CString caption = _T("");
	GetDlgItemText(IDC_BTN_ACQ1, caption);
	bool ret = false;

	if (caption == _T("Start"))
	{
		ret = m_Camera[0].OnStartAcquisition();
		if (ret == true)
		{
			m_bThDspWork[0] = true;
			m_pThDsp[0] = AfxBeginThread(DisplayThread1, this);
			SetDlgItemText(IDC_BTN_ACQ1, _T("Stop"));
		}
	}
	else
	{
		m_bThDspWork[0] = false;
		WaitForSingleObject(m_pThDsp[0]->m_hThread, 5000);

		ret = m_Camera[0].OnStopAcquisition();
		if (ret == true)
			SetDlgItemText(IDC_BTN_ACQ1, _T("Start"));
	}
}


void CFTech_JaiCameraDlg::OnBnClickedBtnConnection2()
{
	CString caption = _T("");
	GetDlgItemText(IDC_BTN_CONNECTION2, caption);
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LTC_LIST);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	int nItem=-1;
	bool ret = false;
	while (pos)
	{
		nItem = pList->GetNextSelectedItem(pos);
	}
	if (nItem == -1) return;

	if (caption == _T("Connect"))
	{
		ret = m_Camera[1].OnConnect(nItem);
		//ret = m_Camera[1].OnConnect(1, false);
		if (ret == true)
		{
			CString value=_T("");
			m_Camera[1].GetDeviceModelName(value);
			SetDlgItemText(IDC_LB_MODEL2, value);

			value = m_Camera[1].GetInterface();
			if (value.Find(_T("GIGE")) != -1)
				m_Camera[1].GetSerialNumber(true,value);
			else if (value.Find(_T("USB")) != -1)
				m_Camera[1].GetSerialNumber(false,value);

			SetDlgItemText(IDC_LB_SN2, value);

			int w=0,h=0,bpp=0;
			w = m_Camera[1].GetWidth();
			h = m_Camera[1].GetHeight();
			bpp =m_Camera[1].GetBpp();

			m_nWidth[1] = w;
			m_nHeight[1] = h;
			m_nBpp[1] = bpp;

			CreateBmpInfo(1,m_nWidth[1],m_nHeight[1],m_nBpp[1]);

			SetDlgItemText(IDC_BTN_CONNECTION2, _T("Disconnect"));
		}

	}
	else
	{
		m_Camera[1].OnDisconnect();

		SetDlgItemText(IDC_LB_MODEL2, _T(""));
		SetDlgItemText(IDC_LB_SN2, _T(""));

		SetDlgItemText(IDC_BTN_CONNECTION2, _T("Connect"));
	}
}


void CFTech_JaiCameraDlg::OnBnClickedBtnAcq2()
{
	CString caption = _T("");
	GetDlgItemText(IDC_BTN_ACQ2, caption);
	bool ret = false;

	if (caption == _T("Start"))
	{
		ret = m_Camera[1].OnStartAcquisition();
		if (ret == true)
		{
			m_bThDspWork[1] = true;
			m_pThDsp[1] = AfxBeginThread(DisplayThread2, this);
			SetDlgItemText(IDC_BTN_ACQ2, _T("Stop"));
		}
	}
	else
	{
		m_bThDspWork[1] = false;
		WaitForSingleObject(m_pThDsp[1]->m_hThread, 5000);

		ret = m_Camera[1].OnStopAcquisition();
		if (ret == true)
			SetDlgItemText(IDC_BTN_ACQ2, _T("Start"));
	}
}


