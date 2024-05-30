// IvrExplorerView.cpp : implementation of the CIvrExplorerView class
//

#include "stdafx.h"
#include "IvrExplorerDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerView

IMPLEMENT_DYNCREATE(CIvrExplorerView, CView)

BEGIN_MESSAGE_MAP(CIvrExplorerView, CView)
	//{{AFX_MSG_MAP(CIvrExplorerView)
	ON_WM_CREATE()
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
    ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_WM_DESTROY()
    ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerView construction/destruction

CIvrExplorerView::CIvrExplorerView()
{
	// TODO: add construction code here
    m_uNumTextLines = 0;
    m_uCurrentWidth = 100;
    m_pEventCP = NULL;
    m_pApp = NULL;
}

CIvrExplorerView::~CIvrExplorerView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerView drawing

void CIvrExplorerView::OnDraw(CDC* pDC)
{
//	CIvrExplorerDoc* pDoc = GetDocument();
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerView diagnostics

#ifdef _DEBUG
void CIvrExplorerView::AssertValid() const
{
	CView::AssertValid();
}

void CIvrExplorerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIvrExplorerView message handlers

int CIvrExplorerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    CListCtrl&  listCtrl = GetListCtrl();

    //
    // Change the style to REPORT without headers.
    //
    lpCreateStruct->style |= LVS_REPORT | LVS_NOCOLUMNHEADER | LBS_EXTENDEDSEL;
    if (CListView::OnCreate(lpCreateStruct) == -1)
        return -1;

    //
    // Add some colors to the background.
    //
    listCtrl.SetBkColor(0x00808000); // 0x00bbggrr
    listCtrl.SetTextBkColor(0x00808000);

    //
    // Create one column.
    //
    listCtrl.InsertColumn(
        0,              // index
        L"details",      // heading
        LVCFMT_LEFT,    // alignment
        m_uCurrentWidth,// width in pixels (can be changed in AddLine)
        -1);            // subitem
    return 0;
}

HRESULT
CIvrExplorerView::Connect(LPTSTR szAppName)
{
    HRESULT hr;
    IConnectionPointContainer *pCPC;
    BSTR    bstrApp;
    CIvrExplorerApp *pIvrExplorerApp = (CIvrExplorerApp*)AfxGetApp();

    //
    // Set the title.
    //
    GetDocument()->SetTitle(szAppName);

    bstrApp = SysAllocString(szAppName);
    if (!bstrApp)
    {
        return E_OUTOFMEMORY;
    }

    //
    // Create the application.
    //
    hr = pIvrExplorerApp->GetWebIvr()->GetActiveConnection(bstrApp, &m_pApp);
    if (hr != 0)
    {
        return hr;
    }

    //
    // Connect to the connection point.
    //
    hr = m_pApp->QueryInterface(IID_IConnectionPointContainer,
                              (void **)&pCPC);
    if (hr != 0)
    {
        return hr;
    }

    hr = pCPC->FindConnectionPoint(DIID_IWebIvrConnectionEvents, &m_pEventCP);
    pCPC->Release();
    if (hr != 0)
    {
        return hr;
    }

    m_DEvents.SetContainer(this);

    hr = m_pEventCP->Advise(&m_DEvents, &m_dwCookie);
    if (hr != 0)
    {
        return hr;
    }

    CString cs;
    cs = "Connected to application ";
    cs += szAppName;
    AddLine(&cs);
    cs ="";
    AddLine(&cs);
	
	return 0;

}

void CIvrExplorerView::AddLine(CString *pCString)
{
    CListCtrl&  listCtrl = GetListCtrl();
    ULONG       uWidth;
    CIvrExplorerApp *pApp = (CIvrExplorerApp*)AfxGetApp();

    //
    // Adjust the column width.
    //
    uWidth = listCtrl.GetStringWidth(*pCString) + 15;    // 15 -> icon ?
    if (uWidth > m_uCurrentWidth)
    {
        m_uCurrentWidth = uWidth;
        listCtrl.SetColumnWidth(0, m_uCurrentWidth);
    }

    //
    // Don't overflow.
    //
    while (m_uNumTextLines >= (pApp->GetNumberOfRows()))
    {
        listCtrl.DeleteItem(0);
        m_uNumTextLines--;
    }
    //
    // Add the text.
    //
    listCtrl.InsertItem(m_uNumTextLines, *pCString);
    listCtrl.EnsureVisible(m_uNumTextLines++, FALSE);
    
}

void CIvrExplorerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    CIvrExplorerApp *pApp = (CIvrExplorerApp*)AfxGetApp();
    CListCtrl&  listCtrl = GetListCtrl();

    while (m_uNumTextLines >= (pApp->GetNumberOfRows()))
    {
        listCtrl.DeleteItem(0);
        m_uNumTextLines--;
    }
}

//
// Enable/disable the Copy item when the Edit menu is selected
//
void CIvrExplorerView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
    CListCtrl&  listCtrl = GetListCtrl();
    if (listCtrl.GetSelectedCount() == 0)
        pCmdUI->Enable(FALSE);
    else
        pCmdUI->Enable(TRUE);
}

//
// Copy selected lines to clipboard
//
void CIvrExplorerView::OnEditCopy() 
{
    CListCtrl&  listCtrl = GetListCtrl();
    int         i;
    CString     csLogLine;
    CString     csAllSelected;
    BOOL        r;
    CIvrExplorerApp    *pApp = (CIvrExplorerApp*)AfxGetApp();
    CString     csLoadString;
    HGLOBAL     hglbCopy;
    LPTSTR      lptstrCopy;
    UINT        uLength;

    r = OpenClipboard();
    if (r == FALSE)
    {
        return;
    }
    r = EmptyClipboard();
    if (r == FALSE)
    {
        CloseClipboard();
        return;
    }
    for(i = -1; (i = listCtrl.GetNextItem(i, LVNI_SELECTED)) != -1;)
    {
        csLogLine = listCtrl.GetItemText(i, 0);
        csAllSelected += csLogLine;
        csAllSelected += _T("\r\n");
    }
    uLength = csAllSelected.GetLength();
    hglbCopy =  GlobalAlloc(GMEM_DDESHARE, 
            ((uLength + 1) * sizeof(TCHAR)));
    if (hglbCopy == NULL) 
    {
        CloseClipboard();
        return; 
    } 
    lptstrCopy = (LPTSTR)GlobalLock(hglbCopy); 
    memcpy(lptstrCopy, (LPCTSTR)csAllSelected, 
            (uLength * sizeof(TCHAR))); 
    lptstrCopy[uLength] = (TCHAR) 0;    // null character 
    GlobalUnlock(hglbCopy); 
 
    // Place the handle on the clipboard. 
    SetClipboardData(CF_UNICODETEXT, hglbCopy); 
    CloseClipboard();
}

void CIvrExplorerView::OnDestroy() 
{
	//
    // Release the connection point.
    //
    if (m_pEventCP)
    {
        m_pEventCP->Unadvise(m_dwCookie);
        m_pEventCP->Release();
    }

    if (m_pApp)
    {
        m_pApp->Release();
    }

    CView::OnDestroy();	
}

