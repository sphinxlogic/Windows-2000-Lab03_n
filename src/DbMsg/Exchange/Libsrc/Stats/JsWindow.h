// --jswindow.h-----------------------------------------------------------------
// 
//  Defines Jump Sliding Window object.
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef __jswindow_h
#define __jswindow_h

#include <windows.h>
#include "fifo.h"

//$--CJSWindow------------------------------------------------------------------
// Defines the Jump Slide base class. Other kinds of Jump Slide windows
// are derived from this class.
// -----------------------------------------------------------------------------
class CJSWindow
{
public:
    CJSWindow ();
    virtual ~CJSWindow ();
    virtual HRESULT HrReset(IN __int64 liNow, IN __int64 liResolution, IN DWORD dwWindowDuration);
    virtual VOID DataPoint(IN __int64 liNow, IN DWORD dwValue) = 0;
    virtual HRESULT HrGetValue(IN __int64 liNow, OUT DWORD &dwValue, DWORD &dwFractionCompleteNum, DWORD &dwFractionCompleteDen) = 0;

    VOID AdvanceToNow(IN __int64 liNow, OUT DWORD &dwFIFOOut, OUT BOOL &fAdvanced);

    __int64 m_liCurrentIntervalTimeStart;
    __int64 m_liResolution;
    CFIFO m_FIFO;
    DWORD m_dwIntervalValue;
};


//$--CJSWindowMin---------------------------------------------------------------
// Defines the Jump Slide window that determines the minimum value for a period.
// Derived from the CJSWindow Base Class.
// -----------------------------------------------------------------------------
class CJSWindowMin : public CJSWindow
{
public:
    VOID DataPoint(IN __int64 liNow, IN DWORD dwValue);
    HRESULT HrGetValue(IN __int64 liNow, OUT DWORD &dwValue, DWORD &dwFractionCompleteNum, OUT DWORD &dwFractionCompleteDen);
};


//$--CJSWindowMax---------------------------------------------------------------
// Defines the Jump Slide window that determines the maximum value for a period.
// Derived from the CJSWindow Base Class.
// -----------------------------------------------------------------------------
class CJSWindowMax : public CJSWindow
{
public:
    VOID DataPoint(IN __int64 liNow, IN DWORD dwValue);
    HRESULT HrGetValue(IN __int64 liNow, OUT DWORD &dwValue, DWORD &dwFractionCompleteNum, DWORD &dwFractionCompleteDen);
};


//$--CJSWindowAverage------------------------------------------------------------
// Defines the Jump Slide window that determines the average value for a period.
// Derived from the CJSWindow Base Class.
// -----------------------------------------------------------------------------
class CJSWindowAverage : public CJSWindow
{
public:
    HRESULT HrReset(IN __int64 liNow, IN __int64 liResolution, IN DWORD dwWindowDuration);
    VOID DataPoint(IN __int64 liNow, IN DWORD dwValue);
    HRESULT HrGetValue(IN __int64 liNow, OUT DWORD &dwValue, DWORD &dwFractionCompleteNum, DWORD &dwFractionCompleteDen);

private:
    DWORD m_dwIntervalTotal;
    DWORD m_cIntervalValues;
};


//$--CJSWindowTotal--------------------------------------------------------------
// Defines the Jump Slide window that determines the total value for a period.
// Derived from the CJSWindow Base Class.
// -----------------------------------------------------------------------------
class CJSWindowTotal : public CJSWindow
{
public:
    HRESULT HrReset(IN __int64 liNow, IN __int64 liResolution, IN DWORD dwWindowDuration);
    VOID DataPoint(IN __int64 liNow, IN DWORD dwValue);
    HRESULT HrGetValue(IN __int64 liNow, OUT DWORD &dwValue, OUT DWORD &dwFractionCompleteNum, OUT DWORD &dwFractionCompleteDen);

private:
    DWORD m_dwWindowTotal;
};

#endif
