// Surface.cpp : Implementation of CSurface
#include "stdafx.h"
#include "grad.h"
#include "Surface.h"
#include <new.h>
#include "gradptr.h"

/////////////////////////////////////////////////////////////////////////////
// CSurface

HRESULT CSurface::CreateARGBPointer(CDXBaseSurface * pSurface, CDXBaseARGBPtr ** ppPtr)
{
    *ppPtr = new CGradPtr(this);
    if (*ppPtr)
    {
        return S_OK;
    }
    else
    {
        return E_OUTOFMEMORY;
    }
}


void CSurface::DeleteARGBPointer(CDXBaseARGBPtr *pPtr)
{
    delete (CGradPtr *)pPtr;
}

STDMETHODIMP CSurface::get_UpperLeftColor(OLE_COLOR * pVal)
{
    HRESULT hr = S_OK;
    if( !pVal )
    {
        hr = E_POINTER;
    }
    else
    {
        *pVal = m_ULColor;    
    }
    return hr;
}

STDMETHODIMP CSurface::put_UpperLeftColor(OLE_COLOR newVal)
{
    m_ULColor = newVal;
    return S_OK;
}

STDMETHODIMP CSurface::get_LowerLeftColor(OLE_COLOR * pVal)
{
    HRESULT hr = S_OK;
    if( !pVal )
    {
        hr = E_POINTER;
    }
    else
    {
        *pVal = m_LLColor;    
    }
    return hr;
}

STDMETHODIMP CSurface::put_LowerLeftColor(OLE_COLOR newVal)
{
    m_LLColor = newVal;
    return S_OK;
}

STDMETHODIMP CSurface::get_UpperRightColor(OLE_COLOR * pVal)
{
    HRESULT hr = S_OK;
    if( !pVal )
    {
        hr = E_POINTER;
    }
    else
    {
        *pVal = m_URColor;    
    }
    return hr;
}

STDMETHODIMP CSurface::put_UpperRightColor(OLE_COLOR newVal)
{
    m_URColor = newVal;
    return S_OK;
}

STDMETHODIMP CSurface::get_LowerRightColor(OLE_COLOR * pVal)
{
    HRESULT hr = S_OK;
    if( !pVal )
    {
        hr = E_POINTER;
    }
    else
    {
        *pVal = m_LRColor;    
    }
    return hr;
}

STDMETHODIMP CSurface::put_LowerRightColor(OLE_COLOR newVal)
{
    m_LRColor = newVal;
    return S_OK;
}

STDMETHODIMP CSurface::get_Height(long * pVal)
{
    HRESULT hr = S_OK;
    if( !pVal )
    {
        hr = E_POINTER;
    }
    else
    {
        *pVal = m_Height;    
    }
    return hr;
}

STDMETHODIMP CSurface::put_Height(long newVal)
{
    m_Height = newVal;
    return S_OK;
}

STDMETHODIMP CSurface::get_Width(long * pVal)
{
    HRESULT hr = S_OK;
    if( !pVal )
    {
        hr = E_POINTER;
    }
    else
    {
        *pVal = m_Width;    
    }
    return hr;
}

STDMETHODIMP CSurface::put_Width(long newVal)
{
    m_Width = newVal;
    return S_OK;
}



STDMETHODIMP CSurface::SetOutputSize(const SIZE OutputSize, BOOL bMaintainAspect)
{
    HRESULT hr = S_OK;
    if (OutputSize.cx < 1 || OutputSize.cy < 1)
    {
        hr = E_INVALIDARG;
    }
    else
    {
        _EnterCritWith0PtrLocks();
        hr = OnSetSize(OutputSize.cx, OutputSize.cy);
        Unlock();
    }
    return hr;
}


