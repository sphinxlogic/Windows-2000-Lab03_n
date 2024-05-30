// Explode.cpp : Implementation of CExplode

#include "stdafx.h"
#include <dxtmsft.h>
#include "Explode.h"

/////////////////////////////////////////////////////////////////////////////
// CExplode

CExplode::CExplode() 
{
    m_dwOptionFlags = DXBOF_INPUTS_MESHBUILDER | DXBOF_OUTPUT_MESHBUILDER;
    m_dwMiscFlags = 0;

    SetMaximumRotations(2);
    m_fFinalVelocity = 2.0f;
    m_fPositionJump = 0.5f;
    m_fDecayTime = 0.1f;
    m_bTumble = TRUE;
    m_Duration = 4.0f;	// Suggested duration.
#if(_ATL_VER >= 0x0300)
    m_bRequiresSave = FALSE;
#endif
}
CExplode::~CExplode()
{
}
STDMETHODIMP CExplode::get_Tumble(/*[out, retval]*/ BOOL *pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_bTumble; 
    return S_OK;
}

STDMETHODIMP CExplode::put_Tumble(/*[in]*/ BOOL newVal)
{
    m_bTumble = newVal;
    return S_OK;
}
STDMETHODIMP CExplode::get_MaxRotations(long * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_iMaxRotations;
    return S_OK;
}

STDMETHODIMP CExplode::put_MaxRotations(long newVal)
{
    if (newVal < 0)
        return E_INVALIDARG;

    SetMaximumRotations(newVal);
    return S_OK;
}
STDMETHODIMP CExplode::get_FinalVelocity (float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_fFinalVelocity; 
    return S_OK;
}

STDMETHODIMP CExplode::put_FinalVelocity(float newVal)
{
    m_fFinalVelocity = newVal;
    return S_OK;
}

STDMETHODIMP CExplode::get_PositionJump (float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_fPositionJump; 
    return S_OK;
}

STDMETHODIMP CExplode::put_PositionJump(float newVal)
{
    m_fPositionJump = newVal;
    return S_OK;
}

STDMETHODIMP CExplode::get_DecayTime (float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_fDecayTime; 
    return S_OK;
}

STDMETHODIMP CExplode::put_DecayTime(float newVal)
{
    if(newVal <= 0.0f)
        return E_INVALIDARG;

    m_fDecayTime = newVal;
    return S_OK;
}

HRESULT CExplode::DetermineBnds(CDXCBnds & Bnds)
{
    if(m_Progress != 0.0f)
    {
	float Delta = (float)(m_Progress * m_fFinalVelocity + 
                      m_fPositionJump * (1.0f - (float)exp(-m_Progress/m_fDecayTime)));

	if(m_bTumble || m_iMaxRotations > 0.0f)
	{
	    float Width = Bnds.Width();
	    float Height = Bnds.Height();
	    float Depth = Bnds[DXB_Z].Max - Bnds[DXB_Z].Min;
	    float MaxExtension = (float)sqrt(Width * Width + Height * Height + Depth * Depth)/2.0f;
	    float MaxTumble = (float)(m_iMaxRotations * 2.0f * PI * m_Progress);

	    if(MaxTumble < PI/2.0)
	    {
		MaxExtension *= (float)sin(MaxTumble);
	    }

	    Delta += MaxExtension;
	}
	Delta *= 2;

	// Delta is the max amount it will grow in any direction.
	// Therefore it can expand up to twice this total (-delta and +delta).
	Bnds.Expand(Delta, Delta, Delta);
    }

    return S_OK;
}

HRESULT CExplode::OnSetup(DWORD dwFlags)
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
void CExplode::SetMaximumRotations(int iRot)
{
    m_iMaxRotations = iRot;
    m_iSpin = (int)(iRot * SPIN_SCALE * 2.0 * PI + 0.5);
}


double CExplode::RandomSpin(void)
{
    // Psuedorandom number generator.
    NextRandom();

    // Get number between 0 and m_iSpin (m_iMaxRotations * SPIN_SCALE * 2 * PI).
    int iRet = ((m_dwNextRandom / 0x10000) * (DWORD)m_iSpin) >> 16;

    // Toggle the sign randomly.
    return ((double)(m_dwNextRandom & 0x8000)? -iRet: iRet)/SPIN_SCALE; 
}

DWORD CExplode::RandomBits(void)
{
    NextRandom();
    return m_dwNextRandom;
}

static HRESULT TraverseSubMeshCallBack (void *lpThis, 
					IDirect3DRMMeshBuilder3* lpMeshBuilderOut,
					IDirect3DRMMeshBuilder3* lpMeshBuilderIn)
{
    return ((CExplode *)(lpThis))->DoOneMeshBuilder(lpMeshBuilderOut, lpMeshBuilderIn);
}


HRESULT CExplode::OnExecute(const GUID* /* pRequestID */,
			    const DXBNDS * /* pClipBnds */,
			    const DXVEC * /* pPlacement */) 
{
    HRESULT hr;

    if (IsInputDirty(0))
    {
        hr = OnSetup(0);    // OnSetup() clears the dirty flag if it was successful.
        if (FAILED(hr))
	{
            return hr;
        }
    }

    SeedRandSpin(1);    // So it will have the same sequence for each step.

    return TraverseSubMeshes(TraverseSubMeshCallBack,(void *)this, 
			    OutputMeshBuilder(), InputMeshBuilder());
}
HRESULT CExplode::DoOneMeshBuilder(IDirect3DRMMeshBuilder3 * lpMeshBuilderOut, 
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

    /*
    This implements a fast initial movement followed by a steady velocity thereafter.
    The direction of motion is directly along the normal to the face.

    The equation for the change in position, from the initial position, (written in 
    terms of the magnitude, not any terms of one individual component):

        Delta = m_fFinalVelocity * t + m_fPositionJump - m_fPositionJump * e^(-t/m_fDecayTime)

    This has been rewritten slightly in the code below, but the result is equivalent.

    By decreasing m_fDecayTime the portion of the time spent in the fast mode is decreased.
    If m_fDecayTime is set to some very small, positive, non-zero value the velocity -- 
    the time to get to m_fPositionJump from the original location will be very small also
    (about 5 times m_fDecayTime).
    */

    const float ScaleFactor = (float)(m_Progress * m_fFinalVelocity + 
                                      m_fPositionJump * (1.0f - (float)exp(-m_Progress/m_fDecayTime)));

    const int ciMaxFaceCount = lpMeshBuilderIn->GetFaceCount();
    _ASSERT(ciMaxFaceCount == lpMeshBuilderOut->GetFaceCount());

    if(ciMaxFaceCount != 0)
    {
	Rotate rttRotator;
	DWORD dwRandomBits = RandomBits();

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
	    // Scale the input face normal by our time dependant function and a random 
	    // amount between 0.5 and 1.0.  This will be our direction vector for translation.
	    D3DVECTOR d3dvctrRandomizeTranslation(1.0f - 0.5f * RandomFloat(),
						  1.0f - 0.5f * RandomFloat(),
						  1.0f - 0.5f * RandomFloat());
	    D3DVECTOR d3dvctrOutwardTranslation = d3dvctrNormal * 
				ScaleFactor * d3dvctrRandomizeTranslation;

	    D3DVECTOR d3dvctrCentroid, d3dvctrDelta;

	    if(m_iSpin)
	    {
		d3dvctrCentroid = lpvctrVerticesIn[lpdwFaceDataIn[uiFaceDataIndex]];
		DWORD dwVertexIndex = 1;

		do
		{
		    d3dvctrCentroid += lpvctrVerticesIn[lpdwFaceDataIn[uiFaceDataIndex + 2 * dwVertexIndex]];
		} while (++dwVertexIndex < dwNumInVertices);

		d3dvctrCentroid = d3dvctrCentroid/(float)dwNumInVertices;

		D3DVECTOR d3dvctrRotAxis = d3dvctrNormal;
		if(m_bTumble)
		{
		    if(dwRandomBits == 0)
		    {
			dwRandomBits = RandomBits();
		    }

		    if(dwRandomBits & 1)
		    {
			float t = d3dvctrRotAxis.x;

			d3dvctrRotAxis.x = d3dvctrRotAxis.y;
			d3dvctrRotAxis.y = t;
		    }

		    dwRandomBits >>= 1;
		    if(dwRandomBits & 1)
		    {
			float t = d3dvctrRotAxis.y;

			d3dvctrRotAxis.y = d3dvctrRotAxis.z;
			d3dvctrRotAxis.z = t;
		    }

		    dwRandomBits >>= 1;
		}
		rttRotator.Set(d3dvctrRotAxis, m_Progress * RandomSpin());

		d3dvctrDelta = d3dvctrCentroid - d3dvctrRotAxis;
	    }


	    do
	    {
		// Get the input vertex and translate it by the proper amount.
		D3DVECTOR d3dvctrNewVertex = lpvctrVerticesIn[lpdwFaceDataIn[uiFaceDataIndex]];
            
		if(m_iSpin)
		{
                        // Translate the normals from the input.
                    const D3DVECTOR d3dvctrNewNormal = rttRotator.RotatePoint(lpvctrNormalsIn[lpdwFaceDataIn[uiFaceDataIndex + 1]]);

                    lpMeshBuilderOut->SetNormal(lpdwFaceDataOut[uiFaceDataIndex + 1], 
					    d3dvctrNewNormal.x, d3dvctrNewNormal.y, d3dvctrNewNormal.z);
    
                    d3dvctrNewVertex = d3dvctrNewVertex - d3dvctrDelta; // Move the new vertex to be centered about the rotational axis.
		    d3dvctrNewVertex = rttRotator.RotatePoint(d3dvctrNewVertex);
		    d3dvctrNewVertex = d3dvctrNewVertex + d3dvctrDelta; // Move the vertex back to it's original position.
		}

		d3dvctrNewVertex = d3dvctrNewVertex + d3dvctrOutwardTranslation;  // Move it outward.

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

