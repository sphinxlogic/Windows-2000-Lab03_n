
/******************************************************************************\
********************************************************************************
* Filename: StdAfx.h
*
* Description:
*				stdafx.h : include file for standard system include files,
*				or project specific include files that are used frequently,
*				but are changed infrequently
*
*
*
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

#define STRICT 1
#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0500
#endif // !defined(_WIN32_WINNT)

#pragma warning( disable : 4786) // disable the warning "identifier was truncated to '255' characters in the debug information" generated by STL
//#define _ATL_APARTMENT_THREADED
#define _ATL_FREE_THREADED
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module

class CRdModule : public CComModule
{
public:
	LONG Unlock();
	
};
extern CRdModule _Module;


#include <atlcom.h>