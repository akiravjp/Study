// MFC_DX.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MFC_DX.h"
//#include "MFC_DXDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_DXApp

BEGIN_MESSAGE_MAP(CMFC_DXApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFC_DXApp ����

CMFC_DXApp::CMFC_DXApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFC_DXApp ����

CMFC_DXApp theApp;


// CMFC_DXApp ��ʼ��

BOOL CMFC_DXApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//CMFC_DXDlg dlg;
	CDXwnd* pDXwnd=new CDXwnd();
	//m_pMainWnd = &dlg;
	m_pMainWnd=pDXwnd;

	pDXwnd->Create(_T("DX_App"),800,600);
//	pDXwnd->UpdateWindow();
//	pDXwnd->SetFocus();

	/*if(!pDXwnd->InitDX())
	{
		pDXwnd->DestroyWindow();
		return FALSE;
 	}

	if(!pDXwnd->Setup())
	{
		pDXwnd->DestroyWindow();
		//AfxMessageBox(_T("Setup() - FAILED"));
		return FALSE;
 	}*/

	//pDXwnd->DestroyWindow();
	delete(pDXwnd);
	pDXwnd = NULL;
/*	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�*/
	/*CDXwnd dxwnd;
	CString className=::AfxRegisterWndClass(0);
	dxwnd.Create(className,(LPCTSTR)"DXWnd", WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 640, 480),NULL,NULL,NULL,false);
	dxwnd.ShowWindow(SW_SHOW);
	dxwnd.UpdateWindow();

	dxwnd.InitDX();
	dxwnd.DispIt();*/

	return FALSE;
}
