// RipProp.h : Declaration of the CRipProp

#ifndef __RIPPROP_H_
#define __RIPPROP_H_

#include "resource.h"       // main symbols
#include "ripple.h"
#include "cripple.h"


EXTERN_C const CLSID CLSID_RipProp;

/////////////////////////////////////////////////////////////////////////////
// CRipProp
class ATL_NO_VTABLE CRipProp :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CRipProp, &CLSID_RipProp>,
	public IPropertyPageImpl<CRipProp>,
	public CDialogImpl<CRipProp>
{
public:
	CRipProp() 
	{
    	    m_dwTitleID = IDS_TITLERipProp;
    	    m_dwHelpFileID = IDS_HELPFILERipProp;
	    m_dwDocStringID = IDS_DOCSTRINGRipProp;
	}

	enum {IDD = IDD_RIPPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_RIPPROP)

BEGIN_COM_MAP(CRipProp) 
	COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CRipProp)
   COMMAND_HANDLER(IDC_ORIGIN, EN_CHANGE, OnEditChange)
   COMMAND_HANDLER(IDC_WAVELEN, EN_CHANGE, OnEditChange)
   COMMAND_HANDLER(IDC_AMPLITUDE, EN_CHANGE, OnEditChange)
   COMMAND_HANDLER(IDC_NUMWAVES, EN_CHANGE, OnEditChange)
   MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)

   CHAIN_MSG_MAP(IPropertyPageImpl<CRipProp>)
END_MSG_MAP()

        LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); 
        HRESULT ShowError(void);
        void SetDlgItemFloat(int id, float val);
        float GetDlgItemFloat(int id);
	STDMETHOD(Apply)(void);
        LRESULT OnEditChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);
};

#endif //__RIPPROP_H_
