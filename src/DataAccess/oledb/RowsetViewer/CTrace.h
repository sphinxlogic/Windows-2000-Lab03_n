//-----------------------------------------------------------------------------
// Microsoft OLE DB RowsetViewer
// Copyright (C) 1994 - 1999 By Microsoft Corporation.
//
// @doc
//
// @module CTRACE.H
//
//-----------------------------------------------------------------------------------

#ifndef _CTRACE_H_
#define _CTRACE_H_
										   

/////////////////////////////////////////////////////////////////////
// Includes
//
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
// Defines
//
/////////////////////////////////////////////////////////////////////
#define TRACE_ADDREF							CTrace::TraceAddRef
#define TRACE_RELEASE(pIUnk, name)				{ CTrace::TraceRelease(pIUnk, name); pIUnk = NULL;				}
#define TRACE_RELEASE_(pIUnk, name, ulRefCount)	{ CTrace::TraceRelease(pIUnk, name, ulRefCount); pIUnk = NULL;	}
#define TRACE_QI								CTrace::TraceQI
#define TRACE_METHOD							CTrace::TraceMethod
#define TRACE_NOTIFICATION						CTrace::TraceNotification



/////////////////////////////////////////////////////////////////////
// CTrace
//
/////////////////////////////////////////////////////////////////////
class CTrace : public CRichEditLite
{
public:
	//constructors
	CTrace(CMainWindow* pCMainWindow);
	virtual ~CTrace();

	//messages
	virtual BOOL	OnRButtonDown(WPARAM fwKeys, REFPOINTS pts);
	virtual BOOL	OnContextMenu(HWND hWnd, REFPOINTS pts);

	virtual BOOL	OnCommand(UINT iID, HWND hWndCtrl);
	virtual BOOL	OnUpdateCommand(HMENU hMenu, UINT nID, DWORD* pdwFlags);
	virtual BOOL	OnUpdateOutputSelected();
			 
	//ListBox (Notifcations)
	virtual HRESULT Clear();
	virtual void	OutputTextFmt(DWORD dwMask, COLORREF dwColor, WCHAR* pwszFmt, ...);
	virtual void	OutputText(DWORD dwMask, COLORREF dwColor, WCHAR* pwszText);
	virtual void	OutputLineEnd();
	virtual void	OutputIndent(ULONG cIndentLevel);
	
	//Static functions, so everyone has access to tracing support...
	static  CTrace*	GetTrace();
	static  ULONG	TraceAddRef(IUnknown* pIUnknown, WCHAR* pwszText);
	static	ULONG	TraceRelease(IUnknown* pIUnknown, WCHAR* pwszText, ULONG ulExpectedRefCount = 1);
	static  HRESULT TraceQI(IUnknown* pIUnknown, REFIID riid, IUnknown** ppIUnknown, WCHAR* pwszFmt = L"IUnknown");
	static	HRESULT TraceMethod(HRESULT hrActual, WCHAR* pwszFmt, ...);
	static	HRESULT TraceNotification(DWORD dwNotifyType, HRESULT hrVeto, WCHAR* pwszInterface, WCHAR* pwszMethod, WCHAR* pwszParams, ...);

	//Trace Provider Receiver
	static	HRESULT CreateTraceProvider();
	static	HRESULT EnableProvider(WCHAR* pwszProgID, BOOL fEnable = TRUE);
	static	HRESULT TraceReceiver(DBLENGTH cbPackageDataLen, BYTE* pPackageData);

	virtual HRESULT TracePackage(IDBTracePackage* pIDBTracePackage);
	virtual HRESULT TraceParameter(IDBTraceParameter* pIDBTraceParameter, BOOL fFirstParam);

	//Data
	CMainWindow*				m_pCMainWindow;

	//Trace Provider
	IDBTracePackage*			m_pIDBTracePackage;
	IDBTraceControlProviders*	m_pIDBTraceControlProviders;
	ULONG						m_ulNestingLevel;
};



/////////////////////////////////////////////////////////////////////
// CMDITrace
//
/////////////////////////////////////////////////////////////////////
class CMDITrace : public CMDIChildLite
{
public:
	//constructors
	CMDITrace(CMainWindow* pCMainWindow);
	virtual ~CMDITrace();

	virtual BOOL	PreCreateWindow(CREATESTRUCTW& cs);
	virtual BOOL	OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL	AutoPosition(BOOL fDefaultPosition = TRUE);

	virtual BOOL	OnDestroy();
	virtual BOOL	OnClose();
	virtual BOOL	OnInitialUpdate();
	virtual BOOL	OnMDIActivate(BOOL bActivate, HWND hWndActivate, HWND hWndDeactivate);

	//members
	virtual BOOL	UpdateControls();
	
	//Messages
	virtual BOOL	OnSize(WPARAM nType,REFPOINTS pts);
	virtual BOOL	OnSetFocus(HWND hWndPrevFocus);

	//Overloads
	virtual BOOL	OnCommand(UINT iID, HWND hWndCtrl);
	virtual BOOL	OnNotify(INT idCtrl, NMHDR* pNMHDR);
	virtual BOOL	OnUpdateCommand(HMENU hMenu, UINT nID, DWORD* pdwFlags);

	//Data
	CMainWindow*	m_pCMainWindow;
	CTrace*			m_pCTrace;
};




#endif	//_CTRACE_H_
