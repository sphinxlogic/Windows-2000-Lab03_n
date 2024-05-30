#if !defined(AFX_ICSAGENTWIZAW_H__8CCE97B0_2B15_11D2_9879_00C04FAE2339__INCLUDED_)
#define AFX_ICSAGENTWIZAW_H__8CCE97B0_2B15_11D2_9879_00C04FAE2339__INCLUDED_

// ICSAgentWizaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see ICSAgentWiz.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CICSAgentWizAppWiz : public CCustomAppWiz
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

// This declares the one instance of the CICSAgentWizAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global ICSAgentWizaw.  (Its definition is in ICSAgentWizaw.cpp.)
extern CICSAgentWizAppWiz ICSAgentWizaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICSAGENTWIZAW_H__8CCE97B0_2B15_11D2_9879_00C04FAE2339__INCLUDED_)
