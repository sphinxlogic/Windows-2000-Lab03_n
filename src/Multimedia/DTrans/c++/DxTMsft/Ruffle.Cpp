// Ruffle.cpp : Implementation of CRuffle
#include "stdafx.h"
#include <dxtmsft.h>
#include "Ruffle.h"

/////////////////////////////////////////////////////////////////////////////
// CRuffle
CRuffle::CRuffle() 
{
    m_dwOptionFlags = DXBOF_INPUTS_MESHBUILDER | DXBOF_OUTPUT_MESHBUILDER;
    m_dwMiscFlags = 0;

    SetMaximumRotations(1); // Just something non-zero.
    m_Duration = 2.0f;	// Suggested duration.
#if(_ATL_VER >= 0x0300)
    m_bRequiresSave = FALSE;
#endif
}
CRuffle::~CRuffle()
{
}
STDMETHODIMP CRuffle::get_MaxRotations(long * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_iMaxRotations;
    return S_OK;
}

STDMETHODIMP CRuffle::put_MaxRotations(long newVal)
{
    if(newVal < 0)
        return E_INVALIDARG;

    SetMaximumRotations(newVal);
    return S_OK;
}
HRESULT CRuffle::DetermineBnds(CDXCBnds & Bnds)
{
    if(m_Progress != 0.0f)
    {
	float Width = Bnds.Width();
	float Height = Bnds.Height();
	float Depth = Bnds[DXB_Z].Max - Bnds[DXB_Z].Min;
	float MaxExtension = (float)sqrt(Width * Width + Height * Height +
		Depth * Depth)/2.0f;
	double MaxRot = (m_iMaxRotations * 2.0f * PI * m_Progress);

	if(MaxRot < PI/2.0)
	{
	    MaxExtension *= (float)sin(MaxRot);
	}
	MaxExtension *= 2;
	Bnds.Expand(MaxExtension, MaxExtension, MaxExtension);
    }

    return S_OK;
}

HRESULT CRuffle::OnSetup(DWORD dwFlags)
{
    HRESULT hr = D3DRMERR_BADVALUE;

    if (OutputMeshBuilder() && InputMeshBuilder())
    {
	hr = DecoupleVertices(OutputMeshBuilder(), InputMeshBuilder());
	if(SUCCEEDED(hr))
	{
	    ClearDirty();
	}
    }
    
    return hr;
}

#define SPIN_SCALE 1000.0

// iRot revolutions, maximum, for any face.
void CRuffle::SetMaximumRotations(int iRot)
{
    m_iMaxRotations = iRot;
    m_iSpin = (int)(iRot * SPIN_SCALE * 2.0 * PI);
}

double CRuffle::RandomSpin(void)
{
    // Psuedorandom number generator.
    m_dwNextRandom = m_dwNextRandom * 1103515245 + 12345;

    // Number between 0 and m_iSpin (max value of m_iMaxRotations * SPIN_SCALE * 2 * PI).
    int iRet = ((m_dwNextRandom / 0x10000) * (DWORD)m_iSpin) >> 16;

    // Toggle the sign randomly and scale from (-2 * PI to 2 * PI) * m_iMaxRotations.
    return ((double)(m_dwNextRandom & 0x80000000)? -iRet: iRet)/SPIN_SCALE; 
}

static HRESULT TraverseSubMeshCallBack (void *lpThis,
					IDirect3DRMMeshBuilder3* lpMeshBuilderOut,
					IDirect3DRMMeshBuilder3* lpMeshBuilderIn)
{
    return ((CRuffle *)(lpThis))->DoOneMeshBuilder(lpMeshBuilderOut, lpMeshBuilderIn);
}


HRESULT CRuffle::OnExecute(const GUID* /* pRequestID */,
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

    SeedRandSpin(1);	// So it will have the same sequence for each step.

    return TraverseSubMeshes(TraverseSubMeshCallBack,(void *)this, 
			     OutputMeshBuilder(), InputMeshBuilder());
}

HRESULT CRuffle::DoOneMeshBuilder (IDirect3DRMMeshBuilder3 * lpMeshBuilderOut,
				   IDirect3DRMMeshBuilder3 * lpMeshBuilderIn)
{
    // Use the initial position from the input meshbuilder as a basis for the new position.
    DWORD dwVerticesIn, dwNormalsIn, dwFaceDataSizeIn;

    HRESULT hr = lpMeshBuilderIn->GetGeometry(&dwVerticesIn, NULL, &dwNormalsIn, NULL, &dwFaceDataSizeIn, NULL);
    if(hr != D3DRM_OK)
    {
	return hr;
    }

    // The output vertices need to be updated.
    DWORD dwVerticesOut, dwNormalsOut, dwFaceDataSizeOut;

    hr = lpMeshBuilderOut->GetGeometry(&dwVerticesOut, NULL, &dwNormalsOut, NULL, &dwFaceDataSizeOut, NULL);
    if(hr != D3DRM_OK)
    {
	return hr;
    }

    // We don't really need the input normals, but can't seem to get the vertices without them.
    D3DVECTOR * const lpvctrVerticesIn = (D3DVECTOR *)malloc(dwVerticesIn * sizeof(*lpvctrVerticesIn));
    D3DVECTOR * const lpvctrNormalsIn = (D3DVECTOR *)malloc(dwNormalsIn * sizeof(*lpvctrNormalsIn));
    DWORD * const lpdwFaceDataIn = (DWORD *)malloc(dwFaceDataSizeIn * sizeof(*lpdwFaceDataIn));

    D3DVECTOR * const lpvctrVerticesOut = (D3DVECTOR *)malloc(dwVerticesOut * sizeof(*lpvctrVerticesOut));
    D3DVECTOR * const lpvctrNormalsOut = (D3DVECTOR *)malloc(dwNormalsOut * sizeof(*lpvctrNormalsOut));
    DWORD * const lpdwFaceDataOut = (DWORD *)malloc(dwFaceDataSizeOut * sizeof(*lpdwFaceDataOut));

    if(!lpvctrVerticesIn  || !lpvctrNormalsIn  || !lpdwFaceDataIn ||
       !lpvctrVerticesOut || !lpvctrNormalsOut || !lpdwFaceDataOut)
    {
	free(lpvctrVerticesIn);
	free(lpvctrNormalsIn);
	free(lpdwFaceDataIn);
	free(lpvctrVerticesOut);
	free(lpvctrNormalsOut);
	free(lpdwFaceDataOut);
        return E_OUTOFMEMORY;
    }

    hr = lpMeshBuilderIn->GetGeometry(&dwVerticesIn, lpvctrVerticesIn, &dwNormalsIn, 
                                        lpvctrNormalsIn, &dwFaceDataSizeIn, lpdwFaceDataIn);
    if(hr == D3DRM_OK)
    {
	hr = lpMeshBuilderOut->GetGeometry(&dwVerticesOut, lpvctrVerticesOut, &dwNormalsOut, 
                                        lpvctrNormalsOut, &dwFaceDataSizeOut, lpdwFaceDataOut);
    }

    if(hr != D3DRM_OK)
    {
	free(lpvctrVerticesIn);
	free(lpvctrNormalsIn);
	free(lpdwFaceDataIn);
	free(lpvctrVerticesOut);
	free(lpvctrNormalsOut);
	free(lpdwFaceDataOut);
        return hr;
    }

    const int ciMaxFaceCount = lpMeshBuilderIn->GetFaceCount();
    _ASSERT(ciMaxFaceCount == lpMeshBuilderOut->GetFaceCount());

    if(ciMaxFaceCount != 0)
    {
	int iFace = 0;
	unsigned int uiFaceDataIndex = 0;
	do
	{
	    DWORD dwNumInVertices = lpdwFaceDataIn[uiFaceDataIndex];  // Vertices on this face.
	    _ASSERT(dwNumInVertices >= 3);

	    DWORD dwNumOutVertices = lpdwFaceDataOut[uiFaceDataIndex++];

	    _ASSERT(dwNumOutVertices >= 3);
	    _ASSERT(dwNumInVertices == dwNumOutVertices);

	    D3DVECTOR d3dvctrNormal = ComputeNormal(lpvctrVerticesIn[lpdwFaceDataIn[uiFaceDataIndex]], 
                                                    lpvctrVerticesIn[lpdwFaceDataIn[uiFaceDataIndex + 2]], 
                                                    lpvctrVerticesIn[lpdwFaceDataIn[uiFaceDataIndex + 4]]);
	    D3DVECTOR d3dvctrCentroid, d3dvctrDelta;

	    d3dvctrCentroid = lpvctrVerticesIn[lpdwFaceDataIn[uiFaceDataIndex]];
	    DWORD dwVertexIndex = 1;

	    do
	    {
		d3dvctrCentroid = d3dvctrCentroid + lpvctrVerticesIn[lpdwFaceDataIn[uiFaceDataIndex + 2 * dwVertexIndex]];
	    } while (++dwVertexIndex < dwNumInVertices);

	    d3dvctrCentroid = d3dvctrCentroid / (float)dwNumInVertices;
	    d3dvctrDelta = d3dvctrCentroid - d3dvctrNormal;

	    Rotate rttRotator (d3dvctrNormal, m_Progress * RandomSpin());

	    do
	    {
		// Get the input vertex and translate it by the proper amount.
		D3DVECTOR d3dvctrNewVertex = lpvctrVerticesIn[lpdwFaceDataIn[uiFaceDataIndex]];
		
		d3dvctrNewVertex = d3dvctrNewVertex - d3dvctrDelta; // Move the new vertex to be centered about the normal.
		d3dvctrNewVertex = rttRotator.RotatePoint(d3dvctrNewVertex);
		d3dvctrNewVertex = d3dvctrNewVertex + d3dvctrDelta; // Move the vertex back to it's original position.

		lpMeshBuilderOut->SetVertex(lpdwFaceDataOut[uiFaceDataIndex], 
						d3dvctrNewVertex.x, d3dvctrNewVertex.y, d3dvctrNewVertex.z);
		uiFaceDataIndex += 2;  // Skip over this one pair of vertex and normal indices.
	    } while(--dwNumInVertices);
	} while (++iFace < ciMaxFaceCount);
    }

    free(lpvctrVerticesIn);
    free(lpvctrNormalsIn);
    free(lpdwFaceDataIn);
    free(lpvctrVerticesOut);
    free(lpvctrNormalsOut);
    free(lpdwFaceDataOut);
    return D3DRM_OK;
}
