// **************************************************************************
// Copyright (c) 1997-1999 Microsoft Corporation.
//
// File:  OnConnect.cpp
//
// Description:
//	This file implements the OnConnect() routine which 
//		demonstrates how to connect to CIMOM and one if
//		its namespaces.
// 
// History:
//
// **************************************************************************

#include "stdafx.h"
#include "WBEMSampDlg.h"

// **************************************************************************
//
//	CWBEMSampleDlg::OnConnect()
//
// Description:
//		Connects to the namespace specified in the edit box.
//
// Parameters:
//		None.
//
// Returns:
//		Nothing.
//
// Globals accessed:
//		None.
//
// Globals modified:
//		None.
//
//===========================================================================
void CWBEMSampleDlg::OnConnect() 
{
	IWbemLocator *pIWbemLocator = NULL;

	UpdateData();
	//------------------------
   // Create an instance of the WbemLocator interface.
   if(CoCreateInstance(CLSID_WbemLocator,
					  NULL,
					  CLSCTX_INPROC_SERVER,
					  IID_IWbemLocator,
					  (LPVOID *) &pIWbemLocator) == S_OK)
   {
		//------------------------
		// Use the pointer returned in step two to connect to
		//     the server using the passed in namespace.
		BSTR pNamespace = m_namespace.AllocSysString();
		HRESULT hr = S_OK;

		if((hr = pIWbemLocator->ConnectServer(pNamespace,
								NULL,   //using current account for simplicity
								NULL,	//using current password for simplicity
								0L,		// locale
								0L,		// securityFlags
								NULL,	// authority (domain for NTLM)
								NULL,	// context
								&m_pIWbemServices)) == S_OK) 
		{	
			SetBlanket();
			// indicate success.
			m_outputList.ResetContent();
			m_outputList.AddString(_T("Connected To Namespace"));

			// its safe the hit the other buttons now.
			m_enumServices.EnableWindow(TRUE);
			m_enumServicesAsync.EnableWindow(TRUE);
			m_enumDisks.EnableWindow(TRUE);
			m_diskDetails.EnableWindow(TRUE);
			m_connect.EnableWindow(TRUE);
			m_addEquipment.EnableWindow(TRUE);
			m_diskDescriptions.EnableWindow(TRUE);

			// dont allow reconnection.
			m_connect.EnableWindow(FALSE);

			// since these guys register for the non-standard
			// root/default/office namespace, dont enable them unless 
			// that namespace exists.
			if(CheckOfficeNamespace())
			{
				m_perm.EnableWindow(TRUE);
				m_temp.EnableWindow(TRUE);
			}

			// initialize the Register Perm button.
			if(PermRegistered())
			{
				// init for UNregistering.
				m_regPerm = FALSE;
				m_perm.SetWindowText(_T("Unregister &Perm"));
			}
			else // its not registered...
			{
				// init for registering.
				m_regPerm = TRUE;
				m_perm.SetWindowText(_T("Register &Perm"));
			}
		}
		else
		{	
			// failed ConnectServer()
			AfxMessageBox(_T("Bad namespace"));
		}

		// done with pNamespace.
		if(pNamespace) 
		{
			SysFreeString(pNamespace);
		}

		//------------------------
		// done with pIWbemLocator. 
		if (pIWbemLocator)
		{ 
			pIWbemLocator->Release(); 
			pIWbemLocator = NULL;
		}
	}
	else // failed CoCreateInstance()
	{	
		AfxMessageBox(_T("Failed to create IWbemLocator object"));

	} // endif CoCreateInstance()
	
}
// **************************************************************************
//
//	CWBEMSampleDlg::SetBlanket()
//
// Description:
//		Adjusts the security blanket on the IWbemServices pointer.
//
// Parameters:
//		None.
//
// Returns:
//		Nothing.
//
// Globals accessed:
//		None.
//
// Globals modified:
//		None.
//
//===========================================================================
void CWBEMSampleDlg::SetBlanket(void) 
{
    if(m_pIWbemServices)
    {
        IClientSecurity* pCliSec;

        if(SUCCEEDED(m_pIWbemServices->QueryInterface(IID_IClientSecurity, 
														(void**)&pCliSec)))
        {

			HRESULT hr = pCliSec->SetBlanket(m_pIWbemServices, 
											RPC_C_AUTHN_WINNT, 
											RPC_C_AUTHZ_NONE,
											NULL, 
											RPC_C_AUTHN_LEVEL_CONNECT, 
											RPC_C_IMP_LEVEL_IMPERSONATE,
											NULL, 
											EOAC_NONE);

			pCliSec->Release();
		}
    }

}