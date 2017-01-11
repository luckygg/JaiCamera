
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


UINT DisplayThread(LPVOID param)
{
	CFTech_JaiCameraDlg* pMain = (CFTech_JaiCameraDlg*)param;

	DWORD dwResult=0;
	while(pMain->m_bThDspWork)
	{
		Sleep(0);

		dwResult = WaitForSingleObject(pMain->m_Camera.GetHandleGrabDone(),1000);
		if (dwResult == WAIT_OBJECT_0)
		{
			pMain->OnDisplay();
			pMain->m_Camera.ResetHandleGrabDone();
		}
	}

	return 0;
}

CFTech_JaiCameraDlg::CFTech_JaiCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTech_JaiCameraDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pBmpInfo = NULL;
	m_pThDsp = NULL;
	m_bThDspWork = false;
}

void CFTech_JaiCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFTech_JaiCameraDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECTION, &CFTech_JaiCameraDlg::OnBnClickedBtnConnection)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CFTech_JaiCameraDlg::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_ACQ, &CFTech_JaiCameraDlg::OnBnClickedBtnAcq)
	ON_WM_DESTROY()
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
	pList->InsertColumn(1, _T("Maker"), LVCFMT_CENTER, 70, -1);
	pList->InsertColumn(2, _T("Model"), LVCFMT_CENTER, 90, -1);
	pList->InsertColumn(3, _T("SN"), LVCFMT_CENTER, 60, -1); 
	pList->InsertColumn(4, _T("Type"), LVCFMT_CENTER, 40, -1); 
	pList->InsertColumn(5, _T("IP"), LVCFMT_CENTER, 90, -1); 

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

void CFTech_JaiCameraDlg::OnBnClickedBtnConnection()
{
	CString caption = _T("");
	GetDlgItemText(IDC_BTN_CONNECTION, caption);
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LTC_LIST);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	int nItem=0;
	bool ret = false;
	while (pos)
	{
		nItem = pList->GetNextSelectedItem(pos);
	}

	if (caption == _T("Connect"))
	{
		ret = m_Camera.OnConnect(nItem, false);	
		if (ret == true)
		{
			CString value=_T("");
			m_Camera.GetDeviceModelName(value);
			SetDlgItemText(IDC_LB_MODEL, value);
			m_Camera.GetSerialNumber(value);
			SetDlgItemText(IDC_LB_SN, value);

			int w=0,h=0,bpp=0;
			m_Camera.GetWidth(w);
			m_Camera.GetHeight(h);
			m_Camera.GetBpp(bpp);

			m_nWidth = w;
			m_nHeight = h;
			m_nBpp = bpp;

			CreateBmpInfo(w,h,bpp);

			SetDlgItemText(IDC_BTN_CONNECTION, _T("Disconnect"));
		}
		
	}
	else
	{
		m_Camera.OnDisconnect();

		SetDlgItemText(IDC_LB_MODEL, _T(""));
		SetDlgItemText(IDC_LB_SN, _T(""));

		SetDlgItemText(IDC_BTN_CONNECTION, _T("Connect"));
	}
}

void CFTech_JaiCameraDlg::OnBnClickedBtnRefresh()
{
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LTC_LIST);
	pList->DeleteAllItems();

	JAI_STANDARD::CJaiSystem system;
	int devices=0;
	bool ret=false;

	ret = system.SearchDevices(devices);
	if (ret == true)
	{
		for (int i=0; i<devices; i++)
		{
			CString list=_T(""), vendor=_T(""), model=_T(""), sn=_T(""), ip=_T(""), lf=_T(""), type=_T("");
			system.GetManufacture(i, vendor);
			system.GetSerialNumber(i, sn);
			system.GetModelName(i, model);
			if (model.Find(_T("GE")) != -1)
			{
				system.GetIPAddress(i, ip);
				system.GetInterface(i, lf);
				
				(lf.Find(_T("FD")) != -1) ? type=_T("FD") : type=_T("SD");
			}

			pList->InsertItem(i, _T(""));
			pList->SetItem(i, 1, LVIF_TEXT, vendor, 0, 0, 0, NULL ); 
			pList->SetItem(i, 2, LVIF_TEXT, model, 0, 0, 0, NULL ); 
			pList->SetItem(i, 3, LVIF_TEXT, sn, 0, 0, 0, NULL ); 
			pList->SetItem(i, 4, LVIF_TEXT, type, 0, 0, 0, NULL ); 
			pList->SetItem(i, 5, LVIF_TEXT, ip, 0, 0, 0, NULL ); 
		}
	}
}


void CFTech_JaiCameraDlg::OnBnClickedBtnAcq()
{
	CString caption = _T("");
	GetDlgItemText(IDC_BTN_ACQ, caption);
	bool ret = false;

	if (caption == _T("Start"))
	{
		ret = m_Camera.OnStartAcquisition();
		if (ret == true)
		{
			m_bThDspWork = true;
			m_pThDsp = AfxBeginThread(DisplayThread, this);
			SetDlgItemText(IDC_BTN_ACQ, _T("Stop"));
		}
	}
	else
	{
		m_bThDspWork = false;
		WaitForSingleObject(m_pThDsp->m_hThread, INFINITE);

		ret = m_Camera.OnStopAcquisition();
		if (ret == true)
			SetDlgItemText(IDC_BTN_ACQ, _T("Start"));
	}
}

void CFTech_JaiCameraDlg::CreateBmpInfo(int nWidth, int nHeight, int nBpp)
{
	if (m_pBmpInfo != NULL) 
	{
		delete []m_pBmpInfo;
		m_pBmpInfo = NULL;
	}

	if (nBpp == 8)
		m_pBmpInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255*sizeof(RGBQUAD)];
	else if (nBpp == 24)
		m_pBmpInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO)];

	m_pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biPlanes = 1;
	m_pBmpInfo->bmiHeader.biBitCount = nBpp;
	m_pBmpInfo->bmiHeader.biCompression = BI_RGB;

	if (nBpp == 8)
		m_pBmpInfo->bmiHeader.biSizeImage = 0;
	else if (nBpp == 24)
		m_pBmpInfo->bmiHeader.biSizeImage = (((nWidth * 24 + 31) & ~31) >> 3) * nHeight;

	m_pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
	m_pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
	m_pBmpInfo->bmiHeader.biClrUsed = 0;
	m_pBmpInfo->bmiHeader.biClrImportant = 0;

	if (nBpp == 8)
	{
		for (int i = 0 ; i < 256 ; i++)
		{
			m_pBmpInfo->bmiColors[i].rgbBlue = (BYTE)i;
			m_pBmpInfo->bmiColors[i].rgbGreen = (BYTE)i;
			m_pBmpInfo->bmiColors[i].rgbRed = (BYTE)i;
			m_pBmpInfo->bmiColors[i].rgbReserved = 0;
		}
	}

	m_pBmpInfo->bmiHeader.biWidth = nWidth;
	m_pBmpInfo->bmiHeader.biHeight = -nHeight;
}

void CFTech_JaiCameraDlg::OnDisplay()
{
	CClientDC dc(GetDlgItem(IDC_VIEW_CAMERA));
	CRect rect;
	GetDlgItem(IDC_VIEW_CAMERA)->GetClientRect(&rect);

	dc.SetStretchBltMode(COLORONCOLOR); 

	BYTE *pBuffer = m_Camera.GetImageBuffer();
	StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0, m_nWidth, m_nHeight, pBuffer, m_pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
}

void CFTech_JaiCameraDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pBmpInfo != NULL)
	{
		delete []m_pBmpInfo;
		m_pBmpInfo = NULL;
	}

	if (m_pThDsp != NULL)
	{
		m_bThDspWork = false;

		DWORD dwResult=0;
		dwResult = WaitForSingleObject(m_pThDsp->m_hThread, INFINITE);
	}

	if (m_Camera.IsConnected() == true)
	{
		if (m_Camera.IsActive() == true)
			m_Camera.OnStopAcquisition();

		m_Camera.OnDisconnect();
	}
}
