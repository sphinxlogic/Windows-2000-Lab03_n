/*******************************************************************************
* DXTWipe.cpp *
*-------------*
*   Description:
*       This module contains the CDXTWipe transform
*-------------------------------------------------------------------------------
*  Created By: EDC                                      Date: 01/06/98
*  Copyright (C) 1998 Microsoft Corporation
*  All Rights Reserved
*
*-------------------------------------------------------------------------------
*  Revisions:
*
*******************************************************************************/
#include "stdafx.h"

//--- Additional includes
#include "Wipe.h"           // IDL
#include "DXTWipe.h"        // Transform implementation stuff
#include <string.h>

//--- Local
static WCHAR g_Notice[] = L"Copyright Microsoft Corporation 1998, Unauthorized duplication of this string is illegal {AF279B30-86EB-11D1-81BF-0000F87557DB}";

/*****************************************************************************
* CDXTWipe::FinalConstruct *
*--------------------------*
*   Description:
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/06/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
HRESULT CDXTWipe::FinalConstruct()
{
    HRESULT hr = S_OK;

    //--- Uncomment this when debugging to allow only
    //    one thread to execute the work proc at a time
    // m_ulMaxImageBands = 1;

    //--- Init base class variables to control setup
    m_ulMaxInputs       = 2;
    m_ulNumInRequired   = 2;
    m_dwOptionFlags     = DXBOF_SAME_SIZE_INPUTS | DXBOF_CENTER_INPUTS;
    m_Duration          = .5;

    //--- Init data
    m_bCopyrightIsNotValid = ( _LICENSED_VERSION )?( false ):( true );
    m_GradPercentSize   = .25;
    m_GradientSize      = 0;
    m_pGradientWeights  = NULL;
    m_eWipeStyle        = DXWD_RIGHT;
    m_InputSize.cx      = 0;
    m_InputSize.cy      = 0;
#if(_ATL_VER >= 0x0300)
    m_bRequiresSave = FALSE;
#endif

    //--- Create marshaler
    hr = CoCreateFreeThreadedMarshaler( GetControllingUnknown(), &m_pUnkMarshaler.p );

    return hr;
} /* CDXTWipe::FinalConstruct */

/*****************************************************************************
* CDXTWipe::_UpdateGradWeights *
*------------------------------*
*   Description:
*       This is a helper method used to generate the transition gradient wieghts
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/08/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
HRESULT CDXTWipe::_UpdateGradWeights( void )
{
    HRESULT hr = S_OK;

    //
    //  BUGBUG -- Should check to see if these are the sampe as before.
    //

    delete m_pGradientWeights;
    m_pGradientWeights = new ULONG[m_GradientSize];

    if( !m_pGradientWeights )
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
        float fWeight = 1.0, fInc = 1.f / m_GradientSize;
        for( long i = 0; i < m_GradientSize; ++i, fWeight -= fInc )
        {
            m_pGradientWeights[i] = (ULONG)(fWeight * 255.);
        }
    }

    return hr;
} /* CDXTWipe::_UpdateGradWeights */

/*****************************************************************************
* CDXTWipe::_UpdateStepRes *
*--------------------------*
*   Description:
*       This is a helper method used to compute the current step resolution
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/08/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
void CDXTWipe::_UpdateStepRes( void )
{
    if( ( m_eWipeStyle == DXWD_RIGHT ) || ( m_eWipeStyle == DXWD_LEFT ) )
    {
        m_GradientSize   = (long)(m_InputSize.cx * m_GradPercentSize);
        m_StepResolution = (float)(m_InputSize.cx + m_GradientSize);
    }
    else
    {
        m_GradientSize   = (long)(m_InputSize.cy * m_GradPercentSize);
        m_StepResolution = (float)(m_InputSize.cy + m_GradientSize);
    }
} /* CDXTWipe::_UpdateStepRes */

/*****************************************************************************
* CDXTWipe::get_WipeStyle *
*-------------------------*
*   Description:
*       This method is used to get the current wipe style.
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/06/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
STDMETHODIMP CDXTWipe::get_WipeStyle( DXWIPEDIRECTION *pVal )
{
    HRESULT hr = S_OK;
    if( !pVal )
    {
        hr = E_POINTER;
    }
    else
    {
        *pVal = m_eWipeStyle;
    }
    return hr;
} /* CDXTWipe::get_WipeStyle */

/*****************************************************************************
* CDXTWipe::put_WipeStyle *
*-------------------------*
*   Description:
*       This method is used to get the size of the transition area between
*   image A and image B.
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/06/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
STDMETHODIMP CDXTWipe::put_WipeStyle( DXWIPEDIRECTION newVal )
{
    m_eWipeStyle = newVal;
    _UpdateStepRes();
    return S_OK;
} /* CDXTWipe::put_WipeStyle */

/*****************************************************************************
* CDXTWipe::get_GradientSize *
*----------------------------*
*   Description:
*       This method is used to get the size of the transition area between
*   image A and image B.
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/06/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
STDMETHODIMP CDXTWipe::get_GradientSize( float *pPercentSize  )
{
    HRESULT hr = S_OK;

    if( !pPercentSize )
    {
        hr = E_POINTER;
    }
    else
    {
        *pPercentSize = m_GradPercentSize;
    }

    return hr;
} /* CDXTWipe::get_GradientSize */

/*****************************************************************************
* CDXTWipe::put_GradientSize *
*----------------------------*
*   Description:
*       This method is used to set the size of the transition area between
*   image A and image B.
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/06/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
STDMETHODIMP CDXTWipe::put_GradientSize( float PercentSize )
{
    HRESULT hr = S_OK;

    if( PercentSize < 0 )
    {
        hr = E_INVALIDARG;
    }
    else
    {
        m_GradPercentSize = PercentSize;
        _UpdateStepRes();
        hr = _UpdateGradWeights();
    }
    return hr;
} /* CDXTWipe::put_GradientSize */

/*****************************************************************************
* CDXTWipe::get_Copyright *
*-------------------------*
*   Description:
*       This method is used to get the copyright notice from the vendor of
*   this transform.
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/06/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
STDMETHODIMP CDXTWipe::get_Copyright( BSTR *pVal )
{
    HRESULT hr = S_OK;

    if( _LICENSED_VERSION )
    {
        if( DXIsBadWritePtr( pVal, sizeof( *pVal ) ) )
        {
            hr = E_POINTER;
        }
        else
        {
            *pVal = SysAllocString( g_Notice );
        }
    }
    else
    {
        hr = E_NOTIMPL;
    }

    return hr;
} /* CDXTWipe::get_Copyright */

/*****************************************************************************
* CDXTWipe::put_Copyright *
*-------------------------*
*   Description:
*       This method is used to compare the copyright notice being passed in
*   with the one generated by the object. The free consumer version does not
*   persist it's properties, but the licensed version does.
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/06/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
STDMETHODIMP CDXTWipe::put_Copyright( BSTR newVal )
{
    HRESULT hr = E_INVALIDARG;

    if( !wcscmp(g_Notice,newVal) )
    {
        hr = S_OK;
        m_bCopyrightIsNotValid = false;
    }
    return hr;
} /* CDXTWipe::put_Copyright */

/*****************************************************************************
* CDXTWipe::OnSetup *
*-------------------*
*   Description:
*       This method is used to get the size of the inputs and validate that
*   they are the same.
*-----------------------------------------------------------------------------
*   Created By: EDC                                     Date: 01/06/98
*-----------------------------------------------------------------------------
*   
*****************************************************************************/
HRESULT CDXTWipe::OnSetup( DWORD dwFlags )
{
    //--- Compute the effect step resolution and weights
    HRESULT hr;
    CDXDBnds InBounds(InputSurface(0), hr);
    if (SUCCEEDED(hr))
    {
        InBounds.GetXYSize(m_InputSize);
        _UpdateStepRes();
        hr = _UpdateGradWeights();
    }
    return hr;
} /* CDXTWipe::OnSetup */


void CDXTWipe::OnGetSurfacePickOrder(const CDXDBnds & OutPoint, ULONG & ulInToTest, ULONG aInIndex[], BYTE aWeight[])
{
    ULONG AWid, AStart, BWid, BUnpackWid, GradStart, GradWid, GradWgtStart;
    _ComputeStartPoints(OutPoint, AWid, AStart, BWid, BUnpackWid,
                        GradStart, GradWid, GradWgtStart);
    if (GradWid)
    {
        ulInToTest = 2;
        BYTE Wgt = (BYTE)m_pGradientWeights[GradWgtStart];
        if (Wgt > 127)
        {
            aInIndex[0] = 1; aInIndex[1] = 0;
            aWeight[0] = Wgt; aWeight[1] = DXInvertAlpha(Wgt);
        }
        else
        {
            aInIndex[0] = 0; aInIndex[1] = 1;
            aWeight[0] = DXInvertAlpha(Wgt); aWeight[1] = Wgt; 
        }
    }
    else
    {
        ulInToTest = 1;
        aWeight[0] = 255;
        aInIndex[0] = (AWid) ? 0 : 1;
    }
}



//  ALL CODE FROM THIS POINT ON IS TIME-CRITICAL SO OPTIMIZE FOR SPEED OVER SIZE!

#ifndef _DEBUG
#pragma optimize("agtp", on)
#endif

void CDXTWipe::_ComputeStartPoints(const CDXDBnds & bnds,
    ULONG & AWid, ULONG & AStart, ULONG & BWid, ULONG & BUnpackWid,
    ULONG & GradStart, ULONG & GradWid, ULONG & GradWgtStart)
{
    AWid = 0, AStart = 0, BWid = 0, BUnpackWid = 0;
    GradStart = 0, GradWid = 0, GradWgtStart = 0;
    ULONG BndsWid = bnds.Width();
    ULONG ulRange     = m_InputSize.cx + m_GradientSize;
    long LeadEdgePos  = (long)(ulRange * GetEffectProgress());
    long TrailEdgePos = LeadEdgePos - m_GradientSize;

    if( LeadEdgePos >= bnds.Left() )
    {
        if( LeadEdgePos <= bnds.Right() )
        {
            if( TrailEdgePos < bnds.Left() )
            {
                //--- Leading in-between, trailing out
                GradWid = m_GradientSize - ( bnds.Left() - TrailEdgePos );
                GradWgtStart = bnds.Left() - TrailEdgePos;
            }
            else
            {
                //--- Leading and Trailing in between
                GradWid = m_GradientSize;
                BWid = TrailEdgePos - bnds.Left();
            }
            GradStart = m_GradientSize - GradWid;
            AWid = BndsWid - GradWid - BWid;
        }
        else
        {
            if( TrailEdgePos < bnds.Left() )
            {
                //--- Leading is past right, trailing is before left
                GradWid      = BndsWid;
                GradWgtStart = bnds.Left() - TrailEdgePos;
            }
            else if( TrailEdgePos < bnds.Right() )
            {
                //--- Leading is past right, trailing is in between
                GradWid = bnds.Right() - TrailEdgePos;
                BWid    = BndsWid - GradWid;
            }
            else
            {
                //--- All B
                BWid = BndsWid;
            }
        }
        GradStart  = BWid;
        BUnpackWid = BWid + GradWid;
        AStart     = GradStart + GradWid;
    }
    else
    {
        //--- All A
        AWid = BndsWid;
    }
}

//
//=== Work procedure =========================================================
//


/*****************************************************************************
* WorkProc *
*----------*
*   Description:
*       This function is used to calculate the result based on the specified
*   bounds and the current effect progress. This is a simple subset of the
*   full functionality to provide the simplest example possible (not necessarily
*   the most efficient). THIS JUST WIPES RIGHT TO KEEP IT SIMPLE.
*-----------------------------------------------------------------------------
*   Created By: EDC                                 Date: 01/06/98
*-----------------------------------------------------------------------------
*   Parameters:
*****************************************************************************/
HRESULT CDXTWipe::WorkProc( const CDXTWorkInfoNTo1& WI, BOOL* pbContinue )
{
    HRESULT hr = S_OK;

    //--- Check security
    if( m_bCopyrightIsNotValid )
    {
        return DXTERR_COPYRIGHT_IS_INVALID;
    }

    //--- Get input sample access pointer for the requested region.
    //    Note: Lock may fail due to a lost surface.
    CComPtr<IDXARGBReadPtr> pInA;
    hr = InputSurface( 0 )->LockSurface( &WI.DoBnds, m_ulLockTimeOut, DXLOCKF_READ,
                                         IID_IDXARGBReadPtr, (void**)&pInA, NULL );
    if( FAILED( hr ) ) return hr;

    CComPtr<IDXARGBReadPtr> pInB;
    hr = InputSurface( 1 )->LockSurface( &WI.DoBnds, m_ulLockTimeOut, DXLOCKF_READ,
                                         IID_IDXARGBReadPtr, (void**)&pInB, NULL );
    if( FAILED( hr ) ) return hr;


    //--- Put a write lock only on the region we are updating so multiple
    //    threads don't conflict.
    //    Note: Lock may fail due to a lost surface.
    CComPtr<IDXARGBReadWritePtr> pOut;
    hr = OutputSurface()->LockSurface( &WI.OutputBnds, m_ulLockTimeOut, DXLOCKF_READWRITE,
                                       IID_IDXARGBReadWritePtr, (void**)&pOut, NULL );
    if( FAILED( hr ) ) return hr;

    //--- Allocate a working buffer
    ULONG DoBndsWid = WI.DoBnds.Width();
    DXPMSAMPLE* pRowBuff = (DXPMSAMPLE*)alloca( DoBndsWid * sizeof( DXPMSAMPLE ) );

    //--- Allocate output buffer if needed
    DXPMSAMPLE *pOutBuff = NULL;
    if( OutputSampleFormat() != DXPF_PMARGB32 )
    {
        pOutBuff = DXPMSAMPLE_Alloca( DoBndsWid );
    }

    //--- Compute the width of each region
    ULONG ulDoNumRows = WI.DoBnds.Height();

    ULONG AWid, AStart, BWid, BUnpackWid, GradStart, GradWid, GradWgtStart;
    _ComputeStartPoints(WI.DoBnds, AWid, AStart, BWid, BUnpackWid,
                        GradStart, GradWid, GradWgtStart);

    //--- Allocate working buffers for the gradient area
    DXPMSAMPLE *pGradBuff = DXPMSAMPLE_Alloca( GradWid );

    //
    //  Set up the dither structure
    //
    DXDITHERDESC dxdd;
    if (DoDither())
    {
        dxdd.x = WI.OutputBnds.Left();
        dxdd.y = WI.OutputBnds.Top();
        dxdd.pSamples = pRowBuff;
        dxdd.cSamples = DoBndsWid;
        dxdd.DestSurfaceFmt = OutputSampleFormat();
    }

    //=== Main loop =================================================
    for( ULONG OutY = 0; *pbContinue && ( OutY < ulDoNumRows); ++OutY )
    {
        //--- Get leading solid B samples
        if( BUnpackWid )
        {
            pInB->MoveToRow( OutY );
            pInB->UnpackPremult( pRowBuff, BUnpackWid, FALSE );
        }
    
        //--- Compute gradient transition area
        if( GradWid )
        {
            pInA->MoveToXY( BWid, OutY );
            pInA->UnpackPremult( pGradBuff, GradWid, FALSE );

            for( ULONG i = 0; i < GradWid; ++i )
            {
                ULONG Wgt = m_pGradientWeights[GradWgtStart+i];
                pRowBuff[BWid+i] = DXScaleSample( pGradBuff[i], Wgt ^ 0xFF ) + 
                                   DXScaleSample( pRowBuff[BWid+i], Wgt ); 
            }
        }

        //--- Get trailing solid A samples
        if( AWid )
        {
            pInA->MoveToXY( AStart, OutY );
            pInA->UnpackPremult( pRowBuff + AStart, AWid, FALSE );
        }

        //--- Get the output row
        pOut->MoveToRow( OutY );
        if (DoDither())
        {
            DXDitherArray(&dxdd);
            dxdd.y++;
        }
        if (DoOver())
        {
            pOut->OverArrayAndMove(pOutBuff, pRowBuff, DoBndsWid);
        }
        else
        {
            pOut->PackPremultAndMove(pRowBuff, DoBndsWid);
        }
    } // End for
    return hr;
} /* WipeProc */



