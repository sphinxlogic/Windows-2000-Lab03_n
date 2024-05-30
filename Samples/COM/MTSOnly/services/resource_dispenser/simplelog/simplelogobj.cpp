
/******************************************************************************\
********************************************************************************
* Filename: SimpleLogObj.cpp
*
* Description: 

*	implementation of a structured storage based log.
*	each transaction is written to its own stream, where the name of the stream
*	is the GUID of the transaction
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
#include "..\..\..\common\inc\SimpleLog.h"
#include "SimpleLogObj.h"

//
// the name of a stream in OLE Structured storage is limited to 37
// chars -- we want to name streams with GUIDs (as strings), which
// are 39 chars -- to get around this, we will 64bit encode the name
// of the GUID
//
// These characters are the legal digits, in order, that are
// used in Base64 encoding
//
const WCHAR rgwchBase64[] =
    L"ABCDEFGHIJKLMNOPQ"
    L"RSTUVWXYZabcdefgh"
    L"ijklmnopqrstuvwxy"
    L"z0123456789+*";


STDMETHODIMP CSimpleLogObj::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISimpleLog,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
CSimpleLogObj::CSimpleLogObj()
{
	m_pStorage = NULL;
	m_bInRecovery = FALSE;

} // CSimpleLogObj:CSimpleLogObj()

CSimpleLogObj::~CSimpleLogObj(void)
{	
	// Realocate space for the recovery directory path name.
	if (NULL != m_pStorage)
	{		
		m_pStorage -> Release();
	}

} // CSimpleLogObj::~CSimpleLogObj

//
//	Init()
//
//	Pass in the filename of the log (pszLogFileName) 
//	read the registery to find the log dir, and open
//	the file using structured storage.  if the file doesn't
//	exit, create it
//
HRESULT CSimpleLogObj::Init(BSTR pszLogFileName)
{
	BOOL				fNew = FALSE;
	
	
	HRESULT hr = StgOpenStorage(
						pszLogFileName, 	//Pointer to the path of the file containing storage object
						NULL, 	//Pointer to a previous opening of a root storage object
						STGM_DIRECT | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 	//Access mode for the object
						NULL, 	//String name block specifying elements to be excluded
						0, 	//Reserved; must be zero
						&m_pStorage	//Indirect pointer to the storage object
					   );

	if (FAILED(hr))
	{

	
		if (hr == STG_E_FILENOTFOUND)
		{
			hr =  StgCreateDocfile(	pszLogFileName, 	//Pointer to path of compound file to create
									STGM_TRANSACTED | STGM_SHARE_EXCLUSIVE | STGM_READWRITE ,	//Access mode for the new storage object
									NULL,
									&m_pStorage	//Indirect pointer to the new storage object
												);	
		}
		if (FAILED(hr))
		{
			::MessageBox(NULL, _T("Failed to open log.  Make sure you don't have another instance running."), _T("CopyFileRm"), MB_ICONSTOP);
			return hr;
		}

	}

	_ASSERTE(m_pStorage);
	return S_OK;
}
//
//	Write the specified info to the log.
//
//	1. we Create (or Open) a stream with the name representing the GUID
//	2. we write the Command into it
//	3. we close the stream
//
STDMETHODIMP CSimpleLogObj::WriteLog(GUID guidTx,LOG_RM_COMMAND eOp, BYTE * pByte, long cbBytes)
{ 
//	if (m_bInRecovery)
//		return E_FAIL;


	HRESULT hr;
	IStream * pStream;
	hr = GetStream(&pStream, guidTx, TRUE);

	if (FAILED(hr))
	{
		_ASSERTE(0);
			return hr;
	}
	ULONG cbWritten;
// seek to the end of the stream;
	LARGE_INTEGER liOff;
	ULARGE_INTEGER liNewPosition;
	LISet32(liOff,  0);
	hr = pStream -> Seek(liOff, STREAM_SEEK_END, &liNewPosition);
	
	if (eOp != LOG_RM_PRIVATE)
	{
	// write the command
		hr = pStream -> Write((void *)&eOp, sizeof(eOp), &cbWritten);	
		_ASSERTE(hr==S_OK);
	}
	

// if the structure exists, and it is not the end of the xact
// don't write the rest of the info if it 
	if (cbBytes && eOp != LOG_RM_XACT_END) 
	{
		// write the struct size
		hr = pStream -> Write((void *)&cbBytes, sizeof(cbBytes), &cbWritten);	
		_ASSERTE(hr==S_OK);

		// write the byte stream
		hr = pStream -> Write((void *)pByte, cbBytes, &cbWritten);	

		_ASSERTE((long)cbWritten == cbBytes);
	}


// commit the write 
	hr = pStream -> Commit(STGC_DEFAULT);

// commit the storage
	hr = m_pStorage -> Commit(STGC_DEFAULT);
	_ASSERTE(hr == S_OK);

// release (close) the stream;
	pStream -> Release();

	return S_OK;
}
//
//	gets a storage that has all of the streams that need to be recovered
//
//	the stream starts with the GUID that is the TxId, followed by RM_BEGIN_TX
//	and then the rest of the information 
//
#define ENUM_GRANULARITY 10
STDMETHODIMP CSimpleLogObj::RecoveryInfo(IStorage **ppStorage)
{
	m_bInRecovery = TRUE;
	_ASSERTE(m_pStorage);
	IEnumSTATSTG * pEnum = NULL;

	*ppStorage = NULL;

	HRESULT hr;
	ILockBytes *pLkbyte = NULL;
	hr = CreateILockBytesOnHGlobal(NULL,TRUE, &pLkbyte);
	
	if (FAILED(hr))
	{
		_ASSERTE(0);
		return hr;
	}

	hr = StgCreateDocfileOnILockBytes(pLkbyte, STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE, NULL, ppStorage);
	if (FAILED(hr))
	{
		pLkbyte -> Release();
		_ASSERTE(0);
		return hr;
	}

//enumate through the existing streams, looking for streams that DO NOT end in LOG_RM_XACT_END
// these are the ones that need to be recovered...

	hr = m_pStorage -> EnumElements(NULL, NULL, NULL, &pEnum);
	_ASSERTE(hr == S_OK);
	STATSTG statstg[ENUM_GRANULARITY];
	ULONG lFetched = 0;
	ULONG i = 0;
	IStream * pStream = NULL;
	LARGE_INTEGER liOff;
	ULARGE_INTEGER liNewPosition;
	long lSizeCommand = sizeof(LOG_RM_COMMAND);
	ULARGE_INTEGER MaxInt;
	MaxInt.HighPart = (ULONG)-1;
	MaxInt.LowPart = (ULONG)-1;
	LOG_RM_COMMAND eOp;
	ULONG cbBytesRead;
	do
	{
		hr = pEnum -> Next(ENUM_GRANULARITY, statstg, &lFetched);
		for (i=0; i<lFetched; i++)
		{
			
			// get the stream
			pStream = NULL;
			hr =  m_pStorage -> OpenStream(
								statstg[i].pwcsName, 	//Pointer to string containing name of stream to open
								NULL, 	//Reserved
								STGM_DIRECT | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 	//Access mode for the new stream
								NULL, 	//Reserved
								&pStream	//Indirect pointer to opened stream object
							   );
			
			_ASSERTE(hr == S_OK);
			LISet32(liOff,  -1 * lSizeCommand);
			// seek to the end of the stream, and back up sizeof(LOG_RM_ACTION)
			hr = pStream -> Seek(liOff, STREAM_SEEK_END, &liNewPosition);
			// read the value
			hr = pStream -> Read(&eOp, sizeof(eOp), &cbBytesRead);
			_ASSERTE(cbBytesRead == sizeof(eOp));
			
			if (eOp != LOG_RM_XACT_END)
			{
				
				IStream * pNewStream;
				pNewStream = NULL;

				
				hr = (*ppStorage) -> CreateStream(
									statstg[i].pwcsName,
									STGM_CREATE|STGM_DIRECT | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 	
									NULL, NULL, 
									&pNewStream	
								   );
				// seek back to the beginning
				LISet32(liOff,  0);
				pStream -> Seek(liOff, STREAM_SEEK_SET, &liNewPosition);
				_ASSERTE(liNewPosition.LowPart == 0);
				// tx need to be recovered, copy the stream from the file to the storage
				hr = pStream -> CopyTo(pNewStream, 
										MaxInt,
										NULL, NULL);
												  
							
				pStream -> Release();
				pNewStream -> Release();
			}
			else
			{
				pStream -> Release();
				//	
				//	the transaction has been completed, we can remove it
				//  from our log...
				//
				hr = m_pStorage -> DestroyElement(statstg[i].pwcsName);
				_ASSERTE(hr == S_OK);
			}
					
		} // end for

	}while (lFetched == ENUM_GRANULARITY);

	pEnum -> Release();
	m_bInRecovery = FALSE;
	return S_OK;
}


//
//	64 bit encodes the guidTx and opens the stream with that name.
//	if the stream does not exist, it creates the stream (if bCreate is TRUE)
//	and then writes the GUID to the stream
//
HRESULT CSimpleLogObj::GetStream(IStream **pStream, GUID &guidTx,  BOOL bCreate)
{

	HRESULT hr;
	CComBSTR sStreamName;
	hr = ToBase64((void *)&guidTx, sizeof(GUID), &sStreamName.m_str);
	_ASSERTE(hr == S_OK);
	_ASSERTE(sStreamName.m_str);
	
	hr =  m_pStorage -> OpenStream(
								sStreamName.m_str, 	//Pointer to string containing name of stream to open
								NULL, 	//Reserved
								STGM_DIRECT | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 	//Access mode for the new stream
								NULL, 	//Reserved
								pStream	//Indirect pointer to opened stream object
							   );


	if (FAILED(hr))
	{
		if (hr == STG_E_FILENOTFOUND && bCreate)
		{
			// create the stream
			hr = m_pStorage -> CreateStream(
									sStreamName.m_str,
									STGM_DIRECT | STGM_SHARE_EXCLUSIVE | STGM_READWRITE, 	
									NULL, NULL, 
									pStream	
								   );
			if (FAILED(hr))
			{
				_ASSERTE(0);				
				return hr;
			}

			DWORD cbWritten;
			hr = (*pStream) -> Write(&guidTx, sizeof(guidTx), &cbWritten);
		}
	}
	
	return hr;
}
//
//	Streams in IStorage are limited to <39 chars, which is how long
//	a GUID as a string is...so we are going to encode them in base64
//
HRESULT CSimpleLogObj::ToBase64(LPVOID pv, ULONG cbStart, BSTR* pbstr)
//
// Encode and return the bytes in base 64
//
    {
    ULONG cb = cbStart;
    *pbstr = NULL;
    HRESULT hr = S_OK;
    int cchPerLine = 72;                        // conservative, must be mult of 4 for us
    int cbPerLine  = cchPerLine / 4 * 3;
    int cbSafe     = cb + 3;                    // allow for padding
    int cLine      = cbSafe / cbPerLine + 2;    // conservative
    int cchNeeded  = cLine * (cchPerLine + 2 /*CRLF*/) + 1 /*NULL*/;
    int cbNeeded   = cchNeeded * sizeof(WCHAR);
    LPWSTR wsz = (LPWSTR)CoTaskMemAlloc(cbNeeded);
    if (wsz)
        {
        BYTE*  pb   = (BYTE*)pv;
        WCHAR* pch  = wsz;
        int cchLine = 0;
        //
        // Main encoding loop
        //
        while (cb >= 3)
            {
            BYTE b0 =                     ((pb[0]>>2) & 0x3F);
            BYTE b1 = ((pb[0]&0x03)<<4) | ((pb[1]>>4) & 0x0F);
            BYTE b2 = ((pb[1]&0x0F)<<2) | ((pb[2]>>6) & 0x03);
            BYTE b3 = ((pb[2]&0x3F));

            *pch++ = rgwchBase64[b0];
            *pch++ = rgwchBase64[b1];
            *pch++ = rgwchBase64[b2];
            *pch++ = rgwchBase64[b3];

            pb += 3;
            cb -= 3;
            
            // put in line breaks
            cchLine += 4;
            if (cchLine >= cchPerLine)
                {
                *pch++ = L'\r';
                *pch++ = L'\n';
                cchLine = 0;
                }
            }
        //
        // Account for gunk at the end
        //
        *pch++ = L'\r';     // easier than keeping track
        *pch++ = L'\n';
        if (cb==0)
            {
            // nothing to do
            }
        else if (cb==1)
            {
            BYTE b0 =                     ((pb[0]>>2) & 0x3F);
            BYTE b1 = ((pb[0]&0x03)<<4) | 0;
            *pch++ = rgwchBase64[b0];
            *pch++ = rgwchBase64[b1];
            *pch++ = L'=';
            *pch++ = L'=';
            }
        else if (cb==2)
            {
            BYTE b0 =                     ((pb[0]>>2) & 0x3F);
            BYTE b1 = ((pb[0]&0x03)<<4) | ((pb[1]>>4) & 0x0F);
            BYTE b2 = ((pb[1]&0x0F)<<2) | 0;
            *pch++ = rgwchBase64[b0];
            *pch++ = rgwchBase64[b1];
            *pch++ = rgwchBase64[b2];
            *pch++ = L'=';
            }
        
        //
        // NULL terminate the string
        //
        *pch = NULL;

        //
        // Allocate our final output
        //
        *pbstr = SysAllocString(wsz);
        if (*pbstr==NULL)
            hr = E_OUTOFMEMORY;

        CoTaskMemFree(wsz);
        }
    else
        hr = E_OUTOFMEMORY;

    #ifdef _DEBUG
    if (hr==S_OK)
        {
        BLOB b;
        FromBase64(*pbstr, &b);
        _ASSERTE(b.cbSize == cbStart);
        _ASSERTE(memcmp(b.pBlobData, pv, cbStart) == 0);
        CoTaskMemFree(b.pBlobData);
        }
    #endif

    return hr;
    }



HRESULT CSimpleLogObj::FromBase64(BSTR bstr, BLOB* pblob)
//
// Decode and return the Base64 encoded bytes
//
    {
    HRESULT hr = S_OK;
    int cbNeeded = lstrlenW(bstr);      // an upper bound
    BYTE* rgb = (BYTE*)CoTaskMemAlloc(cbNeeded);
    if (rgb)
        {
        BYTE  mpwchb[256];
        BYTE  bBad = (BYTE)-1;
        int   i;
        //
        // Initialize our decoding array
        //
        memset(&mpwchb[0], bBad, 256);
        for (i = 0; i < 64; i++)
            {
            WCHAR wch = rgwchBase64[i];
            mpwchb[wch] = i;
            }

        //
        // Loop over the entire input buffer
        //
        ULONG bCurrent = 0;         // what we're in the process of filling up
        int  cbitFilled = 0;        // how many bits in it we've filled
        BYTE* pb = rgb;             // current destination (not filled)
        //
        for (WCHAR* pwch=bstr; *pwch; pwch++)
            {
            WCHAR wch = *pwch;
            //
            // Ignore white space
            //
            if (wch==0x0A || wch==0x0D || wch==0x20 || wch==0x09)
                continue;
            //
            // Have we reached the end?
            //
            if (wch==L'=')
                break;
            //
            // How much is this character worth?
            //
            BYTE bDigit = mpwchb[wch];
            if (bDigit==bBad)
                {
                hr = E_INVALIDARG;
                break;
                }
            //
            // Add in its contribution
            //
            bCurrent <<= 6;
            bCurrent |= bDigit;
            cbitFilled += 6;
            //
            // If we've got enough, output a byte
            //
            if (cbitFilled >= 8)
                {
                ULONG b = (bCurrent >> (cbitFilled-8));     // get's top eight valid bits
                *pb++ = (BYTE)(b&0xFF);                     // store the byte away
                cbitFilled -= 8;
                }
            }

        if (hr==S_OK)
            {
            pblob->pBlobData = rgb;
            pblob->cbSize = pb-rgb;
            }
        else
            {
            CoTaskMemFree(rgb);
            pblob->pBlobData = NULL;
            }
        }
    else
        hr = E_OUTOFMEMORY;
    return hr;
}

STDMETHODIMP CSimpleLogObj::WriteStreamToLog(GUID guidTx, LOG_RM_COMMAND eOp, IStream * pStreamIn)
{
	HRESULT hr;
	IStream * pStream;
	hr = GetStream(&pStream, guidTx, TRUE);

	if (FAILED(hr))
	{
		_ASSERTE(0);
		return hr;
	}
	ULONG cbWritten;
// seek to the end of the stream;
	LARGE_INTEGER liOff;
	ULARGE_INTEGER liNewPosition;
	LISet32(liOff,  0);
	hr = pStream -> Seek(liOff, STREAM_SEEK_END, &liNewPosition);

	if (eOp != LOG_RM_PRIVATE)
	{
	// write the command
		hr = pStream -> Write((void *)&eOp, sizeof(eOp), &cbWritten);	
		_ASSERTE(hr==S_OK);
	}
	


	if (pStreamIn)
	{
		// get info from the stream

		STATSTG stat;
		ZeroMemory(&stat, sizeof(stat));

		hr = pStreamIn -> Stat(&stat, STATFLAG_NONAME);
		_ASSERTE(hr==S_OK);
		_ASSERTE(stat.cbSize.HighPart == 0);
		ULONG cbBytes = stat.cbSize.LowPart;

	// if the structure exists, and it is not the end of the xact
	// don't write the rest of the info if it 
		if (cbBytes && eOp != LOG_RM_XACT_END) 
		{
			// write the struct size
			hr = pStream -> Write((void *)&cbBytes, sizeof(cbBytes), &cbWritten);	
			_ASSERTE(hr==S_OK);

			// write the byte stream
			hr = pStreamIn -> CopyTo(pStream, stat.cbSize, NULL, NULL);
			_ASSERTE(hr == S_OK);
			LARGE_INTEGER li;
			li.LowPart = -1 * stat.cbSize.LowPart;
			li.HighPart = 0; // limits our size...
			hr = pStreamIn -> Seek(li, STREAM_SEEK_CUR, NULL);
			_ASSERTE(hr == S_OK);
		}
	}


// commit the write 
	hr = pStream -> Commit(STGC_DEFAULT);

// commit the storage
	hr = m_pStorage -> Commit(STGC_DEFAULT);
	_ASSERTE(hr == S_OK);

// release (close) the stream;
	pStream -> Release();

	return S_OK;
	
}

STDMETHODIMP CSimpleLogObj::RemoveTxStream(GUID guidTx)
{
	HRESULT hr;
	CComBSTR sStreamName;
	hr = ToBase64((void *)&guidTx, sizeof(GUID), &sStreamName.m_str);
	_ASSERTE(hr == S_OK);
	_ASSERTE(sStreamName.m_str);
	hr = m_pStorage -> DestroyElement(sStreamName);

	if (FAILED(hr))
	{
		_ASSERTE(0);			
	}

	return hr;
}

STDMETHODIMP CSimpleLogObj::WriteVariantToLog(GUID guidTx, VARIANT * pVariant)
{
	HRESULT hr;
	IStream * pStream;
	hr = GetStream(&pStream, guidTx, TRUE);

	if (FAILED(hr))
	{
		_ASSERTE(0);
		return hr;
	}
//
//	Seek to the end
//

	LARGE_INTEGER liOff;
	ULARGE_INTEGER liNewPosition;
	liOff.QuadPart = 0;
	hr = pStream -> Seek(liOff, STREAM_SEEK_END, &liNewPosition);
	_ASSERTE(hr==S_OK);
	CComVariant var(*pVariant);
	hr = var.WriteToStream(pStream);
	if (SUCCEEDED(hr))
	{
	// commit the write 
		hr = pStream -> Commit(STGC_DEFAULT);

	// commit the storage
		hr = m_pStorage -> Commit(STGC_DEFAULT);
		_ASSERTE(hr == S_OK);
	}

	pStream -> Release();
	return hr;
}

STDMETHODIMP CSimpleLogObj::GetStream(GUID guidTx, IStream * * ppStream)
{
	HRESULT hr;
	hr = GetStream(ppStream, guidTx, FALSE);
	return hr;
}
