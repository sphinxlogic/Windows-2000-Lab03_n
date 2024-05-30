// ICSAgentNTServiceaw.cpp : implementation file
//

#include "stdafx.h"
#include "ICSAgentNTService.h"
#include "ICSAgentNTServiceaw.h"
#include "chooser.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CICSAgentNTServiceAppWiz::InitCustomAppWiz()
{
	// Create a new dialog chooser; CDialogChooser's constructor initializes
	//  its internal array with pointers to the steps.
	m_pChooser = new CDialogChooser;

	// Set the maximum number of steps.
	SetNumberOfSteps(LAST_DLG);

	// TODO: Add any other custom AppWizard-wide initialization here.
}

// This is called just before the custom AppWizard is unloaded.
void CICSAgentNTServiceAppWiz::ExitCustomAppWiz()
{
	// Deallocate memory used for the dialog chooser
	ASSERT(m_pChooser != NULL);
	delete m_pChooser;
	m_pChooser = NULL;

	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
//  or "Next" on one of the custom AppWizard's steps.
CAppWizStepDlg* CICSAgentNTServiceAppWiz::Next(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Next(pDlg);
}

// This is called when the user clicks "Back" on one of the custom
//  AppWizard's steps.
CAppWizStepDlg* CICSAgentNTServiceAppWiz::Back(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Back(pDlg);
}

void CICSAgentNTServiceAppWiz::CustomizeProject(IBuildProject* pProject)
{
	// TODO: Add code here to customize the project.  If you don't wish
	//  to customize project, you may remove this virtual override.
	
	// This is called immediately after the default Debug and Release
	//  configurations have been created for each platform.  You may customize
	//  existing configurations on this project by using the methods
	//  of IBuildProject and IConfiguration such as AddToolSettings,
	//  RemoveToolSettings, and AddCustomBuildStep. These are documented in
	//  the Developer Studio object model documentation.

	// WARNING!!  IBuildProject and all interfaces you can get from it are OLE
	//  COM interfaces.  You must be careful to release all new interfaces
	//  you acquire.  In accordance with the standard rules of COM, you must
	//  NOT release pProject, unless you explicitly AddRef it, since pProject
	//  is passed as an "in" parameter to this function.  See the documentation
	//  on CCustomAppWiz::CustomizeProject for more information.

	IConfigurations * pConfigurations;
	long lNumConfigs;

	pProject->get_Configurations(&pConfigurations);
	pConfigurations->get_Count(&lNumConfigs);

	for (long lConfigNum = 1; lConfigNum < lNumConfigs + 1; lConfigNum++)
	{
		_bstr_t varTool;
		_bstr_t varSwitch;
		_variant_t varConfigNum;
		IConfiguration * pConfiguration;
		
		varConfigNum = lConfigNum;
		pConfigurations->Item(varConfigNum, &pConfiguration);

		//
		//  Add libraries to our project
		// 

		varTool = "link.exe";
		varSwitch = "addrlkup.lib edkguid.lib mapi32.lib ole32.lib \
					 edkmapi.lib edkdebug.lib version.lib edkutils.lib kernel32.lib \
					 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib \
					 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib \
					 /nologo /subsystem:console /NODEFAULTLIB:LIBC";
		pConfiguration->AddToolSettings(varTool, varSwitch, varConfigNum);

		pConfiguration->Release();
	}

	pConfigurations->Release();
}


// Here we define one instance of the CICSAgentNTServiceAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global ICSAgentNTServiceaw.
CICSAgentNTServiceAppWiz ICSAgentNTServiceaw;

