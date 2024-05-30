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

/*

     Design:

     We support setting the file name multiple times.
     Setting the file name is deemed to be immediate.
     We notify (EC_...) when we complete READING a file -
     this prompts the application to set a new file name.
     Seeking is not supported

*/

class CMultiFileReader;

/*  Class to turn our file(s) into a stream */

class CMultiFileStream : public CAsyncStream
{
friend class CMultiFileReader;
    //  Locking for streaming (acquire before m_csFile)
    CCritSec    m_csLock;

    //  Current file info (from SetFile)
    HANDLE      m_hFile;
    LPWSTR      m_strFile;
    DWORDLONG   m_llLength;
    DWORDLONG   m_llStart;
    DWORDLONG   m_llFileSize;
    REFERENCE_TIME m_rtOffset;
    HANDLE      m_hEvent;
    HWND        m_hwnd;
    UINT        m_uiMsg;
    WPARAM      m_wParam;
    DWORD       m_dwFlags;

    //  How far we've come
    DWORDLONG   m_llBytesLeft;

    //  Signalling events
    CAMEvent    m_evNew;       //  New file available
    HANDLE      m_hevStop;     //  Filter is being stopped/flushed
#if 0
    CAMEvent    m_evSync;      //  Synchronized with reader
#endif

    int         m_iFileNumber;
    bool        m_bSignalledTime;
    CMultiFileReader * const m_pMFReader;
#if 0
    bool        m_bWaitingForFile;
#endif

public:

    CMultiFileStream(HANDLE hevStop, CMultiFileReader *pMFReader);
    ~CMultiFileStream();
    void        Flush();

    //  CAsyncStream overrides
    HRESULT     Read(PBYTE pbData, DWORD cbData, BOOL bAlign, DWORD *pcbBytesRead);
    LONGLONG Size(LONGLONG *pSizeAvailable);
    HRESULT SetPointer(LONGLONG llPos);

#if 0
    //  Clear old file
    void ClearFile();
#endif

    //  Set new file
    HRESULT SetFile (LPCWSTR lpszFile,
                     LONGLONG llOffset,
                     LONGLONG llLength,
                     LONGLONG rtOffset,
                     HWND hwndNotify,
                     UINT uiMsgNotify,
                     WPARAM wParam,
                     HANDLE hEvent,
                     DWORD dwFlags
                     );

    DWORD Alignment()
    {
        return 1;
    }
    void Lock()
    {
        m_csLock.Lock();
    }
    void Unlock()
    {
        m_csLock.Unlock();
    }
    LPCOLESTR FileName() const { return m_strFile; }
    HRESULT FileComplete(LPCWSTR pszFile);
    HRESULT FileStart(REFERENCE_TIME rtStart);
};

/*  Filter - derived from CAsyncReader - supports IMultiFileReader */
class CMultiFileReader :
    public CAsyncReader,
    public IMultiFileReader,
    public IFileSourceFilter
{

friend class CMultiFileStream;
public:
    CMultiFileReader(LPUNKNOWN pUnk, HRESULT *phr);

    static CUnknown *CreateInstance(LPUNKNOWN, HRESULT *);

#if 0
    //  Hack to initialize process since we don't call the CRunTime init
    static void InitClass(BOOL bLoading, const GUID *pclsid);
#endif

    DECLARE_IUNKNOWN

    //  Async reader stuff
    HRESULT Connect(IPin *pReceivePin, const AM_MEDIA_TYPE *pmt)
    {
        m_bConnecting = true;
        HRESULT hr = CAsyncReader::Connect(pReceivePin, pmt);
        m_bConnecting = false;
        return hr;
    }

    //  Support IMultiFileReader
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv);

    STDMETHODIMP SetFile (LPCWSTR lpszFile,
                     LONGLONG llOffset,
                     LONGLONG llLength,
                     LONGLONG rtOffset,
                     HWND hwndNotify,
                     UINT uiMsgNotify,
                     WPARAM wParam,
                     HANDLE hEvent,
                     DWORD dwFlags
                     );

    STDMETHODIMP SetEnd(void)
    {
        DbgLog((LOG_TRACE, 0, TEXT("SetEnd")));
        return S_OK;
    }

    /*  IFileSourceFilter methods */
    //  Load a (new) file

    STDMETHODIMP Load(LPCOLESTR lpwszFileName, const AM_MEDIA_TYPE *pmt)
    {
        CheckPointer(lpwszFileName, E_POINTER);
        CAutoLock lck(&m_csFilter);

        HRESULT hr = SetFile((LPOLESTR)lpwszFileName, 0, 0, 0, NULL, 0, 0, NULL, 0);

        if (FAILED(hr)) {
            return hr;
        }

        /*  Check the file type */
        CMediaType cmt;
        if (NULL != pmt) {
            cmt = *pmt;
        }


        // this is not a simple assignment... pointers and format
        // block (if any) are intelligently copied
	m_mt = cmt;

        return S_OK;
    }

    // Modelled on IPersistFile::Load
    // Caller needs to CoTaskMemFree or equivalent.

    STDMETHODIMP GetCurFile(LPOLESTR * ppszFileName, AM_MEDIA_TYPE *pmt)
    {
        CheckPointer(ppszFileName, E_POINTER);
        *ppszFileName = NULL;
        if (m_Stream.FileName()!=NULL) {
    	DWORD n = sizeof(WCHAR)*(1+lstrlenW(m_Stream.FileName()));

            *ppszFileName = (LPOLESTR) CoTaskMemAlloc( n );
            if (*ppszFileName!=NULL) {
                  CopyMemory(*ppszFileName, m_Stream.FileName(), n);
            }
        }

        if (pmt!=NULL) {
            CopyMediaType(pmt, &m_mt);
        }

        return NOERROR;
    }

    //  Get IAMParse off the downstream filter
    IAMParse *GetParser();

    //  Are we connecting?
    bool IsConnecting() const { return m_bConnecting; }

protected:
    CMultiFileStream m_Stream;
    bool             m_bConnecting;
};
