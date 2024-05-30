// MtsSpy.h : Declaration of the CMtsSpy

#ifndef __MTSSPY_H_
#define __MTSSPY_H_

#include "resource.h"       // main symbols

#include "mtsevents.h"

#define IF_AUDIT_DO(x)						\
	if (m_pSpy -> Audit())					\
		m_pSpy -> GetAuditObj() -> x		


/////////////////////////////////////////////////////////////////////////////
// CMtsSpy
class ATL_NO_VTABLE CMtsSpy : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMtsSpy, &CLSID_MtsSpy>,
	public CComControl<CMtsSpy>,
	public CStockPropImpl<CMtsSpy, IMtsSpy, &IID_IMtsSpy, &LIBID_MTSSPYCTLLib>,
	public IProvideClassInfo2Impl<&CLSID_MtsSpy, NULL, &LIBID_MTSSPYCTLLib>,
	public IPersistStreamInitImpl<CMtsSpy>,
	public IPersistStorageImpl<CMtsSpy>,
	public IQuickActivateImpl<CMtsSpy>,
	public IOleControlImpl<CMtsSpy>,
	public IOleObjectImpl<CMtsSpy>,
	public IOleInPlaceActiveObjectImpl<CMtsSpy>,
	public IViewObjectExImpl<CMtsSpy>,
	public IOleInPlaceObjectWindowlessImpl<CMtsSpy>,
	public IDataObjectImpl<CMtsSpy>,
	public ISpecifyPropertyPagesImpl<CMtsSpy>,
	public IPropertyBag
{

private:
	HRESULT EnableAudit(BOOL bEnable);
	MapStringToPackageInfo m_map;
	BOOL m_bLogToFile;
	HANDLE m_hFile;
	CComBSTR m_sLogFile;
	int m_cEvents;
	HWND m_hWndList;
	BOOL m_bShowGridLines;	
	BOOL m_bAudit;
	HFONT m_hFont;
	long m_nWidth[NUMBER_COLUMNS];
	BOOL m_bShowOnScreen;
	BOOL m_bCSV;
	HMENU m_hMenuDebug; //the Debug menu
	IMtsSqlAudit * m_pSqlAudit;

public:

	BOOL Audit(){return m_bAudit;}
	IMtsSqlAudit * GetAuditObj(){return m_pSqlAudit;}
	CComPtr<IFontDisp> m_pFont;
	CContainedWindow m_ctlSysListView32;
	~CMtsSpy() 
	{
		m_hWndList = NULL;	

	}
	void FinalRelease()
	{
		SafeRelease(m_pSqlAudit);
	}
	CMtsSpy() :	
		m_ctlSysListView32(_T("SysListView32"), this, 1)
	{
 		m_hWndList = NULL;
		m_bLogToFile = FALSE;
		m_hFile = NULL;
		m_cEvents = 0;
		m_bShowGridLines = TRUE;
		m_bWindowOnly = TRUE; 
		for (int i=0;i<NUMBER_COLUMNS;i++)
		{
			m_nWidth[i] = 60;
		}
		
		m_hFont = NULL;
		m_bShowOnScreen = TRUE;
		m_bCSV = FALSE;
		m_bAudit = FALSE;
		m_pSqlAudit = NULL;
	}

	BOOL ShouldScroll(int nIndex);
	HRESULT ShutdownPackage(LPCOLESTR sPackageName);	
	BOOL AddEventToList(LONGLONG perfCount, LPCOLESTR sEvent, LPCOLESTR sPackage);
	BOOL AddParamValueToList(LPCOLESTR sParamName, LPCOLESTR sValue);


DECLARE_REGISTRY_RESOURCEID(IDR_MTSSPY)

BEGIN_COM_MAP(CMtsSpy)
	COM_INTERFACE_ENTRY(IMtsSpy)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IPropertyBag)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CMtsSpy)
	PROP_ENTRY_EX( "LogFile", DISPID_LOGFILE, CLSID_MtsSpyPropPage, IID_IMtsSpy)
	PROP_ENTRY_EX( "ShowGridLines", DISPID_GRIDLINES, CLSID_MtsSpyPropPage, IID_IMtsSpy)
	PROP_ENTRY_EX( "Audit", DISPID_AUDIT, CLSID_MtsSpyPropPage, IID_IMtsSpy)
	PROP_ENTRY_EX( "ColWidth", DISPID_COLWIDTH, CLSID_MtsSpyPropPage, IID_IMtsSpy)	
	PROP_PAGE(CLSID_StockFontPage)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(CMtsSpy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)

ALT_MSG_MAP(1)
	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
	COMMAND_ID_HANDLER(ID_LOG, OnLogToFile)
	COMMAND_ID_HANDLER(ID_CHOOSE_LOG_FILE_NAME, OnChooseLogFile)
	COMMAND_ID_HANDLER(ID_SAVE, OnSave)
	COMMAND_ID_HANDLER(ID_CLEAR, OnClear)
	COMMAND_ID_HANDLER(ID_OPTIONS_GRID_LINES, OnToggleGridLines)	
	COMMAND_ID_HANDLER(ID_AUDIT, OnToggleAudit)	
	COMMAND_ID_HANDLER(ID_SHOW_ON_SCREEN, OnToggleShowOnScreen)
	COMMAND_ID_HANDLER(IDM_ABOUT, OnAbout)
	MESSAGE_HANDLER(WM_INITMENU, OnInitMenu)
	COMMAND_ID_HANDLER(IDM_SELECT_PACKAGES, OnSelectPackages)
	COMMAND_ID_HANDLER(ID_CHOOSEFONT, OnChooseFont)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	COMMAND_RANGE_HANDLER(ID_DEBUG_BEGIN, ID_DEBUG_END, OnDebugPackage)
END_MSG_MAP()

LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
LRESULT OnLogToFile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnChooseLogFile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnInitMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
LRESULT OnSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnClear(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnToggleGridLines(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnToggleAudit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
LRESULT OnSelectPackages(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnChooseFont(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnToggleShowOnScreen(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
LRESULT OnDebugPackage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);




STDMETHOD(Close)(DWORD dwSaveOption);
	
STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		IOleInPlaceObjectWindowlessImpl<CMtsSpy>::SetObjectRects(prcPos, prcClip);
		int cx, cy;
		cx = prcPos->right - prcPos->left;
		cy = prcPos->bottom - prcPos->top;
		::SetWindowPos(m_ctlSysListView32.m_hWnd, NULL, 0,
			0, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);

		
		return S_OK;
	}

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// IMtsSpy
public:
	BOOL AddRunningAspsToDebugMenu(HMENU hMenu);
	STDMETHOD(ChooseLogFile)(/*[out]*/ BSTR * sLogFileName, /*[out]*/ BOOL * bCanceled);
	STDMETHOD(get_ShowOnScreen)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_ShowOnScreen)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_Audit)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_Audit)(/*[in]*/ BOOL newVal);
	STDMETHOD(ChooseFont)();
	STDMETHOD(get_LogToFile)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_LogToFile)(/*[in]*/ BOOL newVal);
	STDMETHOD(About)();
	STDMETHOD(ClearAllEvents)();
	STDMETHOD(SaveToFile)();
	STDMETHOD(SelectPackages)();
	HFONT CreateHFontFromIFont(IFont * pFont);
	STDMETHOD(get_ColWidth)(short nColumn, /*[out, retval]*/ long *pVal);
	STDMETHOD(put_ColWidth)(short nColumn, /*[in]*/ long newVal);
	STDMETHOD(get_ShowGridLines)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_ShowGridLines)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_LogFile)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_LogFile)(/*[in]*/ BSTR newVal);
	HRESULT OnDrawAdvanced(ATL_DRAWINFO& di);

	HRESULT STDMETHODCALLTYPE putref_Font(IFontDisp* pFont)
	{
		CComQIPtr<IFont, &IID_IFont> pIFont(pFont);						
		if (pIFont)
		{			
			if (m_hFont)
			{
				DeleteObject(m_hFont);
				m_hFont = NULL;

			}
			m_hFont = CreateHFontFromIFont(pIFont);			
			if (m_hFont)
			{								
				::SendMessage(m_hWndList, WM_SETFONT, (WPARAM)m_hFont, 0L);
			}
		}


		if (FireOnRequestEdit(DISPID_FONT) == S_FALSE)
			return S_FALSE;
		m_pFont = pFont;
		m_bRequiresSave = TRUE;
		FireOnChanged(DISPID_FONT);
		FireViewChange();
		return S_OK;
		
	}

	STDMETHOD(Read)(LPCOLESTR pszPropName,VARIANT* pVar,IErrorLog* pErrorLog )
	{
		return S_OK;
	}

	STDMETHOD(Write)(LPCOLESTR pszPropName,VARIANT* pVar)
	{
		return S_OK;
	}

	HRESULT IPersistStreamInit_Load(LPSTREAM pStm, ATL_PROPMAP_ENTRY* pMap);
	HRESULT IPersistStreamInit_Save(LPSTREAM pStm, BOOL /* fClearDirty */,
		ATL_PROPMAP_ENTRY* pMap);


};

#endif //__MTSSPY_H_
