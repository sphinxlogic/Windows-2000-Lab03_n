// Flip.cpp : Implementation of CFlip
#include "stdafx.h"
#include <dxtmsft.h>
#include "Flip.h"

/////////////////////////////////////////////////////////////////////////////
// CFlip
CFlip::CFlip()
{
    //Two surfaces can be input for the transition, one is required
    //A mesh builder is output
    m_ulMaxInputs = 2;
    m_ulNumInRequired = 1;
    m_dwOptionFlags = DXBOF_OUTPUT_MESHBUILDER;
    m_dwMiscFlags = 0;
    m_flDepth = 1.0f;
    m_flWidth  = 2.0f;
    m_flHeight = 2.0f;
#if(_ATL_VER >= 0x0300)
    m_bRequiresSave = FALSE;
#endif
};

// Object is this wide, tall, and deep.  Centered at 0,0, -m_flDepth/2.

HRESULT CFlip::DetermineBnds(CDXCBnds & Bnds)
{
    // Normal case.
    Bnds[DXB_X].Min = -m_flWidth/2;
    Bnds[DXB_X].Max = m_flWidth/2;

    Bnds[DXB_Y].Min = -m_flHeight/2;
    Bnds[DXB_Y].Max = m_flHeight/2;

    Bnds[DXB_Z].Min = -m_flDepth;
    Bnds[DXB_Z].Max = 0.0;

    if(m_ulNumInputs == 1 ||
       (m_ulNumInputs >= 2 && !InputSurface(1))) // Special case?
    {
	if(m_Progress == 1.0)
	{
	    Bnds[DXB_Z].Max = -m_flDepth;
	}else
	if(m_Progress == 0.0)
	{
	    Bnds[DXB_Z].Min = 0.0f;
	}
    }

    return S_OK;
}

HRESULT CFlip::UpdateVertices(LPDIRECT3DRMMESHBUILDER3 lpMBlder, float Percent, BOOL bIsB)
{
    DWORD dwIndex = bIsB? 4: 0;

    if (bIsB) {
        Percent = 1.0f - Percent;
    }

    float zPos[2] = {0.0f, 0.0f};
    if (Percent <= 0.5f) {
        zPos[1] = (0.5f - (0.5f - Percent)) * -m_flDepth * 2.0f;
    } else {
        zPos[0] = (Percent - 0.5f) * -m_flDepth * 2.0f;
        zPos[1] = -m_flDepth;
    }
    
    if (!bIsB) {
        float t = zPos[0];
        zPos[0] = zPos[1];
        zPos[1] = t;
    }

    // Traverse CCW around face.  Lower left, then lower right, then upper right, then upper left.
    HRESULT hr = lpMBlder->SetVertex(dwIndex++, -m_flWidth/2.0f, -m_flHeight/2.0f, zPos[0]);
    if(FAILED(hr))
    {
	return hr;
    }
    hr = lpMBlder->SetVertex(dwIndex++, m_flWidth/2.0f, -m_flHeight/2.0f, zPos[1]);
    if(FAILED(hr))
    {
	return hr;
    }
    hr = lpMBlder->SetVertex(dwIndex++, m_flWidth/2.0f, m_flHeight/2.0f, zPos[1]);
    if(FAILED(hr))
    {
	return hr;
    }
    hr = lpMBlder->SetVertex(dwIndex, -m_flWidth/2.0f, m_flHeight/2.0f, zPos[0]);

    return hr;
}

HRESULT CFlip::OnSetup(DWORD dwFlags)
{
    const int iNumInputs = (m_ulNumInputs > 1 && InputSurface(1))? 2: 1;
    const int iNumVertices = iNumInputs > 1? 8: 4;
    const int iNumFaces = iNumVertices/4;

    CComPtr<IDirect3DRMTexture3> cpTextureA;
    CComPtr<IDirect3DRMTexture3> cpTextureB;

    _ASSERT(InputSurface(0));

    HRESULT hr = m_cpSurfFact->CreateD3DRMTexture( InputSurface(0), m_cpDirectDraw,
                                                   m_cpDirect3DRM, IID_IDirect3DRMTexture3,
                                                   (void**)&cpTextureA);
    if (FAILED(hr))
    {
    	return hr;
    }

    if(iNumInputs > 1)
    {
	    _ASSERT(InputSurface(1));

	    hr = m_cpSurfFact->CreateD3DRMTexture( InputSurface(1), m_cpDirectDraw,
                                               m_cpDirect3DRM, IID_IDirect3DRMTexture,
                                               (void**)&cpTextureB);

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
    hr = OutputMeshBuilder()->ReserveSpace(iNumVertices, iNumVertices, iNumFaces);
    if (FAILED(hr))
    {
	return hr;
    }

    OutputMeshBuilder()->AddNormal(0,0,1);
    int i;
    for(i = 0; i < iNumVertices; i++)
    {
	int iRetVal = OutputMeshBuilder()->AddVertex(0,0,0);	// Just garbage value for now.
	_ASSERT(iRetVal == i);	// We depend on the order in which these are stored.
    }

    // Create the face(s), add the vertices, normals, and texture(s), then add the face(s).
    // One face per surface/texture, four vertices per face.
    for(i = 0; i < iNumFaces && SUCCEEDED(hr); i++)
    {
        CComPtr<IDirect3DRMFace2> cpFace;

	hr = OutputMeshBuilder()->CreateFace(&cpFace);

	if(SUCCEEDED(hr))
	{   // We have a face.
	    _ASSERT(i < 2);
	    hr = cpFace->SetTexture(i == 0? cpTextureA: cpTextureB);
	    if(SUCCEEDED(hr))
	    {   // Texture has been added to the face.

		int iVIndex = 0;
		do
		{
		    hr = cpFace->AddVertexAndNormalIndexed(iVIndex + 4 * i, 0);

		    if(SUCCEEDED(hr))
		    {	// We have another vertex.
			// U and V coordinates go CCW around texture starting at lower left.
			// Texture has positive Y as down.
			static D3DVALUE d3dvTexU[] = {0.0, 1.0, 1.0, 0.0};
			static D3DVALUE d3dvTexV[] = {1.0, 1.0, 0.0, 0.0};

			_ASSERT(iVIndex < sizeof(d3dvTexU)/sizeof(d3dvTexU[0]));
			hr = cpFace->SetTextureCoordinates(iVIndex, d3dvTexU[iVIndex], d3dvTexV[iVIndex]);
		    }
		} while(++iVIndex < 4 && SUCCEEDED(hr));
	    }
	}
    }

    if(SUCCEEDED(hr))
    {
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

    }
    return hr;
} // OnSetup


HRESULT CFlip::OnExecute(const GUID* /* pRequestID */,
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
    if(SUCCEEDED(hr) && m_ulNumInputs > 1 && InputSurface(1))
    {
	hr = UpdateVertices(OutputMeshBuilder(), m_Progress, 1);  // Do the B texture.
    }

    return hr;
}

STDMETHODIMP CFlip::get_Depth(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_flDepth;
    return S_OK;
}

STDMETHODIMP CFlip::put_Depth(float newVal)
{
    Lock();
    m_flDepth = newVal;
    SetDirty();
    Unlock();

    return S_OK;
}

STDMETHODIMP CFlip::get_Width(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_flWidth;
    return S_OK;
}

STDMETHODIMP CFlip::put_Width(float newVal)
{
    if(newVal <= 0.0f)
        return E_INVALIDARG;

    Lock();
    m_flWidth = newVal;
    SetDirty();
    Unlock();

    return S_OK;
}

STDMETHODIMP CFlip::get_Height(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_flHeight;
    return S_OK;
}

STDMETHODIMP CFlip::put_Height(float newVal)
{
    if(newVal <= 0.0f)
        return E_INVALIDARG;

    Lock();
    m_flHeight = newVal;
    SetDirty();
    Unlock();

    return S_OK;
}
