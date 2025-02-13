/*** 
*clsid.h
*
*  This is a part of the Microsoft Source Code Samples.
*
*  Copyright 1992 - 1998 Microsoft Corporation. All rights reserved.
*
*  This source code is only intended as a supplement to Microsoft Development
*  Tools and/or WinHelp documentation.  See these sources for detailed
*  information regarding the Microsoft samples programs.
*
*Purpose:
*  This file defines the CLSIDs referenced by the IDispatch demo app.
*
*Implementation Notes:
*
*****************************************************************************/

DEFINE_GUID(CLSID_CPoly,  0x00020462, 0, 0, 0xC0, 0, 0, 0, 0, 0, 0, 0x46);
DEFINE_GUID(CLSID_CPoly2, 0x00020464, 0, 0, 0xC0, 0, 0, 0, 0, 0, 0, 0x46);


#ifdef INITGUID
# ifdef _MAC
DEFINE_GUID(GUID_NULL, 0L, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
/* The PPC MW gives a warning if these are redefined */
#  ifndef _MW_BUILD
DEFINE_GUID(IID_IDispatch, 0x00020400, 0, 0, 0xC0, 0, 0, 0, 0, 0, 0, 0x46);
DEFINE_GUID(IID_IEnumVARIANT, 0x00020404, 0, 0, 0xC0, 0, 0, 0, 0, 0, 0, 0x46);
#  endif
DEFINE_GUID(IID_IUnknown, 0x00000000, 0, 0, 0xC0, 0, 0, 0, 0, 0, 0, 0x46);
DEFINE_GUID(IID_IClassFactory, 0x00000001, 0, 0, 0xC0, 0, 0, 0, 0, 0, 0, 0x46);
# endif
#endif


