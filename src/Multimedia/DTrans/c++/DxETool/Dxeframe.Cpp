// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DxeTest.h"
#include "DxeFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_MESHA_IN, OnFileLoadMeshA)
	ON_COMMAND(ID_FILE_MESHB_IN, OnFileLoadMeshB)
	ON_COMMAND(ID_FILE_SURFACEA, OnFileLoadSurfaceA)
	ON_COMMAND(ID_FILE_SURFACEB, OnFileLoadSurfaceB)
	ON_COMMAND(ID_FILE_SUBMESHA_IN, OnFileSubmeshAIn)
	ON_COMMAND(ID_FILE_SUBMESHB_IN, OnFileSubmeshBIn)
	ON_COMMAND(ID_VIEW_INPUT_MESHA, OnViewInputMeshA)
	ON_COMMAND(ID_VIEW_INPUT_MESHB, OnViewInputMeshB)
	ON_COMMAND(ID_VIEW_OUTPUT_MESH, OnViewOutputMesh)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INPUT_MESHA, OnUpdateViewInputMeshA)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INPUT_MESHB, OnUpdateViewInputMeshB)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT_MESH, OnUpdateViewOutputMesh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

        //--- Create the dialog bar
        if( !m_DlgBar.Create( this, IDD_DLGBAR, CBRS_LEFT, 0 ) )
        {
    	    TRACE("Failed to create dialog bar.  Line %d. File: %s\n",
			__LINE__, __FILE__);
	    return -1;      // fail to create
        }
        else
        {
            ((CTestApp *)AfxGetApp())->m_pDlgBar = &m_DlgBar;
            m_DlgBar.m_pFrameWnd = this;
            m_DlgBar.UpdateData( false );
        }

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create status bar.  Line %d. File: %s\n",
			__LINE__, __FILE__);
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
        cs.cx = 800;
        cs.cy = 600;
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


#define ON_FILE_SURFACE_A 0
#define ON_FILE_SURFACE_B 1
#define ON_FILE_MESH_A 0
#define ON_FILE_MESH_B 1

static char BASED_CODE szImageDir[MAX_PATH] = ".";
static char BASED_CODE szImageFilter[] =
"Image Files (*.gif;*.png;*.jpg;*.bmp)\0*.gif; *.png; *.jpg; *.bmp\0\
All Files (*.*)\0*.*\0\0";

static char BASED_CODE szMeshDir[MAX_PATH] = ".";
static char BASED_CODE szMeshFilter[] =
"Geometry Files (*.x)\0*.x\0\
All Files (*.*)\0*.*\0\0";

void CMainFrame::OnFileLoadSurfaceA() 
{
    OnSurfaceChange(ON_FILE_SURFACE_A);
}

void CMainFrame::OnFileLoadSurfaceB() 
{
    OnSurfaceChange(ON_FILE_SURFACE_B);
}

void CMainFrame::OnFileLoadMeshA() 
{
    OnMeshChange(ON_FILE_MESH_A);
}

void CMainFrame::OnFileLoadMeshB() 
{
    OnMeshChange(ON_FILE_MESH_B);
}

void 
CMainFrame::OnSurfaceChange(DWORD nWhichSurface)
{ 
	HRESULT hr;
    HKEY    hkResult;
    LONG    lRetVal;
    DWORD   size = MAX_PATH;
    
    // Use the last image directory used by this app (stored in registry)
    lRetVal = RegCreateKeyEx( HKEY_CLASSES_ROOT, _T("PathToImagesDirectory"), 0, NULL, 0,
                        KEY_ALL_ACCESS, NULL, &hkResult, NULL );

    if( lRetVal == ERROR_SUCCESS )
    {
        RegQueryValueEx( hkResult, _T("Images"), NULL, NULL, (PBYTE)szImageDir, &size );
    
        RegCloseKey( hkResult );
    }

	CFileDialog cfdFileDialog(TRUE /* Open */);
	cfdFileDialog.m_ofn.lpstrInitialDir = szImageDir;
	cfdFileDialog.m_ofn.lpstrFilter = szImageFilter;
	
	if (cfdFileDialog.DoModal() != IDOK)
		return;

	CTestApp *pApp = (CTestApp*) AfxGetApp();
	CTestView *pView = pApp->m_pView;
	if (pView == NULL)
		return;
	
	CString csPathFileName = cfdFileDialog.GetPathName();
    
    // Copy the filename and directory contained in csPathFileName to our registry key    
    strcpy (szImageDir, (LPCTSTR)csPathFileName);
       
    lRetVal = RegCreateKeyEx( HKEY_CLASSES_ROOT, _T("PathToImagesDirectory"), 0, NULL, 0,
                        KEY_ALL_ACCESS, NULL, &hkResult, NULL );

    if( lRetVal == ERROR_SUCCESS )
    {
        lRetVal = RegSetValueEx( hkResult, _T("Images"), NULL, REG_EXPAND_SZ, (PBYTE)szImageDir, sizeof(szImageDir) );
        RegCloseKey( hkResult );
    }

    // Copy the filename and directory to an OLECHAR to hand to LoadImage
	OLECHAR osPath[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, csPathFileName, -1, osPath, MAX_PATH);

	if (FAILED(hr = pView->LoadImage(nWhichSurface, osPath))) {
		CString csDispString;
	    CHAR szErrorNumberAndLine[256];
	    sprintf(szErrorNumberAndLine, "0x%08x  Line: %d  File: %s", hr, __LINE__, __FILE__);
		AfxFormatString1(csDispString, IDS_LOAD_SURFACE_ERROR, szErrorNumberAndLine);
		AfxMessageBox(csDispString, MB_OK | MB_ICONEXCLAMATION);
	}
}


void 
CMainFrame::OnMeshChange(DWORD nWhichMesh) 
{
	HRESULT hr;
    HKEY    hkResult;
    LONG    lRetVal;
    DWORD   size = MAX_PATH;

    // Use the last geometry directory used by this app (stored in registry)
    lRetVal = RegCreateKeyEx( HKEY_CLASSES_ROOT, _T("PathToGeometryDirectory"), 0, NULL, 0,
                        KEY_ALL_ACCESS, NULL, &hkResult, NULL );

    if( lRetVal == ERROR_SUCCESS )
    {
        RegQueryValueEx( hkResult, _T("Images"), NULL, NULL, (PBYTE)szMeshDir, &size );
    
        RegCloseKey( hkResult );
    }

    CFileDialog cfdFileDialog(TRUE /* Open */);
    cfdFileDialog.m_ofn.lpstrInitialDir = szMeshDir;
    cfdFileDialog.m_ofn.lpstrFilter = szMeshFilter;

	if (cfdFileDialog.DoModal() != IDOK)
		return;

	CTestView *pView = ((CTestApp*)AfxGetApp())->m_pView;
	if (pView == NULL)
		return;

	CString csPathFileName = cfdFileDialog.GetPathName();

    // Copy the filename and directory contained in csPathFileName to our registry key    
    strcpy (szMeshDir, (LPCTSTR)csPathFileName);
       
    lRetVal = RegCreateKeyEx( HKEY_CLASSES_ROOT, _T("PathToGeometryDirectory"), 0, NULL, 0,
                        KEY_ALL_ACCESS, NULL, &hkResult, NULL );

    if( lRetVal == ERROR_SUCCESS )
    {
        lRetVal = RegSetValueEx( hkResult, _T("Images"), NULL, REG_EXPAND_SZ, (PBYTE)szMeshDir, sizeof(szMeshDir) );
        RegCloseKey( hkResult );
    }

	if (FAILED(hr = pView->LoadMesh(nWhichMesh, (LPCTSTR) csPathFileName))) {
	    CString csDispString;
	    CHAR szErrorNumberAndLine[256];
	    sprintf(szErrorNumberAndLine, "0x%08x  Line: %d  File: %s", hr, __LINE__, __FILE__);
	    AfxFormatString1(csDispString, IDS_LOAD_MESH_ERROR, szErrorNumberAndLine);
	    AfxMessageBox(csDispString, MB_OK | MB_ICONEXCLAMATION);
	}
}


void CMainFrame::OnFileSubmeshAIn() 
{
    OnUseSubmeshes(0);
}

void CMainFrame::OnFileSubmeshBIn() 
{
    OnUseSubmeshes(1);
}

void CMainFrame::OnUseSubmeshes(DWORD dwWhichInput)
{
    CTestView *pView = ((CTestApp*)AfxGetApp())->m_pView;

    ASSERT(pView);

    pView->SubMeshInput(dwWhichInput);
}

void CMainFrame::OnViewInputMeshA() 
{
    CTestView *pView = ((CTestApp*)AfxGetApp())->m_pView;

    ASSERT(pView);

    pView->WhichMeshView(WHICHMESH_A);
}
void CMainFrame::OnUpdateViewInputMeshA(CCmdUI* pCmdUI) 
{
    CTestView *pView = ((CTestApp*)AfxGetApp())->m_pView;

    ASSERT(pView);

    pCmdUI->SetCheck(pView->WhichMeshView() == WHICHMESH_A);
    pCmdUI->Enable(pView->m_bOutputGeo);
}

void CMainFrame::OnViewInputMeshB() 
{
    CTestView *pView = ((CTestApp*)AfxGetApp())->m_pView;

    ASSERT(pView);

    pView->WhichMeshView(WHICHMESH_B);
}

void CMainFrame::OnUpdateViewInputMeshB(CCmdUI* pCmdUI) 
{
    CTestView *pView = ((CTestApp*)AfxGetApp())->m_pView;

    ASSERT(pView);

    pCmdUI->SetCheck(pView->WhichMeshView() == WHICHMESH_B);
    pCmdUI->Enable(pView->m_bOutputGeo);
}

void CMainFrame::OnViewOutputMesh() 
{
    CTestView *pView = ((CTestApp*)AfxGetApp())->m_pView;

    ASSERT(pView);

    pView->WhichMeshView(WHICHMESH_OUTPUT);
}


void CMainFrame::OnUpdateViewOutputMesh(CCmdUI* pCmdUI) 
{
    CTestView *pView = ((CTestApp*)AfxGetApp())->m_pView;

    ASSERT(pView);

    pCmdUI->SetCheck(pView->WhichMeshView() == WHICHMESH_OUTPUT);
    pCmdUI->Enable(pView->m_bOutputGeo);
}
