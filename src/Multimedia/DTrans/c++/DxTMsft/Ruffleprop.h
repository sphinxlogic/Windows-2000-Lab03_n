// RuffleProp.h : Declaration of the CRuffleProp

#ifndef __RUFFLEPROP_H_
#define __RUFFLEPROP_H_

#include "resource.h"       // main symbols
#include "Ruffle.h"

EXTERN_C const CLSID CLSID_RuffleProp;
//const CLSID CLSID_RuffleProp = {0x69EE49C6,0x6268,0x11D1,{0xB8,0x3E,0x00,0xA0,0xC9,0x33,0xBE,0x86}};
/////////////////////////////////////////////////////////////////////////////
// CRuffleProp
class ATL_NO_VTABLE CRuffleProp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRuffleProp, &CLSID_RuffleProp>,
	public IPropertyPageImpl<CRuffleProp>,
	public CDialogImpl<CRuffleProp>
{
public:
	CRuffleProp() 
	{
		m_dwTitleID = IDS_TITLERuffleProp;
		m_dwHelpFileID = IDS_HELPFILERuffleProp;
		m_dwDocStringID = IDS_DOCSTRINGRuffleProp;
	}

	enum {IDD = IDD_RUFFLEPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_RUFFLEPROP)

BEGIN_COM_MAP(CRuffleProp) 
	COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CRuffleProp)
	COMMAND_HANDLER(IDC_Ruffle_MaxRotations, EN_CHANGE, OnEditChange)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)

	CHAIN_MSG_MAP(IPropertyPageImpl<CRuffleProp>)
END_MSG_MAP()

 LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); 
        HRESULT ShowError(void);
        //void SetDlgItemFloat(int id, float val);
        //float GetDlgItemFloat(int id);
		ULONG GetDlgItemInt(int id);
		
		STDMETHOD(Apply)(void);
        LRESULT OnEditChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);
	
};

#endif //__RUFFLEPROP_H_
