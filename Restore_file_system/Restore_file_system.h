
// Restore_file_system.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CRestore_file_systemApp:
// �� Ŭ������ ������ ���ؼ��� Restore_file_system.cpp�� �����Ͻʽÿ�.
//

class CRestore_file_systemApp : public CWinApp
{
public:
	CRestore_file_systemApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CRestore_file_systemApp theApp;