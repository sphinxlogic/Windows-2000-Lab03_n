// HBSubImpl.cpp : Implementation of CHBSubImpl
#include "stdafx.h"
#include "HBSubscriber.h"
#include "HBSubImpl.h"


/////////////////////////////////////////////////////////////////////////////
// CHBSubImpl

STDMETHODIMP CHBSubImpl::NewEvent(BSTR bstr)
{
	return CommonMethod(_T("NewEvent"),bstr);
}

STDMETHODIMP CHBSubImpl::NewsHeadlineNotify( NEWSHEADLINE pgb)
{
	if ( pgb == (NEWSHEADLINE)0 ) {
		return 0;
	}
	else {
		m_pgb = pgb;
		return S_OK;
	}
}

STDMETHODIMP CHBSubImpl::NewsHeadline(BSTR bstr)
{
	return CommonMethod(_T("NewsHeadline"),bstr);
}

STDMETHODIMP CHBSubImpl::HotNews(BSTR bstr)
{
	return CommonMethod(_T("HotNews"),bstr);
}

HRESULT CHBSubImpl::CommonMethod(TCHAR* tzmethod, BSTR bstr)
{
	TCHAR tzcontent[MAX_PATH] = _T("\0");

	USES_CONVERSION;
	TCHAR* tzarg = W2T(bstr);
	wsprintf(tzcontent, _T("Inside method %s. Passed argument is %s"), tzmethod, tzarg);
	MessageBox(NULL, tzcontent, _T("Hanson Brothers News Subscriber"), MB_OK);
	return S_OK;
}

