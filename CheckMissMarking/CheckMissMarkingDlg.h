
// CheckMissMarkingDlg.h : ��� ����
//

#pragma once

#include "Vision.h"

// CCheckMissMarkingDlg ��ȭ ����
class CCheckMissMarkingDlg : public CDialog
{
	CVision *m_pVision;

	BOOL FileBrowse(CString& sPath);
	void InitVision();
	void ShowModel(CString sPath);
	void DoHistogram();

// �����Դϴ�.
public:
	CCheckMissMarkingDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	~CCheckMissMarkingDlg();

	double m_dPixelRes; // Camera Pixel Resolution

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHECKMISSMARKING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnModel();
	afx_msg void OnBnClickedBtnJudge();
};
