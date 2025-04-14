
// CheckMissMarkingDlg.h : 헤더 파일
//

#pragma once

#include "Vision.h"

// CCheckMissMarkingDlg 대화 상자
class CCheckMissMarkingDlg : public CDialog
{
	CVision *m_pVision;

	BOOL FileBrowse(CString& sPath);
	void InitVision();
	void ShowModel(CString sPath);
	void DoHistogram();

// 생성입니다.
public:
	CCheckMissMarkingDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~CCheckMissMarkingDlg();

	double m_dPixelRes; // Camera Pixel Resolution

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHECKMISSMARKING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnModel();
	afx_msg void OnBnClickedBtnJudge();
};
