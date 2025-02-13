#include "stdafx.h"
#include "BenSvr.h"
#include "Benefits.h"
#include "RootNode.h"

CBenefits::CBenefits()
{
	m_pNode = new CRootNode;
	_ASSERTE(m_pNode != NULL);
}

//
// Standard destructor. Simply deletes
// the root node.
//
CBenefits::~CBenefits()
{
	delete m_pNode;
	m_pNode = NULL;
}

HRESULT CBenefits::Initialize(LPUNKNOWN pUnknown)
{
	HRESULT hr = IComponentDataImpl<CBenefits, CBenefitsComponent >::Initialize(pUnknown);
	if (FAILED(hr))
		return hr;

	CComPtr<IImageList> spImageList;

	if (m_spConsole->QueryScopeImageList(&spImageList) != S_OK)
	{
		ATLTRACE(_T("IConsole::QueryScopeImageList failed\n"));
		return E_UNEXPECTED;
	}

	// Load bitmaps associated with the scope pane
	// and add them to the image list
	// Loads the default bitmaps generated by the wizard
	// Change as required
	HBITMAP hBitmap16 = LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_BENEFITS_16));
	if (hBitmap16 == NULL)
		return S_OK;

	HBITMAP hBitmap32 = LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_BENEFITS_32));
	if (hBitmap32 == NULL)
		return S_OK;

	if (spImageList->ImageListSetStrip((long*)hBitmap16, 
		(long*)hBitmap32, 0, RGB(0, 128, 128)) != S_OK)
	{
		ATLTRACE(_T("IImageList::ImageListSetStrip failed\n"));
		return E_UNEXPECTED;
	}

	//
	// This is called to create the unique sub-nodes.
	//
	( (CRootNode*) m_pNode )->InitializeSubNodes();

	return S_OK;
}

//
// This is overridden to handle update notifications from
// the property pages.
//
HRESULT CBenefits::Notify(LPDATAOBJECT lpDataObject, MMC_NOTIFY_TYPE event, long arg, long param)
{
	HRESULT hr = E_NOTIMPL;

	if ( lpDataObject != NULL )
	{
		return IComponentDataImpl<CBenefits,CBenefitsComponent>::Notify( lpDataObject, event, arg, param );
	}
	else
	{
		//
		// There are many events which are sent to Notify with
		// the dataobject == NULL. Make sure that the correct one is
		// being dealt with.
		//
		switch( event )
		{
		case MMCN_PROPERTY_CHANGE:
			//
			// Send the notification to our root node for further processing.
			//
			( (CRootNode*) m_pNode )->OnPropertyChange( m_spConsole );

			//
			// Since we've received an update notification, we'll cause the console
			// to be refreshed. This should handle the updates.
			//
			hr = m_spConsole->UpdateAllViews( NULL, NULL, NULL );
			break;
		}
	}

	return( hr );
}

//
// Call the root node's implementation.
//
STDMETHODIMP CBenefits::IsDirty()
{
	return( ( (CRootNode*) m_pNode )->IsDirty() );
}

//
// Call the root node's implementation.
//
STDMETHODIMP CBenefits::Load(LPSTREAM pStm)
{
	return( ( (CRootNode*) m_pNode )->Load( pStm ) );
}

//
// Call the root node's implementation.
//
STDMETHODIMP CBenefits::Save(LPSTREAM pStm, BOOL fClearDirty)
{
	return( ( (CRootNode*) m_pNode )->Save( pStm, fClearDirty ) );
}

//
// Call the root node's implementation.
//
STDMETHODIMP CBenefits::GetSizeMax(ULARGE_INTEGER FAR* pcbSize )
{
	return( ( (CRootNode*) m_pNode )->GetSizeMax( pcbSize ) );
}

//
// This function copies the data from the given employee and populates
// the appropriate controls within the page.
//
LRESULT CEmployeeNamePage::OnInitDialog( UINT uiMsg, WPARAM wParam, LPARAM lParam, BOOL& fHandled )
{
	UNUSED_ALWAYS( uiMsg );
	UNUSED_ALWAYS( wParam );
	UNUSED_ALWAYS( lParam );
	UNUSED_ALWAYS( fHandled );
	USES_CONVERSION;
	_ASSERTE( m_pEmployee != NULL );

	SetDlgItemText( IDC_EDIT_LASTNAME, W2T( m_pEmployee->m_szLastName ) );
	SetDlgItemText( IDC_EDIT_FIRSTNAME, W2T( m_pEmployee->m_szFirstName ) );
	SetDlgItemText( IDC_EDIT_SOCIALSECURITY, W2T( m_pEmployee->m_szSocialSecurity ) );
	SetDlgItemText( IDC_EDIT_MOTHERNAME, W2T( m_pEmployee->m_szMotherMaiden ) );

	return( TRUE );
}

//
// Handle the storage of any new values to the employee.
//
BOOL CEmployeeNamePage::OnWizardFinish()
{
	USES_CONVERSION;
	BOOL fValid = TRUE;
	TCHAR szBuf[ 256 ];

	//
	// Get the values from the appropriate edit controls.
	// For demo purposes, always assume success unless the last name
	// and first are bad.
	//
	GetDlgItemText( IDC_EDIT_LASTNAME, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szLastName, T2W( szBuf ) );
	GetDlgItemText( IDC_EDIT_FIRSTNAME, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szFirstName, T2W( szBuf ) );
	GetDlgItemText( IDC_EDIT_SOCIALSECURITY, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szSocialSecurity, T2W( szBuf ) );
	GetDlgItemText( IDC_EDIT_MOTHERNAME, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szMotherMaiden, T2W( szBuf ) );

	//
	// Check for validity of first name and last name.
	//
	if ( wcslen( m_pEmployee->m_szLastName ) == 0 || wcslen( m_pEmployee->m_szFirstName ) == 0 ||
		m_pEmployee->m_szLastName[ 0 ] == ' ' || m_pEmployee->m_szFirstName[ 0 ] == ' ' )
	{
		//
		// Inform the user of the error.
		//
		MessageBox( _T( "Must enter valid first and last name." ) );

		fValid = FALSE;
	}
	else
	{
		//
		// Data is valid. As a result, post a notification to the snap-in
		// that the employee contents have changes. This demonstration does
		// not use any sort of hinting, so NULL can be safely pass in as
		// the nofication's arguement.
		//
		PropertyChangeNotify( NULL );
	}

	return( fValid );
}

//
// This is overridden to modify the UI depending on whether
// we're in start-up mode or not.
//
BOOL CEmployeeNamePage::OnSetActive()
{
	if ( m_fStartup )
	{
		//
		// Must use post message during the setactive message.
		//
		CWindow( GetParent() ).PostMessage( PSM_SETWIZBUTTONS, 0, PSWIZB_NEXT );
	}

	return TRUE;
}

//
// This function copies the data from the given employee and populates
// the appropriate controls within the page.
//
LRESULT CEmployeeAddressPage::OnInitDialog( UINT uiMsg, WPARAM wParam, LPARAM lParam, BOOL& fHandled )
{
	UNUSED_ALWAYS( uiMsg );
	UNUSED_ALWAYS( wParam );
	UNUSED_ALWAYS( lParam );
	UNUSED_ALWAYS( fHandled );
	USES_CONVERSION;
	_ASSERTE( m_pEmployee != NULL );

	SetDlgItemText( IDC_EDIT_ADDRESSFIRST, W2T( m_pEmployee->m_szAddress1 ) );
	SetDlgItemText( IDC_EDIT_ADDRESSSECOND, W2T( m_pEmployee->m_szAddress2 ) );
	SetDlgItemText( IDC_EDIT_CITY, W2T( m_pEmployee->m_szCity ) );
	SetDlgItemText( IDC_EDIT_STATE, W2T( m_pEmployee->m_szState ) );
	SetDlgItemText( IDC_EDIT_ZIP, W2T( m_pEmployee->m_szZip ) );
	SetDlgItemText( IDC_EDIT_PHONE, W2T( m_pEmployee->m_szPhone ) );

	return( TRUE );
}

//
// Handle the storage of any new values to the employee.
//
BOOL CEmployeeAddressPage::OnWizardFinish()
{
	USES_CONVERSION;
	BOOL fValid = TRUE;
	TCHAR szBuf[ 256 ];

	//
	// Get the values from the appropriate edit controls.
	// For demo purposes, always assume success unless the last name
	// and first are bad.
	//
	GetDlgItemText( IDC_EDIT_ADDRESSFIRST, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szAddress1, T2W( szBuf ) );
	GetDlgItemText( IDC_EDIT_ADDRESSSECOND, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szAddress2, T2W( szBuf ) );
	GetDlgItemText( IDC_EDIT_CITY, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szCity, T2W( szBuf ) );
	GetDlgItemText( IDC_EDIT_STATE, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szState, T2W( szBuf ) );
	GetDlgItemText( IDC_EDIT_ZIP, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szZip, T2W( szBuf ) );
	GetDlgItemText( IDC_EDIT_PHONE, szBuf, sizeof( szBuf ) );
	wcscpy( m_pEmployee->m_szPhone, T2W( szBuf ) );

	//
	// Data is valid. As a result, post a notification to the snap-in
	// that the employee contents have changes. This demonstration does
	// not use any sort of hinting, so NULL can be safely pass in as
	// the nofication's arguement.
	//
	PropertyChangeNotify( NULL );

	return( fValid );
}

//
// This is overridden to modify the UI depending on whether
// we're in start-up mode or not.
//
BOOL CEmployeeAddressPage::OnSetActive()
{
	if ( m_fStartup )
	{
		//
		// Must use post message during the setactive message.
		//
		CWindow( GetParent() ).PostMessage( PSM_SETWIZBUTTONS, 0, PSWIZB_BACK | PSWIZB_FINISH );
	}

	return TRUE;
}
