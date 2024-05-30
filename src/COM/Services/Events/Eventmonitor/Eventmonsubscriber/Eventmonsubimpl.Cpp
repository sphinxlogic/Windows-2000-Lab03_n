// EventMonSubImpl.cpp : Implementation of CEventMonSubImpl
#include "stdafx.h"
#include "EventMonSubscriber.h"
#include "EventMonSubImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CEventMonSubImpl

STDMETHODIMP CEventMonSubImpl::DiskFull(BSTR bstr)
{
	return CommonMethod(_T("DiskFull"),bstr);
}

STDMETHODIMP CEventMonSubImpl::FileCreated(BSTR bstr)
{
	return CommonMethod(_T("FileCreated"),bstr);
}

STDMETHODIMP CEventMonSubImpl::FileDeleted(BSTR bstr)
{
	return CommonMethod(_T("FileDeleted"),bstr);
}

STDMETHODIMP CEventMonSubImpl::FileRenamed(BSTR bstr)
{
	return CommonMethod(_T("FileRenamed"),bstr);
}

STDMETHODIMP CEventMonSubImpl::FileUpdated(BSTR bstr)
{
	return CommonMethod(_T("FileUpdated"),bstr);
}

STDMETHODIMP CEventMonSubImpl::ProcessCreated(BSTR bstr)
{
	return CommonMethod(_T("ProcessCreated"),bstr);
}

STDMETHODIMP CEventMonSubImpl::ProcessTerminated(BSTR bstr)
{
	return CommonMethod(_T("ProcessTerminated"),bstr);
}

STDMETHODIMP CEventMonSubImpl::PNPDeviceAdded(BSTR bstr)
{
	return CommonMethod(_T("PNPDeviceAdded"),bstr);
}

HRESULT CEventMonSubImpl::CommonMethod(TCHAR* tzmethod, BSTR bstr)
{
	TCHAR tzcontent[MAX_PATH] = _T("\0");

	USES_CONVERSION;
	TCHAR* tzarg = W2T(bstr);
	wsprintf(tzcontent, _T("Inside method %s. Passed argument is %s"), tzmethod, tzarg);
	MessageBox(NULL, tzcontent, _T("EventMon Subscriber"), MB_OK);
	return S_OK;
}

