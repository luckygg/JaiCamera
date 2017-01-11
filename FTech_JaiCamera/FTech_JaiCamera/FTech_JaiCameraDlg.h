
// FTech_JaiCameraDlg.h : header file
//

#pragma once

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
	JAI_STANDARD::CJaiCamera m_Camera;
	void OnDisplay();
	bool m_bThDspWork;

private :
	int m_nWidth;
	int m_nHeight;
	int m_nBpp;
	CWinThread* m_pThDsp;
	BITMAPINFO* m_pBmpInfo;
	
	void CreateBmpInfo(int nWidth, int nHeight, int nBpp);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConnection();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedBtnAcq();
	afx_msg void OnDestroy();
};
