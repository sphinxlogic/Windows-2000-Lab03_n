// GradPtr.cpp: implementation of the CGradPtr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "grad.h"
#include "GradPtr.h"
#include "surface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//
//  In release builds always optimize for speed.
//
#ifndef _DEBUG
#pragma optimize("agtp", on)
#endif

void CGradPtr::_CalcEndColorsForRow(ULONG Row)
{
    CSurface *pSurface = (CSurface *)m_pSurface;
    m_CurY = Row;
    float PercentThere = ((float)Row) / ((float)m_pSurface->m_Height);
    BYTE Weight = (BYTE)(PercentThere * 255.0f);
    DXPMSAMPLE Start = pSurface->m_ULColor;
    DXPMSAMPLE End = pSurface->m_LLColor;
    m_LeftColor = DXScaleSample(Start, DXInvertAlpha(Weight)) + DXScaleSample(End, Weight);
    Start = pSurface->m_URColor;
    End = pSurface->m_LRColor;
    m_RightColor = DXScaleSample(Start, DXInvertAlpha(Weight)) + DXScaleSample(End, Weight);
    m_bColorPremult = true;
}


ULONG STDMETHODCALLTYPE CGradPtr::MoveAndGetRunInfo(ULONG Row, const DXRUNINFO ** ppInfo)
{
    if (m_CurY != Row) _CalcEndColorsForRow(Row);
    m_RunInfo.Type = (m_LeftColor.Alpha == 0xFF && m_RightColor.Alpha == 0xFF) ? DXRUNTYPE_OPAQUE :
    ((m_LeftColor.Alpha == 0 && m_RightColor.Alpha == 0) ? DXRUNTYPE_CLEAR : DXRUNTYPE_TRANS );
    return CDXBaseARGBPtr::MoveAndGetRunInfo(Row, ppInfo);
}


void CGradPtr::FillSamples(const DXPtrFillInfo & FillInfo)
{
    if (m_CurY != FillInfo.y) _CalcEndColorsForRow(FillInfo.y);
    if (FillInfo.bPremult && (!m_bColorPremult))
    {
        m_bColorPremult = FillInfo.bPremult;
        if (FillInfo.bPremult)
        {
            m_LeftColor = DXUnPreMultSample((DXPMSAMPLE)m_LeftColor);
            m_RightColor = DXUnPreMultSample((DXPMSAMPLE)m_RightColor);
        }
        else
        {
            m_LeftColor = DXPreMultSample((DXSAMPLE)m_LeftColor);
            m_RightColor = DXPreMultSample((DXSAMPLE)m_RightColor);
        }
    }
    
    DXBASESAMPLE *pSamples = FillInfo.pSamples;

    // if end colors are the same, just fill with the color
    if( m_LeftColor == m_RightColor )
    {
        for (DXBASESAMPLE * pRunLimit = pSamples + FillInfo.cSamples; pSamples < pRunLimit; pSamples++)
        {
            *pSamples = m_LeftColor;
        }
    }
    else
    {
        float xInc = 1.0F / ((float)m_pSurface->m_Width);
        float PercentThere = ((float)FillInfo.x) * xInc;
        BYTE Weight;
    
        for (DXBASESAMPLE * pRunLimit = pSamples + FillInfo.cSamples; pSamples < pRunLimit; pSamples++)
        {
            Weight = (BYTE)(PercentThere * 255.0f);
            *pSamples = DXScaleSample(m_LeftColor, DXInvertAlpha(Weight)) + DXScaleSample(m_RightColor, Weight);
            PercentThere += xInc;
        }
    }
}

