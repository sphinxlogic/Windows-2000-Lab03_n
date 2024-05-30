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
#include "ClipSrvEx.h"
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
// CClipSrvParamsPage property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE( CClipSrvParamsPage, CBasePropertyPage )

/////////////////////////////////////////////////////////////////////////////
// Message Maps

BEGIN_MESSAGE_MAP( CClipSrvParamsPage, CBasePropertyPage )
	//{{AFX_MSG_MAP(CClipSrvParamsPage)
	//}}AFX_MSG_MAP
	// TODO: Modify the following lines to represent the data displayed on this page.
	ON_EN_CHANGE( IDC_PP_CLIPSRV_COMMENT, CBasePropertyPage::OnChangeCtrl )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CClipSrvParamsPage::CClipSrvParamsPage
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
CClipSrvParamsPage::CClipSrvParamsPage( void )
	: CBasePropertyPage( CClipSrvParamsPage::IDD )
{
	// TODO: Modify the following lines to represent the data displayed on this page.
	//{{AFX_DATA_INIT(CClipSrvParamsPage)
	m_strComment = _T("");
	//}}AFX_DATA_INIT

	// Setup the property array.
	{
		m_rgProps[ epropComment ].Set( REGPARAM_CLIPSRV_COMMENT, m_strComment, m_strPrevComment );
	} // Setup the property array

	m_iddPropertyPage = IDD_PP_CLIPSRV_PARAMETERS;
	m_iddWizardPage = IDD_WIZ_CLIPSRV_PARAMETERS;

} //*** CClipSrvParamsPage::CClipSrvParamsPage()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CClipSrvParamsPage::DoDataExchange
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
void CClipSrvParamsPage::DoDataExchange( CDataExchange * pDX )
{
	if ( ! pDX->m_bSaveAndValidate || ! BSaved() )
	{
		AFX_MANAGE_STATE( AfxGetStaticModuleState() );

		// TODO: Modify the following lines to represent the data displayed on this page.
		//{{AFX_DATA_MAP(CClipSrvParamsPage)
		DDX_Text( pDX, IDC_PP_CLIPSRV_COMMENT, m_strComment );
		//}}AFX_DATA_MAP

		// Handle numeric parameters.
		if ( ! BBackPressed() )
		{
		} // if: back button not pressed

		// TODO: Add any additional field validation here.
		if ( pDX->m_bSaveAndValidate )
		{
			// Make sure all required fields are present.
			if ( ! BBackPressed() )
			{
			} // if: back button not pressed
		} // if: saving data from dialog
	} // if: not saving or haven't saved yet

	CBasePropertyPage::DoDataExchange( pDX );

} //*** CClipSrvParamsPage::DoDataExchange()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CClipSrvParamsPage::OnInitDialog
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
BOOL CClipSrvParamsPage::OnInitDialog( void )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	CBasePropertyPage::OnInitDialog();

	// TODO:
	// Limit the size of the text that can be entered in edit controls.

	return TRUE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE

} //*** CClipSrvParamsPage::OnInitDialog()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CClipSrvParamsPage::OnSetActive
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
BOOL CClipSrvParamsPage::OnSetActive( void )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	// Enable/disable the Next/Finish button.
	if ( BWizard() )
	{
		EnableNext( BAllRequiredFieldsPresent() );
	} // if: displaying a wizard

	return CBasePropertyPage::OnSetActive();

} //*** CClipSrvParamsPage::OnSetActive()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CClipSrvParamsPage::OnChangeRequiredField
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
void CClipSrvParamsPage::OnChangeRequiredField( void )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	OnChangeCtrl();

	if ( BWizard() )
	{
		EnableNext( BAllRequiredFieldsPresent() );
	} // if: displaying a wizard

} //*** CClipSrvParamsPage::OnChangeRequiredField()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CClipSrvParamsPage::BAllRequiredFieldsPresent
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
BOOL CClipSrvParamsPage::BAllRequiredFieldsPresent( void ) const
{
	return TRUE;

} //*** CClipSrvParamsPage::BAllRequiredFieldsPresent()
