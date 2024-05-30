/*==========================================================================;
 *
 *  Copyright (C) 1998 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:	htfield.cpp
 *  Content:	Height Field Implementation file
 *  Author:     Steve J Lacey
 *
 *
 *  Generates a 1x1x1 height field mesh
 ***************************************************************************/

#include "stdafx.h"
#include <dxtmsft.h>
#include "htfield.h"

#define RELEASE(_x) (_x ? _x->Release(), _x = NULL, 1 : 1)
CHeightField::CHeightField() :
    m_pRMTex(NULL),
    m_pDDS(NULL)
{
    m_dwOptionFlags = DXBOF_OUTPUT_MESHBUILDER;
    m_dwMiscFlags = 0;
    m_ulMaxInputs = 1;
    m_ulNumInRequired = 1;
    m_Duration = 4.0f;	// Suggested duration.
    m_flHeight = 2.0f;
    m_flWidth = 2.0f;
    m_flDepth = 1.0f;
    m_dwSamples = 65;
#if(_ATL_VER >= 0x0300)
    m_bRequiresSave = FALSE;
#endif
}

void
CHeightField::FinalRelease()
{
    RELEASE(m_pRMTex);
    RELEASE(m_pDDS);
}


HRESULT CHeightField::DetermineBnds(CDXCBnds & Bnds)
{
    Bnds[DXB_X].Min = -m_flWidth/2;
    Bnds[DXB_X].Max = m_flWidth/2;

    Bnds[DXB_Y].Min = -m_flHeight/2;
    Bnds[DXB_Y].Max = m_flHeight/2;

    Bnds[DXB_Z].Min = 0.0f;
    Bnds[DXB_Z].Max = m_flDepth * m_Progress;

    return S_OK;
}

float
CHeightField::GetHeight(IDXARGBReadPtr* pPtr,
			CDXDBnds* pBnds,
			float fNormX, float fNormY)
{
    ULONG uX, uY;
    DXSAMPLE dxSample;
    float fIntensity;

    uX = (ULONG)((pBnds->Width() - 1) * fNormX);
    uY = (ULONG)((pBnds->Height() - 1) * (1.0f - fNormY));

    pPtr->MoveToXY(uX, uY);

    if (!pPtr->Unpack(&dxSample, 1, FALSE))
    {
	return (0.0f);
    }

    fIntensity = (dxSample.Blue +
		  dxSample.Green +
		  dxSample.Red) / (255.0f * 3.0f);

    return (fIntensity);
}

HRESULT
CHeightField::OnSetup(DWORD dwFlags)
{
    HRESULT hr;
    LPDWORD pdwFaceData = NULL;
    LPDWORD pData;
    LPD3DVECTOR pVerts = NULL;
    IDirect3DRMWrap* pWrap;
    LPD3DVECTOR pV;
    DWORD dwX, dwY, dwNumFaces, dwNumVertices;

    OutputMeshBuilder()->Empty(0);

    RELEASE(m_pRMTex);
    RELEASE(m_pDDS);

    hr = InputSurface(0)->GetDirectDrawSurface(IID_IDirectDrawSurface,(void**)&m_pDDS);
	
    if (FAILED(hr))
    {
	goto _onSetupCleanUp;
    }
    
    hr = m_cpDirect3DRM->CreateTextureFromSurface(m_pDDS, &m_pRMTex);

    if (FAILED(hr))
    {
	goto _onSetupCleanUp;
    }

    dwNumFaces = m_dwSamples * m_dwSamples * 2;
    dwNumVertices = (m_dwSamples+1) * (m_dwSamples+1);

    pdwFaceData = new DWORD[(dwNumFaces * 4) + 1];
    if (!pdwFaceData)
    {
	hr = E_OUTOFMEMORY;
	goto _onSetupCleanUp;
    }

    pVerts = new D3DVECTOR[dwNumVertices];
    if (!pVerts)
    {
	hr = E_OUTOFMEMORY;
	goto _onSetupCleanUp;
    }

    pData = pdwFaceData;

    for (dwY = 0; dwY < (m_dwSamples + 1); dwY++)
    {
	for (dwX = 0; dwX < (m_dwSamples + 1); dwX++)
	{
	    pV = &pVerts[(dwY * (m_dwSamples + 1)) + dwX];
	    
	    pV->x = ((float)dwX / (float)m_dwSamples) * (float)m_flWidth;
	    pV->y = ((float)dwY / (float)m_dwSamples) * (float)m_flHeight;
	    pV->z = 0.0f;	    
	    if ((dwX < m_dwSamples ) && (dwY < m_dwSamples))
	    {
		*pData++ = 3;
		*pData++ = ( dwY      * (m_dwSamples+1)) +  dwX;
		*pData++ = ( dwY      * (m_dwSamples+1)) + (dwX + 1);
		*pData++ = ((dwY + 1) * (m_dwSamples+1)) + (dwX + 1);

		*pData++ = 3;
		*pData++ = ( dwY      * (m_dwSamples+1)) +  dwX;
		*pData++ = ((dwY + 1) * (m_dwSamples+1)) + (dwX + 1);
		*pData++ = ((dwY + 1) * (m_dwSamples+1)) +  dwX;
	    }
	}
    }

    *pData = 0;

    hr = OutputMeshBuilder()->AddFaces(dwNumVertices, pVerts,
				       0, NULL,
				       pdwFaceData, NULL);
    if (FAILED(hr))
    {
	goto _onSetupCleanUp;
    }

    delete [] pdwFaceData;
    pdwFaceData = NULL;
    delete [] pVerts;
    pVerts = NULL;

    OutputMeshBuilder()->SetColorRGB(1.0f, 1.0f, 1.0f);

    hr = OutputMeshBuilder()->SetTexture(m_pRMTex);
    if (FAILED(hr))
    {
	goto _onSetupCleanUp;
    }

    hr = m_cpDirect3DRM->CreateWrap(D3DRMWRAP_FLAT,
				    NULL,
				    0.0f, 0.0f, 0.0f, // Origin
				    0.0f, 0.0f, 1.0f, // Up
				    0.0f, 1.0f, 0.0f, // Right
				    0.0f, 0.0f,       // Offset
				    1.0f/m_flWidth, -1.0f/m_flHeight,// Scale
				    &pWrap);
    if (FAILED(hr))
    {
	goto _onSetupCleanUp;
    }

    hr = pWrap->Apply(OutputMeshBuilder());
    pWrap->Release();
    if (FAILED(hr))
    {
	goto _onSetupCleanUp;
    }

    hr = OutputMeshBuilder()->GenerateNormals(0.0f,0);
    if (FAILED(hr))
    {
	goto _onSetupCleanUp;
    }

    ClearDirty();

    return (S_OK);

_onSetupCleanUp:
    RELEASE(m_pRMTex);
    RELEASE(m_pDDS);
    delete [] pdwFaceData;
    delete [] pVerts;


    return (hr);
} 

HRESULT
CHeightField::OnExecute(const GUID*    /* pRequestID */,
			const DXBNDS * /* pClipBnds  */,
			const DXVEC *  /* pPlacement */)
{
    HRESULT hr;
    CDXDBnds SurfBounds;
    DWORD dwGenID;
    IDXARGBReadPtr* pReadPtr = NULL;
    DWORD dwX, dwY;
    DWORD dwVertex = 0;
    float fX, fY, fZ;

    if (IsTransformDirty())
    {
        hr = OnSetup(0);    // OnSetup() clears the dirty flag if it was successful.
        if (FAILED(hr))
	{
            return hr;
        }
    }

    hr = SurfBounds.SetToSurfaceBounds(InputSurface(0));
    if (FAILED(hr))
    {
	return (hr);
    }

    hr = InputSurface(0)->LockSurface(NULL,
				   INFINITE,
				   DXLOCKF_READ,
				   IID_IDXARGBReadPtr,
				   (void**)&pReadPtr,
				   &dwGenID);
    if (FAILED(hr))
    {
	return (hr);
    }

    for (dwY = 0; dwY < (m_dwSamples + 1); dwY++)
    {
	for (dwX = 0; dwX < (m_dwSamples + 1); dwX++)
	{
	    fX = (((float)dwX / (float)m_dwSamples) *
		  (float)m_flWidth) - 
		((float)m_flWidth / 2.0f);
	    fY = (((float)dwY / (float)m_dwSamples) *
		  (float)m_flHeight) -
		((float)m_flHeight / 2.0f);
	    fZ = (m_Progress ?
		  ((float)m_Progress *
		   GetHeight(pReadPtr, &SurfBounds,
			     (float)dwX / (float)m_dwSamples,
			     (float)dwY / (float)m_dwSamples) *
		             (float)m_flDepth)
		  : 0.0f);
	    OutputMeshBuilder()->SetVertex(dwVertex++, fX, fY, fZ);
	}
    }
    
    pReadPtr->Release();

    return (hr);
}

STDMETHODIMP CHeightField::get_Width(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_flWidth;
    return S_OK;
}

STDMETHODIMP CHeightField::put_Width(float newVal)
{
    Lock();
    m_flWidth = newVal;
    SetDirty();
    Unlock();
    return S_OK;
}

STDMETHODIMP CHeightField::get_Height(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_flHeight;
    return S_OK;
}

STDMETHODIMP CHeightField::put_Height(float newVal)
{
    Lock();
    m_flHeight = newVal;
    SetDirty();
    Unlock();
    return S_OK;
}

STDMETHODIMP CHeightField::get_Depth(float * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_flDepth;
    return S_OK;
}

STDMETHODIMP CHeightField::put_Depth(float newVal)
{
    Lock();
    m_flDepth = newVal;
    SetDirty();
    Unlock();
    return S_OK;
}

STDMETHODIMP CHeightField::get_Samples(long * pVal)
{
    if( DXIsBadWritePtr( pVal, sizeof( *pVal)))
        return E_POINTER;

    *pVal = m_dwSamples;
    return S_OK;
}

STDMETHODIMP CHeightField::put_Samples(long newVal)
{
    Lock();
    m_dwSamples = newVal;
    SetDirty();
    Unlock();
    return S_OK;
}
