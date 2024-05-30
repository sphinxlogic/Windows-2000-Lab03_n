// CRipple.cpp : Implementation of CRipple
#include "stdafx.h"
#include "Ripple.h"
#include "CRipple.h"

#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CRipple


// Amount to rotate per frame.
#define M_PI                  3.14159265359f
#define M_2PI                 6.28318530718f
#define ROTATE_ANGLE_DELTA    (M_2PI / 300.0f)
#define TARGET_WIDTH            2.0
#define TARGET_HEIGHT           2.0

CRipple::CRipple() :
    m_group(0),
    m_prgvert(NULL),
    m_XOrigin(0.0),
    m_YOrigin(0.0),
    m_Amplitude(0.5),
    m_NumWaves(10),
    m_Wavelength(1.0),
    m_pflDistanceTable(0),
    m_MinSteps(5),
    m_MaxSteps(50),
    m_flWidth(TARGET_WIDTH),
    m_flHeight(TARGET_HEIGHT),
    m_Steps(5 + (45/2))
{
    m_dwOptionFlags = DXBOF_OUTPUT_MESHBUILDER;
    m_dwMiscFlags = DXTMF_QUALITY_SUPPORTED;
    m_ulMaxInputs = 1;
    m_ulNumInRequired = 1;
    m_Duration = 3.0f;	// Suggested duration.
#if(_ATL_VER >= 0x0300)
    m_bRequiresSave = FALSE;
#endif
}

	
STDMETHODIMP CRipple::SetQuality(float fQuality)
{
	float fOld = m_fQuality;
	HRESULT hr = CDXBaseNTo1::SetQuality(fQuality);
	if (SUCCEEDED(hr) && fQuality != fOld)
	{
		IncrementGenerationId(TRUE);	// Force a re-setup
	}
	return hr;
}


void CRipple::FinalRelease()
{
    if (m_prgvert) {
        delete[] m_prgvert;
    }
    if (m_pflDistanceTable) {
        delete[] m_pflDistanceTable;
    }
}

float CRipple::GetCurrentAmplitude(void)
{
    if (m_Progress == 0.0f || m_Progress == 1.0f) {
	return 0.0f;
    }
    if (m_Progress <= 0.25f) {
        return m_Amplitude * (1.0f - ((0.25f - m_Progress) * 4.0f));
    } 

    return m_Amplitude * (1.0f - ((m_Progress - 0.25f) / 3.0f * 4.0f));
}
HRESULT CRipple::DetermineBnds(CDXCBnds & Bnds)
{   // Input Bnds is a unit cube.  Scale it by proper amount.
    Bnds.Scale(m_flWidth/2.0f, m_flHeight/2.0f, GetCurrentAmplitude());

    return S_OK;
}

HRESULT CRipple::OnSetup(DWORD)
{
    HRESULT         hr = S_OK;
    int             x;
    int             y;

    hr = InitializeBitmap();
    if (FAILED(hr)) {
        return hr;
    }

    hr = OutputMeshBuilder()->Empty(0);
    if (FAILED(hr))
    {
	return hr;
    }

    // Compute number of steps in each direction based on Quality.
    m_Steps = m_MinSteps + (long)((m_MaxSteps - m_MinSteps) * m_fQuality);
    m_cVertices = (m_Steps + 1) * (m_Steps + 1);

    // Number of polygons
    int cPolys = m_Steps * m_Steps * 2;

    // Reserve space for the output polygons, vertices and normals...
    hr = OutputMeshBuilder()->ReserveSpace(m_cVertices, m_cVertices, cPolys);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = Reset();
    if (FAILED(hr)) {
        return hr;
    }

    // Add all the vertices and normals. We assume the indices of the
    // vertices increase monotonically from zero.
    for (long i = 0; i < m_cVertices; i++)
    {
        int iVertex = OutputMeshBuilder()->AddVertex(m_prgvert[i].position.x,
                                               m_prgvert[i].position.y,
                                               m_prgvert[i].position.z);
	_ASSERT(iVertex == i);
        hr = OutputMeshBuilder()->SetTextureCoordinates(iVertex, m_prgvert[i].tu, m_prgvert[i].tv);
        if (FAILED(hr))
        {
            return hr;
        }
        int iNormal = OutputMeshBuilder()->AddNormal(m_prgvert[i].normal.x,
                                               m_prgvert[i].normal.y,
                                               m_prgvert[i].normal.z);
        _ASSERT(iNormal == i);
    }

    //
    //  Generate the polygons.
    //
    for (y = 0; y < m_Steps; y++)
    {
        for (x = 0; x < m_Steps; x++)
        {
            IDirect3DRMFace2 *pFace = NULL;
            hr = m_cpDirect3DRM->CreateFace(&pFace);
            if (FAILED(hr))
            {
                return hr;
            }

            hr = OutputMeshBuilder()->AddFace(pFace);
            if (FAILED(hr))
            {
                return hr;
            }

	    // First vertex is bottom left.
            int index = (y * (m_Steps + 1)) + x;
            hr = pFace->AddVertexAndNormalIndexed(index, index);
            if (FAILED(hr))
            {
                return hr;
            }
	    // Second vertex is one to the right.
            index = (y * (m_Steps + 1)) + x + 1;
            hr = pFace->AddVertexAndNormalIndexed(index, index);
            if (FAILED(hr))
            {
                return hr;
            }
	    // Third vertex is one up on the left.  Hence we wind in a CCW manner.
            index = ((y + 1) * (m_Steps + 1)) + x;
            hr = pFace->AddVertexAndNormalIndexed(index, index);
            if (FAILED(hr))
            {
                return hr;
            }
            pFace->Release();

            hr = m_cpDirect3DRM->CreateFace(&pFace);
            if (FAILED(hr))
            {
                return hr;
            }

            hr = OutputMeshBuilder()->AddFace(pFace);
            if (FAILED(hr))
            {
                return hr;
            }
	    // One up and one to the right.
            index = ((y + 1) * (m_Steps + 1)) + x + 1;
            hr = pFace->AddVertexAndNormalIndexed(index, index);
            if (FAILED(hr))
            {
                return hr;
            }
	    // One up and on the left.
            index = ((y + 1) * (m_Steps + 1)) + x;
            hr = pFace->AddVertexAndNormalIndexed(index, index);
            if (FAILED(hr))
            {
                return hr;
            }
	    // One to the right on the bottom.  Traverse CCW.
            index = (y * (m_Steps + 1)) + x + 1;
            hr = pFace->AddVertexAndNormalIndexed(index, index);
            if (FAILED(hr))
            {
                return hr;
            }
            pFace->Release();
        }
    }

    // Set the input texture
    hr = OutputMeshBuilder()->SetTexture(m_cpInputTexture);
    if (FAILED(hr))
    {
        return hr;
    }

    ClearDirty();
    return hr;
} 



STDMETHODIMP CRipple::get_XOrigin(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_XOrigin;
    return S_OK;
}

STDMETHODIMP CRipple::put_XOrigin(float newVal)
{
    Lock();
    m_XOrigin = newVal;
    if(m_XOrigin != newVal)
    {
        m_XOrigin = newVal;
        SetDirty();
    }
    Unlock();
    return S_OK;
}

STDMETHODIMP CRipple::get_YOrigin(float * pVal)
{
    *pVal = m_YOrigin;
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    return S_OK;
}

STDMETHODIMP CRipple::put_YOrigin(float newVal)
{
    Lock();
    m_YOrigin = newVal;
    if(m_YOrigin != newVal)
    {
        m_YOrigin = newVal;
        SetDirty();
    }
    Unlock();
    return S_OK;
}


STDMETHODIMP CRipple::get_Wavelength(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_Wavelength;
    return S_OK;
}

STDMETHODIMP CRipple::put_Wavelength(float newVal)
{
    if(newVal <= 0.0f)
        return E_INVALIDARG;

    Lock();
    if(m_Wavelength != newVal)
    {
        m_Wavelength = newVal;
        SetDirty();
    }
    Unlock();
    return S_OK;
}

STDMETHODIMP CRipple::get_Amplitude(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_Amplitude;
    return S_OK;
}

STDMETHODIMP CRipple::put_Amplitude(float newVal)
{
    if(newVal < 0.0f)
        return E_INVALIDARG;

    Lock();
    if(m_Amplitude != newVal)
    {
        m_Amplitude = newVal;
        SetDirty();
    }
    Unlock();
    return S_OK;
}

STDMETHODIMP CRipple::get_NumberOfWaves(long * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_NumWaves;
    return S_OK;
}

STDMETHODIMP CRipple::put_NumberOfWaves(long newVal)
{
    if(newVal <= 0)
        return E_INVALIDARG;

    Lock();
    if (m_NumWaves != newVal)
    {
        m_NumWaves = newVal;
        SetDirty();
    }
    Unlock();
    return S_OK;
}

STDMETHODIMP CRipple::get_MinSteps(long * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_MinSteps;
    return S_OK;
}

STDMETHODIMP CRipple::put_MinSteps(long newVal)
{
    if(newVal <= 2 || newVal > m_MaxSteps)
        return E_INVALIDARG;

    Lock();
    if (m_MinSteps != newVal)
    {
        m_MinSteps = newVal;
        IncrementGenerationId(TRUE);    // Force a re-setup
    }
    Unlock();
    return S_OK;
}


STDMETHODIMP CRipple::get_MaxSteps(long * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_MaxSteps;
    return S_OK;
}


STDMETHODIMP CRipple::put_MaxSteps(long newVal)
{
    if(newVal < 2 || newVal < m_MinSteps)
        return E_INVALIDARG;

    Lock();
    if (m_MaxSteps != newVal)
    {
        m_MaxSteps = newVal;
        IncrementGenerationId(TRUE);    // Force a re-setup
    }
    Unlock();
    return S_OK;
}


HRESULT CRipple::InitializeBitmap(void)
{
    m_cpInputTexture = NULL;

    _ASSERT(InputSurface(0));
    return m_cpSurfFact->CreateD3DRMTexture(InputSurface(0), 
				m_cpDirectDraw,m_cpDirect3DRM, 
				IID_IDirect3DRMTexture3,(void**)&m_cpInputTexture);
}


HRESULT CRipple::Reset()
{
    // Allocate the vertices look up table.
    delete[] m_prgvert;
    m_prgvert = new D3DRMVERTEX[m_cVertices];
    if (NULL == m_prgvert)
    {
        return E_OUTOFMEMORY;
    }

    delete[] m_pflDistanceTable;
    m_pflDistanceTable = new float[m_cVertices];
    if (!m_pflDistanceTable) {
        return E_OUTOFMEMORY;
    }
    HRESULT hr;

    CDXDBnds bndsBounds;

    if(FAILED(hr = bndsBounds.SetToSurfaceBounds(InputSurface(0))))
	return hr;

    if(bndsBounds.Width() == 0 || bndsBounds.Height() == 0)
    {
        m_flHeight = TARGET_HEIGHT;
        m_flWidth = TARGET_WIDTH;
    }
    else
    {
        double dHeightToWidthRatio = sqrt(
            (double)bndsBounds.Height()/(double)bndsBounds.Width());

        m_flHeight = (float)(TARGET_HEIGHT * dHeightToWidthRatio);
        m_flWidth = (float)(TARGET_WIDTH / dHeightToWidthRatio);
    }

    // Generate the vertices.
    D3DRMVERTEX* pvert = m_prgvert;
    float *pDist = m_pflDistanceTable;
    for (int y = 0; y <= m_Steps; y++)
    {
        for (int x = 0; x <= m_Steps; x++)
        {
            pvert->position.x = (-m_flWidth  / 2.0f) + ((m_flWidth  * (float)x) / (float)m_Steps);
            pvert->position.y = (-m_flHeight / 2.0f) + ((m_flHeight * (float)y) / (float)m_Steps);
            float flXDelta = (pvert->position.x - m_XOrigin);
            float flYDelta = (pvert->position.y - m_YOrigin);
            *pDist = (float)sqrt((flXDelta * flXDelta) + (flYDelta * flYDelta));
            pvert->position.z = 0.0f;
            pvert->normal.x   = 0.0f;
            pvert->normal.x   = 0.0f;
            pvert->normal.z   = 1.0f;
            pvert->tu         = (float)x / (float)m_Steps;
            pvert->tv         = 1.0f - ((float)y / (float)m_Steps);
            pvert->color      = D3DRGB(255, 0, 0);
            pvert++;
            pDist++;
        }
    }
    return S_OK;   
}

/***********************
Given three points, return the normal to the plane defined by these three points.
For a Right Handed system points A, B, and C should be in a CW order on the plane.
From CRC Standard Mathematical Tables 22nd Edition, page 380.  
Direction Numbers and Direction Cosines.
***********************/
inline D3DVECTOR ComputeNormal(D3DVECTOR d3dptA, D3DVECTOR d3dptB, D3DVECTOR d3dptC)
{
    const D3DVECTOR d3dptOne = d3dptB - d3dptA;
    const D3DVECTOR d3dptTwo = d3dptC - d3dptB;

    D3DVECTOR d3dptRetValue;
    d3dptRetValue.x = d3dptOne.y * d3dptTwo.z - d3dptOne.z * d3dptTwo.y;
    d3dptRetValue.y = d3dptOne.z * d3dptTwo.x - d3dptOne.x * d3dptTwo.z;
    d3dptRetValue.z = d3dptOne.x * d3dptTwo.y - d3dptOne.y * d3dptTwo.x;

    float Magnitude = (float)sqrt(d3dptRetValue.x * d3dptRetValue.x + 
                                  d3dptRetValue.y * d3dptRetValue.y + 
                                  d3dptRetValue.z * d3dptRetValue.z);
    return d3dptRetValue/Magnitude;
}

#define IsCoreTransformDirty() (m_dwCleanGenId != m_dwGenerationId)

HRESULT CRipple::OnExecute(const GUID* /* pRequestID */, const DXBNDS * /*pClipBnds */,
                          const DXVEC * /*pPlacement */)
{
    HRESULT hr;
    int     x;
    int     y;

    //  If the transform is 'Dirty()' (changed) we need to do a complete setup.
    //  For many transform this isn't the case, or the transform could keep track
    //  of what things have changed and only do a complete setup if required.
    if (IsCoreTransformDirty())
    {
	if(FAILED(hr = OnSetup(0)))
	{
	    return hr;
	}
	ClearDirty();
    }
    else
    {
	if (IsInputDirty(0))
	{
	    if (FAILED(hr = InitializeBitmap()) ||
		FAILED(hr = OutputMeshBuilder()->SetTexture(m_cpInputTexture)))
	    {
		return hr;
	    }
	    ClearDirty();
	}
    }

    float flCurAmplitude = GetCurrentAmplitude();

    _ASSERT(m_prgvert);
 
    // Apply the wave to the vertices
    float flMaxDistance = (float)m_NumWaves * m_Wavelength;
    D3DRMVERTEX* pvert = m_prgvert;
    float * pDistance = m_pflDistanceTable;
    for (y = 0; y <= m_Steps; y++)
    {
        for (x = 0; x <= m_Steps; x++)
        {
            float flDistance = *pDistance;
            if (flDistance < flMaxDistance && flCurAmplitude > 0.0f)
            {
                float flTmp = (1.0f - (flDistance / flMaxDistance));
                float flAmp = flCurAmplitude * flTmp * flTmp;
                float flAngle = (1.0f - m_Progress + (flDistance / m_Wavelength)) * M_2PI;
                pvert->position.z = flAmp * (float)sin(flAngle);

                if ((y == 0) || (x == 0))
                {
                    pvert->normal.x = 0.0f;
                    pvert->normal.y = 0.0f;
                    pvert->normal.z = 1.0f;
                } else {
                    // CW around current point.                                                                    
                    pvert->normal = ComputeNormal(pvert->position, (pvert - 1)->position, (pvert - m_Steps)->position);
                }
            } else {
                pvert->position.z = 0.0f;
                pvert->normal.x = 0.0f;
                pvert->normal.y = 0.0f;
                pvert->normal.z = 1.0f;
            }

            pvert++;
            pDistance++;
        }
    }
    pvert = m_prgvert;
    for (int i = 0; i < m_cVertices; i++)
    {
        hr = OutputMeshBuilder()->SetVertex(i, pvert->position.x,
                                         pvert->position.y,
                                         pvert->position.z);
        if (FAILED(hr))
        {
            ::DebugBreak();
            return hr;
        }
        hr = OutputMeshBuilder()->SetNormal(i, pvert->normal.x,
                                         pvert->normal.y,
                                         pvert->normal.z);

        if (FAILED(hr))
        {
            ::DebugBreak();
            return hr;
        }
        pvert++;
    }

    return S_OK;
}
