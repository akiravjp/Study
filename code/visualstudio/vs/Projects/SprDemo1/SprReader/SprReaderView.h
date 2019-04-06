// SprReaderView.h : interface of the CSprReaderView class
//

#include <d3d9.h>
#include <d3dx9tex.h>
#include "MyFormView.h"
#include "MyDialog.h"
#include "MyDialogTool.h"
#include "KCDialogSet.h"
#include "KDlgSynSprite.h"
#include "stdafx.h"

#pragma once

class CSprReaderView : public CView
{
protected: // create from serialization only
	CSprReaderView();
	DECLARE_DYNCREATE(CSprReaderView)

// Attributes
public:
	CSprReaderDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSprReaderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// myself variable for spr
private:
	// Spr �ļ���ر���
	LPBYTE	m_pSprData;					// �洢Spr�ļ�����
	DWORD	m_uSprDataSize;				// Spr�ļ�����
	FSprHead*	m_pSprHead;				// Spr�ļ�ͷ
//	FSprPal*	m_pSprPaList;			// for old
//	FSprOffs*	m_pSprOffsList;			// for old
	FSprFrame**	m_ppSprFrameList;
	CString		m_FilePath;				// Spr�ļ�����׺�����֣�eg��xxx.spr; m_fileName = "xxx"
	unsigned	m_nFrame;				// ͼ��֡����

	//֡������س�Ա����
	IDirect3DSurface9* surface;			// 
	IDirect3DSurface9* backbuffer;		// 
	HRESULT hResult;					//
	RECT rect;							//
	UINT m_interval;					//

public:
	static int ms_times;				// ѭ�����ٴΣ�ȷ��ÿ����ʾ��֡
protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnViewPro();
	void Render();
public:
	CMyFormView* pMyFormView;
	CMyDialog *m_pMyDialogPro;
	CMyDialogTool *m_pMyDialogTool;
	KCDialogSet *m_pKCDialogSet;
	KDlgSynSprite *m_pKCDlgSynSpr;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnToolsOld2new();
	afx_msg void OnViewSet();
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	void ReNew(UINT interval);
	afx_msg void OnSynthesisSprite();
};

#ifndef _DEBUG  // debug version in SprReaderView.cpp
inline CSprReaderDoc* CSprReaderView::GetDocument() const
   { return reinterpret_cast<CSprReaderDoc*>(m_pDocument); }
#endif

//IDirect3DSurface9* getSurfaceFromFile(const char* filename, RECT *rect);


