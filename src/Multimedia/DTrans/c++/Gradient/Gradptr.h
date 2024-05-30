// GradPtr.h: interface for the CGradPtr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRADPTR_H__D4ADDB81_A306_11D1_9054_00C04FD9189D__INCLUDED_)
#define AFX_GRADPTR_H__D4ADDB81_A306_11D1_9054_00C04FD9189D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSurface;

class CGradPtr : public CDXBaseARGBPtr
{
public:
    ULONG           m_CurY;
    DXBASESAMPLE    m_LeftColor;
    DXBASESAMPLE    m_RightColor;
    BOOL            m_bColorPremult;

    CGradPtr(CDXBaseSurface * pSurface) : CDXBaseARGBPtr(pSurface) {}
    void FillSamples(const DXPtrFillInfo & FillInfo);
    void _CalcEndColorsForRow(ULONG Row);

    ULONG STDMETHODCALLTYPE MoveAndGetRunInfo(ULONG Row, const DXRUNINFO ** ppInfo);
};

#endif // !defined(AFX_GRADPTR_H__D4ADDB81_A306_11D1_9054_00C04FD9189D__INCLUDED_)
