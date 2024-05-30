// EventMonFilterImpl.cpp : Implementation of CEventMonFilter
#include "stdafx.h"
#include "EventMonFilter.h"
#include "EventMonFilterImpl.h"
#include <comdef.h>

WCHAR   g_wzMethod[3][4][30] =  {{L"DiskFull"},
								{L"FileCreated", L"FileDeleted", L"FileRenamed", L"FileUpdated"},
								{L"ProcessCreated", L"ProcessDeleted", L"PNPDeviceAdded"}};

const	GUID*	g_piid[]				= {&__uuidof(IDiskEvents), 
										   &__uuidof(IFileSystemEvents),
										   &__uuidof(ISystemEvents)};

/////////////////////////////////////////////////////////////////////////////
// CEventMonFilter

CEventMonFilter::CEventMonFilter()
{
	// Initialize the structure members
	memset(m_filtattr, 0, sizeof(m_filtattr));
	InitializeStructure();
}

CEventMonFilter::~CEventMonFilter()
{
	ReleaseCollection(TRUE,TRUE);
}

// IDiskEvents method
STDMETHODIMP CEventMonFilter::DiskFull(BSTR bstr)
{
	return CommonFilter(bstr, 0, 0);
}

// IFileSystem methods
STDMETHODIMP CEventMonFilter::FileCreated(BSTR bstr)
{
	return CommonFilter(bstr, 1,0);
}

STDMETHODIMP CEventMonFilter::FileDeleted(BSTR bstr)
{
	return CommonFilter(bstr, 1,1);
}


STDMETHODIMP CEventMonFilter::FileRenamed(BSTR bstr)
{
	return CommonFilter(bstr,1,2);
}


STDMETHODIMP CEventMonFilter::FileUpdated(BSTR bstr)
{
	return CommonFilter(bstr,1,3);
}

// ISystem methods

STDMETHODIMP CEventMonFilter::ProcessCreated(BSTR bstr)
{
	return CommonFilter(bstr,2,0);
}


STDMETHODIMP CEventMonFilter::ProcessTerminated(BSTR bstr)
{
	return CommonFilter(bstr,2,1);
}


STDMETHODIMP CEventMonFilter::PNPDeviceAdded(BSTR bstr)
{
	return CommonFilter(bstr,2,2);
}

// IMultiInterfacePublisherFilter methods
STDMETHODIMP CEventMonFilter::Initialize(IMultiInterfaceEventControl *pmiec)
{
	HRESULT		hr =0;
	int			nummethod =0;
	int			nerr=0;

	if (!pmiec)
		return E_INVALIDARG;

	// Get the collection for all the methods
	for (int i=0; i< NUM_INTERFACE; i++)
	{
		// Find the number of methods for the app. interface
		switch(i)
		{
		case 0:
			nummethod = NUM_METHOD_IDISK;
			break;
		case 1:
			nummethod = NUM_METHOD_IFILESYSTEM;
			break;
		case 2:
			nummethod = NUM_METHOD_ISYSTEM;
			break;
		default:
			exit(E_FAIL);
		}
		for (int j=0; j <nummethod; j++)
		{
			_bstr_t		bmethod = g_wzMethod[i][j];

			hr = pmiec->GetSubscriptions(*g_piid[i],// InterfaceID
										 bmethod,	// MethodName
										 0,
										 &nerr,
										 &m_filtattr[i][j].pcoll);
			exit(hr);
		}
	}

exit:
	if FAILED(hr)
	{
		// Release all pointers to partial collections
		ReleaseCollection(TRUE, FALSE);
	}
	
	return hr;
}

STDMETHODIMP CEventMonFilter::PrepareToFire(REFIID riid, BSTR methodname, IFiringControl *pfc)
{
	int nummethod =0;

	if (!pfc)
		return E_INVALIDARG;

	// Get the firing control for the relevant method

	for (int i=0; i<NUM_INTERFACE; i++)
	{
		switch(i)
		{
		case 0:
			nummethod = NUM_METHOD_IDISK;
			break;
		case 1:
			nummethod = NUM_METHOD_IFILESYSTEM;
			break;
		case 2:
			nummethod = NUM_METHOD_ISYSTEM;
			break;
		default:
			return E_FAIL;
		}

		for (int j=0; j<nummethod; j++)
		{
			if(wcsicmp(g_wzMethod[i][j],methodname)==0)
			{
				m_filtattr[i][j].pfc = pfc;
				pfc->AddRef();
				goto jump;
			}
		}
	}
jump:

	if (i>=NUM_INTERFACE)
		return E_FAIL;

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CEventMonFilter::ReleaseCollection
// Purppose		: Release the collection
// Parameters	:
//				: BOOL	fcoll		- Collection to be released or not
//				: BOOL  ffc			- FiringControl to be released or not
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
HRESULT CEventMonFilter::ReleaseCollection(BOOL fcoll, BOOL ffc)
{
	int		i=0;
	int		j=0;
	int		nummethod=0;

	// Release all the cached IEventObjectCollection pointers
	while(i<NUM_INTERFACE)
	{
		switch(i)
		{
		case 0:
			nummethod = NUM_METHOD_IDISK;
			break;
		case 1:
			nummethod = NUM_METHOD_IFILESYSTEM;
			break;
		case 2:
			nummethod = NUM_METHOD_ISYSTEM;
			break;
		}

		j=0;

		while(j<nummethod)
		{
			if (fcoll)
			{
				RELEASE(m_filtattr[i][j].pcoll);
			}

			if (ffc)
			{
				RELEASE(m_filtattr[i][j].pfc);
			}

			j++;
		}
		i++;
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CEventMonFilter::InitializeStructure
// Purppose		: Initialize the m_filtattr structure
// Parameters	:
//				: BOOL	fcoll		- Collection to be released or not
//				: BOOL  ffc			- FiringControl to be released or not
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
HRESULT CEventMonFilter::InitializeStructure()
{
	int		i=0;
	int		j=0;
	int		nummethod=0;

	// Release all the cached IEventObjectCollection pointers
	while(i<NUM_INTERFACE)
	{
		switch(i)
		{
		case 0:
			nummethod = NUM_METHOD_IDISK;
			break;
		case 1:
			nummethod = NUM_METHOD_IFILESYSTEM;
			break;
		case 2:
			nummethod = NUM_METHOD_ISYSTEM;
			break;
		}

		j=0;

		while(j<nummethod)
		{
			m_filtattr[i][j].pcoll =0;
			m_filtattr[i][j].pfc =0;
			j++;
		}
		i++;
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CEventMonFilter::CommonFilter
// Purppose		: Initialize the m_filtattr structure
// Parameters	:
//				: BSTR bstr			- Passed argument
//				: int nInterface    - Interface identifier
//				: int nMethod		- Method identifier
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
HRESULT CEventMonFilter::CommonFilter(BSTR bstr, int nInterface, int nMethod)
{
	HRESULT				hr =0;
	IEnumEventObject	*penum=0;
	IUnknown			*punk =0;
	IEventSubscription	*psub=0;
	ULONG				nret =0;
	BSTR				bstrm =0;

	
	if (!(m_filtattr[nInterface][nMethod].pcoll && m_filtattr[nInterface][nMethod].pfc))
		return E_INVALIDARG;

	hr = (m_filtattr[nInterface][nMethod].pcoll)->get_NewEnum(&penum);
	exit(hr);


	while((hr = penum->Next(1, &punk, &nret))==S_OK)
	{
		VARIANT		var;

		hr = punk->QueryInterface(__uuidof(IEventSubscription), (void**)&psub);
		jump(hr);

		hr = psub->get_SubscriptionName(&bstrm);
		SysFreeString(bstrm);
		bstrm =0;

		hr = GetProperty(psub, &var);
		if (hr != S_OK)
			goto jump;

		// Decide if we need to fire this subscription or not
		if (wcsicmp(bstr, var.bstrVal)==0)
			hr = m_filtattr[nInterface][nMethod].pfc->FireSubscription(psub);
jump:
		RELEASE(punk);
		RELEASE(psub);
		VariantClear(&var);
		nret =0;
	}
exit:
	RELEASE(penum);
	RELEASE(punk);
	RELEASE(psub);
	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CEventMonFilter::GetProperty
// Purppose		: Initialize the m_filtattr structure
// Parameters	:
//				: IEventSubscription *psub	- Pointer to a subscription
//				: VARIANT *pvar
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
HRESULT CEventMonFilter::GetProperty(IEventSubscription *psub, VARIANT *pvar)
{
	HRESULT		hr =0;
	_bstr_t		bname = L"FilterProperty";

	VariantInit(pvar);

	if (!psub)
		return E_INVALIDARG;

	hr = psub->GetPublisherProperty(bname, pvar);
	return hr;
}




