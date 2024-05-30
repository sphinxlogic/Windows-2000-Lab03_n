
/******************************************************************************\
********************************************************************************
* Filename: RmOptionsDlg.cpp
*
* Description: Implementation of CRmOptionsDlg
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/

#include "stdafx.h"
#include "rmoptions.h"
#include "RmOptionsDlg.h"
#include "direct.h"

/////////////////////////////////////////////////////////////////////////////
// CRmOptionsDlg


CRmOptionsDlg::CRmOptionsDlg()
{
	m_pOptions = new CRmOptions;
	m_bCreatedOptions = TRUE;

}
CRmOptionsDlg::~CRmOptionsDlg()
{
	if(m_bCreatedOptions)
		delete m_pOptions;

}

LRESULT CRmOptionsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetDlgItemText(IDC_LOG, m_pOptions -> GetLogDir());
	SetDlgItemText(IDC_RECOVER, m_pOptions -> GetRecDir());	
	return 1;  // Let the system set the focus
}

LRESULT CRmOptionsDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{

	
	
	TCHAR sPath[MAX_PATH];
	GetDlgItemText(IDC_LOG, sPath, MAX_PATH);

	
	LPTSTR p = sPath + lstrlen(sPath) - 1; 
	if (*p != '\\')
	{
		p++;
		*p = '\\';
		p++;
		*p = NULL;
	}
	
	if (!CheckDirectory(sPath))
		return 0;
	
	m_pOptions -> SetLogDir(sPath);
	GetDlgItemText(IDC_RECOVER, sPath, MAX_PATH);
	p = sPath + lstrlen(sPath) - 1; 
	if (*p != '\\')
	{
		p++;
		*p = '\\';
		p++;
		*p = NULL;
	}
	
	if (!CheckDirectory(sPath))
		return 0;

	
	m_pOptions -> SetRecDir(sPath);
	EndDialog(wID);			
	return 0;
}

LRESULT CRmOptionsDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);		
	return 0;
}


void CRmOptionsDlg::ShowMessage()
{
	LPTSTR lpMsgBuf = NULL;
	FormatMessage( 
					FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,
					0,
					NULL 
			);

	
	if (lpMsgBuf)
	{
		// Display the string.
		MessageBox(lpMsgBuf, L"GetLastError", MB_OK|MB_ICONINFORMATION );

		// Free the buffer.
		LocalFree( lpMsgBuf );
	}
}

BOOL CRmOptionsDlg::CheckDirectory(BSTR sDir)
{
	
	
	// make sure dirs exist
	TCHAR sCurWD[MAX_PATH];


	 /* Get the current working directory: */
	if( _tgetcwd( sCurWD, MAX_PATH ) == NULL )
	{
		_ASSERTE(0); // why would this fail?
		return FALSE;
	}


	// try to set the currect directory to the sDir
	if (_tchdir(sDir) == -1)
	{	
		TCHAR sMsg[1024];
		wsprintf(sMsg, L"The directory %s does not exist.\nDo you wish to create it?", sDir);				
		if (MessageBox(sMsg, L"CopyFileRm", MB_ICONQUESTION|MB_YESNO) == IDNO)
			return FALSE;
		else
		{
			if (_tmkdir( sDir ) != 0)
			{
				wsprintf(sMsg, L"Unable to create directory '%s'", sDir);
				MessageBox(sMsg, L"CopyFileRm", MB_ICONSTOP);
				return FALSE;
			}

		}

	}

	_tchdir(sCurWD);
	return TRUE;
}
