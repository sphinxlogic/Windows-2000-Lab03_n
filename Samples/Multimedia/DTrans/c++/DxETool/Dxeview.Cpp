// testView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "DxeTest.h"
#include <initguid.h>   // Just for ddrawex.h
#include <ddrawex.h>
#include "dxeframe.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Useful Macros
#ifndef MACSTART
#define MACSTART do {
#define MACEND } while(0)
#endif
#ifndef ONFAIL
static DWORD g_nErrorLine = 0;
static const TCHAR *g_szErrorFile = NULL;
static const TCHAR *g_szErrorMsg = NULL;
#define ONFAIL(_szMsg) MACSTART g_nErrorLine = __LINE__; g_szErrorFile = __FILE__; g_szErrorMsg = _T(_szMsg); goto e_Exit; MACEND
#endif

static const GUID * g_BitDepth[] = { 
    &DDPF_PMARGB32,
    &DDPF_ARGB32,
    &DDPF_RGB32,
    &DDPF_RGB24,
    &DDPF_ARGB4444,
    &DDPF_ARGB1555,
    &DDPF_RGB565,
    &DDPF_RGB555,
    &DDPF_RGB8 };

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
    //{{AFX_MSG_MAP(CTestView)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
        ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LIGHT_SPOT, OnLightSpot)
	ON_UPDATE_COMMAND_UI(ID_LIGHT_SPOT, OnUpdateLightSpot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CTestView::CTestView()
{ 
        m_bScaleToOut = TRUE;
        m_iClip = m_iPlace = 0;
        m_bEnableClip = m_bEnablePlacement = FALSE;
        m_BitDepthIndex = 0;
	m_WndWidth = m_WndHeight = 0;
	m_fPercentComplete = 0.f;
	m_pointLastMouse.x = m_pointLastMouse.y = 0;
        m_InSurfBitDepth[0] = m_InSurfBitDepth[1] = 0;

	m_dwLastExecGenId = 0;
	m_bInput0Req = m_bInput1Req = false;
	m_bOutputGeo = m_bInput0Geo = m_bInput1Geo = false;

	m_ulNumInputs;

	m_bRotating = m_bZooming = m_bSliding = m_bInitializingTransform = false;

	m_szSetupError = NULL;

	m_bSpotlight = false;
	m_nInputsDefined = m_nInputsRequired = m_nInputsDesired = m_nInputsPossible = m_nCurInputsUsed = 0;
	m_bBoundsChecking = TRUE;
        m_bDontRender = FALSE;
	m_eWhichMesh = WHICHMESH_OUTPUT;
	m_fQuality = 0.5;
}

void
CTestView::DisplayMessage(HRESULT hr, const char *szMsg, CDC *pDC)
{
	TCHAR szErrorMsg[128];
	if (szMsg == NULL) {
		// create an error message on failure
                if (hr == DXTERR_COPYRIGHT_IS_INVALID)
                {
                    szMsg = _T("Copyright is invalid for transform.  This is the unlicensed version of the selected transform.  You must have a licensed version to use a transform in this tool.");
                }
		else if (FAILED(hr)) {
			if (g_szErrorMsg == NULL)
				g_szErrorMsg = "";
			wsprintf(szErrorMsg, _T("%s  hr: 0x%08x  Line: %d  File: %s\n"), g_szErrorMsg, hr, g_nErrorLine, g_szErrorFile);
			szMsg = szErrorMsg;
		}
	}
	// write the error message to the window, if necessary
	if (szMsg) {
		if (pDC) {
			pDC->PatBlt(0, 0, m_WndWidth, m_WndHeight, PATCOPY);
//			pDC->DrawText(szMsg, &rSrc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			RECT rDraw = {20, 100, m_WndWidth - 20, m_WndHeight - 20};
			pDC->DrawText(szMsg, &rDraw, DT_CENTER | DT_WORDBREAK);
		}
		TRACE(szMsg);
		TRACE("\n");
	}
}


HRESULT
CTestView::CreateRenderer()
{
	HRESULT hr;
	CComPtr<IDirect3DRM> cpD3DRMv1;
	DDSURFACEDESC ddsd;

////////////
        {
            CComPtr<IDirectDrawFactory> cpDDrawFact;
            if(FAILED(hr = ::CoCreateInstance( CLSID_DirectDrawFactory, NULL, CLSCTX_INPROC,
                                     IID_IDirectDrawFactory, (void **)&cpDDrawFact )))
	    {
		ONFAIL("CoCreateInstance(CLSID_DirectDrawFactory ... ) failed.");
	    }

	    if(FAILED(hr = cpDDrawFact->CreateDirectDraw( NULL, GetTopLevelParent()->m_hWnd, DDSCL_NORMAL, 0, NULL,
                                                    &m_cpDD )))
	    {
		ONFAIL("CreateDirectDraw() failed.");
	    }
        }


///////


/*


	if (FAILED(hr = DirectDrawCreate(NULL, &m_cpDD, NULL)))
		ONFAIL("DirectDrawCreate() failed.");

	if (FAILED(hr = m_cpDD->SetCooperativeLevel(GetTopLevelParent()->m_hWnd, DDSCL_NORMAL)))
		ONFAIL("SetCooperativeLevel() failed.");
*/

	// create the primary surface
	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	if (FAILED(hr = m_cpDD->CreateSurface(&ddsd, &m_cpPrimarySurface, NULL)))
		ONFAIL("primary surface CreateSurface() failed.");

	if (FAILED(hr = m_cpDD->CreateClipper(0, &m_cpClipper, NULL)))
		ONFAIL("CreateClipper() failed.");

	if (FAILED(hr = m_cpClipper->SetHWnd(0, m_hWnd)))
		ONFAIL("m_cpClipper->SetHWnd() failed.");

	if (FAILED(hr = m_cpPrimarySurface->SetClipper(m_cpClipper)))
		ONFAIL("m_cpPrimarySurface->SetClipper() failed.");

	if (FAILED(hr = Direct3DRMCreate(&cpD3DRMv1)))
		ONFAIL("Direct3DRMCreate() failed.");

	if (FAILED(cpD3DRMv1->QueryInterface(IID_IDirect3DRM3, (LPVOID*)&m_cpD3DRM)))
        {
            MessageBox(
"Unable to use 3D transforms.  You don't have a required version of D3D-RM installed.  Consult the DirectTransform release notes for details.",
"Unable to Initialize Direct3D RM ver. 6",
		MB_OK);
        }
        else
        {
	    if (FAILED(hr = m_cpD3DRM->SetDefaultTextureColors(256)) ||
	    	FAILED(hr = m_cpD3DRM->SetDefaultTextureShades(256)))
	    	ONFAIL("Default texture setup failed.");

	    DWORD dwOptions;

	    m_cpD3DRM->GetOptions(&dwOptions);

	    dwOptions &= ~D3DRMOPTIONS_LEFTHANDED;
	    dwOptions |= D3DRMOPTIONS_RIGHTHANDED;

	    m_cpD3DRM->SetOptions(dwOptions);
        }
e_Exit:
	// clean up
	if (FAILED(hr)) 
	{
	    DisplayMessage(hr, NULL, NULL);
	}
	return hr;
}


HRESULT
CTestView::CreateTransformFactory()
{
	HRESULT hr;
	ASSERT(m_cpDD);

	if (FAILED(hr = ::CoCreateInstance(CLSID_DXTransformFactory, NULL, CLSCTX_INPROC,
						IID_IDXTransformFactory, (void **) &m_cpTransFact)))
		ONFAIL("CoCreateInstance() of DXTransformFactory failed.");

	if (FAILED(hr = m_cpTransFact->SetService(SID_SDirectDraw, m_cpDD, FALSE)) ||
		FAILED(hr = m_cpTransFact->SetService(SID_SDirect3DRM, m_cpD3DRM, FALSE)))
		ONFAIL("pTransFact->SetService() failed.");
	
	//--- Get the surface factory interface
	if (FAILED(hr = m_cpTransFact->QueryInterface(IID_IDXSurfaceFactory, (void **) &m_cpSurfFact)))
		ONFAIL("TransFact QueryInterface() for SurfaceFactory failed.");

        m_cpTransFact->CreateTransform(NULL, 0, NULL, 0, NULL, NULL,
                                       CLSID_DXGradient, IID_IDXTransform,
                                       (void **)&m_cpGradient);

e_Exit:
	// clean up
	if (FAILED(hr)) 
	{
	    DisplayMessage(hr, NULL, NULL);
	}
	return hr;
}


HRESULT
CTestView::CreateDefaultContent()
{
#if !EMPTY_START
	// try to load the default textures
    if(FAILED(LoadImage(0, L"\\dtrans\\sdk\\samples\\media\\image\\eagle.png")))
    {
	if(FAILED(LoadImage(0, L"\\dxt-sdk\\media\\image\\eagle.png")))
        {
            if(FAILED(LoadImage(0, L"..\\Samples\\Multimedia\\Media\\image\\eagle.png")))
            {
                LoadImage(0, L"..\\..\\Media\\image\\eagle.png");
            }
        }
    }

    if(FAILED(LoadImage(1, L"\\dtrans\\sdk\\samples\\media\\image\\warp_dog.png")))
    {
	if(FAILED(LoadImage(1, L"\\dxt-sdk\\media\\image\\warp_dog.png")))
        {
            if(FAILED(LoadImage(1, L"..\\Samples\\Multimedia\\Media\\image\\warp_dog.png")))
            {
                LoadImage(1, L"..\\..\\Media\\image\\warp_dog.png");
            }
        }
    }

    if (m_cpD3DRM)
    {
	// try to load the default meshes
	if (SUCCEEDED(m_cpD3DRM->CreateMeshBuilder(&m_cpInMeshA))) {
		if (FAILED(m_cpInMeshA->Load("\\dtrans\\sdk\\samples\\media\\geometry\\cow.x", 
			    NULL, D3DRMLOAD_FROMFILE, NULL, NULL)) &&  
		    FAILED(m_cpInMeshA->Load("\\dxt-sdk\\media\\geometry\\cow.x", 
			    NULL, D3DRMLOAD_FROMFILE, NULL, NULL)) && 
		    FAILED(m_cpInMeshA->Load("..\\Samples\\Multimedia\\Media\\geometry\\cow.x", 
			    NULL, D3DRMLOAD_FROMFILE, NULL, NULL)) && 
		    FAILED(m_cpInMeshA->Load("..\\..\\Media\\geometry\\cow.x", 
			    NULL, D3DRMLOAD_FROMFILE, NULL, NULL))) 
		{
		    m_cpInMeshA = NULL;
		}
	}

	if (SUCCEEDED(m_cpD3DRM->CreateMeshBuilder(&m_cpInMeshB))) {
		if (FAILED(m_cpInMeshB->Load("\\dtrans\\sdk\\samples\\media\\geometry\\mslogo.x", 
			NULL, D3DRMLOAD_FROMFILE, NULL, NULL)) && 
		    FAILED(m_cpInMeshB->Load("\\dxt-sdk\\media\\geometry\\mslogo.x", 
			NULL, D3DRMLOAD_FROMFILE, NULL, NULL)) &&
		    FAILED(m_cpInMeshB->Load("..\\Samples\\Multimedia\\Media\\geometry\\mslogo.x", 
			NULL, D3DRMLOAD_FROMFILE, NULL, NULL)) &&
		    FAILED(m_cpInMeshB->Load("..\\..\\Media\\geometry\\mslogo.x", 
			NULL, D3DRMLOAD_FROMFILE, NULL, NULL)))
		{
			m_cpInMeshB = NULL;
		}
	}
    }
#endif	// EMPTY_START


    if(m_cpD3DRM && SUCCEEDED(CreateSubMeshA()))
    {
	CreateSubMeshB();
    }

    return S_OK;
}

#define fCAMDIST 4.0f


HRESULT
CTestView::Create3DScene()
{
//	TRACE("CTestView::Create3DScene\n");
	HRESULT hr = S_OK;

	if (m_cpD3DRM)
        {
	
	    // Create the scene
	    m_cpframeScene = NULL;
	    if (FAILED(hr = m_cpD3DRM->CreateFrame(NULL, &m_cpframeScene)))
		    return hr;
	    
	    // Just a hint of blue so we can see black objects (common in development).
	    if (FAILED(hr = m_cpframeScene->SetSceneBackgroundRGB(0.0f, 0.0f, 0.15f)))
		    return hr;
	    
	    // Create the camera
	    m_cpframeCamera = NULL;
	    if (FAILED(hr = m_cpD3DRM->CreateFrame(m_cpframeScene, &m_cpframeCamera)))
		    return hr;

	    // Create the lights
	    m_cpframeLight = NULL;
	    m_cpframeLightArm = NULL;
	    if (FAILED(hr = m_cpD3DRM->CreateFrame(m_cpframeScene, &m_cpframeLight)) ||
		    FAILED(hr = m_cpD3DRM->CreateFrame(m_cpframeLight, &m_cpframeLightArm)))
		    return hr;
	    
	    D3DRMLIGHTTYPE typeLight = (m_bSpotlight ? D3DRMLIGHT_SPOT : D3DRMLIGHT_DIRECTIONAL);
	    m_cpLight = NULL;
	    if (FAILED(hr = m_cpD3DRM->CreateLightRGB(typeLight, 1.0f, 1.0f, 1.0f, &m_cpLight)) ||
		    FAILED(hr = m_cpframeLightArm->AddLight(m_cpLight)) ||
		    FAILED(hr = m_cpLight->SetUmbra(0.5f)) ||
		    FAILED(hr = m_cpLight->SetPenumbra(0.9f)))
		    return hr;

	    // position the lights and the camera
	    if (FAILED(hr = m_cpframeLightArm->SetPosition(m_cpframeLight, 0.0f, 0.0f, fCAMDIST)) ||
		FAILED(hr = m_cpframeLightArm->SetOrientation(NULL, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f)))
		    return hr;
	    if (FAILED(hr = m_cpframeCamera->SetPosition(m_cpframeScene, 0.0f, 0.0f, fCAMDIST)) ||
		    FAILED(hr = m_cpframeCamera->SetOrientation(NULL, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f)))
		    return hr;
	    
	    m_cpframeVisual = NULL;
	    if (FAILED(hr = m_cpD3DRM->CreateFrame(m_cpframeScene, &m_cpframeVisual)))
		    return hr;

	    m_cpOutMesh = NULL;
	    if (FAILED(hr = m_cpD3DRM->CreateMeshBuilder(&m_cpOutMesh)) ||
		FAILED(hr = m_cpframeVisual->AddVisual((LPDIRECT3DRMVISUAL) m_cpOutMesh)) ||
		FAILED(hr = m_cpOutMesh->SetPerspective(TRUE)))
	    {
		    return hr;
	    }
    }	
    return hr;
}


int 
CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    HRESULT hr = S_OK;
	
    ((CTestApp*)AfxGetApp())->m_pView = this;

	if( CView::OnCreate(lpCreateStruct) == -1 )
	{
		return -1;
	}

	if (FAILED(hr = CreateRenderer()) ||
		FAILED(hr = CreateTransformFactory()) ||
		FAILED(hr = CreateDefaultContent()) ||
		FAILED(hr = Create3DScene()))
		goto e_Exit;

e_Exit:
	// clean up
	if (FAILED(hr)) {
		DisplayMessage(hr, NULL, NULL);
		return -1;
	}
        else
        {
            SetTimer(1234, 500, NULL);
        }

	return 0;
}




HRESULT
CTestView::Resize2D(DWORD nX, DWORD nY)
{
        HDC foo;
        IDirectDrawSurface *pDDS;
        HRESULT hrTest;

	TRACE("CTestView::Resize2D\n");
	HRESULT hr;
	CDXDBnds bnds;
	bnds.SetXYSize(nX, nY);
	m_cpdxs2DOut.Release();
        m_bFillAll = TRUE;
	if (FAILED(hr = m_cpSurfFact->CreateSurface(NULL, NULL, g_BitDepth[m_BitDepthIndex], &bnds, 0, NULL,
						IID_IDXSurface, (void **) &m_cpdxs2DOut)))
		ONFAIL("OutImage CreateSurface() failed.");

        if (m_cpGradient)
        {
            m_cpGradient->Setup(NULL, 0, (IUnknown **)&m_cpdxs2DOut.p, 1, 0);
            CComQIPtr<IDXTScaleOutput, &IID_IDXTScaleOutput> cpOutSize(m_cpGradient);
            SIZE sz;
            sz.cx = nX; sz.cy = nY;
            cpOutSize->SetOutputSize(sz, FALSE);
        }

        if (m_bScaleToOut && m_cpDXScaleOutput)
        {
            SIZE sz;
            sz.cx = nX;
            sz.cy = nY;
            m_cpDXScaleOutput->SetOutputSize(sz, FALSE);
        }

        m_cpdxs2DOut->GetDirectDrawSurface(IID_IDirectDrawSurface, (void **)&pDDS);
        hrTest = pDDS->GetDC(&foo);
        pDDS->ReleaseDC(foo);
        pDDS->Release();

e_Exit:
	// clean up
	if (FAILED(hr)) 
	{
	    DisplayMessage(hr, NULL, NULL);
	}
	return hr;
}


HRESULT
CTestView::Resize3D(DWORD nX, DWORD nY)
{
//	TRACE("CTestView::Resize3D\n");
    HRESULT hr = S_OK;
    if (m_cpD3DRM)
    {
	LPDIRECTDRAWSURFACE pDDS = NULL;
        DDSURFACEDESC ddsd;
	BOOL bCreatedHW = FALSE;

	/*
	 * Attempt to create a hardware device
	 */

        ddsd.dwSize = sizeof(ddsd);
        ddsd.dwWidth = nX;
        ddsd.dwHeight = nY;
        ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS;
        ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE | DDSCAPS_VIDEOMEMORY;

        m_cpdds3DOut = NULL;
	m_cpD3DDevice = NULL;

	hr = m_cpDD->CreateSurface(&ddsd, &m_cpdds3DOut, NULL);
	if (SUCCEEDED(hr))
	{
	    hr = m_cpD3DRM->CreateDeviceFromSurface((LPGUID)&IID_IDirect3DHALDevice, m_cpDD, m_cpdds3DOut, 0, &m_cpD3DDevice);
	    if (SUCCEEDED(hr))
	    {
		hr = m_cpD3DDevice->SetRenderMode(D3DRMRENDERMODE_SORTEDTRANSPARENCY);
		if(SUCCEEDED(hr))
		{
		    // Get the IM device and test the caps of it.
		    CComPtr<IDirect3DDevice2> m_cpD3DDeviceIM;
		    hr = m_cpD3DDevice->GetDirect3DDevice2(&m_cpD3DDeviceIM);
		    if(SUCCEEDED(hr))
		    {
			D3DDEVICEDESC descHW, descHEL;
			descHW.dwSize = sizeof(descHW);
			descHEL.dwSize = sizeof(descHW);

			hr = m_cpD3DDeviceIM->GetCaps(&descHW, &descHEL);
			if(SUCCEEDED(hr) && (descHW.dpcTriCaps.dwMiscCaps & D3DPMISCCAPS_CULLCW))
			{
			    bCreatedHW = TRUE;
			}
		    }
		}
	    }
	}

	if (!bCreatedHW)
	{
	    m_cpdds3DOut = NULL;
	    m_cpD3DDevice = NULL;

	    /* Failed to create hardware device, try software */
	    ddsd.dwSize = sizeof(ddsd);
	    ddsd.dwWidth = nX;
	    ddsd.dwHeight = nY;
	    ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH | DDSD_CAPS;
	    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY | DDSCAPS_3DDEVICE;

	    if (FAILED(hr = m_cpDD->CreateSurface(&ddsd, &m_cpdds3DOut, NULL)))
		    ONFAIL("Out3DSurf CreateSurface() failed.");

	    if (FAILED(hr = m_cpD3DRM->CreateDeviceFromSurface((LPGUID)&IID_IDirect3DRGBDevice, m_cpDD, m_cpdds3DOut, 0, &m_cpD3DDevice)))
		    ONFAIL("CreateDeviceFromSurface() failed.");
	    if (FAILED(hr = m_cpD3DDevice->SetRenderMode(D3DRMRENDERMODE_SORTEDTRANSPARENCY)))
		    ONFAIL("SetRenderMode() failed.");
	}
	
        m_cpD3DDevice->SetQuality(D3DRMRENDER_GOURAUD);

        m_cpViewport.Release();
        if (FAILED(hr = m_cpD3DRM->CreateViewport(m_cpD3DDevice, m_cpframeCamera, 0, 0, nX, nY, &m_cpViewport)))
	        return hr;
    
        if (FAILED(hr = m_cpViewport->SetProjection(D3DRMPROJECT_PERSPECTIVE)))
	        return hr;
    
        if (FAILED(hr = m_cpViewport->SetUniformScaling(FALSE)))
	        return hr;
    }
e_Exit:
    // clean up
    if (FAILED(hr)) 
    {
	DisplayMessage(hr, NULL, NULL);
    }
    return hr;
}

HRESULT CTestView::SetFlatShading(BOOL bNewVal)
{
    InvalidateRect(NULL, false);
    if( !m_cpD3DDevice ) return S_FALSE;

    D3DRMRENDERQUALITY rqQuality = m_cpD3DDevice->GetQuality();

    rqQuality &= ~D3DRMSHADE_MASK;
    rqQuality |= bNewVal? D3DRMSHADE_FLAT: D3DRMSHADE_GOURAUD;
  
    return m_cpD3DDevice->SetQuality(rqQuality);
}

HRESULT
CTestView::Resize(DWORD nX, DWORD nY)
{
    HRESULT hr = S_OK;

    if (nX && nY && ((nX != (DWORD)m_WndWidth) || (nY != (DWORD)m_WndHeight)))
    {
        // keep 2D & 3D sizes synchronous
        if (FAILED(hr = Resize3D(nX, nY)) ||
	        FAILED(hr = Resize2D(nX, nY)))
	        goto e_Exit;

	// save the window size
	m_WndWidth = nX;
	m_WndHeight = nY;
        hr = Setup(m_fPercentComplete);
    }

e_Exit:
	// clean up
	if (FAILED(hr)) 
	{
	    DisplayMessage(hr, NULL, NULL);
	}
	return hr;
}


void 
CTestView::OnDraw(CDC *pDC)
{
//	TRACE("CTestView::OnDraw\n");
        HRESULT hr = S_OK;
        CPaintDC & PaintDC = *((CPaintDC *)pDC);
	CComPtr<IDirectDrawSurface> cpdds;
	const TCHAR *szMsg = NULL;
	bool bExecute;
	DWORD dwGenId;

	// check if the window has changed size
	RECT rSrc, rDst;
	GetClientRect(&rSrc);
	if ((rSrc.right != long(m_WndWidth)) || (rSrc.bottom != long(m_WndHeight))) {
		if (FAILED(hr = Resize(rSrc.right, rSrc.bottom)))
			goto e_Exit;
		if (!m_bOutputGeo && FAILED(hr = Setup(m_fPercentComplete)))
			goto e_Exit;
	}

	// check if window has zero area
	if (!(m_WndWidth && m_WndHeight))
		goto e_Exit;

	// create progress message, if necessary
	if (m_bInitializingTransform)
		szMsg = _T("Initializing Transform...");
	else if (m_cpDXTransform == NULL)
		szMsg = _T("Transform did not load or initialize properly.");
	else if (m_szSetupError)
		szMsg = m_szSetupError;
	if (szMsg)
		goto e_Exit;

	// execute the transform and draw into backbuffer, if necessary
	m_cpDXTransform->GetGenerationId(&dwGenId);
	bExecute = (m_dwLastExecGenId != dwGenId);
	m_dwLastExecGenId = dwGenId;

	if (m_bOutputGeo) {
		hr = Render3DScene(&cpdds, bExecute);
	} else {
		hr = Render2DScene(&cpdds, bExecute, PaintDC.m_ps.rcPaint);
	}

	if (FAILED(hr))
		goto e_Exit;

        if (!m_bDontRender)
        {
	    // copy the back buffer to the window
            if (m_bOutputGeo)
            {
	        rDst = rSrc;
	        ClientToScreen(&rDst);
	        if (FAILED(m_cpPrimarySurface->Blt(&rDst, cpdds, &rSrc, DDBLT_WAIT, NULL))) {
		        // try GDI blt instead
		        HDC hdcSurf;
		        if (FAILED(hr = cpdds->GetDC( &hdcSurf )))
			        goto e_Exit;
		        ::BitBlt(pDC->m_hDC, 0, 0, m_WndWidth, m_WndHeight, hdcSurf, 0, 0, SRCCOPY);
		        cpdds->ReleaseDC( hdcSurf );
	        }
            }
            else
            {
	        HDC hdcSurf;
	        if (FAILED(hr = cpdds->GetDC( &hdcSurf )))
		        goto e_Exit;
	        ::BitBlt(pDC->m_hDC, PaintDC.m_ps.rcPaint.left,
                    PaintDC.m_ps.rcPaint.top,
                    PaintDC.m_ps.rcPaint.right - PaintDC.m_ps.rcPaint.left,
                    PaintDC.m_ps.rcPaint.bottom - PaintDC.m_ps.rcPaint.top,
                    hdcSurf, PaintDC.m_ps.rcPaint.left, PaintDC.m_ps.rcPaint.top, SRCCOPY);
	        cpdds->ReleaseDC( hdcSurf );
            }
        }

e_Exit:
	DisplayMessage(hr, szMsg, pDC);
}


void 
CTestView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);
}


BOOL CTestView::OnEraseBkgnd(CDC* pDC) 
{
    return 1;
}


afx_msg void CTestView::OnTimer(UINT nID)
{
    if (m_cpDXTransform)
    {
        DWORD dwGenId;
	m_cpDXTransform->GetGenerationId(&dwGenId);
        if (m_dwLastExecGenId != dwGenId)
        {
            InvalidateRect(NULL, false);
        }
    }
}

HRESULT
CTestView::ReCreateMesh()
{
    HRESULT hr = S_OK;
    
    // reset the output mesh
    if (m_cpOutMesh && FAILED(hr = m_cpOutMesh->Empty(0)))
	return hr;	

    switch(m_eWhichMesh)
    {
    case WHICHMESH_OUTPUT:
	if(SUCCEEDED(hr = Setup(m_fPercentComplete)))
	    ReExecuteTransform();
	break;

    case WHICHMESH_A:
	if(SUCCEEDED(hr = m_cpOutMesh->AddMeshBuilder(m_cpInMeshA,0)))
	    InvalidateRect(NULL, false);
	break;
	
    case WHICHMESH_B:
	if(SUCCEEDED(hr = m_cpOutMesh->AddMeshBuilder(m_cpInMeshB,0)))
	    InvalidateRect(NULL, false);
	break;
    default:
	ASSERT(0);
    }

    return hr;
}


HRESULT 
CTestView::SetTransform(const CLSID &clsid)
{
//	TRACE("CTestView::SetTransform\n");
    HRESULT hr = S_OK;
	DWORD dwFlags = 0;
	ULONG cGuids = 10;
	GUID aguid[10];

	ASSERT(m_cpTransFact);

    m_bInitializingTransform = TRUE;
    InvalidateRect(NULL, false);
    UpdateWindow();
	
	m_ClsId = clsid;
	
	m_cpDXTransform.Release();
	m_cpDXEffect.Release();
        m_cpDXScaleOutput.Release();

	if (FAILED(hr = m_cpTransFact->CreateTransform(NULL, 0, NULL, 0, NULL, NULL, 
						clsid, IID_IDXTransform, (void **) &m_cpDXTransform)))
		ONFAIL("CreateTransform() failed.");

	//--- Cache effect interface if there is one
	m_cpDXTransform->QueryInterface(IID_IDXEffect, (void **) &m_cpDXEffect);
        m_cpDXTransform->QueryInterface(IID_IDXTScaleOutput, (void **) &m_cpDXScaleOutput);

	if (FAILED(hr = m_cpDXTransform->GetInOutInfo(TRUE, 0, NULL, aguid, &cGuids, NULL)))
		ONFAIL("GetInOutInfo() failed.");

	if (hr == S_OK)
		m_bOutputGeo = IsEqualGUID(IID_IDirect3DRMMeshBuilder3, aguid[0]);

	// compute information about inputs
	m_nInputsRequired = 0;
	m_nInputsPossible = 0;

	cGuids = 10;
	if (FAILED(hr = m_cpDXTransform->GetInOutInfo(FALSE, 0, &dwFlags, aguid, &cGuids, NULL)))
		ONFAIL("GetInOutInfo() failed.");
	if (hr == S_OK) {
		m_bInput0Geo = IsEqualGUID(IID_IDirect3DRMMeshBuilder3, aguid[0]);
		m_bInput0Req = ((dwFlags & DXINOUTF_OPTIONAL) == 0);
		m_nInputsRequired += m_bInput0Req;
		m_nInputsPossible++;
	}
	cGuids = 10;
	if (FAILED(hr = m_cpDXTransform->GetInOutInfo(FALSE, 1, &dwFlags, aguid, &cGuids, NULL)))
		ONFAIL("GetInOutInfo() failed.");
	if (hr == S_OK) {
		m_bInput1Geo = IsEqualGUID(IID_IDirect3DRMMeshBuilder3, aguid[0]);
		m_bInput1Req = ((dwFlags & DXINOUTF_OPTIONAL) == 0);
		m_nInputsRequired += m_bInput1Req;
		m_nInputsPossible++;
	}

	if (m_nInputsDesired < m_nInputsRequired)
		m_nInputsDesired = m_nInputsRequired;
	if (m_nInputsDesired > m_nInputsPossible)
		m_nInputsDesired = m_nInputsPossible;

	if(m_cpDXEffect)
	{
	    // Use the effect suggested duration.
	    CTransitionDlg *pDlg = ((CTestApp *) AfxGetApp())->m_pDlgBar;

	    float fDuration;

	    m_cpDXEffect->get_Duration(&fDuration);
	    pDlg->SetSuggestedDuration(fDuration);
	}

	if(m_cpDXTransform)
	{
	    DWORD dwMiscFlags;

	    hr = m_cpDXTransform->GetMiscFlags(&dwMiscFlags);

	    if(SUCCEEDED(hr))
	    {
                if(dwMiscFlags & DXTMF_QUALITY_SUPPORTED)
                {
		    m_cpDXTransform->GetQuality(&m_fQuality);

		    CTransitionDlg *pDlg = ((CTestApp *) AfxGetApp())->m_pDlgBar;
		    pDlg->SetSuggestedQuality(m_fQuality);
                }
                m_bEnableClip = (dwMiscFlags & DXTMF_BOUNDS_SUPPORTED) != 0;
                m_bEnablePlacement = (dwMiscFlags & DXTMF_PLACEMENT_SUPPORTED) != 0;
	    }
	}

	// cache property page interface
	m_cpSpecifyPropertyPages = NULL;
	m_cpDXTransform->QueryInterface(IID_ISpecifyPropertyPages, (void **) &m_cpSpecifyPropertyPages);

	m_fPercentComplete = 0.f;

	if(!m_bOutputGeo || 
	  (!m_bInput0Geo && m_bInput0Req) ||
	  (!m_bInput1Geo && m_bInput1Req))
	{
	    WhichMeshView(WHICHMESH_OUTPUT);
	}
        else
        {
	    if (FAILED(hr = ReCreateMesh()))
		    goto e_Exit;
        }

e_Exit:
	DisplayMessage(hr, NULL, NULL);

	// force OnDraw message
	m_bInitializingTransform = FALSE;
	InvalidateRect(NULL, false);
	UpdateWindow();

	return hr;
}


HRESULT 
CTestView::Setup(float fPercentComplete)
{
//	TRACE("CTestView::Setup\n");
    if(m_bOutputGeo && m_eWhichMesh != WHICHMESH_OUTPUT)
    {
	return ReCreateMesh();
    }

	InvalidateRect(NULL, false);

	if (m_cpDXTransform == NULL) {
		m_szSetupError = _T("No Transform Defined.");
		return S_OK;
	}
	
	IUnknown *rgpUnkIn[2];
	IUnknown *pUnkOut;

    if (!m_cpdxs2DOut)
	{
		Resize(100, 100);    // Bugbug -- Workaround
		if (m_cpDXTransform == NULL) return S_OK;
	}

	pUnkOut = (m_bOutputGeo ? (IUnknown *) m_cpOutMesh : (IUnknown *) m_cpdxs2DOut);
	rgpUnkIn[0] = (m_bInput0Geo ? (IUnknown *) m_cpInMeshA : (IUnknown *) m_cpBitDepthCorrectInSurf[0]);
	rgpUnkIn[1] = (m_bInput1Geo ? (IUnknown *) m_cpInMeshB : (IUnknown *) m_cpBitDepthCorrectInSurf[1]);
	
	// check if all the inputs are defined
	m_szSetupError = NULL;
	
	// compute the number of inputs used for this rendering
	DWORD nInputsUsed = ((m_nInputsDesired < m_nInputsRequired) ? m_nInputsRequired : m_nInputsDesired);
	if (nInputsUsed > m_nInputsPossible)
		nInputsUsed = m_nInputsPossible;
	
	if ((nInputsUsed > 0) && !rgpUnkIn[0])
		m_szSetupError = (m_bInput0Geo ? _T("Need mesh A for Input.") : _T("Need surface A for Input."));
	else if ((nInputsUsed > 1) && !rgpUnkIn[1])
		m_szSetupError = (m_bInput1Geo ? _T("Need mesh B for Input.") : _T("Need surface B for Input."));

	// do full setup if number of inputs changed
	if (nInputsUsed != m_nCurInputsUsed) {
		// update the input radio buttons
		CheckRadioButton(IDC_RADIO_0, IDC_RADIO_2, IDC_RADIO_0 + nInputsUsed);
		m_nCurInputsUsed = nInputsUsed;
	}

	if (m_szSetupError)
		return S_OK;

	DWORD dwStart = GetTickCount();
	HRESULT hr = m_cpDXTransform->Setup(rgpUnkIn, nInputsUsed, &pUnkOut, 1, 0);
	((CTestApp *) AfxGetApp())->m_pDlgBar->SetupTime(GetTickCount() - dwStart);
	
	if (FAILED(hr)) {
		TRACE("Transform Setup() failed.  Error 0x%08x.  Line %d. File: %s\n", hr, __LINE__, __FILE__);
		m_cpDXTransform = NULL;
		m_cpDXEffect = NULL;
	} else {
                if (m_bScaleToOut && m_cpDXScaleOutput)
                {
                    SIZE sz;
                    sz.cx = m_WndWidth;
                    sz.cy = m_WndHeight;
                    m_cpDXScaleOutput->SetOutputSize(sz, FALSE);
                }


		SetPercentComplete(fPercentComplete);
		m_cpDXTransform->GetGenerationId(&m_dwLastExecGenId);
		m_dwLastExecGenId--;
                if (!m_bOutputGeo)
                {
//                    m_cpDXTransform->MapBoundsIn2Out(NULL, 0, 0, &m_2DOutBnds);
                    m_bFillAll = TRUE;
                }
	}

	return hr;
}


HRESULT 
CTestView::Render3DScene(IDirectDrawSurface **ppdds, bool bExecute)
{
//	TRACE("Render3DScene: %s\n", (bExecute ? "true" : "false"));
	ASSERT(m_cpdds3DOut);

    HRESULT hr;
	if (ppdds == NULL)
		return E_POINTER;

	if (bExecute && m_eWhichMesh == WHICHMESH_OUTPUT) {
		CDXCBnds dxbndsPredicted;
		if(m_bBoundsChecking && 
		   FAILED(hr = m_cpDXTransform->MapBoundsIn2Out(NULL, 0, 0, &dxbndsPredicted))) {
			ONFAIL("MapBoundsIn2Out() failed.");
		}

		if (FAILED(hr = m_cpDXTransform->Execute(NULL, NULL, NULL))) {
			m_szSetupError = "Execution of Transform failed.";
			ONFAIL(m_szSetupError);
		}
		if(m_bBoundsChecking)
		{
		    D3DRMBOX d3dboxActual;

		    m_cpOutMesh->GetBox(&d3dboxActual);

#define BNDS_ERR_SUBSTRING_LEN 30
		    char szBndsError[BNDS_ERR_SUBSTRING_LEN * 6 + 1];

		    szBndsError[0] = 0;

		    if(d3dboxActual.min.x < dxbndsPredicted[DXB_X].Min)
		    {
			static char szError[] = "Minimum X bound exceeded.\n";
			_ASSERT(sizeof(szError) <= BNDS_ERR_SUBSTRING_LEN);
			strcat(szBndsError, szError);
		    }

		    if(d3dboxActual.min.y < dxbndsPredicted[DXB_Y].Min)
		    {
			static char szError[] = "Minimum Y bound exceeded.\n";
			_ASSERT(sizeof(szError) <= BNDS_ERR_SUBSTRING_LEN);
			strcat(szBndsError, szError);
		    }

		    if(d3dboxActual.min.z < dxbndsPredicted[DXB_Z].Min)
		    {
			static char szError[] = "Minimum Z bound exceeded.\n";
			_ASSERT(sizeof(szError) <= BNDS_ERR_SUBSTRING_LEN);
			strcat(szBndsError, szError);
		    }

		    if(d3dboxActual.max.x > dxbndsPredicted[DXB_X].Max)
		    {
			static char szError[] = "Maximum X bound exceeded.\n";
			_ASSERT(sizeof(szError) <= BNDS_ERR_SUBSTRING_LEN);
			strcat(szBndsError, szError);
		    }

		    if(d3dboxActual.max.y > dxbndsPredicted[DXB_Y].Max)
		    {
			static char szError[] = "Maximum Y bound exceeded.\n";
			_ASSERT(sizeof(szError) <= BNDS_ERR_SUBSTRING_LEN);
			strcat(szBndsError, szError);
		    }

		    if(d3dboxActual.max.z > dxbndsPredicted[DXB_Z].Max)
		    {
			static char szError[] = "Maximum Z bound exceeded.\n";
			_ASSERT(sizeof(szError) <= BNDS_ERR_SUBSTRING_LEN);
			strcat(szBndsError, szError);
		    }
#undef BNDS_ERR_SUBSTRING_LEN

		    if(szBndsError[0])
		    {
			MessageBox(szBndsError, "Bounds reporting error.", MB_ICONINFORMATION | MB_OK);
		    }
		}
	}
	
        if (!m_bDontRender)
        {
	    if (FAILED(hr = m_cpViewport->ForceUpdate(0, 0, m_WndWidth, m_WndHeight)))
		    ONFAIL("pViewport->ForceUpdate() failed.");
	    
	    // Clear both back and z-buffer.
	    if (FAILED(hr = m_cpViewport->Clear(D3DRMCLEAR_ALL)))
		    ONFAIL("pViewport->Clear() failed.");
	    
	    // Render the scene
	    if (FAILED(hr = m_cpViewport->Render(m_cpframeScene)))
		    ONFAIL("pViewport->Render() failed.");
	    
	    // Update the device
	    if (FAILED(hr = m_cpD3DDevice->Update()))
		    ONFAIL("pD3DDevice->Update() failed.");
        }

e_Exit:
	(*ppdds = m_cpdds3DOut)->AddRef();

	// clean up
	if (FAILED(hr)) 
	{
	    DisplayMessage(hr, NULL, NULL);
	}
	return hr;
}

BOOL CTestView::Get2DOutRect(RECT & r)
{
    if ((!m_bOutputGeo) && m_cpDXTransform)
    {
        CDXDBnds bnds;
        CDXDVec place;
        GetBoundsAndPlacement(bnds, place);
        bnds.SetToSize();
        bnds += place;
        bnds.GetXYRect(r);
        if (r.left < 0) r.left = 0;
        if (r.right > (long)m_WndWidth) r.right = m_WndWidth;
        if (r.top < 0) r.top = 0;
        if (r.bottom > (long)m_WndHeight) r.bottom = m_WndHeight;
        return TRUE;
    }
    return FALSE;
}


void 
CTestView::GetBoundsAndPlacement(CDXDBnds & bnds, CDXDVec & place)
{
    m_cpDXTransform->MapBoundsIn2Out(NULL, 0, 0, &bnds);
    long Width = bnds.Width();
    long Height = bnds.Height();
    
    if(m_bEnableClip)
    {
        switch (m_iClip)
        {
        case 1:
            bnds[DXB_Y].Max = Height / 2;
            break;
        case 2:
            bnds[DXB_Y].Min = Height / 2;
            break;
        case 3:
            bnds[DXB_X].Min = Width / 2;
            break;
        case 4:
            bnds[DXB_X].Max = Width / 2;
            break;
        case 5:
            {
                long W2 = Width / 2;
                long H2 = Height / 2;
                bnds[DXB_X].Min = W2 / 2;
                bnds[DXB_X].Max = bnds[DXB_X].Min + W2;
                bnds[DXB_Y].Min = H2 / 2;
                bnds[DXB_Y].Max = bnds[DXB_Y].Min + H2;
            }
            break;
        }
    }

    //
    //  Now place based on the clip size.
    //
    if(m_bEnablePlacement)
    {
        Width = bnds.Width();
        Height = bnds.Height();

        switch (m_iPlace)
        {
        case 1:
            place[DXB_X] = (m_WndWidth - Width) / 2;
            place[DXB_Y] = (m_WndHeight - Height) / 2;
            break;

        case 2:
            place[DXB_X] = place[DXB_Y] = 20;
            break;
        case 3:
            place[DXB_X] = place[DXB_Y] = -20;
            break;
        case 4:
            place[DXB_X] = -Width / 2;
            place[DXB_Y] = -Height / 2;
            break;

        case 5:
            place[DXB_X] = -Width / 2;
            place[DXB_Y] = m_WndHeight - (Height / 2);
            break;

        case 6:
            place[DXB_X] = m_WndWidth - (Width / 2);
            place[DXB_Y] = -Height / 2;
            break;

        case 7:
            place[DXB_X] = m_WndWidth - (Width / 2);
            place[DXB_Y] = m_WndHeight - (Height / 2);
            break;
        }
    }
    else
    {
       place[DXB_X] = 0;
       place[DXB_Y] = 0;
    }
}

HRESULT 
CTestView::Render2DScene(IDirectDrawSurface **ppdds, bool bExecute, const RECT & rectInvalid)
{
   HRESULT hr;

   if (ppdds == NULL)
		return E_POINTER;
	if (bExecute) 
        {
            CDXDBnds bnds;
            CDXDVec place;
            GetBoundsAndPlacement(bnds, place);
            if (!m_bDontRender)
            {
		if(m_bBoundsChecking && m_cpDXTransform)
		{
		    CDXDBnds dxbndsPredicted;

		    hr = m_cpDXTransform->MapBoundsIn2Out(NULL, 0, 0, &dxbndsPredicted);
		    if(FAILED(hr))
		    {
			DisplayMessage(hr, "MapBoundsIn2Out() failed.", NULL);
		    }
		    else
		    {
			// Only check to see if type returned is discrete.
			if(dxbndsPredicted.eType != DXBT_DISCRETE && 
			   dxbndsPredicted.eType != DXBT_DISCRETE64)
			{
			    MessageBox(	"Bounds type must be discrete.", 
					"Bounds reporting error.", 
					MB_ICONINFORMATION | MB_OK);
			}
		    }
		}

                if (m_bFillAll)
                {
                    m_bFillAll = FALSE;
                    if (m_cpGradient)
                    {
                        m_cpGradient->Execute(NULL, NULL, NULL);
                    }
                    else
                    {
                        DXFillSurface(m_cpdxs2DOut, 0xFFC0C0FF, FALSE, INFINITE);
                    }
                }
                else
                {
                    if (GetBlend() && !GetInPlace() )
                    {
                        RECT rFill;
                        RECT rDraw;
                        CDXDBnds OutBnds(bnds);
                        OutBnds.SetToSize();
                        OutBnds += place;
                        OutBnds.GetXYRect(rDraw);
                        if (rDraw.left < 0) rDraw.left = 0;
                        if (rDraw.right > (long)m_WndWidth) rDraw.right = m_WndWidth;
                        if (rDraw.top < 0) rDraw.top = 0;
                        if (rDraw.bottom > (long)m_WndHeight) rDraw.bottom = m_WndHeight;
                        if (UnionRect(&rFill, &rectInvalid, &rDraw))
                        {
                            if (m_cpGradient)
                            {
                                OutBnds.SetXYRect(rFill);
                                CDXDVec v(false);
                                OutBnds.GetMinVector(v);
                                m_cpGradient->Execute(NULL, &OutBnds, &v);
                            }
                            else
                            {
                                DXFillSurfaceRect(m_cpdxs2DOut, rFill, 0xFFC0C0FF, FALSE, INFINITE);
                            }
                        }
                    }
                }
            }


            if (FAILED(hr = m_cpDXTransform->Execute( NULL, m_bEnableClip && m_iClip? &bnds : NULL, 
                                                      m_bEnablePlacement && m_iPlace? &place : NULL)))
            {
		ONFAIL("Transform execution() failed.");
            }
	}

e_Exit:
	m_cpdxs2DOut->GetDirectDrawSurface(IID_IDirectDrawSurface, (void **) ppdds);

	// clean up
	if (FAILED(hr)) 
	{
	    DisplayMessage(hr, NULL, NULL);
	}
	return hr;
}

void
CTestView::RotateFrame(float dX, float dY, IDirect3DRMFrame3 *pFrame)
{
	ASSERT(pFrame);

	float dR = (float) sqrt(dX * dX + dY * dY);
	float radius = 50.f;
	float denom = (float) sqrt(radius * radius + dR * dR);
	
	if ((dR != 0.f) && (denom != 0.f)) {
		pFrame->SetRotation(m_cpframeScene, dY / dR, dX / dR, 0.f, -dR / denom);
		pFrame->Move(0.5f);
		pFrame->SetRotation(m_cpframeScene, 0.0f, 0.0f, 0.0f, 0.0f);
	}
}


void
CTestView::MoveLight(float dX, float dY, UINT nFlags)
{
	if ((nFlags & MK_LBUTTON) && !(nFlags & MK_SHIFT)) {
		if (m_bRotating) {
			RotateFrame(dX, dY, m_cpframeLight);
			InvalidateRect(NULL, false);
		} else {
			m_bRotating = TRUE;
		}
	} else {
		m_bRotating = FALSE;
	}
}


void CTestView::OnLButtonDown( UINT nFlags, CPoint point )
{
    CView::OnLButtonDown(nFlags, point);

    // Is it a 3D transform.
    if (m_bOutputGeo && m_cpDXTransform) 
    {
        CStatusBar & StatusBar = ((CMainFrame*)GetParent())->m_wndStatusBar;
	CComPtr<IDirect3DRMPickedArray> cpPickArray;
	HRESULT hr = m_cpViewport->Pick(point.x, point.y, &cpPickArray);

	if(SUCCEEDED(hr))
	{
	    DWORD dwNum = cpPickArray->GetSize();
	    if(dwNum > 0)
	    {
		CComPtr<IDirect3DRMVisual> cpVisual;
		CComPtr<IDirect3DRMFrameArray> cpFrameArray;
		D3DRMPICKDESC PickDesc;

		// Pickarray is depth sorted.
		hr = cpPickArray->GetPick(0, &cpVisual, &cpFrameArray, &PickDesc);
		if(SUCCEEDED(hr))
		{
		    TCHAR szInput[100];
		    CComPtr<IDirect3DRMMeshBuilder3> cpMeshBuilder;

		    hr = cpVisual->QueryInterface(IID_IDirect3DRMMeshBuilder3, 
			(void **)&cpMeshBuilder);

		    if(SUCCEEDED(hr))
		    {
			CComPtr<IDirect3DRMFace2> cpFace;
			hr = cpMeshBuilder->GetFace(PickDesc.ulFaceIdx, &cpFace);
			if(SUCCEEDED(hr))
			{
			    CComPtr<IDirect3DRMTexture3> cpTexture;
			    hr = cpFace->GetTexture(&cpTexture);
			    if(SUCCEEDED(hr) && cpTexture)
			    {
				sprintf( szInput,
				    _T("Number picked: %u.  Closest MeshBuilder AppData = %lu. Face: %lu. Texture AppData = %lu."), 
				    dwNum, cpVisual->GetAppData(), PickDesc.ulFaceIdx, cpTexture->GetAppData());
			    }
			    else
			    {
				sprintf( szInput,
				    _T("Number picked: %u.  Closest MeshBuilder AppData = %lu. Face: %lu. No texture."), 
				    dwNum, cpVisual->GetAppData(), PickDesc.ulFaceIdx);
			    }
			}
			else
			{
			    sprintf(szInput,
				_T("Number picked: %u.  Closest MeshBuilder AppData = %lu.  Unable to retrive face %lu."),
				dwNum, cpVisual->GetAppData(), PickDesc.ulFaceIdx);

			}
		    }
		    else
		    {
			sprintf( szInput, _T("Number picked: %u. Unknown Visual type AppData = %lu"), 
			    dwNum, cpVisual->GetAppData());
		    }

		    StatusBar.SetPaneText(0, szInput);
		}
	    }
	    else
	    {
		StatusBar.SetPaneText(0, _T("No pickable object found."));
	    }
	}
	else
	{
            StatusBar.SetPaneText(0, _T("Get ViewPort failed."));
	}

	return;
    }

    // Just a 2D transform.
    if (m_cpDXTransform)
    {
        CStatusBar & StatusBar = ((CMainFrame*)GetParent())->m_wndStatusBar;
        CComPtr<IDXSurfacePick> cpPick;
        if (SUCCEEDED(m_cpDXTransform->QueryInterface(IID_IDXSurfacePick, (void **)&cpPick)))
        {
            ULONG ulIndex;
            CDXDVec OutVec(point.x, point.y, 0, 0);
            //
            //  Subtract the placement and add the min vector from the clip bounds
            //
            CDXDBnds bnds;
            CDXDVec place;
            GetBoundsAndPlacement(bnds, place);
            CDXDVec MinVecBnds(false);
            bnds.GetMinVector(MinVecBnds);
            OutVec += MinVecBnds;
            OutVec -= place;
            CDXDVec InVec(false);
            HRESULT hrPick = cpPick->PointPick(&OutVec, &ulIndex, &InVec);
            if (SUCCEEDED(hrPick))
            {
                if (hrPick == DXT_S_HITOUTPUT)
                {
                    StatusBar.SetPaneText(0, _T("Hit the output, but maps to no input"));
                }
                else
                {
                    if (hrPick == S_FALSE)
                    {
                        StatusBar.SetPaneText(0, _T("No surface hit"));
                    }
                    else
                    {
                        TCHAR szInput[50];
                        if (ulIndex)
                        {
	                    sprintf( szInput, _T("Hit input B at %i, %i"), InVec[0], InVec[1] );
                        }
                        else
                        {
	                    sprintf( szInput, _T("Hit input A at %i, %i"), InVec[0], InVec[1] );
                        }
                        StatusBar.SetPaneText(0, szInput);
                    }
                }
            }
            else
            {
                if( hrPick == E_NOTIMPL )
                {
                    StatusBar.SetPaneText(0, _T("Pick method is not implemented."));
                }
                else
                {
                    StatusBar.SetPaneText(0, _T("Pick interface failed."));
                }
            }
        }
        else
        {
            StatusBar.SetPaneText(0, _T("Pick interface not supported."));
        }
    }
}


void 
CTestView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CView::OnMouseMove(nFlags, point);

        if (!m_bOutputGeo) return;

	float dX, dY;

	if (m_bZooming || m_bSliding || m_bRotating) {
		dX = float(m_pointLastMouse.x - point.x);
		dY = float(m_pointLastMouse.y - point.y);
	}

	m_pointLastMouse = point;

	// skip out if we aren't doing anything
	if ((nFlags & (MK_LBUTTON | MK_RBUTTON)) == 0) {
		m_bZooming = m_bSliding = m_bRotating = false;
		return;
	}

    IDirect3DRMFrame3 *pFrame = ((nFlags & MK_CONTROL) ? m_cpframeLight : m_cpframeVisual);
	ASSERT(pFrame);

	if (nFlags & MK_LBUTTON) {
		if (nFlags & MK_SHIFT) {
			m_bRotating = FALSE;
			if (nFlags & MK_CONTROL) {
				m_bSliding = FALSE;
			} else {
				// If the shift and the left mouse button we move left or right and up or down.
				if (m_bSliding) {
					if ((dX != 0.f) || (dY != 0.f)) {
						pFrame->SetVelocity(m_cpframeCamera, -dX, dY, 0.f, FALSE);
						pFrame->Move(0.04f);
						pFrame->SetVelocity(m_cpframeCamera, 0.f, 0.f, 0.f, FALSE);
					}
				} else {
					m_bSliding = TRUE;
				}
			}
		} else {
			// if left mouse button, we just rotate the object
			m_bSliding = FALSE;
			if (m_bRotating) {
				RotateFrame(dX, dY, pFrame);
			} else {
				m_bRotating = TRUE;
			}
		}
	}

	// If the right button we dolly the frame in or out.
	if ((nFlags & MK_RBUTTON) && !(nFlags & MK_CONTROL)) {
		if (m_bZooming) {
			float fDist = dY;
			if (fDist != 0.f) {
				// Increasing Y brings the camera closer (-Z).
				pFrame->SetVelocity(m_cpframeCamera, 0.f, 0.f, -fDist, FALSE);
				pFrame->Move(0.2f);
				pFrame->SetVelocity(m_cpframeCamera, 0.f, 0.f, 0.f, FALSE);
			}
		} else {
			m_bZooming = TRUE;
		}
	} else {
		m_bZooming = FALSE;
	}

	InvalidateRect(NULL, false);
}

void CTestView::Quality(float fQuality, const RECT *pInvalidate)
{
    if (m_cpDXTransform)
    {
        HRESULT hr = m_cpDXTransform->SetQuality( fQuality );

	ASSERT(SUCCEEDED(hr));

        InvalidateRect(pInvalidate, false );
        UpdateWindow();
    }
    m_fQuality = fQuality;
}
void 
CTestView::SetPercentComplete(float fPercentComplete, const RECT *pInvalidate)
{
    if (m_cpDXEffect)
    {
        m_cpDXEffect->put_Progress( fPercentComplete );
        InvalidateRect(pInvalidate, false );
        UpdateWindow();
    }
    m_fPercentComplete = fPercentComplete;
}


HRESULT 
CTestView::LoadTexture(OLECHAR *pszFileName, IDXSurface **ppNewSurf)
{
	if (!pszFileName || !ppNewSurf)
		return E_INVALIDARG;

	if (m_cpSurfFact == NULL)
		return E_FAIL;

    DDSURFACEDESC ddsd;
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE | DDSCAPS_SYSTEMMEMORY;

    return m_cpSurfFact->LoadImage(pszFileName, NULL, &ddsd, NULL, IID_IDXSurface, (void **) ppNewSurf);
}


void 
CTestView::OnLightSpot() 
{
	m_bSpotlight ^= 1;

	D3DRMLIGHTTYPE typeLight = (m_bSpotlight ? D3DRMLIGHT_SPOT : D3DRMLIGHT_DIRECTIONAL);
	m_cpLight->SetType(typeLight);
	InvalidateRect(NULL, false);
}

void CTestView::OnUpdateLightSpot(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_bSpotlight);
}

HRESULT
CTestView::SetDesiredInputs(DWORD nInputs)
{
	if (m_nInputsDesired != nInputs) {
		m_nInputsDesired = nInputs;
		return ReCreateMesh();
	}
	return S_OK;
}

HRESULT
CTestView::LoadImage(DWORD nSurface, OLECHAR *osPath)
{
	HRESULT hr;
	CComPtr<IDXSurface> cpdxs;

	if (m_cpSurfFact == NULL)
		return E_FAIL;

	if ((osPath == NULL) || (nSurface > 1))
		return E_INVALIDARG;

	if (FAILED(hr = m_cpSurfFact->LoadImage(osPath, NULL, NULL,
						NULL, IID_IDXSurface, (void **) &cpdxs))) {
		ONFAIL("Failed LoadImage().");
	}

        m_cpInSurf[nSurface] = cpdxs;
        //
        //  This function will do the needed setup.
        //
        SetInputBitDepth(nSurface, m_InSurfBitDepth[nSurface]);

e_Exit:
	InvalidateRect(NULL, false);

	// clean up
	if (FAILED(hr)) 
	{
	    DisplayMessage(hr, NULL, NULL);
	}
	return hr;
}

HRESULT CTestView::SetInputBitDepth(ULONG ulSurface, int BitDepthIndex)
{
    if( !m_cpInSurf[ulSurface] ) return S_FALSE;
    HRESULT hr = S_OK;
    GUID PixelFmt;
    m_InSurfBitDepth[ulSurface] = BitDepthIndex;
    m_cpInSurf[ulSurface]->GetPixelFormat(&PixelFmt, NULL);
    if (IsEqualGUID(PixelFmt, *g_BitDepth[BitDepthIndex]))
    {
        m_cpBitDepthCorrectInSurf[ulSurface] = m_cpInSurf[ulSurface];
    }
    else
    {
        m_cpBitDepthCorrectInSurf[ulSurface].Release();
        hr = m_cpSurfFact->CopySurfaceToNewFormat(m_cpInSurf[ulSurface],
                    NULL, NULL, g_BitDepth[BitDepthIndex],
                    &m_cpBitDepthCorrectInSurf[ulSurface]);
        if (FAILED(hr))
        {
            MessageBox("Specified format could not be created.  Unexpeced error.", "Unable to convert input to format");
        }
    }
    hr = Setup(m_fPercentComplete);
    InvalidateRect(NULL, false);
    return hr;
}

static void LoadXFileCallback(LPDIRECT3DRMOBJECT pObj, REFIID guidObj, LPVOID pArg)
{
    CComPtr<IDirect3DRMMeshBuilder3> cpMeshBuilderIn;

    if (SUCCEEDED(pObj->QueryInterface(IID_IDirect3DRMMeshBuilder3, 
                  (LPVOID*)&cpMeshBuilderIn))) 
    {
        ((LPDIRECT3DRMMESHBUILDER3)pArg)->AddMeshBuilder(cpMeshBuilderIn, 0);
    }
    else
    {
        MessageBox(NULL, "Non-Meshbuilder X file object found. Not supported by this tool.", 
	    "X file read error.", MB_ICONINFORMATION | MB_OK);
    }

    pObj->Release();

    return;
}

HRESULT
CTestView::LoadMesh(DWORD nMesh, LPCTSTR szPath)
{
	HRESULT hr;
	CComPtr<IDirect3DRMMeshBuilder3> cpNewMesh;
	
	if (m_cpD3DRM == NULL)
		return E_FAIL;
	
	if ((szPath == NULL) || (nMesh > 1))
		return E_INVALIDARG;

	if (FAILED(hr = m_cpD3DRM->CreateMeshBuilder(&cpNewMesh)))
		ONFAIL("CreateMeshBuilder() failed.");

        // Get all objects, but callback function will complain to user 
        // if non-MeshBuilder objects are found.
        if(FAILED(hr = m_cpD3DRM->Load((LPVOID)szPath, NULL, NULL, 0,
                                  D3DRMLOAD_FROMFILE,
                                  LoadXFileCallback, (LPVOID)cpNewMesh,
                                  NULL, NULL, NULL)))
        {
		ONFAIL("new mesh Load() failed.");
        }

	switch (nMesh) {
	case 0:
		m_cpInMeshA = cpNewMesh;
		break;
	case 1:
		m_cpInMeshB = cpNewMesh;
		break;
	default:
		ASSERT(0);
		break;
	}

	if (FAILED(hr = Setup(m_fPercentComplete)))
		goto e_Exit;

e_Exit:
	InvalidateRect(NULL, false);

	// clean up
	if (FAILED(hr)) 
	{
	    DisplayMessage(hr, NULL, NULL);
	}
	return hr;
}

void
CTestView::ReExecuteTransform()
{
    if (m_cpDXTransform)
    {
	m_cpDXTransform->GetGenerationId(&m_dwLastExecGenId);
        m_dwLastExecGenId--;
    }
    InvalidateRect(NULL, false);
}



/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics
#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

BOOL CTestView::SetBlend(BOOL bBlend)
{
    if (m_cpDXTransform)
    {
        DWORD dwFlags;
        m_cpDXTransform->GetMiscFlags(&dwFlags);
        dwFlags &= (~DXTMF_BLEND_WITH_OUTPUT);
        if (bBlend) dwFlags |= DXTMF_BLEND_WITH_OUTPUT;
        m_cpDXTransform->SetMiscFlags(dwFlags);
        m_cpDXTransform->GetMiscFlags(&dwFlags);
	InvalidateRect(NULL, false);
        return (dwFlags & DXTMF_BLEND_WITH_OUTPUT) != 0;
    }
    else
    {
        return TRUE;
    }
}

BOOL CTestView::GetBlend()
{
    if (m_cpDXTransform)
    {
        DWORD dwFlags;
        m_cpDXTransform->GetMiscFlags(&dwFlags);
        return dwFlags & DXTMF_BLEND_WITH_OUTPUT;
    }
    else
    {
        return TRUE;
    }
}

BOOL CTestView::GetInPlace()
{
    if (m_cpDXTransform)
    {
        DWORD dwFlags;
        m_cpDXTransform->GetMiscFlags(&dwFlags);
        return dwFlags & DXTMF_INPLACE_OPERATION;
    }
    else
    {
        return FALSE;
    }
}

void CTestView::SetBitDepth(int Index)
{
    static BOOL bWarned = FALSE;
    m_BitDepthIndex = Index;
    if (Index == 4 && (!bWarned))
    {
        bWarned = TRUE;
        MessageBox( _T("Windows 95 and Windows 98 GDI do not properly support 4444 pixel format.  Your output will look strange on these systems.  Windows NT 4.0 should work correctly."), _T("GDI Limitation"), MB_OK | MB_ICONINFORMATION );
    }
    Resize2D(m_WndWidth, m_WndHeight);
    Setup(m_fPercentComplete);
}

BOOL CTestView::GetDither()
{
    if (m_cpDXTransform)
    {
        DWORD dwFlags;
        m_cpDXTransform->GetMiscFlags(&dwFlags);
        return dwFlags & DXTMF_DITHER_OUTPUT;
    }
    else
    {
        return TRUE;
    }
}

BOOL CTestView::SetDither(BOOL bDither)
{
    if (m_cpDXTransform)
    {
        DWORD dwFlags;
        m_cpDXTransform->GetMiscFlags(&dwFlags);
        dwFlags &= (~DXTMF_DITHER_OUTPUT);
        if (bDither) dwFlags |= DXTMF_DITHER_OUTPUT;
        m_cpDXTransform->SetMiscFlags(dwFlags);
        m_cpDXTransform->GetMiscFlags(&dwFlags);
	InvalidateRect(NULL, false);
        return (dwFlags & DXTMF_DITHER_OUTPUT) != 0;
    }
    else
    {
        return TRUE;
    }
}

HRESULT CTestView::CreateSubMeshA(void)
{
    static const float fVertices[] =
    {
#define X 2.0f
#define Y 2.0f
#define Z 2.0f
    // Create vertices for a cube, front face.
	X, Y, Z,    // Index 0.  Right, top, front.
#define RTF 0
	-X, Y, Z,   // Index 1.  Left, top, front.
#define LTF 1
	-X, -Y, Z,  // Index 2.  Left, bottom, front.
#define LBF 2
	X, -Y, Z,   // Index 3.  Right, bottom, front.
#define RBF 3

    // Rear face.
	X, Y, -Z,   // Index 4.  Right, top, rear.
#define RTR 4
	-X, Y, -Z,  // Index 5.  Left, top, rear.
#define LTR 5
	-X, -Y, -Z, // Index 6.  Left, bottom, rear.
#define LBR 6
	X, -Y, -Z,  // Index 7.  Right, bottom, rear.
#define RBR 7

    // Additional stuff on top.
	0.0f, 2*Y, 0.0f // Index 8.  Centered above cube.
#define CAC 8
    };

    // Vertices and normals.  
    // Format is # of sets, vertex, v, etc. terminating 0.
    static DWORD scdwIndices[] = 
    {
	4, RTF, LTF, LBF, RBF, 0,	// Front face, traverse CCW.
	4, RTR, RBR, LBR, LTR, 0,	// Rear face.
	4, RTR, LTR, LTF, RTF, 0,	// Top face.
	4, RTR, RTF, RBF, RBR, 0,	// Right face.
	4, LBF, LBR, RBR, RBF, 0,	// Bottom face.
	4, LBF, LTF, LTR, LBR, 0,	// Left face.
	3, CAC, LTR, LTF, 0, 0,	// 3 vertex face on top with two 0's for padding.
	3, CAC, RTF, RTR, 0, 0,	// 3 vertex face on top with two 0's for padding.
    };
    const int iNumFaces = sizeof(scdwIndices)/sizeof(scdwIndices[0])/6;

    static const int iSubMeshes[] = 
    {	-1, // Use root for the parent of this submesh.
	 0, // Use submesh 0 as the parent.
	 0, 
	 0, 
	 1, // Use submesh 1 as the parent.
	 2, 
	 3, 
	 6
    };
    ASSERT(sizeof(iSubMeshes)/sizeof(iSubMeshes[0]) == iNumFaces);

    return CreateSubMeshes(&m_cpInSubMeshA, 
			   fVertices, sizeof(fVertices)/sizeof(fVertices[0])/3,
			   scdwIndices, iNumFaces,
			   iSubMeshes, 6);

#undef X
#undef Y
#undef Z
#undef RTF
#undef LTF
#undef LTB
#undef RBF
#undef RTR
#undef LTR
#undef LBR
#undef RBR
#undef CAC
}
HRESULT CTestView::CreateSubMeshB(void)
{
    static const float fVertices[] =
    {
#define X 2.0f
#define Y 2.0f
#define Z 2.0f
    // Create vertices for the object.
	X, 0.0f, Z,	// Index 0.  Right, center, front.
#define RCF 0
	-X, 0.0f, Z,	// Index 1.  Left, center, front.
#define LCF 1
	0.0f, 0.0f,-Z,	// Index 2.  Center, center, rear.
#define CCR 2
	0.0f, Y, 0.0f,  // Index 3.  Center, top, center.
#define CTC 3
	0.0f,-Y, 0.0f   // Index 4.  Center, bottom, center.
#define CBC 4
    };

    // Vertices and normals.  
    // Format is # of sets, vertex, v, etc. terminating 0.
    static DWORD scdwIndices[] = 
    {
	3, RCF, CTC, LCF, 0,	// Top front, face.
	3, CTC, RCF, CCR, 0,	// Right, top, rear face.
	3, CTC, CCR, LCF, 0,	// Left, top, rear face.
	3, CBC, RCF, LCF, 0,	// Front bottom face..
	3, RCF, CBC, CCR, 0,	// Bottom face.
	3, LCF, CCR, CBC, 0,	// Left rear face.
    };
    const int iNumFaces = sizeof(scdwIndices)/sizeof(scdwIndices[0])/5;

    static const int iSubMeshes[] = 
    {	-1, // Use root for the parent of this submesh.
	 0, // Use submesh 0 as the parent.
	 1, // Deep linear nesting of submeshes.
	 2, 
	 3,
	 4,
    };
    ASSERT(sizeof(iSubMeshes)/sizeof(iSubMeshes[0]) == iNumFaces);

    return CreateSubMeshes(&m_cpInSubMeshB, 
			   fVertices, sizeof(fVertices)/sizeof(fVertices[0])/3,
			   scdwIndices, iNumFaces,
			   iSubMeshes, 5);
#undef X
#undef Y
#undef Z
#undef RCF
#undef LCF
#undef CCR
#undef CTC
#undef CBC
}

HRESULT CTestView::CreateSubMeshes(IDirect3DRMMeshBuilder3 **lplpDestMesh, 
				   const float *lpfVertices, int iNumVertices,
				   DWORD *lpdwMeshFaces, int iNumFaces,
				   const int *lpiSubMeshStructure, DWORD dwMeshDataSize)
{
    int iV, iM;
    HRESULT hr;
    CComPtr<IDirect3DRMMeshBuilder3> *cpSubMeshes = 
	(CComPtr<IDirect3DRMMeshBuilder3> *)new CComPtr<IDirect3DRMMeshBuilder3> [iNumFaces];

    if (m_cpD3DRM == NULL)
    {
	hr = E_FAIL;
	ONFAIL("No D3DRM available.");
    }

    if(!cpSubMeshes)
    {
	hr = E_OUTOFMEMORY;
	ONFAIL("Out of memory.");
    }

    if (FAILED(hr = m_cpD3DRM->CreateMeshBuilder(lplpDestMesh)))
	ONFAIL("CreateMeshBuilder() failed.");

    for(iV = 0; iV < iNumVertices; iV++)
    {
	const int iT = 3 * iV;	// Index into the table.

	(*lplpDestMesh)->AddVertex(lpfVertices[iT], lpfVertices[iT + 1], lpfVertices[iT + 2]);
        (*lplpDestMesh)->AddNormal(0.0f, 0.0f, 1.0f);    // We need normals for place holders.
    }

    for(iM = 0; iM < iNumFaces; iM++)
    {
	LPUNKNOWN lpunkSubmesh;

	// Create multiple levels of submeshes.
	if(lpiSubMeshStructure[iM] < 0)
	{
	    if(FAILED(hr = (*lplpDestMesh)->CreateSubMesh(&lpunkSubmesh)))
	    {
		ONFAIL("CreateSubMesh() failed.");
	    }
	}
	else
	{
	    int iParent = lpiSubMeshStructure[iM];

	    ASSERT(iParent >= 0);
	    ASSERT(iParent < iM);
	    if(FAILED(hr = cpSubMeshes[iParent]->CreateSubMesh(&lpunkSubmesh)))
	    {
		ONFAIL("CreateSubMesh() failed.");
	    }
	}

	hr = lpunkSubmesh->QueryInterface(IID_IDirect3DRMMeshBuilder3, 
						    (void **)&cpSubMeshes[iM]);
	lpunkSubmesh->Release();
	if(FAILED(hr))
	{
	    ONFAIL("QI on Submesh failed.");
	}

	hr = cpSubMeshes[iM]->AddFacesIndexed(D3DRMADDFACES_VERTICESONLY, 
                                              &lpdwMeshFaces[iM * dwMeshDataSize], 
                                              NULL, NULL);
	if(FAILED(hr))
	    ONFAIL("AddFacesIndexed() failed.");

	hr = cpSubMeshes[iM]->SetAppData(iM);
	if(FAILED(hr))
	    ONFAIL("SubMesh SetAppData() failed.");

	static const D3DVALUE d3dvColorTable[] =
	{
	    1.0f, 0.0f, 0.0f,
	    0.0f, 1.0f, 0.0f,
	    1.0f, 1.0f, 0.0f,
	    0.0f, 0.0f, 1.0f,
	    1.0f, 0.0f, 1.0f,
	    0.0f, 1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    0.5f, 0.0f, 0.0f,
	    0.0f, 0.5f, 0.0f,
	    0.5f, 0.5f, 0.0f,
	    0.0f, 0.0f, 0.5f,
	    0.5f, 0.0f, 0.5f,
	    0.0f, 0.5f, 0.5f,
	    0.5f, 0.5f, 0.5f
	};
	
	const int iTableIndex = (iM * 3) % // If we run out of color table entries, wrap.
	    (sizeof(d3dvColorTable)/sizeof(d3dvColorTable[0]));

	if(FAILED(hr = cpSubMeshes[iM]->SetColorRGB(d3dvColorTable[iTableIndex],
						    d3dvColorTable[iTableIndex + 1],
						    d3dvColorTable[iTableIndex + 2])))
	{
	    ONFAIL("SubMesh SetColor() failed.");
	}
    }

    if(FAILED(hr = (*lplpDestMesh)->GenerateNormals(0.0f, 0)))
    {
        ONFAIL("GenerateNormals() failed.");
    }

e_Exit:
    if (FAILED(hr)) 
    {
	DisplayMessage(hr, NULL, NULL);
    }
    delete []cpSubMeshes;
    return hr;
}

void CTestView::WhichMeshView(WHICHMESH eWhich)
{
    m_eWhichMesh = eWhich;
    DisplayMessage(ReCreateMesh(), NULL, NULL);
}
HRESULT CTestView::SubMeshInput(DWORD dwWhichInput)
{
    HRESULT hr = S_OK;

    if(!m_cpD3DRM)
    {
	return E_FAIL;
    }

    switch (dwWhichInput)
    {
    case 0:
	if(!m_cpInMeshA)
	{
	    if(FAILED(hr = m_cpD3DRM->CreateMeshBuilder(&m_cpInMeshA)))
	    {
		break;
	    }
	}
	ASSERT(m_cpInMeshA);
	if(SUCCEEDED(hr = m_cpInMeshA->Empty(0)))
	{
	    hr = m_cpInMeshA->AddMeshBuilder(m_cpInSubMeshA,0);
	}
	break;
    case 1:
	if(!m_cpInMeshB)
	{
	    if(FAILED(hr = m_cpD3DRM->CreateMeshBuilder(&m_cpInMeshB)))
	    {
		break;
	    }
	}
	ASSERT(m_cpInMeshB);
	if(SUCCEEDED(hr = m_cpInMeshB->Empty(0)))
	{
	    m_cpInMeshB->AddMeshBuilder(m_cpInSubMeshB,0);
	}
	break;
    default:
	ASSERT(0);
	break;
    }

    if(SUCCEEDED(hr))
	hr = Setup(m_fPercentComplete);

    InvalidateRect(NULL, false);

    return hr;
}

void CTestView::ZeroPosition()
{
    ASSERT(m_cpframeVisual);
    m_cpframeVisual->SetPosition(m_cpframeScene, 0.0f, 0.0f, 0.0f);
    m_cpframeVisual->SetOrientation(m_cpframeScene, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

    if(m_bOutputGeo && m_cpOutMesh)
    {
        // Apply some hueristics to reposition the camera to a pleasant location.
	D3DRMBOX d3dboxObject;

	m_cpOutMesh->GetBox(&d3dboxObject);

        float fCamDist = d3dboxObject.max.x > d3dboxObject.max.y? 
            d3dboxObject.max.x: d3dboxObject.max.y;

        if (fCamDist < -d3dboxObject.min.x)
            fCamDist = -d3dboxObject.min.x;
            
        if (fCamDist < -d3dboxObject.min.y)
            fCamDist = -d3dboxObject.min.y;
            
        fCamDist += d3dboxObject.max.z + fCAMDIST;

        m_cpframeCamera->SetPosition(m_cpframeScene, 0.0f, 0.0f, fCamDist);
        m_cpframeLightArm->SetPosition(m_cpframeLight, 0.0f, 0.0f, fCamDist);
    }

    InvalidateRect(NULL, false);
}

void CTestView::SetPlacement(int i)
{
    m_iPlace = i;
    ReExecuteTransform();
}

void CTestView::SetClip(int i)
{
    m_iClip = i;
    ReExecuteTransform();
}

void CTestView::SetScaleOutput(BOOL bScaleOut)
{
    m_bScaleToOut = bScaleOut;
    if (m_bScaleToOut && m_cpDXScaleOutput)
    {
        SIZE sz;
        sz.cx = m_WndWidth;
        sz.cy = m_WndHeight;
        m_cpDXScaleOutput->SetOutputSize(sz, FALSE);
        ReExecuteTransform();
    }
}