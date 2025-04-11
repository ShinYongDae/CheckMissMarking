
// CheckMissMarkingDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CheckMissMarking.h"
#include "CheckMissMarkingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCheckMissMarkingDlg ��ȭ ����



CCheckMissMarkingDlg::CCheckMissMarkingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CHECKMISSMARKING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pVision = NULL;
	m_dPixelRes = 0.008;
}

void CCheckMissMarkingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCheckMissMarkingDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_MODEL, &CCheckMissMarkingDlg::OnBnClickedBtnModel)
	ON_BN_CLICKED(IDC_BTN_JUDGE, &CCheckMissMarkingDlg::OnBnClickedBtnJudge)
END_MESSAGE_MAP()


// CCheckMissMarkingDlg �޽��� ó����

BOOL CCheckMissMarkingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	InitVision();

	GetDlgItem(IDC_STC_VISION)->ShowWindow(SW_HIDE);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCheckMissMarkingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCheckMissMarkingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCheckMissMarkingDlg::InitVision()
{
	// Select Live Camera Viewer
	HWND hCtrlV0[4] = { 0 };
	hCtrlV0[0] = GetDlgItem(IDC_STC_VISION)->GetSafeHwnd();
	MIL_ID MilSys = M_NULL;
	m_pVision = new CVision(0, MilSys, hCtrlV0, this);
	MilSys = m_pVision->GetSystemID();


	// Select Model Viewer
	HWND hW;
	CRect rt;

	// Display image buffer: CLibMilDisp *m_pMilDispModel
	// source image buffer : CLibMilBuf *m_pMilBufModel
	hW = GetDlgItem(IDC_PIC_MODEL)->GetSafeHwnd();
	GetDlgItem(IDC_PIC_MODEL)->GetWindowRect(&rt);
	m_pVision->SelDispModel(hW, rt);
}


void CCheckMissMarkingDlg::OnBnClickedBtnModel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString sPath;

	if (!FileBrowse(sPath))
		return;
	GetDlgItem(IDC_STC_PATH_MODEL)->SetWindowText(sPath);
	ShowModel(sPath);	// source image buffer : CLibMilBuf *m_pMilBufModel

	DoHistogram();
}

BOOL CCheckMissMarkingDlg::FileBrowse(CString& sPath)
{
	sPath = _T("");

	/* Load from file */
	CString FilePath;
	CFileFind finder;
	CString SrchPath, strTitleMsg, strErrMsg;

	CWaitCursor mCursor;

	CString DirPath[10];
	CString strWorkDir;
	BOOL bResult;

	CString strMcNum;
	int nAoiMachineNum = 0;

	// File Open Filter 
	static TCHAR BASED_CODE szFilter[] = _T("Mst Files (*.tif)|*.tif|All Files (*.*)|*.*||");

	// CFileDialog 
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	// Win2k Style FileDialog Box
	dlg.m_ofn.lStructSize = sizeof(OPENFILENAME) + 12; // +12�� Win2k Style�� ���̾�α� �ڽ��� Open��.

													   // Open Directory
	TCHAR strPrevDir[MAX_PATH];
	DWORD dwLength = GetCurrentDirectory(MAX_PATH, strPrevDir);
	strWorkDir = strPrevDir;
	dlg.m_ofn.lpstrInitialDir = strWorkDir;

	bResult = 0;

	// Dialog Open
	if (dlg.DoModal() == IDOK)
	{
		sPath = FilePath = dlg.GetPathName();
		return TRUE;
	}

	return FALSE;
}

void CCheckMissMarkingDlg::ShowModel(CString sPath)
{
	CFileFind findfile;
	if (findfile.FindFile(sPath))
	{
		// source image buffer : CLibMilBuf *m_pMilBufModel
		if (m_pVision)
			m_pVision->ShowModel(sPath);// , m_bUseCamMstModel);
	}
}


void CCheckMissMarkingDlg::OnBnClickedBtnJudge()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CCheckMissMarkingDlg::DoHistogram()
{
	CString sTemp, sVal = _T("");
	int nHistoVal;

	if (m_pVision)
	{
		m_pVision->DoHistogram();

		for (int i = 0; i < 256; i++)
		{
			nHistoVal = m_pVision->m_nHistoRst[i];
			if (nHistoVal > 0)
			{
				sTemp.Format(_T("%d(%d) "), i + 1, nHistoVal < 0 ? 0 : nHistoVal);
				sVal += sTemp;
			}
		}
		GetDlgItem(IDC_EDIT_HISTO_RST)->SetWindowTextW(sVal);
	}
}