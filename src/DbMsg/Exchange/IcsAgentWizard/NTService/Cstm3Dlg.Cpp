// cstm3dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICSAgentNTService.h"
#include "cstm3dlg.h"
#include "ICSAgentNTServiceaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg dialog


CCustom3Dlg::CCustom3Dlg()
	: CAppWizStepDlg(CCustom3Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom3Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCustom3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom3Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom3Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	// TODO: Set template variables based on the dialog's data.

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom3Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom3Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom3Dlg message handlers
