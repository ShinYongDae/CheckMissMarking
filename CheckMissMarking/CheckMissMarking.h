
// CheckMissMarking.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCheckMissMarkingApp:
// �� Ŭ������ ������ ���ؼ��� CheckMissMarking.cpp�� �����Ͻʽÿ�.
//

class CCheckMissMarkingApp : public CWinApp
{
public:
	CCheckMissMarkingApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCheckMissMarkingApp theApp;