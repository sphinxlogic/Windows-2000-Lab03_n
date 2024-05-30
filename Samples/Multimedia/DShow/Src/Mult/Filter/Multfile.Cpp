//==========================================================================;
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (c) 1997 - 1998  Microsoft Corporation.  All Rights Reserved.
//
//--------------------------------------------------------------------------;

#include <streams.h>

//  Include ATL string conversions
#include <atlbase.h>
#include <atlconv.h>
#include <atlconv.cpp>
#include <limits.h>

#include <asyncio.h>
#include <asyncrdr.h>
#include <initguid.h>
#include <amparse.h>
#include "multfile.h"
#include "multfili.h"

/*  Register */
const AMOVIESETUP_FILTER
sudMultiFile = { &CLSID_MultiFileReader       // class id
            , L"MultiFile Reader"             // strName
            , MERIT_DO_NOT_USE                // dwMerit
            , 0                               // nPins - no need to register any
            , NULL                            // lpPin
            };

//  No need to register pins etc etc
CFactoryTemplate g_Templates[] = {
    { L"MultiFile reader"
    , &CLSID_MultiFileReader
    , CMultiFileReader::CreateInstance
    , NULL
    , &sudMultiFile }
};

int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);

//  Registration

STDAPI
DllRegisterServer( void )
{
    return AMovieDllRegisterServer2( TRUE );
}

STDAPI
DllUnregisterServer( void )
{
  return AMovieDllRegisterServer2( FALSE );
}

/* Create a new instance of this class */

CUnknown *CMultiFileReader::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
    /*  DLLEntry does the right thing with the return code and
        returned value on failure
    */
    return new CMultiFileReader(pUnk, phr);
}

STDMETHODIMP CMultiFileReader::NonDelegatingQueryInterface(
    REFIID riid,
    void **ppv
)
{
    if (riid == IID_IMultiFileReader) {
        return GetInterface((IMultiFileReader *)this, ppv);
    } else
    if (riid == IID_IFileSourceFilter) {
        return GetInterface((IFileSourceFilter *)this, ppv);
    } else {
        return CAsyncReader::NonDelegatingQueryInterface(riid, ppv);
    }
}

CMultiFileReader::CMultiFileReader(LPUNKNOWN pUnk, HRESULT *phr) :
    CAsyncReader(NAME("CMultiFileReader"),
                 pUnk,
                 &m_Stream,
                 phr),
    m_Stream(m_Io.StopEvent(), this),
    m_bConnecting(false)
{
    m_clsid = CLSID_MultiFileReader;
    m_mt.SetType(&MEDIATYPE_Stream);
    m_mt.SetSubtype(&MEDIASUBTYPE_MPEG2_PROGRAM);
    /*  Work out file type */
    m_mt.bTemporalCompression = TRUE;	       //???
    m_mt.lSampleSize = 1;

}

IAMParse *CMultiFileReader::GetParser()
{
    IPin *pPin = m_OutputPin.GetConnected();
    IAMParse *pParse = NULL;
    if (pPin) {
        PIN_INFO pi;
        if (SUCCEEDED(pPin->QueryPinInfo(&pi)) &&pi.pFilter) {
            pi.pFilter->QueryInterface(IID_IAMParse, (void **)&pParse);
            pi.pFilter->Release();
        }
    }
    return pParse;
}

STDMETHODIMP CMultiFileReader::SetFile (LPCWSTR lpszFile,
                 LONGLONG llOffset,
                 LONGLONG llLength,
                 LONGLONG rtOffset,
                 HWND hwndNotify,
                 UINT uiMsgNotify,
                 WPARAM wParam,
                 HANDLE hEvent,
                 DWORD dwFlags
)
{
#ifdef DEBUG
    USES_CONVERSION;
    DbgLog((LOG_TRACE, 0, TEXT("SetFile(%s)"), W2T(lpszFile)));
#endif

#if 0
    //  Try to get to a synchronized state so we can read the
    //  start time from the parser
    m_Stream.ClearFile();

    //  Make sure we don't send any more data so we get a good reading
    //  on GetParseTime.
    IPin *pPin = m_OutputPin.GetConnected();
    IAMParse *pParse = NULL;
    if (pPin) {
        PIN_INFO pi;
        if (SUCCEEDED(pPin->QueryPinInfo(&pi)) &&pi.pFilter) {
            pi.pFilter->QueryInterface(IID_IAMParse, (void **)&pParse);
            pi.pFilter->Release();
        }
    }
    *prtStart = 0;
    if (pParse) {
        HANDLE hEvent[] = { m_Stream.m_hevStop, m_Stream.m_evSync };
        DWORD dwWaitResult = WaitForMultipleObjects(2, hEvent, FALSE, INFINITE);
        pParse->GetParseTime(prtStart);
        pParse->Release();
    }
#endif // 0

    HRESULT hr = m_Stream.SetFile(
        lpszFile,
        llOffset,
        llLength,
        rtOffset,
        hwndNotify,
        uiMsgNotify,
        wParam,
        hEvent,
        dwFlags
        );

    return hr;
}


HRESULT CMultiFileStream::FileStart(REFERENCE_TIME rtStart)
{
    if (!m_bSignalledTime && m_hwnd) {
        m_bSignalledTime = true;
        REFERENCE_TIME *prtStart = 
            (REFERENCE_TIME *)CoTaskMemAlloc(sizeof(rtStart));
        if (NULL == prtStart) {
            return E_OUTOFMEMORY;
        }
        *prtStart = rtStart;
        if (!PostMessage(m_hwnd, m_uiMsg, m_wParam, (LPARAM)prtStart)) {
            CoTaskMemFree((LPVOID)prtStart);
            return E_FAIL;
        }
    }
    return S_OK;
}

HRESULT CMultiFileStream::FileComplete(LPCWSTR pszFile)
{
    if (m_hwnd) {
        if (!PostMessage(m_hwnd, m_uiMsg, m_wParam, 0)) {
            return E_FAIL;
        }
    }
    if (m_hEvent) {
        EXECUTE_ASSERT(SetEvent(m_hEvent));
        m_hEvent = NULL;
    }
    return S_OK;
}

CMultiFileStream::CMultiFileStream(HANDLE hevStop, CMultiFileReader *pMFReader) :
    m_hFile(INVALID_HANDLE_VALUE),
    m_iFileNumber(0),
    m_bSignalledTime(false),
    m_hevStop(hevStop),
    m_pMFReader(pMFReader),
    m_strFile(NULL),
    m_dwFlags(0)
#if 0
    ,
    m_bWaitingForFile(false)
#endif
{
}


CMultiFileStream::~CMultiFileStream()
{
    if (m_hFile != INVALID_HANDLE_VALUE) {
        EXECUTE_ASSERT(CloseHandle(m_hFile));
    }
    delete [] m_strFile;
}

LONGLONG CMultiFileStream::Size(LONGLONG *pllSizeAvailable)
{
    if (pllSizeAvailable) {
        //  Only allow the size of the current file
        *pllSizeAvailable = 0;
        if (m_hFile) {
            if (m_pMFReader->IsConnecting()) {
                *pllSizeAvailable = m_llFileSize;
            } else {
                *pllSizeAvailable = m_llLength;
            }
        }
    }
    return _I64_MAX / (2 * UNITS);
}

#if 0
void CMultiFileStream::ClearFile()
{
    CAutoLock lck(&m_csLock);
    m_evSync.Reset();
    if (m_hFile != INVALID_HANDLE_VALUE) {
        EXECUTE_ASSERT(CloseHandle(m_hFile));
        m_hFile = INVALID_HANDLE_VALUE;
    }
    if (m_bWaitingForFile) {
        m_evSync.Set();
    }

}
#endif

HRESULT CMultiFileStream::SetFile (LPCWSTR lpszFile,
                 LONGLONG llOffset,
                 LONGLONG llLength,
                 LONGLONG rtOffset,
                 HWND hwndNotify,
                 UINT uiMsgNotify,
                 WPARAM wParam,
                 HANDLE hEvent,
                 DWORD dwFlags
                 )
{
    USES_CONVERSION;

    if (dwFlags & 
        ~(AM_MULTIFILE_READER_SEAMLESS |
          AM_MULTIFILE_READER_LAST     |
          AM_MULTIFILE_READER_FLUSH
          )
       ) {
        return E_INVALIDARG;
    }
    if (dwFlags & AM_MULTIFILE_READER_FLUSH) {
        IAMParse *pParse = m_pMFReader->GetParser();
        if (pParse) {
            pParse->Flush();
            pParse->Release();
        }
    }

    CAutoLock lck(&m_csLock);

    if (m_hFile != INVALID_HANDLE_VALUE) {
        EXECUTE_ASSERT(CloseHandle(m_hFile));
        m_hFile = INVALID_HANDLE_VALUE;
    }

    //  Handle EOS
    if (lpszFile == NULL) {
        if (dwFlags & AM_MULTIFILE_READER_LAST) {
            m_evNew.Set();
        }
        m_dwFlags = dwFlags;
        //  No file
        return S_OK;
    }

    if (m_strFile) {
        delete [] m_strFile;
    }
    m_strFile = new WCHAR [lstrlenWInternal(lpszFile) + 1];
    if (m_strFile == NULL) {
        return E_OUTOFMEMORY;
    }
    lstrcpyWInternal(m_strFile, lpszFile);

    HANDLE hFile = CreateFile(W2T(lpszFile),
                              GENERIC_READ,
                              FILE_SHARE_READ,
                              NULL,
                              OPEN_EXISTING,
                              0,
                              NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        DWORD dwError = GetLastError();
        return HRESULT_FROM_WIN32(dwError);
    }

    ULARGE_INTEGER uli;
    uli.QuadPart = (DWORDLONG)llLength;
    ULARGE_INTEGER uliSize;
    uliSize.LowPart = GetFileSize(hFile, &uliSize.HighPart);
    DWORD dwErr = GetLastError();

    ULARGE_INTEGER uliOffset;
    uliOffset.QuadPart = (DWORDLONG)llOffset;
    if (uliOffset.QuadPart > uliSize.QuadPart) {
        uliOffset.QuadPart = uliSize.QuadPart;
    }

    if (uliSize.LowPart != 0xFFFFFFFF || dwErr == 0) {

        //  Save file size for connection
        m_llFileSize = uliSize.QuadPart;
        if (uli.QuadPart + uliOffset.QuadPart > uliSize.QuadPart || uli.QuadPart == 0) {
            uli.QuadPart = uliSize.QuadPart - uliOffset.QuadPart;
        }
    } else {
        EXECUTE_ASSERT(CloseHandle(hFile));
        return HRESULT_FROM_WIN32(dwErr);
    }

    m_hFile = hFile;
    m_hwnd = hwndNotify;
    m_uiMsg = uiMsgNotify;
    m_wParam = wParam;
    m_hEvent = hEvent;
    m_rtOffset = rtOffset;

    if (hEvent) {
        EXECUTE_ASSERT(ResetEvent(hEvent));
    }
    m_llBytesLeft = uli.QuadPart;
    m_llLength = uli.QuadPart;
    m_llStart = uliOffset.QuadPart;
    m_iFileNumber++;
    m_bSignalledTime = false;
    m_evNew.Set();
    m_dwFlags = dwFlags;

    return S_OK;
}

//  Read more data.  Return with incomplete data if we reach the
//  end of a file
HRESULT CMultiFileStream::Read(
    PBYTE pbData,
    DWORD cbData,
    BOOL bAlign,
    DWORD *pcbBytesRead
)
{
    UNREFERENCED_PARAMETER(bAlign);
    *pcbBytesRead = 0;

    if (m_pMFReader->IsConnecting()) {
        if (m_hFile == INVALID_HANDLE_VALUE) {
            return E_UNEXPECTED;
        }
        if (!::ReadFile(m_hFile, (PVOID)pbData, cbData, pcbBytesRead, NULL)) {
            DWORD dwErr = GetLastError();
            return HRESULT_FROM_WIN32(dwErr);
        }
        return S_OK;
    }

#if 0
    m_evSync.Set();
#endif 

    /*  Read from the file until we satisfy the data required
        If necessary wait for a new file
    */
    bool bDone = false;
    bool bFirst = m_llBytesLeft == m_llLength ? true : false;
    /*  If this is the first read then set the position */
    if (bFirst) {
        ULARGE_INTEGER uliOffset;
        uliOffset.QuadPart = m_llStart;
        uliOffset.LowPart = SetFilePointer(m_hFile, 
                                           (LONG)uliOffset.LowPart,
                                           (PLONG)&uliOffset.HighPart,
                                           FILE_BEGIN);
    }


    while (cbData && !bDone) {
    
        DWORD cbRead = 0;
        {
            //CAutoLock(&m_csLock);
            if (INVALID_HANDLE_VALUE != m_hFile) {
                /*  if bFirst is set signal start of file */
                if (bFirst) {
                    IAMParse *pParse = m_pMFReader->GetParser();
                    if (pParse) {
                        REFERENCE_TIME rtStart;
            
                        /*  Bad things happen if we do it on the first file because
                            things may not be connected etc etc
                        */
                        HRESULT hr = S_OK;
                        if (m_iFileNumber == 1) {
                            rtStart = 0;
                        } else {
                            hr = pParse->GetParseTime(&rtStart);
                        }
                        if (SUCCEEDED(hr)) {
                            /*  Set the offset */
                            if (m_rtOffset != 0) {
                                rtStart += m_rtOffset;
                                DbgLog((LOG_TRACE, 0, TEXT("Setting parse time to %d seconds"),
                                        (LONG)(rtStart / 10000000)));
                                hr = pParse->SetParseTime(rtStart);
                                m_rtOffset = 0;
                            }
                            FileStart(rtStart);
                        }
                        pParse->Release();
                    }
                }
                DWORD cbToRead = (DWORD)(min(m_llBytesLeft, cbData));
                if (cbToRead != 0) {
                    if (!::ReadFile(m_hFile, (PVOID)pbData, cbToRead, &cbRead, NULL)) {
                        DWORD dwErr = GetLastError();
                        return HRESULT_FROM_WIN32(dwErr);
                    } else {
                        *pcbBytesRead += cbRead;
                        cbData        -= cbRead;
                        pbData        += cbRead;
                        m_llBytesLeft -= cbRead;
                    }
                }
                if (m_llBytesLeft == 0 || cbRead == 0) {
                    EXECUTE_ASSERT(CloseHandle(m_hFile));
                    m_hFile = INVALID_HANDLE_VALUE;
                    FileComplete(m_strFile);
                }
            }
        }
        if (cbRead == 0) {
            if (m_dwFlags & AM_MULTIFILE_READER_LAST) {
                return HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);
            } else {
                if (*pcbBytesRead == 0 || 
                    (m_dwFlags & AM_MULTIFILE_READER_SEAMLESS)) {
                    //  caller locks us so we have to unlock here
#if 0
                    m_bWaitingForFile = true;
#endif
                    m_csLock.Unlock();
                    //  Wait for a new file
                    HANDLE ev[2] = { m_evNew, m_hevStop };
                    DWORD dwErr = WaitForMultipleObjects(2, ev, FALSE, INFINITE);
                    m_csLock.Lock();
#if 0
                    m_bWaitingForFile = false;
#endif

                    if (dwErr == WAIT_OBJECT_0 + 1) {
                        return VFW_E_WRONG_STATE;
                    }
                    bFirst = true;
                } else {
                    bDone = true;
                }
            }
        }
    }
    return bFirst && !(m_dwFlags & AM_MULTIFILE_READER_SEAMLESS) ? OLE_S_FIRST : S_OK;
}

HRESULT CMultiFileStream::SetPointer(LONGLONG llPos)
{
    //  Should only really allow during connection
    if (!m_pMFReader->IsConnecting()) {
        return S_OK;
    }
    if (m_hFile == INVALID_HANDLE_VALUE) {
        return E_UNEXPECTED;
    }
    LARGE_INTEGER li;
    li.QuadPart = llPos;

    //  Do we really care if this works?
    //  Yes - during initial processing
    SetFilePointer(m_hFile, (LONG)li.LowPart, &li.HighPart, FILE_BEGIN);
    return S_OK;
}

