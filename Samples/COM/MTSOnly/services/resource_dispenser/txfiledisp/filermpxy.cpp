
/******************************************************************************\
********************************************************************************
* Filename: FileRmPxy.cpp
*
* Description:  Implementation of the RM Proxy. Also registers
				the resource dispenser
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
#include "..\..\..\common\inc\TxFileDisp.h"
#include "..\..\..\common\inc\copyfilerm.h"
#include "mtxdm.h"
#include "txcoord.h"
#include "FileRmPxy.h"
#include "txdtc.h"
#include "xolehlp.h"
#include "eh.h"


CFileRmPxy::CFileRmPxy()
{
	m_pRm = NULL;
	m_pDispMan = NULL;
	m_pHolder = NULL;
	m_pFreeThreadedMarshaler = NULL;
	m_pGIT = NULL;
	
}
CFileRmPxy::~CFileRmPxy() 
{

	ATLTRACE(_T("FileRmPxy is being destroyed.\n"));


}

STDMETHODIMP CFileRmPxy::CopyDirTx(long hConnection, BSTR sSource, BSTR sDestination)
{

	HRESULT hr;	
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;

	
	// Do Work
	WIN32_FIND_DATA fd;
	memset(&fd, NULL, sizeof(fd));
	HANDLE hFile;
	CComBSTR sFileSource;
	CComBSTR sFileDest;
	LPTSTR lpSource = sSource;
	LPTSTR lpDest = sDestination;
	TCHAR sTemp[MAX_PATH];
	TCHAR lpFileSpec[MAX_PATH];
	memset(lpFileSpec, NULL, MAX_PATH);
	memset(sTemp, NULL, MAX_PATH);
	wsprintf(lpFileSpec, L"%s\\*.*", lpSource);
	BOOL bFound = TRUE;
	DWORD dwTest;

	hFile = FindFirstFile(lpFileSpec, &fd);	
	while (hFile != INVALID_HANDLE_VALUE && bFound)
	{
		dwTest = fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
		if (dwTest == 0) // copy if not a dir
		{
			wsprintf(sTemp, L"%s\\%s", lpSource, fd.cFileName);
			sFileSource = sTemp;
			wsprintf(sTemp, L"%s\\%s", lpDest, fd.cFileName);
			sFileDest = sTemp;			
			pRm -> AddFile(hConnection, sFileSource, sFileDest);
		}

		memset(&fd, NULL, sizeof(fd));	
		bFound = FindNextFile(hFile, &fd);	
	}

	FindClose(hFile);
	hr = pRm -> CopyListTx(hConnection);		
	SafeRelease(pRm);
	return hr;
}

#ifdef _DEBUG
void CFileRmPxy::ShowMessage()
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
			MessageBox( NULL, lpMsgBuf, L"GetLastError", MB_OK|MB_ICONINFORMATION );

			
			// Free the buffer.
			LocalFree( lpMsgBuf );
		}
}
#endif

STDMETHODIMP CFileRmPxy::AddFile(long hConnection, BSTR sSource, BSTR sDestination)
{
	HRESULT hr;	
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;

	
	hr = pRm -> AddFile(hConnection, sSource, sDestination);
	SafeRelease(pRm);
	return hr;
}

STDMETHODIMP CFileRmPxy::CopyFilesInCopyList(long hConnection)
{
	
	HRESULT hr;	
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;

	
	hr = pRm -> CopyListTx(hConnection);
	SafeRelease(pRm);
	return hr;
	
}


STDMETHODIMP CFileRmPxy::Connect(long *hConnection)
{
	if (m_pDispMan)
	{
		if (!m_pHolder)
		{
			_ASSERTE(0);
			return E_INVALIDARG;
		}
	}
		
	if (!m_pRm)
	{
		_ASSERTE(0);
		return E_INVALIDARG;
	}
	
	HRESULT hr;	
	if (m_pDispMan)
	{
		*hConnection = NULL;
		hr = m_pHolder -> AllocResource((RESID)1, (RESID *)hConnection);
		if (FAILED(hr))
		{
			AtlTrace(_T("AllocResource failed! Error code %x\n"), hr);
		}
	}
	else  // not running under MTS, we must create our own resource
	{
		TIMEINSECS timeout;
		hr = CreateResource((RESID)1,(RESID *)hConnection,&timeout);
	}	
	return hr;
}
STDMETHODIMP CFileRmPxy::Disconnect(long hConnection)
{


	if (m_pDispMan)
	{
		if (!m_pHolder)
		{
			_ASSERTE(0);
			return E_INVALIDARG;
		}
	}
		
	if (!m_pRm)
	{
		_ASSERTE(0);
		return E_INVALIDARG;
	}

	HRESULT hr;	
	if (m_pDispMan)
	{	
		hr = m_pHolder -> FreeResource(hConnection);
	}
	else
	{
		hr = DestroyResource(hConnection);
	}
	
	_ASSERTE(hr == S_OK);
	return hr;
}
STDMETHODIMP CFileRmPxy::CopyFileTx(long hConnection,BSTR sSource,BSTR sDestination,  BOOL bFailIfExists)
{
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;
	HRESULT hr = pRm -> FileCopyTx(hConnection, sSource, sDestination, bFailIfExists);
	SafeRelease(pRm);
	return hr;
	
}
STDMETHODIMP CFileRmPxy::MoveFileTx(long hConnection,BSTR sSource,BSTR sDestination)
{
	IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;
	HRESULT hr = pRm -> FileMoveTxt(hConnection, sSource, sDestination);
	SafeRelease(pRm);
	return hr;		
}
STDMETHODIMP CFileRmPxy::DeleteFileTx(long hConnection,BSTR sFileName)
{
		IFileRm * pRm = GetFileRmPointer();
	if (!pRm)
		return E_UNEXPECTED;
	HRESULT hr = pRm -> FileDeleteTx(hConnection, sFileName);
	SafeRelease(pRm);
	return hr;		
	
}