// --jswindow.cpp---------------------------------------------------------------
//
//  Implements a Jump Sliding window (jswindow) object.  The window collects
//  events and can return either an estimate or actual number of events
//  collected during the most recent window period.
//
//  The window contains a current register and a FIFO buffer.
//
//
//    |___|    |___|___|___|___|___|___| ... |___|___|
//   Current     1   2   3   4   5   6        i-1  i
//                      FIFO Buffer
//
//  The current register will collect events until the current interval has
//  passed. The this interval defines the resolution of the JSWindow.
//  A typical interval resolution is 10 seconds.
//
//  When the current register's interval has elapsed, it dumps its contents
//  into the FIFO buffer. In doing so it pushes the oldest contents out of
//  the end of the buffer.  The length of the FIFO buffer is called the
//  "duration" of the window and is expressed as the number of intervals.
//
//  A running total of all of the events contained within the FIFO buffer
//  is kept. Whenever new events are added to the buffer, they are also
//  added to the running total. When the old events are pushed out of the
//  end of the buffer, they are subtracted from the running total.
//
//  The running total is the number of events recorded in the last
//  "duration" of time.  ie.  If the duration time is 60 resolution
//  units, each resolution unit being 60 seconds long, then the
//  running total is the number of events per hour (60 * 60 = 3600 seconds).
//
//  You can query the window value using the GetValue() member function.
//  If the interval hasn't had time to fill (ie. if the interval is 1 hour and
//  you query it after 1 minute) then the ratio of dwFractionCompleteNum /
//  dwFractionCompleteDen will represent the fraction of the window
//  period that was filled when the GetValue request was made.
//
//  This code is NOT multithread safe.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "jswindow.h"
#include "jswindow.chk"


//$--CJSWindow::CJSWindow-------------------------------------------------------
//  Constructor
// -----------------------------------------------------------------------------
CJSWindow::CJSWindow()
{
    DEBUGPRIVATE("CJSWindow::CJSWindow\n");

}

//$--CJSWindow::~CJSWindow------------------------------------------------------
//  Destructor
// -----------------------------------------------------------------------------
CJSWindow::~CJSWindow()
{
    DEBUGPRIVATE("CJSWindow::~CJSWindow\n");

}

//$--CJSWindow::HrReset---------------------------------------------------------
//  Sets up the parameters of the JSWindow. This function must be called
//  after creating and before using the interval.
// -----------------------------------------------------------------------------
HRESULT CJSWindow::HrReset(        // RETURNS: HRESULT
    IN __int64 liNow,              // The current time in arbitrary units.
    IN __int64 liResolution,       // The resolution of the interval in arbitrary units.
    IN DWORD dwWindowDuration)     // The interval duration expressed in multiples of
                                   // resolution.
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("CJSWindow::rcReset\n");

    hr = m_FIFO.HrReset(dwWindowDuration);

    m_liCurrentIntervalTimeStart = liNow;
    m_liResolution = liResolution;
    m_dwIntervalValue = 0;

    RETURN(hr);
}


//$--CJSWindow::AdvanceToNow----------------------------------------------------
//  Advances the JSWindow so that liNow is within the current active interval.
// -----------------------------------------------------------------------------
VOID CJSWindow::AdvanceToNow(       // RETURNS: nothing
    IN __int64 liNow,               // Current time.
    OUT DWORD &dwFIFOOut,           // Data pushed out of the FIFO buffer
	OUT BOOL &fAdvanced)            // returns TRUE if a jump happened
{

    HRESULT hr = NOERROR;
    DWORD dwFIFOOut1    = 0;
    DWORD dwFIFOOut2    = 0;
    DWORD iDelta        = 0;
    __int64 liDeltaTime = 0;

    DEBUGPRIVATE("CJSWindow::AdvanceToNow\n");

	fAdvanced = FALSE;

	hr = CHK_CJSWindow_AdvanceToNow(liNow, dwFIFOOut, fAdvanced);
	if (FAILED(hr))
		return;

    ASSERTERROR(m_liResolution!=0,"CJSWindow::AdvanceToNow() member m_liResolution == 0");

    // Calculate the number of intervals that have passed since
    // the window was last updated and liNow. 
    //
    // Find the difference between liNow and the last interval and divide
    // by the resolution.
    //
    // -----------------------------------------------------------------------------

    liDeltaTime = liNow - m_liCurrentIntervalTimeStart;
    iDelta = (DWORD)(liDeltaTime / m_liResolution);

    if (iDelta > 0)
    {
        fAdvanced = TRUE;
        m_FIFO.PushElement(m_dwIntervalValue, dwFIFOOut1);
        m_dwIntervalValue = 0;


        m_FIFO.PushNNulls(iDelta-1, dwFIFOOut2);
        m_liCurrentIntervalTimeStart = (m_liResolution * iDelta) + m_liCurrentIntervalTimeStart;
    }

    dwFIFOOut = dwFIFOOut1 + dwFIFOOut2;

    return;
}


//$--CJSWindowTotal::HrReset----------------------------------------------------
//  Sets up the parameters of the JSWindow. This function must be called
//  after creating and before using the interval.
// -----------------------------------------------------------------------------
HRESULT CJSWindowTotal::HrReset(   // RETURNS: HRESULT
    IN __int64 liNow,              // The current time in arbitrary units.
    IN __int64 liResolution,       // The resolution of the interval in arbitrary units.
    IN DWORD dwWindowDuration)     // The interval duration expressed in multiples of
                                   // resolution.
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("CJSWindowTotal::HrReset()\n");

	hr = CHK_CJSWindowTotal_HrReset(liNow, liResolution, dwWindowDuration);
	if (FAILED(hr))
		RETURN(hr);

    hr = CJSWindow::HrReset(liNow,liResolution,dwWindowDuration);

    m_dwWindowTotal = 0;

    RETURN(hr);
}

//$--CJSWindowTotal::DataPoint--------------------------------------------------
//  Used to add a count of events to the total window.
// -----------------------------------------------------------------------------
VOID CJSWindowTotal::DataPoint(
    IN __int64 liNow,           // Event time in arbitrary units.
    IN DWORD dwValue)           // Number of events to add for this time.
{
    HRESULT hr = NOERROR;
    DWORD dwFIFOIn  = 0;
    DWORD dwFIFOOut  = 0;
    BOOL fAdvanced = FALSE;

    DEBUGPRIVATE("CJSWindowTotal::DataPoint()\n");

	hr = CHK_CJSWindowTotal_DataPoint(liNow, dwValue);
	if (FAILED(hr))
		return;

    dwFIFOIn = m_dwIntervalValue;

    AdvanceToNow(liNow, dwFIFOOut, fAdvanced);
    if (fAdvanced)
    {
        m_dwWindowTotal += dwFIFOIn;
        m_dwWindowTotal -= dwFIFOOut;
    }

    m_dwIntervalValue += dwValue;
}


//$--CJSWindowTotal::HrGetValue-------------------------------------------------
//  Returns the total number of events in the window period. Also returns
//  the number of intervals that have been entered.
// -----------------------------------------------------------------------------
HRESULT CJSWindowTotal::HrGetValue(
    IN __int64 liNow,                   // Current time expressed as FILETIME.
    OUT DWORD &dwValue,                 // Receives window value.
    OUT DWORD &dwFractionCompleteNum,   // numerator
    OUT DWORD &dwFractionCompleteDen)   // denominator
{
    HRESULT hr          = NOERROR;
    DWORD dwFIFOOut     = 0;
    DWORD dwFIFOIn      = 0;
    BOOL fAdvanced      = FALSE;

    DEBUGPRIVATE("CJSWindowTotal::HrGetValue()\n");

	hr = CHK_CJSWindowTotal_HrGetValue(
		liNow, 
		dwValue, 
		dwFractionCompleteNum, 
		dwFractionCompleteDen);
	if (FAILED(hr))
		RETURN(hr);

    dwValue = 0;
    dwFractionCompleteNum = 0;
    dwFractionCompleteDen = 1;

    dwFIFOIn = m_dwIntervalValue;
    AdvanceToNow(liNow, dwFIFOOut, fAdvanced);
    if (fAdvanced)
    {
        m_dwWindowTotal += dwFIFOIn;
        m_dwWindowTotal -= dwFIFOOut;
    }

    if (m_FIFO.dwNumberElements() != 0 )
    {
        dwValue =  m_dwWindowTotal;
        dwFractionCompleteNum = m_FIFO.dwNumberElements();
        dwFractionCompleteDen = m_FIFO.dwMaxNumberElements();
    }

    RETURN(hr);
}


//$--CJSWindowMin::DataPoint----------------------------------------------------
//  Used to add a count of events to the total window.
// -----------------------------------------------------------------------------
VOID CJSWindowMin::DataPoint(
    IN __int64 liNow,           // Event time in arbirary units.
    IN DWORD dwValue)           // Number of events to add for this time.
{
    HRESULT hr = NOERROR;
    DWORD dwFIFOOut;
    BOOL fAdvanced = FALSE;

    DEBUGPRIVATE("CJSWindow::DataPoint()\n");

	hr = CHK_CJSWindowMin_DataPoint(liNow, dwValue);
	if (FAILED(hr))
		return;

    AdvanceToNow(liNow, dwFIFOOut, fAdvanced);

    if (m_dwIntervalValue > dwValue)
        m_dwIntervalValue = dwValue;
}


//$--CJSWindowMin::HrGetValue---------------------------------------------------
//  Returns the total number of events in the window period. Also returns
//  the number of intervals that have been entered.
// -----------------------------------------------------------------------------
HRESULT CJSWindowMin::HrGetValue(
    IN __int64 liNow,                   // Current time expressed as FILETIME.
    OUT DWORD &dwValue,                 // Receives window value.
    OUT DWORD &dwFractionCompleteNum,   // numerator
    OUT DWORD &dwFractionCompleteDen)   // denominator
{
    HRESULT hr = NOERROR;
    DWORD i = 0;
    DWORD dwFIFOOut =0;
    BOOL fAdvanced = FALSE;

    DEBUGPRIVATE("CJSWindowMin::HrGetValue()\n");

	hr = CHK_CJSWindowMin_HrGetValue(
		liNow, 
		dwValue, 
		dwFractionCompleteNum, 
		dwFractionCompleteDen);
	if (FAILED(hr))
		RETURN(hr);

    dwValue = 0;
    dwFractionCompleteNum = 0;
    dwFractionCompleteDen = 1;

    AdvanceToNow(liNow, dwFIFOOut, fAdvanced);
    m_FIFO.Min(dwValue);

    dwFractionCompleteNum = m_FIFO.dwNumberElements();
    dwFractionCompleteDen = m_FIFO.dwMaxNumberElements();

    RETURN(hr);
}


//$--CJSWindowMax::DataPoint----------------------------------------------------
//  Used to add a count of events to the total window.
// -----------------------------------------------------------------------------
VOID CJSWindowMax::DataPoint(
    IN __int64 liNow,           // Event time in arbirary units.
    IN DWORD dwValue)           // Number of events to add for this time.
{
    HRESULT hr = NOERROR;
    DWORD dwFIFOOut = 0;
    BOOL fAdvanced = FALSE;

    DEBUGPRIVATE("CJSWindowMax::DataPoint()\n");

	hr = CHK_CJSWindowMax_DataPoint(liNow, dwValue);
	if (FAILED(hr))
		return;

    AdvanceToNow(liNow, dwFIFOOut, fAdvanced);

    if (m_dwIntervalValue < dwValue)
        m_dwIntervalValue = dwValue;
}


//$--CJSWindowMax::HrGetValue---------------------------------------------------
//  Returns the total number of events in the window period. Also returns
//  the number of intervals that have been entered.
// -----------------------------------------------------------------------------
HRESULT CJSWindowMax::HrGetValue(
    IN __int64 liNow,                  // Current time expressed as FILETIME.
    OUT DWORD &dwValue,                // Receives window value.
    OUT DWORD &dwFractionCompleteNum,  // Numerator of fraction completed.
    OUT DWORD &dwFractionCompleteDen)  // Denominator of fraction completed.
{
    HRESULT hr = NOERROR;
    DWORD i = 0;
    DWORD dwFIFOOut = 0;
    BOOL fAdvanced = FALSE;

    DEBUGPRIVATE("CJSWindowMax::HrGetValue()\n");

	hr = CHK_CJSWindowMax_HrGetValue(
		liNow, 
		dwValue, 
		dwFractionCompleteNum, 
		dwFractionCompleteDen);
	if (FAILED(hr))
		RETURN(hr);

    dwValue = 0;
    dwFractionCompleteNum = 0;
    dwFractionCompleteDen = 1;

    AdvanceToNow(liNow,dwFIFOOut, fAdvanced);

    m_FIFO.Max(dwValue);
    dwFractionCompleteNum = m_FIFO.dwNumberElements();
    dwFractionCompleteDen = m_FIFO.dwMaxNumberElements();

    RETURN(hr);
}


//$--CJSWindowAverage::HrReset----------------------------------------------------
//  Sets up the parameters of the JSWindow. This function must be called
//  after creating and before using the interval.
// -----------------------------------------------------------------------------
HRESULT CJSWindowAverage::HrReset( // RETURNS: HRESULT
    IN __int64 liNow,              // The current time in arbitrary units.
    IN __int64 liResolution,       // The resolution of the interval in arbitrary units.
    IN DWORD dwWindowDuration)     // The interval duration expressed in multiples of
                                   // resolution.
{
    HRESULT hr = NOERROR;

    DEBUGPRIVATE("CJSWindowAverage::HrReset\n");

	hr = CHK_CJSWindowAverage_HrReset(liNow, liResolution, dwWindowDuration);
	if (FAILED(hr))
		RETURN(hr);

    m_cIntervalValues = 0;
    m_dwIntervalTotal = 0;

    hr = CJSWindow::HrReset(liNow, liResolution, dwWindowDuration);
    RETURN(hr);
}


//$--CJSWindowAverage::DataPoint----------------------------------------------------
//  Used to add a count of events to the total window.
// -----------------------------------------------------------------------------
VOID CJSWindowAverage::DataPoint(
    IN __int64 liNow,             // Event time in arbirary units.
    IN DWORD dwValue)             // Number of events to add for this time.
{
    HRESULT hr = NOERROR;
    DWORD dwFIFOOut = 0;
    BOOL  fAdvanced = FALSE;

    DEBUGPRIVATE("CJSWindowAverage::DataPoint()\n");

	hr = CHK_CJSWindowAverage_DataPoint(liNow, dwValue);
	if (FAILED(hr))
		return;

    AdvanceToNow(liNow, dwFIFOOut, fAdvanced);

    if (fAdvanced)
    {
        m_dwIntervalTotal = 0;
        m_cIntervalValues = 0;
    }

    m_dwIntervalTotal += dwValue;
    m_cIntervalValues ++;
    if (m_cIntervalValues > 0)
        m_dwIntervalValue = m_dwIntervalTotal / m_cIntervalValues;
    else
        m_dwIntervalValue = 0;

}

//$--CJSWindowAverage::HrGetValue-----------------------------------------------
//  Returns the total number of events in the window period. Also returns
//  the number of intervals that have been entered.
// -----------------------------------------------------------------------------
HRESULT CJSWindowAverage::HrGetValue(
    IN __int64 liNow,                   // Current time expressed as FILETIME.
    OUT DWORD &dwValue,                 // Receives window value.
    OUT DWORD &dwFractionCompleteNum,   // numerator
    OUT DWORD &dwFractionCompleteDen)   // denominator
{
    HRESULT hr = NOERROR;
    DWORD dwSum = 0;
    DWORD i = 0;
    DWORD dwFIFOOut = 0;
    BOOL fAdvanced = FALSE;

    DEBUGPRIVATE("CJSWindowAverage::HrGetValue()\n");

	hr = CHK_CJSWindowAverage_HrGetValue(
		liNow, 
		dwValue, 
		dwFractionCompleteNum, 
		dwFractionCompleteDen);
	if (FAILED(hr))
		RETURN(hr);

    dwValue = 0;
    dwFractionCompleteNum = 0;
    dwFractionCompleteDen = 1;

    AdvanceToNow(liNow, dwFIFOOut, fAdvanced);

    m_FIFO.Average(dwValue);
    dwFractionCompleteNum = m_FIFO.dwNumberElements();
    dwFractionCompleteDen = m_FIFO.dwMaxNumberElements();

    RETURN(hr);
}

