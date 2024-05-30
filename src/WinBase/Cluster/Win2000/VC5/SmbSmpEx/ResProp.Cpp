/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 99 <company name>
//
//	Module Name:
//		ResProp.cpp
//
//	Description:
//		Implementation of the resource extension property page classes.
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 99
//
//	Revision History:
//
//	Notes:
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SmbSmpEx.h"
#include "ResProp.h"
#include "ExtObj.h"
#include "DDxDDv.h"
#include "BasePage.inl"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmbSmpParamsPage property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE( CSmbSmpParamsPage, CBasePropertyPage )

/////////////////////////////////////////////////////////////////////////////
// Message Maps

BEGIN_MESSAGE_MAP( CSmbSmpParamsPage, CBasePropertyPage )
	//{{AFX_MSG_MAP(CSmbSmpParamsPage)
	ON_EN_CHANGE( IDC_PP_SMBSMP_SHARENAME, OnChangeRequiredField )
	ON_EN_CHANGE( IDC_PP_SMBSMP_PATH, OnChangeRequiredField )
	//}}AFX_MSG_MAP
	// TODO: Modify the following lines to represent the data displayed on this page.
	ON_EN_CHANGE( IDC_PP_SMBSMP_SHARENAME, CBasePropertyPage::OnChangeCtrl )
	ON_EN_CHANGE( IDC_PP_SMBSMP_PATH, CBasePropertyPage::OnChangeCtrl )
	ON_EN_CHANGE( IDC_PP_SMBSMP_REMARK, CBasePropertyPage::OnChangeCtrl )
	ON_EN_CHANGE( IDC_PP_SMBSMP_MAXUSERS, CBasePropertyPage::OnChangeCtrl )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::CSmbSmpParamsPage
//
//	Description:
//		Default constructor.
//
//	Arguments:
//		None.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
CSmbSmpParamsPage::CSmbSmpParamsPage( void )
	: CBasePropertyPage( CSmbSmpParamsPage::IDD )
{
	// TODO: Modify the following lines to represent the data displayed on this page.
	//{{AFX_DATA_INIT(CSmbSmpParamsPage)
	m_strShareName = _T("");
	m_strPath = _T("");
	m_strRemark = _T("");
	m_nMaxUsers = static_cast< DWORD >( 0 );
	//}}AFX_DATA_INIT

	// Setup the property array.
	{
		m_rgProps[ epropShareName ].Set( REGPARAM_SMBSMP_SHARENAME, m_strShareName, m_strPrevShareName );
		m_rgProps[ epropPath ].Set( REGPARAM_SMBSMP_PATH, m_strPath, m_strPrevPath );
		m_rgProps[ epropRemark ].Set( REGPARAM_SMBSMP_REMARK, m_strRemark, m_strPrevRemark );
		m_rgProps[ epropMaxUsers ].Set( REGPARAM_SMBSMP_MAXUSERS, m_nMaxUsers, m_nPrevMaxUsers );
	} // Setup the property array

	m_iddPropertyPage = IDD_PP_SMBSMP_PARAMETERS;
	m_iddWizardPage = IDD_WIZ_SMBSMP_PARAMETERS;

} //*** CSmbSmpParamsPage::CSmbSmpParamsPage()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::DoDataExchange
//
//	Description:
//		Do data exchange between the dialog and the class.
//
//	Arguments:
//		pDX		[IN OUT] Data exchange object
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
void CSmbSmpParamsPage::DoDataExchange( CDataExchange * pDX )
{
	if ( ! pDX->m_bSaveAndValidate || ! BSaved() )
	{
		AFX_MANAGE_STATE( AfxGetStaticModuleState() );

		// TODO: Modify the following lines to represent the data displayed on this page.
		//{{AFX_DATA_MAP(CSmbSmpParamsPage)
		DDX_Control( pDX, IDC_PP_SMBSMP_SHARENAME, m_editShareName );
		DDX_Control( pDX, IDC_PP_SMBSMP_PATH, m_editPath );
		DDX_Text( pDX, IDC_PP_SMBSMP_SHARENAME, m_strShareName );
		DDX_Text( pDX, IDC_PP_SMBSMP_PATH, m_strPath );
		DDX_Text( pDX, IDC_PP_SMBSMP_REMARK, m_strRemark );
		DDX_Text( pDX, IDC_PP_SMBSMP_MAXUSERS, m_nMaxUsers );
		//}}AFX_DATA_MAP

		// Handle numeric parameters.
		if ( ! BBackPressed() )
		{
			DDX_Number(
				pDX,
				IDC_PP_SMBSMP_MAXUSERS,
				m_nMaxUsers,
				static_cast< DWORD >( 0 ),
				static_cast< DWORD >( 4294967295 ),
				FALSE /*bSigned*/
				);
		} // if: back button not pressed

		// TODO: Add any additional field validation here.
		if ( pDX->m_bSaveAndValidate )
		{
			// Make sure all required fields are present.
			if ( ! BBackPressed() )
			{
				DDV_RequiredText( pDX, IDC_PP_SMBSMP_SHARENAME, IDC_PP_SMBSMP_SHARENAME_LABEL, m_strShareName );
				DDV_RequiredText( pDX, IDC_PP_SMBSMP_PATH, IDC_PP_SMBSMP_PATH_LABEL, m_strPath );
			} // if: back button not pressed
		} // if: saving data from dialog
	} // if: not saving or haven't saved yet

	CBasePropertyPage::DoDataExchange( pDX );

} //*** CSmbSmpParamsPage::DoDataExchange()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::OnInitDialog
//
//	Description:
//		Handler for the WM_INITDIALOG message.
//
//	Arguments:
//		None.
//
//	Return Value:
//		TRUE		We need the focus to be set for us.
//		FALSE		We already set the focus to the proper control.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CSmbSmpParamsPage::OnInitDialog( void )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	CBasePropertyPage::OnInitDialog();

	// TODO:
	// Limit the size of the text that can be entered in edit controls.

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE

} //*** CSmbSmpParamsPage::OnInitDialog()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::OnSetActive
//
//	Description:
//		Handler for the PSN_SETACTIVE message.
//
//	Arguments:
//		None.
//
//	Return Value:
//		TRUE	Page successfully initialized.
//		FALSE	Page not initialized.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CSmbSmpParamsPage::OnSetActive( void )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	// Enable/disable the Next/Finish button.
	if ( BWizard() )
	{
		EnableNext( BAllRequiredFieldsPresent() );
	} // if: displaying a wizard

	return CBasePropertyPage::OnSetActive();

} //*** CSmbSmpParamsPage::OnSetActive()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::OnChangeRequiredField
//
//	Description:
//		Handler for the EN_CHANGE message on the Share name or Path edit
//		controls.
//
//	Arguments:
//		None.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
void CSmbSmpParamsPage::OnChangeRequiredField( void )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	OnChangeCtrl();

	if ( BWizard() )
	{
		EnableNext( BAllRequiredFieldsPresent() );
	} // if: displaying a wizard

} //*** CSmbSmpParamsPage::OnChangeRequiredField()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CSmbSmpParamsPage::BAllRequiredFieldsPresent
//
//	Description:
//		Handler for the EN_CHANGE message on the Share name or Path edit
//		controls.
//
//	Arguments:
//		None.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CSmbSmpParamsPage::BAllRequiredFieldsPresent( void ) const
{
	BOOL	_bPresent;

	if ( 0
		|| (m_editShareName.GetWindowTextLength() == 0)
		|| (m_editPath.GetWindowTextLength() == 0)
		)
	{
		_bPresent = FALSE;
	} // if: required field not present
	else
	{
		_bPresent = TRUE;
	} // else: all required fields are present

	return _bPresent;

} //*** CSmbSmpParamsPage::BAllRequiredFieldsPresent()
