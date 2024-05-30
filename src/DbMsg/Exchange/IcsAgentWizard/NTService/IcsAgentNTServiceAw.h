#if !defined(AFX_ICSAGENTNTSERVICEAW_H__2A802944_2D4D_11D2_9879_00C04FAE2339__INCLUDED_)
#define AFX_ICSAGENTNTSERVICEAW_H__2A802944_2D4D_11D2_9879_00C04FAE2339__INCLUDED_

// ICSAgentNTServiceaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see ICSAgentNTService.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CICSAgentNTServiceAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);

protected:
	CDialogChooser* m_pChooser;
};

// This declares the one instance of the CICSAgentNTServiceAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global ICSAgentNTServiceaw.  (Its definition is in ICSAgentNTServiceaw.cpp.)
extern CICSAgentNTServiceAppWiz ICSAgentNTServiceaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICSAGENTNTSERVICEAW_H__2A802944_2D4D_11D2_9879_00C04FAE2339__INCLUDED_)
