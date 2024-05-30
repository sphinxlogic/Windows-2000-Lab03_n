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

// MultiF.cpp : Implementation of CMultiF
#include "stdafx.h"
#include <multfile.h>
#include "multi.h"
#include "MultiF.h"
#include <limits.h>


//  Helper function


/////////////////////////////////////////////////////////////////////////////
// CMultiF


STDMETHODIMP CMultiF::SetFile(
    BSTR FileName, 
    long lStartLow, 
    long lStartHigh, 
    long lLengthLow, 
    long lLengthHigh,
    long lTimeOffset,
    long lFileId,
    SetFileFlags lFlags)
{
    LARGE_INTEGER liStart, liLength;
    liStart.LowPart = lStartLow;
    liStart.HighPart = lStartHigh;
    liLength.LowPart = lLengthLow;
    liLength.HighPart = lLengthHigh;

    HRESULT hr;
    hr = m_pMF->SetFile(FileName, 
                        liStart.QuadPart,
                        liLength.QuadPart,
                        lTimeOffset,
                        m_hwnd,
                        WM_USER,
                        lFileId,
                        NULL,
                        lFlags);

    //  If it's the first one we need to render
    if (SUCCEEDED(hr) && m_bFirst) {
        //  Render the filter's output pin
        IPin *pPin;
        hr = m_pBF->FindPin(L"Output", &pPin);
        if (SUCCEEDED(hr)) {
            hr = m_pGB->Render(pPin);
            pPin->Release();
        }

        if (SUCCEEDED(hr)) {
            m_bFirst = false;
        }
    }
    return hr;
}

HRESULT CMultiF::FindAudioInfo(
    long lAudioIndex,
    IAMStreamSelect **ppSel,
    long *plIndex
)
{
    IEnumFilters *pEnum;
    HRESULT hr = m_pGB->EnumFilters(&pEnum);
    *ppSel = NULL;
    if (SUCCEEDED(hr)) {
        for (; ; ) {
            IBaseFilter *pFilter;
            ULONG ulFound;
            HRESULT hr = pEnum->Next(1, &pFilter, &ulFound);
            if (S_OK == hr) {
                hr = pFilter->QueryInterface(
                         IID_IAMStreamSelect, (void **)ppSel);
                pFilter->Release();
                if (SUCCEEDED(hr)) {
                    break;
                }
            } else {
                break;
            }
        }
        pEnum->Release();
    }
    if (*ppSel) {
        long lAudio = -1;
        for (long l = 0; ; l++) {
            AM_MEDIA_TYPE *pmt;
            hr = (*ppSel)->Info(
                l,
                &pmt,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL);
            if (FAILED(hr)) {
               break;
            }
            if (pmt->majortype == MEDIATYPE_Audio) {
                lAudio++;
            }
            if (pmt->pbFormat) {
                CoTaskMemFree(pmt->pbFormat);
            }
            CoTaskMemFree(pmt);
            if (lAudio == lAudioIndex) {
                *plIndex = l;
                break;
            }
        }
    } else {
        hr = E_NOINTERFACE;
    }
    return hr;
}

STDMETHODIMP CMultiF::GetAudioStream(
    long lIndex, 
    long *plSelected, 
    BSTR *lpName
)
{

    IAMStreamSelect *pSel;
    long lAudioIndex;
    *lpName = NULL;
    *plSelected = 0;
    HRESULT hr = FindAudioInfo(lIndex, &pSel, &lAudioIndex);
    if (pSel) {
        if (SUCCEEDED(hr)) {
            LPWSTR pszName;
            DWORD dwFlags;
            hr = pSel->Info(
                lIndex,
                NULL,
                &dwFlags,
                NULL,
                NULL,
                &pszName,
                NULL,
                NULL);
            if (SUCCEEDED(hr)) {
                *plSelected = (dwFlags & AMSTREAMSELECTINFO_ENABLED) != 0;
                *lpName = SysAllocString(pszName);
                if (*lpName == NULL) {
                    hr = E_OUTOFMEMORY;
                }
            }
        } else {
            /*  Just return NULL string */
            hr = S_OK;
        }

        pSel->Release();
    }
    return hr;
}

STDMETHODIMP CMultiF::SetAudioStream(long lIndex)
{
    IAMStreamSelect *pSel;
    long lAudioIndex;
    HRESULT hr = FindAudioInfo(lIndex, &pSel, &lAudioIndex);
    if (pSel) {
        if (SUCCEEDED(hr)) {
            hr = pSel->Enable(lAudioIndex, AMSTREAMSELECTENABLE_ENABLE);
        }
        pSel->Release();
    }
    return hr;
}         

CMultiF::CMultiF()
    : m_hwnd(NULL),
      m_bFirst(true),
      m_nTimers(0)
{
}


CMultiF::~CMultiF()
{ 
    if (m_hwnd) {
        //  Avoid leaking memory
        MSG msg;
        while (PeekMessage(&msg, m_hwnd, WM_USER + 1, WM_USER + 1, PM_REMOVE)) {
            if (msg.message == WM_USER + 1) {
                CoTaskMemFree((PVOID)msg.lParam);
            }
        }
        SendMessage(m_hwnd, WM_CLOSE, 0, 0);
    }
}

HRESULT CMultiF::FinalConstruct()
{
    HRESULT hr;
    hr = CComObjectRoot::FinalConstruct();
    if (SUCCEEDED(hr)) {
        hr = CreateCallbackWindow(
                         _Module.GetModuleInstance(),
                         this,
                         &m_hwnd);
    }
    if (SUCCEEDED(hr)) {
        hr = CoCreateInstance(CLSID_FilterGraph,
                              NULL,
                              CLSCTX_INPROC,
                              IID_IGraphBuilder,
                              (void **)&m_pGB);
    }
    if (SUCCEEDED(hr)) {
        hr = CoCreateInstance(CLSID_MultiFileReader,
                              NULL,
                              CLSCTX_INPROC,
                              IID_IMultiFileReader,
                              (void **)&m_pMF);
    }
    if (SUCCEEDED(hr)) {
        hr = m_pGB->QueryInterface(IID_IMediaEventEx, (void **)&m_pME);
    }

    if (SUCCEEDED(hr)) {
        hr = m_pME->SetNotifyWindow((OAHWND)m_hwnd, WM_USER + 1, 0);
    }
    hr = m_pMF->QueryInterface(IID_IBaseFilter, (void **)&m_pBF);
    if (SUCCEEDED(hr)) {
        hr = m_pGB->AddFilter(m_pBF, L"MultiFile Source");
    }

    return hr;
}

//  Do the callbacks
void CMultiF::DoEventProcessing(UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    //  Check for graph events
    bool bComplete = false;
    if (uiMsg == WM_USER + 1) {
        for (; ; ) {
            long levCode;
			LONG_PTR lParam1, lParam2;
            HRESULT hr = m_pME->GetEvent(&levCode, &lParam1, &lParam2, 0);
            if (S_OK != hr) {
                break;
            }
            if (levCode == EC_COMPLETE) {
                bComplete = true;
            }
        }
        if (!bComplete) {
            return;
        }
    }


    //  Use our disp interface

    /*  Only 1 connection point */
    for (IUnknown **pp = m_vec.begin() ;pp < m_vec.end(); pp++) {
        if (*pp != NULL) {
            IDispatch *pDispatch = reinterpret_cast<IDispatch *>(*pp);

            /*  DISPPARAMS are in REVERSE order (!) */
            CComVariant var[3];
            DISPID dispid;
            DISPPARAMS disp = { 0, NULL, 0, 0 };
            CComVariant varResult;

            if (uiMsg == WM_USER) {
                disp.rgvarg = var;
                if (lParam != NULL) {
                    REFERENCE_TIME rt;
                    rt = *((REFERENCE_TIME *)lParam);
                    var[1] = (long)(rt / 10000000);
                    var[0] = (long)((long)(rt % 10000000) / 10000);
                    dispid = 3;
                    disp.cArgs = 3;
                    var[2] = (long)wParam;
                } else {
                    dispid = 1;
                    disp.cArgs = 1;
                    var[0] = (long)wParam;
                }
            } else {
                if (uiMsg == WM_TIMER) {
                    disp.rgvarg = var;
                    dispid = 4;
                    disp.cArgs = 1;
                    var[0] = (long)wParam;
                } else {
                    dispid = 2;
                }
            }

            pDispatch->Invoke(dispid, 
                              IID_NULL,
                              LOCALE_USER_DEFAULT,
                              DISPATCH_METHOD,
                              &disp, 
                              &varResult,
                              NULL,
                              NULL);
        }
    }
    if (uiMsg == WM_USER && lParam != NULL) {
        CoTaskMemFree((PVOID)lParam);
    }
}

//  Timer stuff

STDMETHODIMP CMultiF::SetTimer(long lSeconds, long lMilliseconds, long lTimerId)
{
    if (lTimerId == 0) {
        return E_INVALIDARG;
    }
    CancelTimer(lTimerId);
    if (m_nTimers == MAX_TIMERS) {
        return E_INVALIDARG;
    }
    m_Timers[m_nTimers].rtTimer = (LONGLONG)lSeconds * 10000000 +
                                  lMilliseconds * 10000;
    m_Timers[m_nTimers].lTimerId = lTimerId;
    m_nTimers++;
    ReevaluateTimers(false);
    return S_OK;
}
STDMETHODIMP CMultiF::CancelTimer(long lTimerId)
{
    if (lTimerId == 0) {
        m_nTimers = 0;
        return S_OK;
    }
    if (RemoveTimer(lTimerId)) {
        ReevaluateTimers();
    }
    return S_OK;
}

bool CMultiF::RemoveTimer(long lTimerId)
{
    bool bFound = false;
    for (int i = 0; i < m_nTimers; i++) {
        if (!bFound) {
            if (m_Timers[i].lTimerId == lTimerId) {
                bFound = true;
            }
        } else {
            m_Timers[i - 1] = m_Timers[i];
        }
    }
    if (bFound) {
        m_nTimers--;
    }
    return bFound;
}

void CMultiF::ReevaluateTimers(bool bCanCallNow)
{
    //  What time is it?
    CComQIPtr<IMediaSeeking, &IID_IMediaSeeking> pSeeking(m_pGB);
    REFERENCE_TIME rtNext = _I64_MAX, rtNow;
    if (SUCCEEDED(pSeeking->GetCurrentPosition(&rtNow))) {
        for (int i = 0; i < m_nTimers;) {
            if (bCanCallNow && rtNow + 10000 >= m_Timers[i].rtTimer) {
                //  Fire it
                DoEventProcessing(WM_TIMER, m_Timers[i].lTimerId, 0);
                RemoveTimer(m_Timers[i].lTimerId);
            } else {
                //  Find the next one
                if (m_Timers[i].rtTimer < rtNext) {
                    rtNext = m_Timers[i].rtTimer;
                }
                i++;
            }
        }
    }
    KillTimer(m_hwnd, 1);
    if (rtNext < rtNow) {
        rtNext = rtNow;
    }
    if (rtNext < _I64_MAX) {
        //  Set to wait for the next one
        LONG lTimeout = (LONG)((rtNext - rtNow) / 10000);
        if (lTimeout > 1000) {
            lTimeout = 1000;
        }
        ::SetTimer(m_hwnd, 1, lTimeout, NULL);
    }
}

