
// FTech_JaiCameraDlg.h : header file
//

#pragma once

#define MAX_CAMERA 2
#include "JaiCamera.h"

// CFTech_JaiCameraDlg dialog
class CFTech_JaiCameraDlg : public CDialogEx
{
// Construction
public:
	CFTech_JaiCameraDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTech_JaiCamera_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public :
	JAI_SDK::CJaiCamera m_Camera[MAX_CAMERA];
	void OnDisplayCam1();
	void OnDisplayCam2();
	bool m_bThDspWork[MAX_CAMERA];

private :
	int m_nWidth[MAX_CAMERA];
	int m_nHeight[MAX_CAMERA];
	int m_nBpp[MAX_CAMERA];
	
	CWinThread* m_pThDsp[MAX_CAMERA];
	BITMAPINFO* m_pBmpInfo[MAX_CAMERA];
	
	void CreateBmpInfo(int nIdx, int nWidth, int nHeight, int nBpp);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnConnection1();
	afx_msg void OnBnClickedBtnAcq1();
	afx_msg void OnBnClickedBtnConnection2();
	afx_msg void OnBnClickedBtnAcq2();
};
