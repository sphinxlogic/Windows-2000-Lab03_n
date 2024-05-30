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

// MultiF.h : Declaration of the CMultiF

#ifndef __MULTIF_H_
#define __MULTIF_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiF
class ATL_NO_VTABLE CMultiF :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CMultiF, &CLSID_MultiF>,
    public IConnectionPointContainerImpl<CMultiF>,
    public IDispatchImpl<IMultiF, &IID_IMultiF, &LIBID_MULTILib>,
    public IConnectionPointImpl<CMultiF, &DIID_IMultiEvent>
{
public:
    CMultiF();
    ~CMultiF();

    HRESULT FinalConstruct();

    static HRESULT CreateCallbackWindow(
        HINSTANCE hInst,
        CMultiF *pThis,
        HWND *phwnd
    )
    {
        WNDCLASS wc;
        ZeroMemory(&wc, sizeof(wc));
        wc.lpfnWndProc = WndProc;
        wc.hInstance = hInst;
        wc.lpszClassName = TEXT("AMCallbackWindow");
        if (!RegisterClass(&wc)) {
            //return E_OUTOFMEMORY;
        }

        HWND hwnd = CreateWindow(TEXT("AMCallbackWindow"),
                                 TEXT("AMCallbackWindow"),
                                 0,
                                 0, 0, 1, 1,
                                 NULL,
                                 NULL,
                                 hInst,
                                 NULL);

        if (hwnd == NULL) {
            return E_OUTOFMEMORY;
        }

        SetWindowLong(hwnd, GWL_USERDATA, (LONG)pThis);
        *phwnd = hwnd;
        return S_OK;
    }

    void DoEventProcessing(UINT uiMsg, WPARAM wParam, LPARAM lParam);

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam,
                                    LPARAM lParam)
    {
        if (uiMsg >= WM_USER)
        {
            /*  Do the callback here */
            CMultiF *pThis =
                (CMultiF *)GetWindowLong(hwnd, GWL_USERDATA);
            pThis->DoEventProcessing(uiMsg, wParam, lParam);
            return (LRESULT)0;
        } else {
            CMultiF *pThis =
                (CMultiF *)GetWindowLong(hwnd, GWL_USERDATA);
            if (uiMsg == WM_TIMER) {
                pThis->ReevaluateTimers();
            }
            return DefWindowProc(hwnd, uiMsg, wParam, lParam);
        }
    }

DECLARE_REGISTRY_RESOURCEID(IDR_MULTIF)

BEGIN_COM_MAP(CMultiF)
    COM_INTERFACE_ENTRY(IMultiF)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CMultiF)
    CONNECTION_POINT_ENTRY(DIID_IMultiEvent)
END_CONNECTION_POINT_MAP()


// IMultiF
public:
    STDMETHODIMP SetFile(
        BSTR FileName,
        long lStartLow,
        long lStartHigh,
        long lLengthLow,
        long lLengthHigh,
        long lTimeOffset,
        long lIdFile,
        SetFileFlags lFlags);

    STDMETHODIMP GetGraph(
        IUnknown **ppGraph
    )
    {
        return m_pGB->QueryInterface(IID_IMediaControl, (void **)ppGraph);
    }

    STDMETHODIMP GetAudioStream(long lIndex, long *plSelected, BSTR *lpName);

    STDMETHODIMP SetAudioStream(long lIndex);

    //  Timer stuff
    STDMETHODIMP SetTimer(long lTimerLow, long lTimerHigh, long lTimerId);
    STDMETHODIMP CancelTimer(long lTimerId);

    //  Helpers
    HRESULT FindAudioInfo(
        long lAudioIndex, 
        IAMStreamSelect **ppSel, 
        long *plIndex);

    bool RemoveTimer(long lTimerId);
    void ReevaluateTimers(bool bCanCallNow = true);

private:
    HWND                      m_hwnd;
    bool                      m_bFirst;
    CComPtr<IMultiFileReader> m_pMF;
    CComPtr<IGraphBuilder>    m_pGB;
    CComPtr<IMediaEventEx>    m_pME;
    CComPtr<IBaseFilter>      m_pBF;

    //  Timer management
    enum { MAX_TIMERS = 10 };
    int                       m_nTimers;
    struct {
        REFERENCE_TIME        rtTimer;
        long                  lTimerId;
    } m_Timers[MAX_TIMERS];
};

#endif //__MULTIF_H_
