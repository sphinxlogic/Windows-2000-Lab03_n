// Dissolve.cpp : Implementation of CDissolve
#include "stdafx.h"
#include "Dissolve.h"

#define DEFAULT_XVERTICES 15
#define DEFAULT_YVERTICES 2

// Object is this wide, tall, and deep.  Centered at 0,0, -gc_flDepth/2.
static const float gc_flWidth  = 2.0f;
static const float gc_flHeight = 2.0f;
static const float gc_flDepth = 0.02f;


// See comments in the header file for what the values mean.
static float sDefaultBaseRate[] =
{
    1.2f, 1.0f, 1.5f, 1.75f, 2.0f, 
    2.0f, 1.75f, 1.5f, 1.0f, 1.2f
};

/////////////////////////////////////////////////////////////////////////////
// CDissolve
CDissolve::CDissolve()
{
    //Two surfaces can be input for the transition, one is required
    //A mesh builder is output
    m_ulMaxInputs = 2;
    m_ulNumInRequired = 1;
    m_dwOptionFlags = DXBOF_OUTPUT_MESHBUILDER;
    m_dwMiscFlags = 0;
    m_iXVertices = DEFAULT_XVERTICES;
    m_iYVertices = DEFAULT_YVERTICES;
    _ASSERT(sizeof(m_BaseRate) == sizeof(sDefaultBaseRate));
    memcpy(m_BaseRate,sDefaultBaseRate, sizeof(m_BaseRate));
    m_Duration = 3.0f;	// Suggested duration.
    m_iDirection = 1;	// Down.  -1 == up.
#if(_ATL_VER >= 0x0300)
    m_bRequiresSave = FALSE;
#endif
};


HRESULT CDissolve::DetermineBnds(CDXCBnds & Bnds)
{
    Bnds[DXB_X].Min = -gc_flWidth/2;
    Bnds[DXB_X].Max = gc_flWidth/2;

    Bnds[DXB_Y].Min = -gc_flHeight/2;
    Bnds[DXB_Y].Max = gc_flHeight/2;

    Bnds[DXB_Z].Min = -gc_flDepth;
    Bnds[DXB_Z].Max = 0;

    return S_OK;
}

HRESULT CDissolve::UpdateVertices(LPDIRECT3DRMMESHBUILDER3 lpMBlder, float Percent, BOOL isB)
{
    const float zCoord = isB? -gc_flDepth: 0.0f;
    float *RateArray = (float *)_alloca(m_iXVertices * sizeof(*RateArray));
    HRESULT hr = RateArray? S_OK: E_OUTOFMEMORY;

    if(FAILED(hr))
    {
	return hr;
    }


    // Map the base rate of dissolve to the X vertices.
    // This is a simple linear interpolation between adjacent bBaseRate data mapped to 
    // the RateArray.
    int iX = m_iXVertices - 1;
    const float MappingConst = (DXEFFECT_MSFT_DISSOLVE_NUM_RATES - 1.0f)/iX;

    do
    {
	int iRateIndex = (int) (iX * MappingConst);  // Find the nearest lower index into m_BaseRate.
	if(iRateIndex > DXEFFECT_MSFT_DISSOLVE_NUM_RATES - 2)
	{
	    iRateIndex = DXEFFECT_MSFT_DISSOLVE_NUM_RATES - 2;
	}
	// Now the slope between the two base rates.
	float Slope = m_BaseRate[iRateIndex + 1] - m_BaseRate[iRateIndex];
	// The offset between the two.
	float Offset = m_BaseRate[iRateIndex] - Slope * iRateIndex;

	// Simple "y = x * slope + offset" interpolation, with percent complete factored in.
	RateArray[iX] = 1.0f - Percent * (iX * MappingConst * Slope + Offset) * m_iDirection;
	if(RateArray[iX] < 0.0f)
	{
	    RateArray[iX] = 0.0f;
	}
    }while(--iX >= 0);

// BUG BUG Direction stuff not fully implemented!

    int iIndex = 0;
    int iY;
    for(iY = 0; iY < m_iYVertices; iY++)
    {
	float y = gc_flHeight * (float)iY/(m_iYVertices - 1);

	for(iX = 0; iX < m_iXVertices; iX++)
	{
	    _ASSERT(RateArray[iX] >= 0.0f);
	    _ASSERT(RateArray[iX] <= 1.0f);
	    lpMBlder->SetVertex(iIndex++, gc_flWidth * ((float)iX/(m_iXVertices - 1) - 0.5f), 
		(y * RateArray[iX] - gc_flHeight/2.0f), zCoord);
	}
    }

    return hr;
}

HRESULT CDissolve::OnSetup(DWORD dwFlags)
{
    const int iNumInputs = (m_ulNumInputs > 1 && InputSurface(1))? 2: 1;
    const int iNumVertices = iNumInputs * m_iXVertices * m_iYVertices;
    const int iNumFacesPerInput = (m_iXVertices - 1) * (m_iYVertices - 1);

    _ASSERT(InputSurface(0));

    CComPtr<IDirect3DRMTexture3> cpTextureA;
    CComPtr<IDirect3DRMTexture3> cpTextureB;

    HRESULT hr = m_cpSurfFact->CreateD3DRMTexture( InputSurface(0), m_cpDirectDraw, 
                                    		       m_cpDirect3DRM, IID_IDirect3DRMTexture3,
                                                   (void**)&cpTextureA );
    if (FAILED(hr))
    {
    	return hr;
    }

    if(iNumInputs > 1)
    {
	    _ASSERT(InputSurface(1));
	    hr = m_cpSurfFact->CreateD3DRMTexture( InputSurface(1), m_cpDirectDraw,
                                               m_cpDirect3DRM, IID_IDirect3DRMTexture,
                                               (void**)&cpTextureB );
	    if (FAILED(hr))
	    {
	        return hr;
	    }
    }

    hr = OutputMeshBuilder()->Empty(0);
    if (FAILED(hr))
    {
    	return hr;
    }

    // Make things go faster.
    hr = OutputMeshBuilder()->ReserveSpace(iNumVertices, iNumVertices, 
	iNumFacesPerInput * iNumInputs);
    if (FAILED(hr))
    {
	return hr;
    }

    OutputMeshBuilder()->AddNormal(0.0f, 0.0f, 1.0f);	// Only need one.
    int i;
    for(i = 0; i < iNumInputs; i++)
    {
	const float zCoord = -i * gc_flDepth;

    // Add vertices from left to right then bottom to top.
	int y;
	for(y = 0; y < m_iYVertices; y++)
	{
	    const float yCoord = gc_flHeight * ((float)y/(float)(m_iYVertices - 1) - 0.5f);

	    int x;
	    for(x = 0; x < m_iXVertices; x++)
	    {
		int iRetVal = OutputMeshBuilder()->AddVertex(
		    gc_flWidth * ((float)x/(float)(m_iXVertices - 1) - 0.5f),
		    yCoord,
		    zCoord);

		// We depend on the order in which these are stored.
		_ASSERT(iRetVal == i * m_iXVertices * m_iYVertices + y * m_iXVertices + x);
	    }
	}

	/* Vertices of previous 'page' */ 
	const int iPrevVertices = i * m_iXVertices * m_iYVertices;

	// Create the face(s), add the vertices, normals, and texture(s) to the face.
	for(y = 0; y < m_iYVertices - 1; y++)
	{
	    int x;

	    for(x = 0; x < m_iXVertices - 1; x++)
	    {
		CComPtr<IDirect3DRMFace2> cpFace;

		hr = OutputMeshBuilder()->CreateFace(&cpFace);
		if(FAILED(hr))
		{
		    return hr;
		}
		// We have a valid face.

		_ASSERT(i <= 1);
		hr = cpFace->SetTexture(i == 0? cpTextureA: cpTextureB);
		if(FAILED(hr))
		{
		    return hr;
		}
		// Texture has been added to the face.


		/***********
		Now input the vertices and texture coordinations in a CCW manner. 
		***********/
		const float XDivsor = m_iXVertices - 1.0f;
		const float YDivsor = m_iYVertices - 1.0f;

		// First the lower left corner.
		int iIndex = y * m_iXVertices + x + iPrevVertices;

		hr = cpFace->AddVertexAndNormalIndexed(iIndex, 0);
		if(FAILED(hr))
		{
		    return hr;
		}
		// Texture has positive Y as down.
		hr = cpFace->SetTextureCoordinates(0, x/XDivsor, 1.0f - y/YDivsor);
		if(FAILED(hr))
		{
		    return hr;
		}

		// Lower right corner.
		hr = cpFace->AddVertexAndNormalIndexed(iIndex + 1, 0);
		if(FAILED(hr))
		{
		    return hr;
		}
		hr = cpFace->SetTextureCoordinates(1, (x + 1)/XDivsor, 1.0f - y/YDivsor);
		if(FAILED(hr))
		{
		    return hr;
		}

		// Upper right corner.
		hr = cpFace->AddVertexAndNormalIndexed(iIndex + m_iXVertices + 1, 0);
		if(FAILED(hr))
		{
		    return hr;
		}
		hr = cpFace->SetTextureCoordinates(2, (x + 1)/XDivsor, 1.0f - (y + 1)/YDivsor);
		if(FAILED(hr))
		{
		    return hr;
		}

		// Upper left corner.
		hr = cpFace->AddVertexAndNormalIndexed(iIndex + m_iXVertices, 0);
		if(FAILED(hr))
		{
		    return hr;
		}
		hr = cpFace->SetTextureCoordinates(3, x/XDivsor, 1.0f - (y + 1)/YDivsor);
		if(FAILED(hr))
		{
		    return hr;
		}
	    }
	}
    }

    hr = UpdateVertices(OutputMeshBuilder(), 0.0f, 0);  // Do the A texture.
    if(FAILED(hr))
    {
	return hr;
    }
    if(iNumInputs > 1)
    {
	hr = UpdateVertices(OutputMeshBuilder(), 0.0f, 1);  // Do the B texture.
	if(FAILED(hr))
	{
	    return hr;
	}
    }
    hr = OutputMeshBuilder()->GenerateNormals(0.0f, 0);
    if(SUCCEEDED(hr))
    {
	ClearDirty();
    }

    return hr;
} // OnSetup


HRESULT CDissolve::OnExecute(const GUID* /* pRequestID */,
                         const DXBNDS * /* pClipBnds */,
                         const DXVEC * /* pPlacement */)
{
    HRESULT hr;

    if (IsInputDirty())
    {
        hr = OnSetup(0);    // OnSetup() clears the dirty flag if it was successful.
        if (FAILED(hr))
	{
            return hr;
        }
    }

    hr = UpdateVertices(OutputMeshBuilder(), m_Progress, 0);  // Do the A texture.

    return hr;
}


STDMETHODIMP CDissolve::get_SpeedPt0(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[0];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt0(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[0] = newVal;
    return S_OK;
}

STDMETHODIMP CDissolve::get_SpeedPt1(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[1];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt1(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[1] = newVal;
    return S_OK;
}

STDMETHODIMP CDissolve::get_SpeedPt2(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[2];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt2(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[2] = newVal;
    return S_OK;
}

STDMETHODIMP CDissolve::get_SpeedPt3(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[3];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt3(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[3] = newVal;
    return S_OK;
}

STDMETHODIMP CDissolve::get_SpeedPt4(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[4];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt4(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[4] = newVal;
    return S_OK;
}

STDMETHODIMP CDissolve::get_SpeedPt5(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[5];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt5(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[5] = newVal;
    return S_OK;
}

STDMETHODIMP CDissolve::get_SpeedPt6(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[6];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt6(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[6] = newVal;
    return S_OK;
}

STDMETHODIMP CDissolve::get_SpeedPt7(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[7];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt7(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[7] = newVal;
    return S_OK;
}

STDMETHODIMP CDissolve::get_SpeedPt8(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[8];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt8(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[8] = newVal;
    return S_OK;
}

STDMETHODIMP CDissolve::get_SpeedPt9(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_BaseRate[9];
    return S_OK;
}

STDMETHODIMP CDissolve::put_SpeedPt9(float newVal)
{
    if(newVal < 0.0f || newVal > 100.0f)
	return E_INVALIDARG;

    m_BaseRate[9] = newVal;
    return S_OK;
}
