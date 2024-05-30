// cstm2dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICSAgentNTService.h"
#include "cstm2dlg.h"
#include "ICSAgentNTServiceaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog


CCustom2Dlg::CCustom2Dlg()
	: CAppWizStepDlg(CCustom2Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCustom2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom2Dlg)
	DDX_Control(pDX, IDC_SCP, m_ManualButton);
	DDX_Control(pDX, IDC_POLL_CHECK, m_PollBox);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom2Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	if (m_PollBox.GetCheck())
		DefineMacro("SERVICE_POLL_CONTINUOUSLY", "TRUE");

	if (m_ManualButton.GetCheck())
		DefineMacro("SERVICE_MANUAL_CONTROL", "TRUE");


	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom2Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom2Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg message handlers
