// MFC_DX.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#include "DXwnd.h"

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_DXApp:
// �йش����ʵ�֣������ MFC_DX.cpp
//

class CMFC_DXApp : public CWinApp
{
public:
	CMFC_DXApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_DXApp theApp;