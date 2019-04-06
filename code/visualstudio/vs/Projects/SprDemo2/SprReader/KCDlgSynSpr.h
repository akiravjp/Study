#pragma once
#include "afxcmn.h"

#include "SprConverter.h"

class KCDialogRename;

#define MAXFILENUM 5000			//����һ�����򿪵��ļ�����
//
struct KStrcutSynSpr{
	CString fname;
	unsigned int nFrame;
};
typedef struct KStrcutSynSpr KStrcutSynSpr;

// KCDlgSynSpr dialog

class KCDlgSynSpr : public CDialog
{
	DECLARE_DYNAMIC(KCDlgSynSpr)

public:
	KCDlgSynSpr(CWnd* pParent = NULL);   // standard constructor
	virtual ~KCDlgSynSpr();

// Dialog Data
	enum { IDD = IDD_DIALOGSYNSPR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	KCDialogRename *m_pKCDlgRename;	// �½��Ի���
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonsyn();


	unsigned int m_nFrame;			// ��Ҫת��֡��
	CString m_FileName;				// �ϳ�Sprite������
	FSprHead m_SprHead;				// SPR�ļ�ͷ
	afx_msg void OnBnClickedButleave();
	afx_msg void OnBnClickedButtonDeleteAll();
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	CString m_Interval;
	afx_msg void OnBnClickedButtonRename();
	void RenameUpdate(void);
};


extern KStrcutSynSpr g_KSSynSpr;