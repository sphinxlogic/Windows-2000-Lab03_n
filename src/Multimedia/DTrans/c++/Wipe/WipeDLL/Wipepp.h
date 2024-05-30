/*******************************************************************************
* WipePP.h *
*----------*
*   Description:
*       This is the header file for the CDXTWipePropPage implementation.
*-------------------------------------------------------------------------------
*  Created By: EDC                                      Date: 01/06/98
*  Copyright (C) 1998 Microsoft Corporation
*  All Rights Reserved
*
*-------------------------------------------------------------------------------
*  Revisions:
*
*******************************************************************************/
#ifndef WipePP_h
#define WipePP_h

//--- Additional includes
#include "wipe.h"
#include "resource.h"       // main symbols

//=== Constants ====================================================
EXTERN_C const CLSID CLSID_DXTWipePropPage;

//=== Class, Enum, Struct and Union Declarations ===================

/*** CDXTWipePropPage
*
*/
class ATL_NO_VTABLE CDXTWipePropPage :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CDXTWipePropPage, &CLSID_DXTWipePropPage>,
    public IPropertyPageImpl<CDXTWipePropPage>,
    public CDialogImpl<CDXTWipePropPage>
{
  /*=== ATL Setup ===*/
  public:
    DECLARE_REGISTRY_RESOURCEID(IDR_DXTWIPEPROPPAGE)

    BEGIN_COM_MAP(CDXTWipePropPage) 
	COM_INTERFACE_ENTRY_IMPL(IPropertyPage)
    END_COM_MAP()

    BEGIN_MSG_MAP(CDXTWipePropPage)
        MESSAGE_HANDLER( WM_INITDIALOG, OnInitDialog )
        COMMAND_HANDLER( IDC_GRAD_SIZE, EN_CHANGE, OnEditChange )
        COMMAND_HANDLER( IDC_DURATION, EN_CHANGE, OnEditChange )
        COMMAND_HANDLER( IDC_WIPE_STYLE, CBN_CLOSEUP, OnEditChange )
        CHAIN_MSG_MAP(IPropertyPageImpl<CDXTWipePropPage>)
    END_MSG_MAP()

    enum {IDD = IDD_DXTWIPEPROPPAGE};

  /*=== Methods =======*/
  public:
    //--- Constructors
    CDXTWipePropPage() 
    {
	m_dwTitleID     = IDS_TITLEDXTWipePropPage;
	m_dwHelpFileID  = IDS_HELPFILEDXTWipePropPage;
	m_dwDocStringID = IDS_DOCSTRINGDXTWipePropPage;
    }

    //--- Helpers
    float GetDlgItemFloat(int id);

    //--- Interface methods
    STDMETHOD( Apply )(void);

    //--- Message handlers
    LRESULT OnInitDialog( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ); 
    LRESULT OnEditChange( WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled );
};

#endif /* This must be the last line in the file */
