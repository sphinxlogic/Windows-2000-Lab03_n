#include <stdafx.h>
#include "Adminwrap.h"
#include "..\include\macro.h"
#include <comadmin.h>
#include <assert.h>

//*********************************************
// Globals

WCHAR	g_wczAPP[]  = L"Applications";
WCHAR	g_wczCOMP[] = L"Components";
WCHAR   g_wczNAME[] = L"Name";
WCHAR	g_wczProgIDProp[] = L"ProgID";
WCHAR   g_wczSUB[] = L"SubscriptionsForComponent";
WCHAR   g_wczTRANSUB[] = L"TransientSubscriptions";
WCHAR	g_wczPUBPROP[] = L"PublisherProperties";
WCHAR   g_wczTRANSPUBPROP[] = L"TransientPublisherProperties";

_bstr_t g_bAPP	= g_wczAPP;
_bstr_t g_bCOMP = g_wczCOMP;
_bstr_t g_bPUBID = L"PublisherID";
_bstr_t g_bFILTER = L"MultiInterfacePublisherFilterCLSID";
_bstr_t g_bALLOWINPROC = L"AllowInprocSubscribers";
_bstr_t g_bFIREINPARALLEL = L"FireInParallel";
_bstr_t g_bSUB = g_wczSUB;
_bstr_t g_bNAME = L"Name";
_bstr_t g_bVALUE = L"Value";
_bstr_t g_bECID = L"EventCLSID";
_bstr_t g_bIID = L"InterfaceID";
_bstr_t g_bMETHOD = L"MethodName";
_bstr_t g_bCRITERIA = L"FilterCriteria";
_bstr_t g_bPUBPROP = g_wczPUBPROP;
_bstr_t g_bTRANSSUB = g_wczTRANSUB;
_bstr_t g_bSUBINT = L"SubscriberInterface";
_bstr_t g_bTRANSPUBPROP = g_wczTRANSPUBPROP;


//////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::CApp
// Purppose		: CApp constructor
// Parameters	:
//				: ICOMAdminCatalog* pcat - Pointer to ICOMAdminCatalog interface
//				: WCHAR* pwzname         - Name of the Application
///////////////////////////////////////////////////////////////////////////////////////
CApp::CApp(ICOMAdminCatalog* pcat, WCHAR* pwzname)
{
	if (pcat)
	{
		m_pcat=pcat;
		m_pcat->AddRef();
	}

	m_pwzapp = new WCHAR[wcslen(pwzname)+1];
	if (m_pwzapp)
		wcscpy(m_pwzapp, pwzname);	
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::~CApp
// Purppose		: CApp destructor
///////////////////////////////////////////////////////////////////////////////////////
CApp::~CApp()
{
	SAFERELEASE(m_pcat);
	if (m_pwzapp)
	{
		DeleteApp();
		delete [] m_pwzapp;
		m_pwzapp=0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::SetProperties
// Purppose		: Sets the properties of the CApp object
// Parameters	:
//				: ICOMAdminCatalog* pcat - Pointer to ICOMAdminCatalog interface
//				: WCHAR* pwzname         - Name of the Application
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::SetProperties(ICOMAdminCatalog* pcat, WCHAR* pwzname)
{
	if (!pcat || !pwzname)
		return E_INVALIDARG;

	SAFERELEASE(m_pcat);
	m_pcat = pcat;
	m_pcat->AddRef();

	if (m_pwzapp)
	{
		DeleteApp();
		delete [] m_pwzapp;
		m_pwzapp=0;
	}

	m_pwzapp = new WCHAR[wcslen(pwzname)+1];
	if (!m_pwzapp)
		return E_OUTOFMEMORY;
	wcscpy(m_pwzapp, pwzname);
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::CreateApp
// Purppose		: Creates a COM+ Application
// Parameters	:
//				: BOOL fServer - Specifies if is a Server app of Library app
//				: BOOL fQueued - Specifies if the app is QUEUED or not
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::CreateApp(BOOL fServer, BOOL fQueued)
{
	HRESULT				hr =0;
	ICatalogObject		*pobj = 0;
	ICatalogCollection	*pcoll = 0;
	IDispatch			*pdisp = 0;
	_bstr_t				bname; ;
	long				lret =0;
	VARIANT				var;

	if (!m_pwzapp || !m_pcat)
		return E_POINTER;

	hr = GetCollection(m_pcat, g_bAPP, &pcoll);
	exit(hr);

	hr = pcoll->Add(&pdisp);
	exit(hr);

	hr = pdisp->QueryInterface(__uuidof(ICatalogObject), (void**)&pobj);
	exit(hr);

	VariantInit(&var);

	var.vt = VT_BSTR;
	var.bstrVal = SysAllocString(m_pwzapp);
	if (!var.bstrVal)
		exit(hr=E_OUTOFMEMORY);

	hr = pobj->put_Value(g_bNAME, var);
	exit(hr);

	bname = L"Activation";
	VariantClear(&var);
	var.vt = VT_BOOL;
	var.boolVal = fServer;

	hr = pobj->put_Value(bname,var);
	exit(hr);

	bname = L"QueuingEnabled";
	var.vt = VT_BOOL;
	var.boolVal = fQueued;
	
	hr = pobj->put_Value(bname,var);
	exit(hr);

	bname = L"QueueListenerEnabled";
	var.vt = VT_BOOL;
	var.boolVal = fQueued;

	hr = pobj->put_Value(bname,var);
	exit(hr);		

	hr = pcoll->SaveChanges(&lret);

exit:
	VariantClear(&var);
	SAFERELEASE(pcoll);
	SAFERELEASE(pobj);
	SAFERELEASE(pdisp);
	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::DeleteApp
// Purppose		: Deletes a COM+ Application and its components
// Parameters	:
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::DeleteApp()
{
	HRESULT				hr = E_FAIL;
	ICatalogCollection	*pIApps = NULL;
	ICatalogObject		*pIApp = NULL;
	_bstr_t				bappname;

	if (!m_pwzapp || !m_pcat)
		return E_POINTER;

	bappname	= m_pwzapp;

	hr = GetCollection(m_pcat, g_bAPP, &pIApps);
	exit(hr);
	hr = RemoveNamedObjectFromCollection(pIApps, bappname, APPLICATION);	
	m_pwzapp = NULL;
exit:
	SAFERELEASE(pIApps);
	SAFERELEASE(pIApp);
	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::InstallComponent
// Purppose		: Installs a component
// Parameters	:
//				: WCHAR* pwzcompdllname		- Path of the dll which exports this 
//											  component
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::InstallComponent(WCHAR* pwzcompdllname)
{
	_bstr_t			bappname, bdllname;

	if (!m_pwzapp || !pwzcompdllname || !m_pcat)
		return E_INVALIDARG;

	bappname = m_pwzapp;
	bdllname = pwzcompdllname;
	
	return m_pcat->InstallComponent(bappname, pwzcompdllname,0,0);
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::RemoveComponent
// Purppose		: Removes the specified component from the application
// Parameters	:
//				: WCHAR* progid - Name of the component
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::RemoveComponent(WCHAR* progid)
{
	ICatalogCollection		*pIApps=0, *pIComps=0;
	ICatalogObject			*pIApp=0;
	HRESULT					hr =0;

	if (!m_pwzapp || !m_pcat || !progid)
		return E_INVALIDARG;


	hr = GetObjectAndCollection(m_pcat, g_bAPP, _bstr_t(m_pwzapp), APPLICATION, &pIApps, &pIApp);
	exit(hr);

	hr = GetCollection(pIApps, pIApp, g_bCOMP, &pIComps);
	exit(hr);

	hr = RemoveNamedObjectFromCollection(pIComps, _bstr_t(progid), COMPONENT);

exit:
	SAFERELEASE(pIApps);
	SAFERELEASE(pIComps);
	SAFERELEASE(pIApp);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::AddEventClass
// Purppose		: Installs an EventClass component under the application
// Parameters	:
//				: WCHAR* pwzdllname		- Dll path that has DllRegisterServer exported
//				: WCHAR* pwztlbpath		- TLB path that contains Firing Interface definitions
//				: WCHAR* pwzCompName	- Name of the component
//				: WCHAR* pwzPublisherID - Name of the Publisher
//				: WCHAR* pwzFilterCLSID - CLSID (in string from) of the filter component
//				: BOOL   fAllowinproc   - Flag that sets the "AllowInProcSubscribers" property
//				: BOOL	 fFireinparallel- Flag that decides if it is serial or parallel firing
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::AddEventClass(WCHAR* pwzdllname, WCHAR* pwztlbpath, WCHAR* pwzCompName, WCHAR* pwzPublisherID, 
							WCHAR* pwzFilterCLSID, BOOL fAllowinproc, BOOL fFireinparallel)
{
	HRESULT					hr = 0;
	ICatalogCollection		*pIApps=0, *pIComps=0;
	ICatalogObject			*pIApp=0, *pIComp=0;
	long					lret =0;
	_bstr_t					bapp, bdll("\0"), btlb("\0");
	BOOL					fCreate=FALSE, fComplete = FALSE;

	if (!pwzdllname || !m_pcat || !m_pwzapp || !pwzCompName)
		return E_INVALIDARG;

	if (pwzdllname)
		bdll = pwzdllname;

	if (pwztlbpath)
		btlb = pwztlbpath;
	
	bapp = m_pwzapp;

	hr = m_pcat->InstallEventClass(bapp, bdll, btlb,0);
	exit(hr);

	fCreate = TRUE;

	hr = GetObjectAndCollection(m_pcat, g_bAPP, bapp, APPLICATION, &pIApps, &pIApp);
	exit(hr);

	hr = GetObjectAndCollection(pIApps, pIApp, g_bCOMP, _bstr_t(pwzCompName), COMPONENT, &pIComps, &pIComp);
	exit(hr);

	hr = SetStringProperty(pIComp, g_bPUBID, pwzPublisherID);
	exit(hr);

	hr = SetStringProperty(pIComp, g_bFILTER, pwzFilterCLSID);
	exit(hr);

	hr = SetBoolProperty(pIComp, g_bALLOWINPROC, fAllowinproc);
	exit(hr);

	hr = SetBoolProperty(pIComp, g_bFIREINPARALLEL, fFireinparallel);
	exit(hr);

	hr = pIComps->SaveChanges(&lret);
	exit(hr);

	fComplete = TRUE;
	
exit:
	if (fCreate && !fComplete)
		RemoveComponent(pwzCompName);

	SAFERELEASE(pIComp);
	SAFERELEASE(pIApps);
	SAFERELEASE(pIComps);
	SAFERELEASE(pIApps);

	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::AddSubscription
// Purppose		: Creates a Persistent Subscription
// Parameters	:
//				: WCHAR* pwzProgID		- Name of the component for which the subscription to be created
//				: WCHAR* pwzSubName		- Name of the subscription
//				: WCHAR* pwzECID		- EventClass ID
//				: WCHAR* pwzPubID		- Name of the Publisher
//				: WCHAR* pwzIID         - Interface Name (in string form)
//				: WCHAR* pwzMethod		- Method in the interface to subscribe
//				: WCHAR* pwzCriteria	- Filter Criteria (used in parameterized filtering)
//				: WCHAR* pwzPubProp		- Publisher Property Name
//				: WCHAR* pwzPubVal		- Publisher Property Value
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::AddSubscription(WCHAR* pwzProgID, WCHAR* pwzSubName, WCHAR* pwzECID, WCHAR* pwzPubID, WCHAR* pwzIID,
							  WCHAR* pwzMethod, WCHAR* pwzCriteria, WCHAR* pwzPubProp, WCHAR* pwzPubVal)
{
	HRESULT				hr=0;
	ICatalogObject		*pIApp=0,  *pIComp=0, *pISub=0, *pIProp=0;
	ICatalogCollection  *pIApps=0, *pIComps=0, *pISubs=0, *pIProps=0;
	IDispatch			*pIDisp=0;
	_bstr_t				bcomp, bapp;
	BOOL				fCreate=FALSE, fComplete = FALSE;
	long				lret;

	if (!m_pcat || !pwzProgID || !m_pwzapp)
		return E_INVALIDARG;

	bcomp = pwzProgID;
	bapp  = m_pwzapp;

	hr = GetObjectAndCollection(m_pcat, g_bAPP, bapp, APPLICATION, &pIApps, &pIApp);
	exit(hr);

	hr = GetObjectAndCollection(pIApps, pIApp, g_bCOMP, bcomp, COMPONENT, &pIComps, &pIComp);
	exit(hr);

	hr = GetCollection(pIComps, pIComp, g_bSUB, &pISubs);
	exit(hr);

	hr = pISubs->Add(&pIDisp);
	exit(hr);

	hr = pIDisp->QueryInterface(__uuidof(IDispatch), (LPVOID*)&pISub);
	exit(hr);

	hr = SetStringProperty(pISub, g_bNAME, pwzSubName);
	exit(hr);

	hr = SetStringProperty(pISub, g_bECID, pwzECID);
	exit(hr);

	hr = SetStringProperty(pISub, g_bPUBID, pwzPubID);
	exit(hr);

	hr = SetStringProperty(pISub, g_bIID, pwzIID);
	exit(hr);

	hr = SetStringProperty(pISub, g_bMETHOD, pwzMethod);
	exit(hr);

	hr = SetStringProperty(pISub, g_bCRITERIA, pwzCriteria);
	exit(hr);

	hr = pISubs->SaveChanges(&lret);
	exit(hr);

	fCreate = TRUE;

	if (pwzPubProp && pwzPubVal)
	{
		hr = GetCollection(pISubs, pISub, g_bPUBPROP, &pIProps);
		exit(hr);

		SAFERELEASE(pIDisp);
		hr = pIProps->Add(&pIDisp);
		exit(hr);

		hr = pIDisp->QueryInterface(__uuidof(ICatalogObject), (LPVOID*)&pIProp);
		exit(hr);

		hr = SetStringProperty(pIProp, g_bNAME, pwzPubProp);
		exit(hr);

		hr = SetStringProperty(pIProp, g_bVALUE, pwzPubVal);
		exit(hr);

		hr = pIProps->SaveChanges(&lret);
		exit(hr);
	}

	fComplete = TRUE;	

exit:
	if (fCreate && !fComplete)
		RemoveSubscription(pwzProgID, pwzSubName);

	SAFERELEASE(pIDisp);
	SAFERELEASE(pIProp);
	SAFERELEASE(pIProps);
	SAFERELEASE(pIDisp);
	SAFERELEASE(pISub);
	SAFERELEASE(pISubs);
	SAFERELEASE(pIComp);
	SAFERELEASE(pIComps);
	SAFERELEASE(pIApp);
	SAFERELEASE(pIApps);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::RemoveSubscription
// Purppose		: Removes a Persistent Subscription
// Parameters	:
//				: WCHAR* pwzProgID		- Name of the component for which the subscription to be deleted
//				: WCHAR* pwzSubName		- Name of the subscription
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::RemoveSubscription(WCHAR* pwzProgID, WCHAR* pwzSubName)
{
	HRESULT				hr =0;
	ICatalogObject		*pIApp =0, *pIComp=0;
	ICatalogCollection	*pIApps=0, *pIComps=0, *pISubs=0;

	if (!m_pcat || !m_pwzapp || !pwzProgID || !pwzSubName)
		return E_INVALIDARG;

	hr = GetObjectAndCollection(m_pcat, g_bAPP, _bstr_t(m_pwzapp), APPLICATION, &pIApps, &pIApp);
	exit(hr);

	hr = GetObjectAndCollection(pIApps, pIApp, g_bCOMP, _bstr_t(pwzProgID), COMPONENT, &pIComps, &pIComp);
	exit(hr);

	hr = GetCollection(pIComps, pIComp, g_bSUB, &pISubs);
	exit(hr);

	hr = RemoveNamedObjectFromCollection(pISubs, _bstr_t(pwzSubName), SUBSCRIPTION);

exit:
	SAFERELEASE(pISubs);
	SAFERELEASE(pIApp);
	SAFERELEASE(pIApps);

	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::AddTransientSubscription
// Purppose		: Adds a Persistent Subscription
// Parameters	:
//				: WCHAR* pwzSubName		- Name of the subscription
//				: WCHAR* pwzECID		- EventClass ID
//				: WCHAR* pwzPubID		- Name of the Publisher
//				: WCHAR* pwzIID         - Interface Name (in string form)
//				: IUnknown* punk		- IUnknown* of the subscriber
//				: WCHAR* pwzMethod		- Method in the interface to subscribe
//				: WCHAR* pwzCriteria	- Filter Criteria (used in parameterized filtering)
//				: WCHAR* pwzPubProp		- Publisher Property Name
//				: WCHAR* pwzPubVal		- Publisher Property Value
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::AddTransientSubscription(WCHAR* pwzSubName, WCHAR* pwzECID, WCHAR* pwzPubID, WCHAR* pwzIID, IUnknown *punk,
									   WCHAR* pwzMethod, WCHAR* pwzCriteria, WCHAR* pwzPubProp, WCHAR* pwzPubVal)
{
	HRESULT					hr =0;
	ICatalogObject			*pISub=0, *pIProp=0;
	ICatalogCollection		*pISubs=0, *pIProps=0;
	IDispatch				*pIDisp=0;
	long					lret=0;
	BOOL					fCreate=FALSE, fComplete = FALSE;
	
	if (!m_pcat || !m_pwzapp || !pwzSubName || !punk)
		return E_INVALIDARG;

	hr = GetCollection(m_pcat, g_bTRANSSUB, &pISubs);
	exit(hr);

	hr = pISubs->Add(&pIDisp);
	exit(hr);

	hr = pIDisp->QueryInterface(__uuidof(ICatalogObject), (LPVOID*)&pISub);
	exit(hr);

	hr = SetStringProperty(pISub, g_bNAME, pwzSubName);
	exit(hr);

	hr = SetStringProperty(pISub, g_bECID, pwzECID);
	exit(hr);

	hr = SetStringProperty(pISub, g_bPUBID, pwzPubID);
	exit(hr);

	hr = SetStringProperty(pISub, g_bIID, pwzIID);
	exit(hr);

	hr = SetIUnknownProperty(pISub, g_bSUBINT, punk);
	exit(hr);

	hr = SetStringProperty(pISub, g_bMETHOD, pwzMethod);
	exit(hr);

	hr = SetStringProperty(pISub, g_bCRITERIA, pwzCriteria);
	exit(hr);

	hr = pISubs->SaveChanges(&lret);
	exit(hr);

	fCreate = TRUE;

	if (pwzPubProp && pwzPubVal)
	{

		hr = GetCollection(pISubs, pISub, g_bTRANSPUBPROP, &pIProps);
		exit(hr);

		SAFERELEASE(pIDisp);
		hr = pIProps->Add(&pIDisp);
		exit(hr);

		hr = pIDisp->QueryInterface(__uuidof(ICatalogObject), (LPVOID*)&pIProp);
		exit(hr);

		hr = SetStringProperty(pIProp, g_bNAME, pwzPubProp);
		exit(hr);
		
		hr = SetStringProperty(pIProp, g_bVALUE, pwzPubVal);
		exit(hr);

		hr = pIProps->SaveChanges(&lret);
		exit(hr);
	}

	fComplete = TRUE;
	
exit:
	if (fCreate && !fComplete)
		RemoveTransientSubscription(pwzSubName);
	SAFERELEASE(pIDisp);
	SAFERELEASE(pIProp);
	SAFERELEASE(pIProps);
	SAFERELEASE(pISub);
	SAFERELEASE(pISubs);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::RemoveTransientSubscription
// Purppose		: Remolves a Persistent Subscription
// Parameters	:
//				: WCHAR* pwzSubName		- Name of the subscription
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::RemoveTransientSubscription(WCHAR* pwzName)
{
	HRESULT					hr =0;
	ICatalogCollection		*pISubs=0;

	if (!m_pcat || !m_pwzapp || !pwzName)
		return E_INVALIDARG;

	hr = GetCollection(m_pcat, g_bTRANSSUB, &pISubs);
	exit(hr);

	hr = RemoveNamedObjectFromCollection(pISubs, _bstr_t(pwzName), TRANSIENTSUB);
exit:
	SAFERELEASE(pISubs);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: CApp::SetProperty
// Purppose		: Sets a property on any component (Application, EventClass, Component, Persistent 
//				: subscription, Transient subscription, Persistent sub. property bag, Trans sub. 
//				: property bag)
// Parameters	:
//				: ADMINTYPE type		- Type of the component
//				: WCHAR* pwztypename	- Value depends on the type
//				: WCHAR* pwztypename2	- Value depends on the type
//				: WCHAR* pwzPropName	- Name of the Property
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT CApp::SetProperty(ADMINTYPE type, WCHAR* pwztypename, WCHAR* pwztypename2,
						  WCHAR* pwzPropName, VARIANT& var)
{
	HRESULT					hr=0;
	long					lindex;
	_bstr_t					bname;
	VARIANT					varname;
	ICatalogObject			*pIApp=0, *pIComp=0, *pISub=0, *pIProp=0, *pIFinal=0;
	ICatalogCollection		*pIApps=0, *pIComps=0, *pISubs=0, *pIProps=0, *pIFinals=0;
	IDispatch				*pIDisp=0;
	long					lret =0;
	

	// ADMINTYPE					pwztypename			pwztypename2		   
	//========================================================================
	// APPLICATION					Ignored				Ignored				   
	// COMPONENT					progid of the comp	Ignored				
	// SUBSCRIPTION					progid of the comp	name of the sub		
	// TRANSIENTSUB					name of the sub		Ignored				
	// PUBPROP						progid of the comp	name of the sub		
	// TRANSIENTPUBPROP				name of the sub		Ignored
	if (!m_pcat || !m_pwzapp || var.vt == VT_EMPTY)
		return E_INVALIDARG;

	hr = GetObjectAndCollection(m_pcat, g_bAPP, _bstr_t(m_pwzapp), APPLICATION, &pIApps, &pIApp);
	exit(hr);
	bname = pwzPropName;

	switch(type)
	{
	case APPLICATION:
		if (!pwzPropName)
			exit(hr= E_INVALIDARG);
		pIFinal = pIApp;
		pIFinals = pIApps;
		break;

	case COMPONENT:
		if (!pwztypename || !pwzPropName)
			exit(hr= E_INVALIDARG);

		hr = GetObjectAndCollection(pIApps, pIApp, g_bCOMP, _bstr_t(pwztypename), COMPONENT, &pIComps, &pIComp);
		exit(hr);
		pIFinal = pIComp;
		pIFinals = pIComps;
		break; 

	case SUBSCRIPTION:
		if (!pwztypename || !pwztypename2 || !pwztypename)
			exit(hr= E_INVALIDARG);

		hr = GetObjectAndCollection(pIApps, pIApp, g_bCOMP, _bstr_t(pwztypename), COMPONENT, &pIComps, &pIComp);
		exit(hr);

		hr = GetObjectAndCollection(pIComps, pIComp, g_bSUB, _bstr_t(pwztypename2), SUBSCRIPTION, &pISubs, &pISub);
		exit(hr);

		pIFinal = pISub;
		pIFinals = pISubs;
		break;

	case TRANSIENTSUB:
		if (!pwzPropName)
			exit(hr= E_INVALIDARG);
		hr = GetObjectAndCollection(m_pcat, g_bTRANSSUB, _bstr_t(pwztypename), TRANSIENTSUB, &pISubs, &pISub);
		exit(hr);

		pIFinal = pISub;
		pIFinals = pISubs;
		break;

	case PUBPROP:
		if (!pwzPropName || !pwztypename || !pwztypename2)
			exit(hr= E_INVALIDARG);

		hr = GetObjectAndCollection(pIApps, pIApp, g_bCOMP, _bstr_t(pwztypename), COMPONENT, &pIComps, &pIComp);
		exit(hr);

		hr = GetObjectAndCollection(pIComps, pIComp, g_bSUB, _bstr_t(pwztypename2), SUBSCRIPTION, &pISubs, &pISub);
		exit(hr);

		hr = GetCollection(pISubs, pISub, g_bPUBPROP, &pIProps);
		exit(hr);

		hr = GetNamedObjectFromCollection(pIProps, g_bNAME, &pIProp, &lindex, PUBPROP, _bstr_t(pwzPropName));
		if SUCCEEDED(hr)	// Change the VALUE
			bname = g_bVALUE;
		else if	(FAILED(hr) && (lindex == -1))			// Create a new NAME/VALUE property
		{
			hr = pIProps->Add(&pIDisp);
			exit(hr);

			hr = pIDisp->QueryInterface(__uuidof(IDispatch), (LPVOID*)&pIProp);
			exit(hr);

			varname.bstrVal = SysAllocString(pwzPropName);
			if (!varname.bstrVal)
				exit(hr=E_OUTOFMEMORY);
			varname.vt = VT_BSTR;

			hr = pIProp->put_Value(g_bNAME, varname);
			exit(hr);

			bname = g_bVALUE;
			pIFinal = pIProp;
			pIFinals = pIProps;
		}
		else
			exit(hr);
		pIFinal = pIProp;
		pIFinals = pIProps;
		break;

	case TRANSIENTPUBPROP:
		if (!pwzPropName || !pwztypename)
			exit(hr= E_INVALIDARG);

		hr = GetObjectAndCollection(m_pcat, g_bTRANSSUB, _bstr_t(pwztypename), TRANSIENTSUB, &pISubs, &pISub);
		exit(hr);

		hr = GetCollection(pISubs, pISub, g_bTRANSPUBPROP, &pIProps);
		exit(hr);

		hr = GetNamedObjectFromCollection(pIProps, g_bNAME, &pIProp, &lindex, TRANSIENTPUBPROP, _bstr_t(pwzPropName));
		if SUCCEEDED(hr)	// Change the VALUE
			bname = g_bVALUE;
		else if	(FAILED(hr) && (lindex == -1))		// Create a new NAME/VALUE property
		{
			hr = pIProps->Add(&pIDisp);
			exit(hr);

			hr = pIDisp->QueryInterface(__uuidof(IDispatch), (LPVOID*)&pIProp);
			exit(hr);

			varname.bstrVal = SysAllocString(pwzPropName);
			if (!varname.bstrVal)
				exit(hr=E_OUTOFMEMORY);
			varname.vt = VT_BSTR;

			hr = pIProp->put_Value(g_bNAME, varname);
			exit(hr);

			bname = g_bVALUE;
			pIFinal = pIProp;
			pIFinals = pIProps;
		}
		else
			exit(hr);
		pIFinal = pIProp;
		pIFinals = pIProps;
		break;

	default:
		exit(hr= E_INVALIDARG);
	}

	hr = pIFinal->put_Value(bname, var);
	exit(hr);

	hr = pIFinals->SaveChanges(&lret);

exit:
	SAFERELEASE(pIDisp);
	SAFERELEASE(pIProp);
	SAFERELEASE(pIProps);
	SAFERELEASE(pISubs);
	SAFERELEASE(pISub);
	SAFERELEASE(pIApp);
	SAFERELEASE(pIApps);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: GetCollection
// Purppose		: Gets a collection from the Catalogue
// Parameters	:
//				: ICOMAdminCatalog* pICat				- Admin Catalog object
//				: BSTR szCollName						- Collection Name
//				: ICatalogCollection** ppICol			- Collection returned
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT GetCollection(ICOMAdminCatalog* pICat, BSTR szCollName, ICatalogCollection** ppICol)
{
	HRESULT hr = E_INVALIDARG;
	CComBSTR bstr;
	IDispatch* pIDisp = NULL;
	if (!pICat || !szCollName || !ppICol) 
		goto exit;
	bstr = szCollName;
	hr = pICat->GetCollection(bstr.m_str, &pIDisp);
	exit(hr);
	hr = pIDisp->QueryInterface(__uuidof(ICatalogCollection), (LPVOID*)ppICol);
	exit(hr);
	hr = (*ppICol)->Populate();
exit:
	SAFERELEASE(pIDisp);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: GetCollection
// Purppose		: Gets a collection from the Catalogue
// Parameters	:
//				: ICatalogCollection* pIParentColl		- Parent Collection
//				: ICatalogObject* pICatObj				- Parent Object
//				: BSTR szCollName						- Collection Name
//				: ICatalogCollection** ppICol			- Collection returned
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////	
HRESULT GetCollection(ICatalogCollection* pIParentColl, ICatalogObject* pICatObj, BSTR szCollName, 
					  ICatalogCollection** ppICol)
{
	HRESULT hr = E_INVALIDARG;
	CComBSTR bstr;
	VARIANT var;
	IDispatch* pIDisp = NULL;
	VariantInit(&var);
	if (!pIParentColl || !pICatObj || !szCollName || !ppICol)
		goto exit;
	hr = pICatObj->get_Key(&var);
	exit(hr);
	bstr = szCollName;
	hr = pIParentColl->GetCollection(bstr.m_str, var, &pIDisp);
	exit(hr);
	hr = pIDisp->QueryInterface(__uuidof(ICatalogCollection), (LPVOID*)ppICol);
	exit(hr);
	hr = (*ppICol)->Populate();
exit:
	VariantClear(&var);
	if(pIDisp)
		pIDisp->Release();
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: GetObjectAndCollection
// Purppose		: Gets a collection from the Catalogue
// Parameters	:
//				: ICOMAdminCatalog* pICat				- Admin Catalog object
//				: BSTR szCollName						- Collection Name
//				: BSTR szObjectName						- Object name
//				: ADMINTYPE type						- Type of the object
//				: ICatalogCollection** ppICol			- Collection returned
//				: ICatalogObject* ppIObj				- Object returned
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////	
HRESULT GetObjectAndCollection(ICOMAdminCatalog* pICat, BSTR szCollName, BSTR szObjectName, ADMINTYPE type, 
							   ICatalogCollection** ppICol, ICatalogObject** ppIObj)
{
	HRESULT hr = E_FAIL;
	hr = GetCollection(pICat, szCollName, ppICol);
	exit(hr);
	hr = GetNamedObjectFromCollection(*ppICol, szObjectName, ppIObj, NULL, type);
exit:
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: GetObjectAndCollection
// Purppose		: Gets a collection from the Catalogue
// Parameters	:
//				: ICatalogCollection* pIParentColl		- Parent Collection
//				: ICatalogObject* pIParentObject		- Parent Object
//				: BSTR szCollName						- Collection Name
//				: BSTR szObjectName						- Object name
//				: ADMINTYPE type						- Type of the object
//				: ICatalogCollection** ppICol			- Collection returned
//				: ICatalogObject* ppIObj				- Object returned
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////	
HRESULT GetObjectAndCollection(ICatalogCollection* pIParentColl, ICatalogObject* pIParentObject, BSTR szCollName, 
							   BSTR szObjectName, ADMINTYPE type, ICatalogCollection** ppICol, ICatalogObject** ppIObj)
{
	HRESULT hr = E_FAIL;
	hr = GetCollection(pIParentColl, pIParentObject, szCollName, ppICol);	
	exit(hr);
	hr = GetNamedObjectFromCollection(*ppICol, szObjectName, ppIObj, NULL, type);
exit:
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: RemoveNamedObjectFromCollection
// Purppose		: Removes an object from a collection
// Parameters	:
//				: ICatalogCollection* pIParentColl		- Collection from the object has to be 
//														  removed
//				: BSTR szObjectName						- Object name
//				: ADMINTYPE type						- type of the object
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////	
HRESULT RemoveNamedObjectFromCollection(ICatalogCollection* pICol, BSTR szObjectName, ADMINTYPE type)
{
	HRESULT hr = E_FAIL;
	ICatalogObject* pICatObj = NULL;
	LONG i, lTotal;

	if (wcscmp(szObjectName, SysAllocString(L"*"))) 
	{
		hr = GetNamedObjectFromCollection(pICol, szObjectName, &pICatObj, &i, type);
		exit(hr);
		hr = pICol->Remove(i);
		exit(hr);
		hr = pICol->SaveChanges(&i);
	}
	else
	{
		hr = pICol->get_Count(&lTotal);
		exit(hr);
		for (i=lTotal-1; i >= 0; i--)
		{
			hr = pICol->Remove(i);
			exit(hr);
			hr = pICol->SaveChanges(&i);
			exit(hr);
		}
	}

exit:
	if(pICatObj)
		pICatObj->Release();
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: GetNamedObjectFromCollection
// Purppose		: Gets an object from a collection
// Parameters	:
//				: ICatalogCollection* pIParentColl		- Collection from the object has to be 
//														  retrieved
//				: BSTR bstrObjName						- Object name
//				: ADMINTYPE type						- type of the object
//				: ICatalogObject** ppObj				- return Object
//				: LONG* plIndex							- Index of the object (-1, if not found)
//				: ADMINTYPE type						- type of the object
//				: BSTR bstrPropname						- name of the property
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////	
HRESULT GetNamedObjectFromCollection(ICatalogCollection* pCol, BSTR bstrObjName, ICatalogObject** ppObj, 
									 LONG* plIndex, ADMINTYPE type, BSTR bstrPropname)
{
	HRESULT hr = E_FAIL;
	LONG lCount = 0;
	LONG i = 0;
	ICatalogObject* pObj = NULL;
	BSTR bstrName;
	VARIANT varProp;
	BOOL	fFound = FALSE;

	VariantInit(&varProp);
	if (!pCol || !bstrObjName || !ppObj)  	
		return E_INVALIDARG;
	
	if (!bstrPropname)
	{
		hr = GetObjectNameProperty(type, &bstrName);
		exit(hr);
	}
	else
		bstrName = bstrPropname;

	*ppObj = NULL;

	hr = pCol->Populate();
	exit(hr);

	hr = pCol->get_Count(&lCount);
	exit(hr);

	if (lCount == 0)
	{
		*plIndex = -1; // To indicate that the object is not found in the collection
		exit(hr=E_FAIL);
	}
	
	// Loop through 
	for (i = 0; i < lCount; i++)
	{
		VariantClear(&varProp);

		// Get the next item
		hr = pCol->get_Item(i, (IDispatch**)&pObj);
		exit(hr);
		
		// Retrieve it's name property
		hr = pObj->get_Value((BSTR)bstrName, &varProp);
		exit(hr);

		// Check it's name property for a match
		if (wcscmp(bstrObjName, varProp.bstrVal) == 0)
		{
			// Found it!
			*ppObj = pObj;
			pObj->AddRef();
			VariantClear(&varProp);
			// does user want index of the just-found object?
			if (plIndex)
				*plIndex = i;
			fFound = TRUE;
			hr = S_OK;
			goto exit;
		}
	    SAFERELEASE(pObj);
	}
	if (plIndex)
		*plIndex = -1; // To indicate that the object is not found in the collection
exit:
	SysFreeString(bstrName);
	// If we got here then we didn't find it
	SAFERELEASE(pObj);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: GetObjectNameProperty
// Purppose		: Gets the property name of the object
// Parameters	:
//				: ADMINTYPE type						- type of the object
//				: BSTR* pbstr							- name
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////	
HRESULT GetObjectNameProperty(ADMINTYPE type, BSTR* pbstr)
{	
	if (!pbstr)
		return E_INVALIDARG;

	switch (type)
	{	
	case APPLICATION:
	case SUBSCRIPTION:
	case TRANSIENTSUB:
		*pbstr = SysAllocString(g_wczNAME);
		break;
	case COMPONENT:
		*pbstr = SysAllocString(g_wczProgIDProp);
		break;
	default:
		assert(FALSE);
		break;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: SetStringProperty
// Purppose		: Gets the property name of the object
// Parameters	:
//				: ICatalogObject *pcat			-  Pointer to the object
//				: BSTR bPROP					-  Name of the property
//              : WCHAR* pval					-  Value of the property
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////	
HRESULT SetStringProperty(ICatalogObject *pcat, BSTR bPROP, WCHAR* pval)
{
	HRESULT hr;
	VARIANT var;
	if (!pcat)
		return E_INVALIDARG;

	if (!pval)
		return S_FALSE;

	VariantClear(&var);

	var.bstrVal = SysAllocString(pval);
	if (!var.bstrVal)
		exit(hr=E_OUTOFMEMORY);
	var.vt = VT_BSTR;

	hr = pcat->put_Value(bPROP, var);
	exit(hr);

exit:
	VariantClear(&var);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: SetIUnknownProperty
// Purppose		: Gets the property name of the object
// Parameters	:
//				: ICatalogObject *pcat			-  Pointer to the object
//				: BSTR bPROP					-  Name of the property
//              : IUnknown* punk				-  Value of the property
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////	
HRESULT SetIUnknownProperty(ICatalogObject *pcat, BSTR bPROP, IUnknown* punk)
{
	HRESULT hr;
	VARIANT var;
	if (!punk || !pcat)
		return E_INVALIDARG;

	VariantClear(&var);

	var.punkVal = punk;
	var.vt = VT_UNKNOWN;
	punk->AddRef();	// We'll be caling VariantClear

	hr = pcat->put_Value(bPROP, var);
	exit(hr);

exit:
	VariantClear(&var);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Name			: SetIUnknownProperty
// Purppose		: Gets the property name of the object
// Parameters	:
//				: ICatalogObject *pcat			-  Pointer to the object
//				: BSTR bPROP					-  Name of the property
//              : BOOL fFlag					-  Value of the property
// Return Value : HRESULT
////////////////////////////////////////////////////////////////////////////////////////////////////	
HRESULT SetBoolProperty(ICatalogObject *pcat, BSTR bPROP, BOOL fFlag)
{
	HRESULT	hr;
	VARIANT var;

	if (!pcat)
		return E_INVALIDARG;

	VariantClear(&var);

	var.boolVal = fFlag;
	var.vt = VT_BOOL;

	hr = pcat->put_Value(bPROP, var);
	exit(hr);

exit:
	VariantClear(&var);
	return hr;
}

