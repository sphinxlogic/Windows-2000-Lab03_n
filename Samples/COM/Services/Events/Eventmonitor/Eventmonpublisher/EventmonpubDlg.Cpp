// EventMonPubdlg.cpp : Implementation of CPubdlg
#include "stdafx.h"
#include "EventMonPubdlg.h"
#include "..\include\macro.h"
#include "..\EventMoneventclass\EventMoneventclass.h"
#include "..\include\adminwrap.h"
#include "..\EventMonSubscriber\EventMonSubscriber.h"
#include "..\EventMonfilter\EventMonfilter.h"
#include "Adminwrap.h"

//*********************************************
// Globals

#define PROGID_EventMonEventClass	OLESTR("EventMonEventClass.EventMonEventClass.1")
#define PROGID_EventMonSubscriber	OLESTR("EventMonSubscriber.EventMonSubscriber.1")

const	TCHAR tszReg[]						= _T("Register");

const	TCHAR tszUnReg[]					= _T("UnRegister");

const	TCHAR tszDummy[]					= _T("Dummy");

const	TCHAR g_tzFilterProp[]				= _T("FilterProperty"); 

WCHAR	g_wzInterface[NUM_INTERFACE][30]	= {L"IDiskEvents",L"IFileSystemEvents",L"ISystemEvents"};
TCHAR   g_tzInterface[NUM_INTERFACE][30]      = {_T("IDiskEvents"),_T("IFileSystemEvents"),_T("ISystemEvents")};

const	GUID*	g_piid[]					= {&__uuidof(IDiskEvents), 
											   &__uuidof(IFileSystemEvents),
										       &__uuidof(ISystemEvents)};
WCHAR   g_wzMethod[3][4][30]				= {{L"DiskFull"},
												{L"FileCreated", L"FileDeleted", L"FileRenamed", L"FileUpdated"},
												{L"ProcessCreated", L"ProcessTerminated", L"PNPDeviceAdded"}};
TCHAR	g_tzCriteria[]= _T("szDriveName = \'Dummy\'");

WCHAR	g_wzPubAppName[] = L"EventMonPublisherApp";
WCHAR	g_wzSubAppName[] = L"EventMonSubscriberApp";
WCHAR	g_wzPubID[]		 = L"EventMonPublisher";
WCHAR	g_wzsubname[]	 = L"EventMonSubscription";
TCHAR   g_tzString[MAX_PATH];

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::OnInitDialog
// Purppose		: Message Handler. 
// Parameters	:
//				: WORD wNotifyCode
//				: WORD wID
//				: HWND hWndCtl
//			    : BOOL& bHandled
// Return Value : LRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRESULT		hr =0;
	TCHAR		tzDllPathName[MAX_PATH];
	WCHAR		*pwzdllname=0;
	USES_CONVERSION;
	
	m_pSubApp =0;
	m_pPubApp =0;

	SetDlgItemText(IDC_REGEC, tszReg);
	SetDlgItemText(IDC_REGSUB, tszReg);
	CheckDlgButton(IDC_PERSISTENT, BST_CHECKED);
	//CheckDlgButton(IDC_ALLINT, BST_CHECKED);
	CheckDlgButton(IDC_ALLOWINPROC, BST_CHECKED);
	
	for (int i=0; i<NUM_COMBO; i++)
		PopulateCombo(IDC_DEFAULTQUERY+i);

	SetDlgItemText(IDC_PARAM, tszDummy);
	hr = CoCreateInstance(__uuidof(COMAdminCatalog),
					      NULL,
						  CLSCTX_SERVER,
						  __uuidof(ICOMAdminCatalog),
						  (LPVOID*)&m_pcat);
	exit(hr);

	SetDlgItemText(IDC_FILTERCRITERIASTR, g_tzCriteria);
	
	m_pPubApp = new CApp(m_pcat, g_wzPubAppName);
	m_pSubApp = new CApp(m_pcat, g_wzSubAppName);

	if (!m_pPubApp || !m_pSubApp)
		exit(hr = E_OUTOFMEMORY);

	hr = m_pPubApp->CreateApp(TRUE);
	exit(hr);

	hr = m_pSubApp->CreateApp();
	exit(hr);
	
	hr = GetSubDllPathName(tzDllPathName);
	exit(hr);

	pwzdllname = T2W(tzDllPathName);

	hr = m_pSubApp->InstallComponent(pwzdllname);
	exit(hr);

exit:
	if FAILED(hr)
	{
		wsprintf(g_tzString,_T("CPubdlg::OnInitDialog failed. Value of hr is %08x"),hr);
		MessageBox(g_tzString, _T("EventMonPubliser"),MB_OK);
	}
	return 1;  
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::OnDestroy
// Purppose		: Message Handler. Called when the Close button is clicked
// Parameters	:
//				: WORD wNotifyCode
//				: WORD wID
//				: HWND hWndCtl
//			    : BOOL& bHandled
// Return Value : LRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Cleanup
	if (m_pPubApp)
	{
		m_pPubApp->DeleteApp();
		delete m_pPubApp;
		m_pPubApp=0;
	}

	if (m_pSubApp)
	{
		m_pSubApp->DeleteApp();
		m_pSubApp->RemoveTransientSubscription(g_wzsubname);
		delete m_pSubApp;
		m_pSubApp=0;
	}
	SAFERELEASE(m_pcat);
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::OnClickedRegec
// Purppose		: Command Handler
// Parameters	:
//				: WORD wNotifyCode
//				: WORD wID
//				: HWND hWndCtl
//			    : BOOL& bHandled
// Return Value : LRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::OnClickedRegec(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	TCHAR	tzquery[MAX_PATH]=_T("\0");
	UINT	ufilter ,uallowinproc ,	ufireinparallel,udefaultquery, upubid;
	HRESULT	hr;
	TCHAR	tzdllname[MAX_PATH];
	WCHAR	*pwzdllname=0;
	LPOLESTR	strFilterCLSID = 0;
	USES_CONVERSION;

	GetDlgItemText(IDC_REGEC, tzquery, MAX_PATH);

	if (!m_pPubApp || !m_pSubApp)
		exit(hr= E_POINTER);

	// Register the EventClass
	if (lstrcmpi(tzquery, tszReg) ==0)	
	{
		ufilter			= IsDlgButtonChecked(IDC_DECL_FILTER);
		uallowinproc	= IsDlgButtonChecked(IDC_ALLOWINPROC);
		ufireinparallel = IsDlgButtonChecked(IDC_FIREINPARALLEL);
		udefaultquery	= IsDlgButtonChecked(IDC_SETDEFAULTQUERY);
		upubid			= IsDlgButtonChecked(IDC_PUBID_EC);

		hr = GetECDllPathName(tzdllname);
		exit(hr);

		pwzdllname = T2W(tzdllname);
			
		hr = StringFromCLSID(__uuidof(EventMonFilter), &strFilterCLSID);
		exit(hr);

		hr = m_pPubApp->AddEventClass(pwzdllname,
								      0, 
									  PROGID_EventMonEventClass,
									  (upubid == BST_CHECKED)?g_wzPubID:NULL, 
									  (ufilter == BST_CHECKED)?strFilterCLSID:NULL,
									  (uallowinproc == BST_CHECKED)?TRUE:FALSE,
									  (ufireinparallel == BST_CHECKED)?TRUE:FALSE);
		if SUCCEEDED(hr)
		{
			SetDlgItemText(IDC_REGEC, tszUnReg);

			// Disable the runtime filter option
			if (ufilter == BST_CHECKED)
				::EnableWindow(GetDlgItem(IDC_RUNTIME_FILTER), FALSE);
		}
	}
	else // unregister the EventClass
	{
		hr = m_pPubApp->RemoveComponent(PROGID_EventMonEventClass);
		//hr = UnregisterEventClass(m_pcat);
		if SUCCEEDED(hr)
		{
			SetDlgItemText(IDC_REGEC, tszReg);

			// Enable the runtime filter option
			::EnableWindow(GetDlgItem(IDC_RUNTIME_FILTER), TRUE);
		}
	}

exit:
	CoTaskMemFree(strFilterCLSID);
	if FAILED(hr)
	{
		wsprintf(g_tzString,_T("CPubdlg::OnClickedRegec failed. Value of hr is %08x"),hr);
		MessageBox(g_tzString,_T("EventMonPubliser"),MB_OK);
	}
	return hr;
}
//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::OnClickedRegsub
// Purppose		: Command Handler
// Parameters	:
//				: WORD wNotifyCode
//				: WORD wID
//				: HWND hWndCtl
//			    : BOOL& bHandled
// Return Value : LRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::OnClickedRegsub(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HRESULT			hr =0;
	IUnknown		*punk =0;
	TCHAR			tzInterface[MAX_PATH] = _T("\0");
	TCHAR			tzMethod[MAX_PATH] = _T("\0");
	TCHAR			tzFilterCriteria[MAX_PATH] = _T("\0");
	TCHAR			tzPubprop[MAX_PATH] = _T("\0");
	LPOLESTR		strECID=0, strIID =0;
	VARIANT			var;

	UINT  ufiltercriteria, ulocal, upersistent, uall, uallint, uecid, upubid, utransient;
	UINT  upubprop;
	
	USES_CONVERSION;
	WCHAR	*pwzMethod =0 , *pwzCriteria =0, *pwzPubprop =0, *pwzPubVal=0;

	
	GetDlgItemText(IDC_REGSUB, tzInterface, MAX_PATH);

	upersistent		= IsDlgButtonChecked(IDC_PERSISTENT);
	utransient		= IsDlgButtonChecked(IDC_TRANSIENT);
	// Register the Subscription
	if (lstrcmpi(tzInterface, tszReg) ==0)
	{
		ufiltercriteria = IsDlgButtonChecked(IDC_FILTERCRITERIA);
		ulocal			= IsDlgButtonChecked(IDC_LOCAL);
		uall			= IsDlgButtonChecked(IDC_ALL);
		uallint			= IsDlgButtonChecked(IDC_ALLINT);
		uecid			= IsDlgButtonChecked(IDC_ECID);
		upubid			= IsDlgButtonChecked(IDC_PUBID);
		upubprop		= IsDlgButtonChecked(IDC_PUBPROP);

		// Check for any invalid inputs from GUI
		if (upersistent == utransient)
			exit(hr = E_FAIL);

		tzInterface[0] = _T('\0');

		if (ufiltercriteria == BST_CHECKED)
		{
			if (!GetDlgItemText(IDC_FILTERCRITERIASTR, tzFilterCriteria, MAX_PATH))
				exit( hr = HRESULT_FROM_WIN32(GetLastError()));
			pwzCriteria = T2W(tzFilterCriteria);
		}

		if (uallint != BST_CHECKED)
		{
			if (!GetDlgItemText(IDC_INTERFACE, tzInterface, MAX_PATH))
				exit(hr = HRESULT_FROM_WIN32(GetLastError()));

			for (int i=0; i<NUM_INTERFACE; i++)
			{
				if (_tcscmp(g_tzInterface[i], tzInterface)==0)
				{
					hr = StringFromCLSID(*g_piid[i],&strIID);
					exit(hr);
					break;
				}
			}
		}

		if (uallint != BST_CHECKED && uall != BST_CHECKED)
		{
			if (!GetDlgItemText(IDC_METHOD, tzMethod, MAX_PATH))
				exit(hr = HRESULT_FROM_WIN32(GetLastError()));
			pwzMethod = T2W(tzMethod);
		}

		if (upubprop == BST_CHECKED)
		{
			if (!GetDlgItemText(IDC_PUBPROPEDIT, tzPubprop, MAX_PATH))
				exit(hr = HRESULT_FROM_WIN32(GetLastError()));
			pwzPubprop = T2W(g_tzFilterProp);
			pwzPubVal = T2W(tzPubprop);
		}

		// Check for Valid combinations
		if (uecid == BST_CHECKED && upubid == BST_CHECKED)
		{	
			wsprintf(g_tzString,_T("You cannot have both PublisherID and EventClassID properties set on a subscription"));
			MessageBox(g_tzString, _T("EventMonPubliser - CPubdlg::OnClickedRegsub"),MB_OK);
			goto exit;
		}

		if (uecid != BST_CHECKED && upubid != BST_CHECKED && uallint == BST_CHECKED)
		{
			wsprintf(g_tzString,_T("You cannot have PublisherID, EventClassID and InterfaceID set to NULL"));
			MessageBox(g_tzString, _T("EventMonPubliser - CPubdlg::OnClickedRegsub"),MB_OK);
			goto exit;
		}


		hr = StringFromCLSID(__uuidof(EventMonEventClass), &strECID);
		exit(hr);

		if (upersistent == BST_CHECKED)
		{
			if (ulocal == BST_CHECKED)
			{
				var.boolVal = TRUE;
				var.vt = VT_BOOL;

				// Set the Activation of App to "Server"
				hr = m_pSubApp->SetProperty(APPLICATION, NULL, NULL, L"Activation",var);
				exit(hr);
			}

			hr = m_pSubApp->AddSubscription(PROGID_EventMonSubscriber,
											g_wzsubname,
											(uecid == BST_CHECKED)?strECID:NULL,
											(upubid == BST_CHECKED)?g_wzPubID:NULL,
											strIID,
											pwzMethod,
											(ufiltercriteria == BST_CHECKED)?pwzCriteria:NULL,
											pwzPubprop,
											pwzPubVal);
		}
		else
		{

			// Create a transient subscriber
			hr = CoCreateInstance(__uuidof(EventMonSubscriber),
								  NULL,
								  CLSCTX_SERVER,
								  IID_IUnknown,
								  (LPVOID*)&punk);
			exit(hr);

			hr = m_pSubApp->AddTransientSubscription(g_wzsubname,
													 (uecid == BST_CHECKED)?strECID:NULL,
													 (upubid == BST_CHECKED)?g_wzPubID:NULL,
													 strIID,
													 punk,
													 pwzMethod,
													 (ufiltercriteria == BST_CHECKED)?pwzCriteria:NULL,
													 pwzPubprop,
													 pwzPubVal);
		}
		exit(hr);

		SetDlgItemText(IDC_REGSUB, tszUnReg);
		m_fPersistent = (upersistent == BST_CHECKED)?TRUE:FALSE;
	}
	else	// unregister the subscription
	{
		if (m_fPersistent)
			hr = m_pSubApp->RemoveSubscription(PROGID_EventMonSubscriber,
										       g_wzsubname);
		else
			hr = m_pSubApp->RemoveTransientSubscription(g_wzsubname);
		exit(hr);
		
		SetDlgItemText(IDC_REGSUB, tszReg);
	}

exit:
	SAFERELEASE(punk);
	CoTaskMemFree(strECID);
	CoTaskMemFree(strIID);
	if FAILED(hr)
	{
		wsprintf(g_tzString,_T("CPubdlg::OnClickedRegsub failed. Value of hr is %08x"),hr);
		MessageBox(g_tzString, _T("EventMonPubliser"),MB_OK);
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::OnSelChange
// Purppose		: Command Handler
// Parameters	:
//				: WORD wNotifyCode
//				: WORD wID
//				: HWND hWndCtl
//			    : BOOL& bHandled
// Return Value : LRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::OnSelChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int nSel = ::SendMessage(GetDlgItem(wID), CB_GETCURSEL, 0,0);
	if (nSel == CB_ERR)
		return E_FAIL;

	// Interface in the Subscription
	if (wID == IDC_INTERFACE)
		PopulateCombo(IDC_METHOD, nSel, FALSE);

	if (wID == IDC_FIREINTERFACE)
		PopulateCombo(IDC_FIREMETHOD, nSel, FALSE);

	return S_OK;			
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::OnClickedFire
// Purppose		: Command Handler
// Parameters	:
//				: WORD wNotifyCode
//				: WORD wID
//				: HWND hWndCtl
//			    : BOOL& bHandled
// Return Value : LRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::OnClickedFire(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// Create EventClass object and fire
	HRESULT		hr;
	TCHAR		tszmax[MAX_PATH] = _T("\0");
	USES_CONVERSION;
	WCHAR*		wzmax =0;
	_bstr_t		bval;
	int			i=0;
	int			nErr=0;

	CComPtr<IUnknown> unk;
	CComPtr<IMultiInterfaceEventControl> mec;
	CComPtr<IMultiInterfacePublisherFilter> mpf;
	CComPtr<IDispatch> disp;

	hr = unk.CoCreateInstance(__uuidof(EventMonEventClass));	
	exit(hr);

	// Pickup the Interface name from the Combobox IDC_FIREINTERFACE
	if (!GetDlgItemText(IDC_FIREINTERFACE, tszmax, sizeof(tszmax)))
		exit(HRESULT_FROM_WIN32(GetLastError()));

	wzmax = T2W(tszmax);

	for (i=0; i<NUM_INTERFACE; i++)
	{
		if (wcsicmp(wzmax, g_wzInterface[i])==0)
			break;	
	}

	if (i>= NUM_INTERFACE)
		exit(E_FAIL);

	// Pickup the Method name from the Combobox IDC_FIREMETHOD
	if (!GetDlgItemText(IDC_FIREMETHOD, tszmax, sizeof(tszmax)))
		exit(HRESULT_FROM_WIN32(GetLastError()));

	wzmax = T2W(tszmax);

	// Get the Method argument from the IDC_PARAM
	if (!GetDlgItemText(IDC_PARAM, tszmax, sizeof(tszmax)))
		exit(HRESULT_FROM_WIN32(GetLastError()));

	// Check if we want to install Pubisher Filter
	if (IsDlgButtonChecked(IDC_RUNTIME_FILTER) == BST_CHECKED)
	{
		_bstr_t	bmethod;

		// Get a pointer to IMultiInterfaceEventControl
		hr = unk.QueryInterface(&mec);
		exit(hr);

		hr = mec.QueryInterface(&disp);
		exit(hr);

		bmethod = wzmax;

		// Create and Initlialize the filter
		hr = mpf.CoCreateInstance(__uuidof(EventMonFilter));
		exit(hr);

		// Initialize the filter
		hr = mpf->Initialize(mec);
		exit(hr);

		hr = mec->SetMultiInterfacePublisherFilter(mpf);
		exit(hr);
	}

	bval = tszmax;


	switch(i)
	{
	case 0:	// IDiskEvents interface
		hr = FireDiskMethod(unk, wzmax, bval);
		break;

	case 1: // IFileSystemEvents interface
		hr = FireFileMethod(unk, wzmax, bval);
		break;

	case 2: // ISystemEvents interface
		hr = FireSystemMethod(unk, wzmax, bval);
		break;
	}

exit:
	if FAILED(hr)
	{
		wsprintf(g_tzString,_T("CPubdlg::OnClickedRegsub failed. Value of hr is %08x"),hr);
		MessageBox(g_tzString, _T("EventMonPubliser"),MB_OK);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::OnClickedAlInterfaces
// Purppose		: Command Handler
// Parameters	:
//				: WORD wNotifyCode
//				: WORD wID
//				: HWND hWndCtl
//			    : BOOL& bHandled
// Return Value : LRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::OnClickedAlInterfaces(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	// If we are selecting all interfaces then we've to disable
	// the interface combo box, method combo box and all methods check box

	BOOL fEnable = (IsDlgButtonChecked(wID) == BST_CHECKED)?FALSE:TRUE;
	::EnableWindow(GetDlgItem(IDC_INTERFACE), fEnable);
	::EnableWindow(GetDlgItem(IDC_METHOD), fEnable);
	::EnableWindow(GetDlgItem(IDC_ALL), fEnable);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::OnClickedAllMethods
// Purppose		: Command Handler
// Parameters	:
//				: WORD wNotifyCode
//				: WORD wID
//				: HWND hWndCtl
//			    : BOOL& bHandled
// Return Value : LRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::OnClickedAllMethods(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	BOOL fEnable = (IsDlgButtonChecked(wID) == BST_CHECKED)?FALSE:TRUE;
	::EnableWindow(GetDlgItem(IDC_METHOD), fEnable);
	::EnableWindow(GetDlgItem(IDC_ALLINT), fEnable);
	
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::PopulateCombo
// Purppose		: Populates the Combo Boxes
// Parameters	:
//				: int nCombo			- ComboBox ID
//				: int ncasespecific		- Identifies the Interface
//				: BOOL bdef			    - Default Value flag
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::PopulateCombo(int nCombo, int ncasespecific, BOOL bdef)
{
	USES_CONVERSION;
	TCHAR* tzstring =0;

	switch(nCombo)
	{
	case IDC_DEFAULTQUERY:
		break;

	case IDC_INTERFACE:
	case IDC_FIREINTERFACE:
		{
			for (int i=0; i<NUM_INTERFACE; i++)
			{
				tzstring = W2T(g_wzInterface[i]);
				::SendMessage(GetDlgItem(nCombo), CB_ADDSTRING,0,(LPARAM)(LPCTSTR)tzstring);
			}
			tzstring = W2T(g_wzInterface[0]);
			::SendMessage(GetDlgItem(nCombo), CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)tzstring);
		}
		break;

	case IDC_METHOD:
	case IDC_FIREMETHOD:
		{
			if (bdef)
			{
				HWND hwnd = GetDlgItem(nCombo);
				tzstring = W2T(g_wzMethod[0][0]);
				::SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)tzstring);
				::SendMessage(hwnd, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)tzstring);
			}
			else // populate combobox according to ncasespecific
			{
				int nMethod =0;
				HWND hwnd = GetDlgItem(nCombo);

				switch(ncasespecific)
				{
				case 0:	// IDiskEvents interface
					nMethod = NUM_METHOD_IDISK;
					break;

				case 1: // IFileSystemEvents interface
					nMethod = NUM_METHOD_IFILESYSTEM;
					break;

				case 2: // ISystemEvents interface
					nMethod = NUM_METHOD_ISYSTEM;
					break;
				}
				
				::SendMessage(hwnd, CB_RESETCONTENT, 0, 0);
				for (int i=0; i<nMethod; i++)
				{
					tzstring = W2T(g_wzMethod[ncasespecific][i]);
					::SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)tzstring);
				}
				tzstring = W2T(g_wzMethod[ncasespecific][0]);
				::SendMessage(hwnd, CB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)tzstring);
			}
		}
		break;

	default:
		break;
	}
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::FireDiskMethod
// Purppose		: Fires the method related to IDiskEvents interface
// Parameters	:
//				: IUnknown* punk		- IUnknown of the EventClass
//				: WCHAR* wzmethod		- Method in the IDiskEvents interface
//				: BSTR bstrval			- BSTR value to be passed as the method arg.
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::FireDiskMethod(IUnknown* punk, WCHAR* wzmethod, BSTR bstrval)
{
	IDiskEvents	*pdisk = 0;

	// Ignore wzmethod value as IDiskEvents interface has only one method
	if (!punk)
		return E_INVALIDARG;

	HRESULT hr = punk->QueryInterface(__uuidof(IDiskEvents), (void**)&pdisk);
	exit(hr);

	// Event firing happens here...
	hr = pdisk->DiskFull(bstrval);

exit:
	RELEASE(pdisk);
	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::FireFileMethod
// Purppose		: Fires the method related to IFileSystemEvents interface
// Parameters	:
//				: IUnknown* punk		- IUnknown of the EventClass
//				: WCHAR* wzmethod		- Method in the IFileSystemEvents interface
//				: BSTR bstrval			- BSTR value to be passed as the method arg.
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::FireFileMethod(IUnknown* punk, WCHAR* wzmethod, BSTR bstrval)
{
	IFileSystemEvents	*pfile =0;

	if (!punk)
		return E_INVALIDARG;

	for (int i=0; i<NUM_METHOD_IFILESYSTEM; i++)
	{
		if (wcsicmp(wzmethod, g_wzMethod[1][i])==0)
			break;
	}

	if (i>= NUM_METHOD_IFILESYSTEM)
		return E_FAIL;

	HRESULT hr = punk->QueryInterface(__uuidof(IFileSystemEvents), (void**)&pfile);
	exit(hr);

	switch(i)
	{
	case 0:	// FileCreated
		// Event firing happens here
		hr = pfile->FileCreated(bstrval);
		break;

	case 1: // FileDeleted
		// Event firing happens here
		hr = pfile->FileDeleted(bstrval);
		break;

	case 2: // FileRenamed
		// Event firing happens here
		hr = pfile->FileRenamed(bstrval);
		break;

	case 3: // FileUpdated
		// Event firing happens here
		hr = pfile->FileUpdated(bstrval);
		break;
	}

exit:
	RELEASE(pfile);
	return hr;
}

//////////////////////////////////////////////////////////////////////////////////////
// Name			: CPubdlg::FireSystemMethod
// Purppose		: Fires the method related to ISystemEvents interface
// Parameters	:
//				: IUnknown* punk		- IUnknown of the EventClass
//				: WCHAR* wzmethod		- Method in the ISystemEvents interface
//				: BSTR bstrval			- BSTR value to be passed as the method arg.
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////////////
LRESULT CPubdlg::FireSystemMethod(IUnknown* punk, WCHAR* wzmethod, BSTR bstrval)
{
	ISystemEvents	*psystem =0;

	if (!punk)
		return E_INVALIDARG;

	for (int i=0; i<NUM_METHOD_ISYSTEM; i++)
	{
		if (wcsicmp(wzmethod, g_wzMethod[2][i])==0)
			break;
	}

	if (i>= NUM_METHOD_ISYSTEM)
		return E_FAIL;

	HRESULT hr = punk->QueryInterface(__uuidof(ISystemEvents), (void**)&psystem);
	exit(hr);

	switch(i)
	{
	case 0:	// ProcessCreated
		// Event firing happens here
		hr = psystem->ProcessCreated(bstrval);
		break;

	case 1: // ProcessTerminated
		// Event firing happens here
		hr = psystem->ProcessTerminated(bstrval);
		break;

	case 2: // PNPDeviceAdded
		// Event firing happens here
		hr = psystem->PNPDeviceAdded(bstrval);
		break;
	}

exit:
	RELEASE(psystem);
	return hr;
}

//////////////////////////////////////////////////////////////////////////////
// Name			: GetECDllPathName
// Purppose		: Gets the EventClass dll name with full path
// Parameters	:
//				: THCAR tzfilename[MAX_PATH] - A TCHAR array of size MAX_PATH
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////	
HRESULT GetECDllPathName(TCHAR tzfilename[MAX_PATH])
{
	TCHAR				*tzFirst=0, *tzLast =0;
	TCHAR				tzRoot[MAX_PATH];
	int					i=0;

	// Get the path name of the eventclass
	if (!GetCurrentDirectory(MAX_PATH, tzfilename))
		return HRESULT_FROM_WIN32(GetLastError());

#if(IDE)	// IDE - Only on IDE
	tzFirst = tzfilename;

	tzLast = StrRStrI(tzFirst,NULL,_T("\\"));
	
	while (tzLast && (tzLast != tzFirst))
	{
		tzRoot[i] = *tzFirst;
		tzFirst++;
		i++;
	}
	tzRoot[i++] = _T('\\');
	tzRoot[i] = _T('\0');

	if (!lstrcpy(tzfilename,tzRoot))
		return E_FAIL;

	if (!lstrcat(tzfilename,_T("Output\\EventMonEventClass.dll")))
		return E_FAIL;
#else
	if (!lstrcat(tzfilename, _T("\\EventMonEventClass.dll")))
		return E_FAIL;
#endif
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// Name			: GetSubDllPathName
// Purppose		: Gets the Subscriber dll name with full path
// Parameters	:
//				: THCAR tzfilename[MAX_PATH] - A TCHAR array of size MAX_PATH
// Return Value : HRESULT
///////////////////////////////////////////////////////////////////////////////	
HRESULT GetSubDllPathName(TCHAR tzfilename[MAX_PATH])
{
	TCHAR				*tzFirst=0, *tzLast =0;
	TCHAR				tzRoot[MAX_PATH];
	int					i=0;

	// Get the path name of the eventclass
	if (!GetCurrentDirectory(MAX_PATH, tzfilename))
		return HRESULT_FROM_WIN32(GetLastError());

#if(IDE)	// IDE - Only on IDE
	tzFirst = tzfilename;

	tzLast = StrRStrI(tzFirst,NULL,_T("\\"));
	
	while (tzLast && (tzLast != tzFirst))
	{
		tzRoot[i] = *tzFirst;
		tzFirst++;
		i++;
	}
	tzRoot[i++] = _T('\\');
	tzRoot[i] = _T('\0');

	if (!lstrcpy(tzfilename,tzRoot))
		return E_FAIL;

	if (!lstrcat(tzfilename,_T("Output\\EventMonSubscriber.dll")))
		return E_FAIL;
#else
	if (!lstrcat(tzfilename, _T("\\EventMonSubscriber.dll")))
		return E_FAIL;
#endif
	return S_OK;
}

