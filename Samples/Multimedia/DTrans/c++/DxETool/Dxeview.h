// DxeView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__53BE8357_4A55_11D1_81AA_0000F87557DB__INCLUDED_)
#define AFX_TESTVIEW_H__53BE8357_4A55_11D1_81AA_0000F87557DB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTestCntrItem;

enum	WHICHMESH {WHICHMESH_OUTPUT, WHICHMESH_A, WHICHMESH_B};

class CTestView : public CView
{

protected: // create from serialization only
							CTestView();

	DECLARE_DYNCREATE(CTestView)

public:
	HRESULT		CreateRenderer();
	HRESULT		CreateTransformFactory();
	HRESULT		CreateDefaultContent();
	void		DisplayMessage(HRESULT hr, const char *szMsg, CDC *pDC);

public:
	CComPtr<IDXTransformFactory>	m_cpTransFact;
	CComPtr<IDXSurfaceFactory>		m_cpSurfFact;
	CComPtr<IDirectDraw>			m_cpDD;
	CComPtr<IDirect3DRM3>			m_cpD3DRM;
	CComPtr<IDirectDrawSurface>		m_cpPrimarySurface;
	CComPtr<IDirectDrawClipper>		m_cpClipper;

	CComPtr<IDirect3DRMDevice3> 	m_cpD3DDevice;
	CComPtr<IDirect3DRMFrame3>		m_cpframeScene;
	CComPtr<IDirect3DRMFrame3>		m_cpframeLight;
	CComPtr<IDirect3DRMFrame3>		m_cpframeLightArm;
	CComPtr<IDirect3DRMFrame3>		m_cpframeCamera;
	CComPtr<IDirect3DRMFrame3>		m_cpframeVisual;
	CComPtr<IDirect3DRMLight>		m_cpLight;
	CComPtr<IDirect3DRMViewport2>	m_cpViewport;
	CComPtr<IDirectDrawSurface>		m_cpdds3DOut;
	CComPtr<IDirect3DRMMeshBuilder3> m_cpOutMesh;

	CComPtr<IDXSurface>				m_cpdxs2DOut;

	CComPtr<IDXTransform>			m_cpDXTransform;
	CComPtr<IDXEffect>			m_cpDXEffect;
        CComPtr<IDXTScaleOutput>                m_cpDXScaleOutput;

	CComPtr<ISpecifyPropertyPages>	m_cpSpecifyPropertyPages; 

	CComPtr<IDXSurface>				m_cpInSurf[2];
        int                                             m_InSurfBitDepth[2];
        CComPtr<IDXSurface>                             m_cpBitDepthCorrectInSurf[2];
	CComPtr<IDirect3DRMMeshBuilder3> m_cpInMeshA;
	CComPtr<IDirect3DRMMeshBuilder3> m_cpInMeshB;
	CComPtr<IDirect3DRMMeshBuilder3> m_cpInSubMeshA;
	CComPtr<IDirect3DRMMeshBuilder3> m_cpInSubMeshB;
        BOOL        m_bFillAll;

        CComPtr<IDXTransform>           m_cpGradient;    

	long    m_WndWidth, m_WndHeight;   // These should be signed to make placement computations work correctly!
	float	m_fPercentComplete;
	CPoint	m_pointLastMouse;

	DWORD	m_dwLastExecGenId;
	BOOL	m_bInput0Req, m_bInput1Req;
	BOOL	m_bOutputGeo, m_bInput0Geo, m_bInput1Geo;
        BOOL    m_bScaleToOut;

	ULONG	m_ulNumInputs;

	BOOL	m_bRotating, m_bZooming, m_bSliding, m_bInitializingTransform;

	TCHAR *	m_szSetupError;
	GUID	m_ClsId;	    // Class ID of current transform.

	bool	m_bSpotlight;
	BOOL	m_bBoundsChecking;
        BOOL    m_bDontRender;
	DWORD	m_nInputsDefined;
	DWORD	m_nInputsRequired;
	DWORD	m_nInputsDesired;
	DWORD	m_nInputsPossible;
	DWORD	m_nCurInputsUsed;
	WHICHMESH m_eWhichMesh;

// Implementation
public:
	void		WhichMeshView(WHICHMESH eWhich);
	WHICHMESH	WhichMeshView() {return m_eWhichMesh;}
	HRESULT		LoadTexture(OLECHAR *pszFilename, IDXSurface **ppNewSurf);
	void		SetPercentComplete(float fPercentComplete, const RECT *pInvalidate = NULL);
	float		GetPercentComplete(void) { return m_fPercentComplete; }
	HRESULT		Setup(float fPercentComplete);
	HRESULT		ResetTransform() { return SetTransform(m_ClsId); }
	HRESULT		SetTransform(const CLSID & clsid);
	void		ReExecuteTransform();
	HRESULT		SetDesiredInputs(DWORD nInputs);
	HRESULT		SetFlatShading(BOOL bNewVal);
	HRESULT		Resize(DWORD nX, DWORD nY);
	HRESULT		Render3DScene(IDirectDrawSurface **ppdds, bool bExecute);
	HRESULT		Create3DScene();
	HRESULT		Resize3D(DWORD nX, DWORD nY);
	HRESULT		Render2DScene(IDirectDrawSurface **ppdds, bool bExecute, const RECT &);
	HRESULT		Resize2D(DWORD nX, DWORD nY);
	HRESULT		ReCreateMesh();

	HRESULT		LoadImage(DWORD nSurface, OLECHAR *osPath);
	HRESULT		LoadMesh(DWORD nMesh, LPCTSTR szPath);

	void		RotateFrame(float dX, float dY, IDirect3DRMFrame3 *pFrame);
	void		MoveLight(float dX, float dY, UINT nFlags);
	void		Quality(float fQual, const RECT *pInvalidate = NULL);
	float		Quality(void) {return m_fQuality;}

private:
	HRESULT		CreateSubMeshA(void);
	HRESULT		CreateSubMeshB(void);
	HRESULT		CreateSubMeshes(IDirect3DRMMeshBuilder3 **lpDestMesh, 
				   const float *lpfVertices, int iNumVertices,
				   DWORD *lpdwMeshFaces, int iNumFaces,
				   const int *lpiSubMeshStructure, DWORD dwMeshDataSize);
	HRESULT         LoadXFile(const char *szfilename, IDirect3DRMMeshBuilder3* pMeshBuilderDest);
        float	m_fQuality;

public:
	void SetClip(int i);
	int m_iClip;
	int m_iPlace;
        BOOL m_bEnableClip;
        BOOL m_bEnablePlacement;
	void SetPlacement(int i);
	BOOL SetDither(BOOL bDither);
	BOOL GetDither(void);
	void ZeroPosition(void);
	HRESULT SubMeshInput(DWORD dwWhichInput);
        BOOL Get2DOutRect(RECT & r);

        HRESULT SetInputBitDepth(ULONG ulSurface, int BitDepthIndex);
	void SetBitDepth(int Index);
	int m_BitDepthIndex;
	BOOL GetBlend(void);
	BOOL SetBlend(BOOL bBlend);
	BOOL GetInPlace(void);
	BOOL GetBoundsChecking(void) {return m_bBoundsChecking;}
	BOOL SetBoundsChecking(BOOL bBoundsChecking) {return m_bBoundsChecking = bBoundsChecking;}
        void SetScaleOutput(BOOL bScaleOutput);
        void GetBoundsAndPlacement(CDXDBnds & bnds, CDXDVec & place);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//}}AFX_VIRTUAL


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
        afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLightSpot();
	afx_msg void OnUpdateLightSpot(CCmdUI* pCmdUI);
        afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__53BE8357_4A55_11D1_81AA_0000F87557DB__INCLUDED_)
