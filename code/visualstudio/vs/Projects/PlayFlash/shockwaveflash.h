#if !defined(AFX_SHOCKWAVEFLASH_H__B015C623_EC3C_41E4_809E_D1A4D5FA7858__INCLUDED_)
#define AFX_SHOCKWAVEFLASH_H__B015C623_EC3C_41E4_809E_D1A4D5FA7858__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CShockwaveFlash wrapper class

class CShockwaveFlash : public CWnd
{
protected:
	DECLARE_DYNCREATE(CShockwaveFlash)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xd27cdb6e, 0xae6d, 0x11cf, { 0x96, 0xb8, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	long GetReadyState();
	long GetTotalFrames();
	BOOL GetPlaying();
	void SetPlaying(BOOL bNewValue);
	long GetQuality();
	void SetQuality(long nNewValue);
	long GetScaleMode();
	void SetScaleMode(long nNewValue);
	long GetAlignMode();
	void SetAlignMode(long nNewValue);
	long GetBackgroundColor();
	void SetBackgroundColor(long nNewValue);
	BOOL GetLoop();
	void SetLoop(BOOL bNewValue);
	CString GetMovie();
	void SetMovie(LPCTSTR lpszNewValue);
	long GetFrameNum();
	void SetFrameNum(long nNewValue);
	void SetZoomRect(long left, long top, long right, long bottom);
	void Zoom(long factor);
	void Pan(long x, long y, long mode);
	void Play();
	void Stop();
	void Back();
	void Forward();
	void Rewind();
	void StopPlay();
	void GotoFrame(long FrameNum);
	long CurrentFrame();
	BOOL IsPlaying();
	long PercentLoaded();
	BOOL FrameLoaded(long FrameNum);
	long FlashVersion();
	CString GetWMode();
	void SetWMode(LPCTSTR lpszNewValue);
	CString GetSAlign();
	void SetSAlign(LPCTSTR lpszNewValue);
	BOOL GetMenu();
	void SetMenu(BOOL bNewValue);
	CString GetBase();
	void SetBase(LPCTSTR lpszNewValue);
	CString GetScale();
	void SetScale(LPCTSTR lpszNewValue);
	BOOL GetDeviceFont();
	void SetDeviceFont(BOOL bNewValue);
	BOOL GetEmbedMovie();
	void SetEmbedMovie(BOOL bNewValue);
	CString GetBGColor();
	void SetBGColor(LPCTSTR lpszNewValue);
	CString GetQuality2();
	void SetQuality2(LPCTSTR lpszNewValue);
	void LoadMovie(long layer, LPCTSTR url);
	void TGotoFrame(LPCTSTR target, long FrameNum);
	void TGotoLabel(LPCTSTR target, LPCTSTR label);
	long TCurrentFrame(LPCTSTR target);
	CString TCurrentLabel(LPCTSTR target);
	void TPlay(LPCTSTR target);
	void TStopPlay(LPCTSTR target);
	void SetVariable(LPCTSTR name, LPCTSTR value);
	CString GetVariable(LPCTSTR name);
	void TSetProperty(LPCTSTR target, long property, LPCTSTR value);
	CString TGetProperty(LPCTSTR target, long property);
	void TCallFrame(LPCTSTR target, long FrameNum);
	void TCallLabel(LPCTSTR target, LPCTSTR label);
	void TSetPropertyNum(LPCTSTR target, long property, double value);
	double TGetPropertyNum(LPCTSTR target, long property);
	double TGetPropertyAsNumber(LPCTSTR target, long property);
	CString GetSWRemote();
	void SetSWRemote(LPCTSTR lpszNewValue);
	CString GetFlashVars();
	void SetFlashVars(LPCTSTR lpszNewValue);
	CString GetAllowScriptAccess();
	void SetAllowScriptAccess(LPCTSTR lpszNewValue);
	CString GetMovieData();
	void SetMovieData(LPCTSTR lpszNewValue);
	LPUNKNOWN GetInlineData();
	void SetInlineData(LPUNKNOWN newValue);
	BOOL GetSeamlessTabbing();
	void SetSeamlessTabbing(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOCKWAVEFLASH_H__B015C623_EC3C_41E4_809E_D1A4D5FA7858__INCLUDED_)
