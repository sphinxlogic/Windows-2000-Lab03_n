// --fifo.h---------------------------------------------------------------------
// 
//  Defines the fifo object
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef __FIFO_H
#define __FIFO_H

#include <windows.h>

//$--CFIFO----------------------------------------------------------------------
//  Defines the CFIFO object, a First In First Out Buffer.
// -----------------------------------------------------------------------------
class CFIFO
{
public:
    CFIFO(void);
    virtual ~CFIFO(void);
    HRESULT HrReset(IN DWORD maxElements);
    VOID PushElement(IN DWORD dwValue, OUT DWORD &dwPushedOut);
    VOID PushNNulls(IN DWORD nNulls, OUT DWORD &dwPushedOut);
    DWORD dwNumberElements(VOID)  { return m_nElements; };
    DWORD dwMaxNumberElements(VOID) { return m_maxElements; };
    VOID Min(OUT DWORD &);
    VOID Max(OUT DWORD &);
    VOID Average(OUT DWORD &);

private:
    DWORD m_nElements;
    DWORD m_maxElements;
    DWORD m_iCurrentElement;
    DWORD *m_padwFIFOBuffer;
};

#endif
