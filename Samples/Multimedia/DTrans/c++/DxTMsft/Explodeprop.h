// ExplodeProp.h : Declaration of the CExplodeProp

#ifndef __ExplodePROP_H_
#define __ExplodePROP_H_

#include "resource.h"       // main symbols
#include "Explode.h"

EXTERN_C const CLSID CLSID_ExplodeProp;
					 
/////////////////////////////////////////////////////////////////////////////
// CExplodeProp
class ATL_NO_VTABLE CExplodeProp :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CExplodeProp, &CLSID_ExplodeProp>,
	public IPropertyPageImpl<CExplodeProp>,
	public CDialogImpl<CExplodeProp>
{
public:
	CExplodeProp() 
	{
        m_dwTitleID = IDS_TITLEExplodeProp;
        m_dwHelpFileID = IDS_HELPFILEExplodeProp;
        m_dwDocStringID = IDS_DOCSTRINGExplodeProp;
	}

	enum {IDD = IDD_ExplodePROP};

    DECLARE_REGISTRY_RESOURCEID(IDR_EXPLODEPROP)

    BEGIN_COM_MAP(CExplodeProp) 
	    COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
    END_COM_MAP()

    BEGIN_MSG_MAP(CExplodeProp)
       //COMMAND_HANDLER(IDC_Explode_, EN_CHANGE, OnEditChange)
       COMMAND_HANDLER(IDC_Explode_Tumble, EN_CHANGE, OnEditChange)
       COMMAND_HANDLER(IDC_Explode_MaxRotations, EN_CHANGE, OnEditChange)
       COMMAND_HANDLER(IDC_Explode_FinalVelocity, EN_CHANGE, OnEditChange)
       COMMAND_HANDLER(IDC_Explode_PositionJump, EN_CHANGE, OnEditChange)
       COMMAND_HANDLER(IDC_Explode_DecayTime, EN_CHANGE, OnEditChange)
       MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
       CHAIN_MSG_MAP(IPropertyPageImpl<CExplodeProp>)
    END_MSG_MAP()

    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); 
    HRESULT ShowError(void);
    void SetDlgItemFloat(int id, float val);
    float GetDlgItemFloat(int id);
	ULONG GetDlgItemInt(int id);
	
	STDMETHOD(Apply)(void);
    LRESULT OnEditChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled);
};

#endif //__ExplodePROP_H_
