
/******************************************************************************\
********************************************************************************
* Filename: rmoptions.h
*
* Description: 

		Contains a class that encapsulates all options for the CopyFileRm
		Automatically persists/loads itself to/from the registry

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
class CRmOptions
{
private:
	HKEY m_hKey;
	CComBSTR m_sLogDir;
	CComBSTR m_sRecDir;
public:
		
	CComBSTR & GetLogDir(){return m_sLogDir;}
	CComBSTR & GetRecDir(){return m_sRecDir;}

	BOOL SetLogDir(BSTR sLogDir)
	{

		m_sLogDir = sLogDir;
		_ASSERTE(m_hKey);
		if (!m_sLogDir.m_str)
		{
			_ASSERTE(0);	
			return FALSE;
		}

		LPTSTR lpszValueName = _T("LogDir");
		if (RegSetValueEx(m_hKey, lpszValueName, NULL, REG_SZ, (BYTE *)m_sLogDir.m_str, m_sLogDir.Length() * 2) == 0)
			return TRUE;
		return FALSE;

	}

	BOOL SetRecDir(BSTR sRecDir)
	{

		m_sRecDir = sRecDir;
		_ASSERTE(m_hKey);
		if (!m_sRecDir.m_str)
		{
			_ASSERTE(0);	
			return FALSE;
		}

		LPTSTR lpszValueName = _T("RecoverDir");
		if (RegSetValueEx(m_hKey, lpszValueName, NULL, REG_SZ, (BYTE *)m_sRecDir.m_str, m_sRecDir.Length() * 2) == 0)
			return TRUE;

		return FALSE;

	}


	CRmOptions()
	{
		LPTSTR sKey= L"Software\\Microsoft\\CopyFileRm";
		DWORD dwDisp;
		LONG lRes = RegCreateKeyEx( HKEY_CURRENT_USER, sKey, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,NULL, &m_hKey, &dwDisp);	
		_ASSERTE(m_hKey);
		TCHAR szDir[MAX_PATH];
		DWORD dw = 0;
		DWORD dwType = 0;
		TCHAR* lpszValueName = L"LogDir";
		lRes = RegQueryValueEx(m_hKey, (TCHAR*)lpszValueName, NULL, &dwType, 
									NULL, &dw);
		if (lRes == ERROR_SUCCESS)
		{
			_ASSERTE(dwType == REG_SZ);
			TCHAR* lpsz = szDir;
			lRes = RegQueryValueEx(m_hKey, (TCHAR*)lpszValueName, NULL, &dwType, (BYTE*)lpsz, &dw);		
			_ASSERTE(lRes == ERROR_SUCCESS);
		}
		else
		{
			GetTempPath(MAX_PATH, szDir); // if it is not in the registery, put it in the temp directory			
		}

		m_sLogDir = szDir;
		dw = 0;
		dwType = REG_SZ;
		lpszValueName = L"RecoverDir";
		lRes = RegQueryValueEx(m_hKey, (TCHAR*)lpszValueName, NULL, &dwType, NULL, &dw);
		if (lRes == ERROR_SUCCESS)
		{
			_ASSERTE(dwType == REG_SZ);
			TCHAR* lpsz = szDir;
			lRes = RegQueryValueEx(m_hKey, (TCHAR*)lpszValueName, NULL, &dwType, (BYTE*)lpsz, &dw);		
			_ASSERTE(lRes == ERROR_SUCCESS);
		}
		else
		{
			GetTempPath(MAX_PATH, szDir); // if it is not in the registery, put it in the temp directory			
			
		}			

		m_sRecDir = szDir;
	}

	~CRmOptions()
	{
		RegCloseKey(m_hKey);
	}

};
