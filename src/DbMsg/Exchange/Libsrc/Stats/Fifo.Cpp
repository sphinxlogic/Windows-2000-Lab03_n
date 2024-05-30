// --fifo.cpp-------------------------------------------------------------------
// 
//  Implements a FIFO buffer.
// 
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#include "edk.h"
#include "fifo.h"
#include "fifo.chk"

//$--CFIFO::CFIFO---------------------------------------------------------------
//  Constructor
// -----------------------------------------------------------------------------
CFIFO::CFIFO()
{
    DEBUGPRIVATE("CFIFO::CFIFIO()\n");

    m_nElements       = 0;
    m_maxElements     = 0;
    m_iCurrentElement = 0;
    m_padwFIFOBuffer  = NULL;
}

//$--CFIFO::~CFIFO--------------------------------------------------------------
//  Destructor
// -----------------------------------------------------------------------------
CFIFO::~CFIFO()
{
    DEBUGPRIVATE("CFIFO::~CFIFIO()\n");

    FREE(m_padwFIFOBuffer);
}


//$--CFIFO::HrReset-------------------------------------------------------------
//  Resets the FIFO buffer. Should be called after object is constructed
//  and before it is used.
// -----------------------------------------------------------------------------
HRESULT CFIFO::HrReset(                 // RETURNS: NOERROR if reset successful.
    IN DWORD maxElements)               // Maximum number of elements in buffer. 
{
    HRESULT hr  = NOERROR;
    DWORD cb    = sizeof(DWORD) * maxElements;

    DEBUGPRIVATE("CFIFO::HrReset()\n");

	hr = CHK_CFIFO_HrReset(maxElements);
	if (FAILED(hr))
		RETURN(hr);

    FREE(m_padwFIFOBuffer);

    m_padwFIFOBuffer = (DWORD *) malloc( cb );
    if (m_padwFIFOBuffer == NULL)
    {
        hr = HR_LOG(E_OUTOFMEMORY);
        goto cleanup;
    }

    FillMemory(m_padwFIFOBuffer,cb,0);

    m_maxElements     = maxElements;
    m_nElements       = 0;
    m_iCurrentElement = 0;

cleanup:
    RETURN(hr);        
    
}


//$--CFIFO::PushElement---------------------------------------------------------
//  Pushes a new element into the FIFO buffer. Returns the value pushed out
//  the other side.
// -----------------------------------------------------------------------------
VOID CFIFO::PushElement(        
    IN DWORD dwValue,           // New Value to Push into buffer. 
    OUT DWORD &dwPushedOut)     // Recieves old value pushed out of buffer. 
{
    HRESULT hr  = NOERROR;

    DEBUGPRIVATE("CFIFO::PushElement()\n");

	hr = CHK_CFIFO_PushElement(dwValue, dwPushedOut);
	if (FAILED(hr))
		return;

    // Return whatever is at curent element.
    // -------------------------------------
    dwPushedOut = m_padwFIFOBuffer[m_iCurrentElement];
    m_padwFIFOBuffer[m_iCurrentElement] = dwValue;

    if (m_nElements < m_maxElements)
    {
        m_nElements++;
    }
        
    // Update current element pointer
    //-------------------------------
    m_iCurrentElement++;
    if (m_iCurrentElement >= m_maxElements)
    {
        m_iCurrentElement = 0;
    }

    return;
}


//$--CFIFO::PushNNulls----------------------------------------------------------
//  Push a number of 0 Values into the FIFO buffer.  Returns a summation
//  of the values pushed out the other side.
// -----------------------------------------------------------------------------
VOID CFIFO::PushNNulls(         
    IN DWORD cNulls,            // Number of NULLS to push. 
    OUT DWORD &dwPushedOut)     // Receives total values pushed out. 
{
    HRESULT hr  = NOERROR;
    DWORD i = 0;
    DWORD cCurrentToEnd = 0;

    DEBUGPRIVATE("CFIFO::PushNNulls()\n");

	hr = CHK_CFIFO_PushNNulls(cNulls, dwPushedOut);
	if (FAILED(hr))
		return;

    dwPushedOut = 0;

    if (cNulls == 0)
        goto cleanup;

    // case: cNulls is larger than the max number of buffer elements.
    // Action: Clear the entire buffer and reset the current index.
    // ------------------------------------------------------------
    if (cNulls >=  m_maxElements)
    {
        for (i=0; i<m_maxElements; i++)
        {
            dwPushedOut += m_padwFIFOBuffer[i];
            m_padwFIFOBuffer[i] = 0 ;
        }

        m_iCurrentElement = 0;
        goto cleanup;
    }

    // case: cNulls will advance current index past end of buffer
    // action:  1) clear the elements from current index+1 to end of buffer.
    //          2) clear elements from start of buffer to new index. 
    // ---------------------------------------------------------------------
    cCurrentToEnd = (m_maxElements-1) - m_iCurrentElement;
    if (cNulls > cCurrentToEnd)
    {
        for (i=m_iCurrentElement; i<m_maxElements; i++)
        {
            dwPushedOut += m_padwFIFOBuffer[i];
            m_padwFIFOBuffer[i] = 0;
        } 

        m_iCurrentElement = cNulls - cCurrentToEnd - 1;
        for (i=0; i< m_iCurrentElement; i++)
        {
            dwPushedOut += m_padwFIFOBuffer[i];
            m_padwFIFOBuffer[i] = 0;
        } 
        goto cleanup;
    }

    // case: cbDelta will not advance current pointer past end of buffer
    // action: clear the elements between the old current index and the
    //         new current index.
    // -----------------------------------------------------------------
    for (i=0; i<cNulls; i++)   
    {
        dwPushedOut += m_padwFIFOBuffer[m_iCurrentElement+i];
        m_padwFIFOBuffer[m_iCurrentElement+i] = 0;
    } 
    m_iCurrentElement += cNulls;

cleanup:
    m_nElements += cNulls;
    if (m_nElements > m_maxElements)
    {
        m_nElements = m_maxElements;
    }

    return;
}


//$--CFIFO::Min-----------------------------------------------------------------
// Returns the minimum value in the buffer. 
// -----------------------------------------------------------------------------
VOID CFIFO::Min(
    OUT DWORD &dwMin)  // receives the minimum of all values in the buffer. 
{
    HRESULT hr  = NOERROR;
    DWORD i = 0;

    DEBUGPRIVATE("CFIFO::Min()\n");

	hr = CHK_CFIFO_Min(dwMin);
	if (FAILED(hr))
		return;

    dwMin = MAXWORD;

    if (m_nElements == 0)
    {
        dwMin = 0;
        goto cleanup;
    }

    for (i=0; i<m_iCurrentElement; i++)
    {
        if (m_padwFIFOBuffer[i] < dwMin )
            dwMin = m_padwFIFOBuffer[i];
    }

    for (i=m_iCurrentElement; i<m_nElements; i++)
    {
        if (m_padwFIFOBuffer[i] < dwMin )
            dwMin = m_padwFIFOBuffer[i];
    }

cleanup:
    return;
}


//$--CFIFO::Max-----------------------------------------------------------------
// Returns the maximum value in a buffer. 
// -----------------------------------------------------------------------------
VOID CFIFO::Max(
    OUT DWORD &dwMax)  // receives the maximum value in the buffer. 
{
    HRESULT hr  = NOERROR;
    DWORD i = 0;

    DEBUGPRIVATE("CFIFO::Max()\n");

	hr = CHK_CFIFO_Max(dwMax);
	if (FAILED(hr))
		return;

    dwMax = 0;
  
    for (i=0; i<m_iCurrentElement; i++)
    {
        if (m_padwFIFOBuffer[i] > dwMax )
           dwMax = m_padwFIFOBuffer[i];
    }

    for (i=m_iCurrentElement; i<m_nElements; i++)
    {
        if (m_padwFIFOBuffer[i] > dwMax )
            dwMax = m_padwFIFOBuffer[i];
    }

    return;
}


//$--CFIFO::Average-------------------------------------------------------------
// Returns the average value in the buffer.
// -----------------------------------------------------------------------------
VOID CFIFO::Average(
    OUT DWORD &dwAverage)  // receives buffer average 
{
    HRESULT hr  = NOERROR;
    DWORD i = 0;
    DWORD dwSum = 0;

    DEBUGPRIVATE("CFIFO::Average()\n");

	hr = CHK_CFIFO_Average(dwAverage);
	if (FAILED(hr))
		return;

    dwAverage = 0;
  
    for (i=0; i<m_iCurrentElement; i++)
    {
        dwSum += m_padwFIFOBuffer[i];
    }

    for (i=m_iCurrentElement; i<m_nElements; i++)
    {
        dwSum += m_padwFIFOBuffer[i];
    }

    if (m_nElements != 0)
        dwAverage = dwSum / m_nElements;
    return;
}
