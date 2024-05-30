/* Copyright 1992 - 1998 Microsoft Corporation, All rights reserved. 
 *
 * 
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, 
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE. 
 */

#include "CFactory.h"
#include "UDTServer.h"
///////////////////////////////////////////////////////////
//
// Server.cpp
//
// This file contains the component server code.
// The FactoryDataArray contains the components that 
// can be served.
//

// Each component derived from CUnknown defines a static function
// for creating the component with the following prototype. 
// HRESULT CreateInstance(IUnknown* pUnknownOuter, 
//                        CUnknown** ppNewComponent) ;
// This function is used to create the component.
//

//
// The following array contains the data used by CFactory
// to create components. Each element in the array contains
// the CLSID, the pointer to the creation function, and the name
// of the component to place in the Registry.
//


#define _OLEIVERB_PRIMARY		0
#define _OLEIVERB_SHOW			FF	
#define _OLEIVERB_OPEN			FE
#define _OLEIVERB_HIDE			FD
#define _OLEIVERB_PROPERTIES	F9
// MACRO's used to combine and extract the OLE verb and name

#define MAKEINTS1(s) #s
#define MAKEINTS2(iVerb) MAKEINTS1(\x ## iVerb)
#define MAKEINTVERB(iVerb, lpstrName) MAKEINTS2(iVerb) lpstrName
#define MAKEINTI(i) i

#define MAKEVERSION(M, m) ((DWORD)(WORD)(m) | (DWORD)(WORD)(M) << 16) // M=Major, m=minor


CFactoryData g_FactoryDataArray[] =
{
	{	
		MAKEVERSION(1, 0),						// Version of CFactoryData
		LOCAL,									// Type of COM server
		NULL,									// Threading model
		&CLSID_UDT,								// CLSID for object
		CServer::CreateInstance,				// Helper function for ICF::CreateInstance()
		"User Defined Data Test - Work in Progress",			// Friendly Name
		L"UDT.Test.1",							// ProgID
		L"UDT.Test",								// Version-independent ProgID
		NULL,									// Short User type
		NULL,									// Appliction name			
		&LIBID_Student,							// TypeLibrary
		MAKELCID(								// LCID of typelib
			MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
		MAKEVERSION(1, 0),						// Version of typelib
		false,									// True for custom interface
		0,										// Verbs
		0										// MISC	bits
	}

} ;

int g_cFactoryDataEntries
	= sizeof(g_FactoryDataArray) / sizeof(CFactoryData) ;

