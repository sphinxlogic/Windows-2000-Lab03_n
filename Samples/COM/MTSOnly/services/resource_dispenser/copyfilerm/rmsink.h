
/******************************************************************************\
********************************************************************************
* Filename: RmSink.h
*
* Description: implements the DTC interface IResourceManagerSink
*
* This file is provided as part of the Microsoft Transaction Server
* Software Development Kit
*
*THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
*WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
*INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
*OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
*PURPOSE.
*
* Copyright (C) 1997 Microsoft Corporation, All rights reserved
********************************************************************************
\******************************************************************************/
#ifndef __RMSINK_H__
#define __RMSINK_H__

interface IFileRm;
class ATL_NO_VTABLE CResourceManagerSink : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public IResourceManagerSink

{

public:

BEGIN_COM_MAP(CResourceManagerSink)
	COM_INTERFACE_ENTRY(IResourceManagerSink)
END_COM_MAP()

IFileRm * m_pRm;
CResourceManagerSink()
{
	m_pRm = NULL;
}

void SetRm(IFileRm * pRm)
{
	m_pRm = pRm; // NOTE:  no reference added
}

//
//	delegate to the RM
//
STDMETHODIMP TMDown()
{
	_ASSERTE(m_pRm);
	if (m_pRm)
		return m_pRm -> TMDown();

	return E_UNEXPECTED;
}




};

#endif