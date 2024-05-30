/*++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    sampcall.h

Abstract:

    Declaration of the CSampleMSPCall

--*/

#ifndef __SAMPCALL_H_
#define __SAMPCALL_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


/////////////////////////////////////////////////////////////////////////////
// CSampleMSPCall
/////////////////////////////////////////////////////////////////////////////

class CSampleMSPCall : public CMSPCallMultiGraph
{
public:
// DECLARE_POLY_AGGREGATABLE(CSampleMSP)

// To add extra interfaces to this class, use the following:
// BEGIN_COM_MAP(CSampleMSPCall)
//     COM_INTERFACE_ENTRY( YOUR_INTERFACE_HERE )
//     COM_INTERFACE_ENTRY_CHAIN(CMSPCallMultiGraph)
// END_COM_MAP()

public:
    CSampleMSPCall();
    virtual ~CSampleMSPCall();
    virtual ULONG MSPCallAddRef(void);
    virtual ULONG MSPCallRelease(void);

    virtual HRESULT Init(
        IN      CMSPAddress *       pMSPAddress,
        IN      MSP_HANDLE          htCall,
        IN      DWORD               dwReserved,
        IN      DWORD               dwMediaType
        );

    virtual HRESULT CreateStreamObject(
        IN      DWORD               dwMediaType,
        IN      TERMINAL_DIRECTION  Direction,
        IN      IMediaEvent *       pGraph,
        IN      ITStream **         ppStream
        );

    virtual HRESULT ReceiveTSPCallData(
        IN      PBYTE               pBuffer,
        IN      DWORD               dwSize
        );

    //
    // We override these to make sure the number of
    // streams we have is constant.
    //

    STDMETHOD (CreateStream) (
        IN      DWORD               dwMediaType,
        IN      TERMINAL_DIRECTION  Direction,
        IN OUT  ITStream **         ppStream
        );
    
    STDMETHOD (RemoveStream) (
        IN      ITStream *          pStream
        );                      

protected:
    // 
    // Protected data members.
    //

    CSampleMSPStream * m_pRenderStream;
    CSampleMSPStream * m_pCaptureStream;
};

#endif //__SAMPCALL_H_
