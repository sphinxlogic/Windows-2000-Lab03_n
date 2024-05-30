/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    conv.h

Abstract:

    UNICODE / ASCII conversion macros

--*/

#ifndef USES_CONVERSION

// USES_CONVERSION must be defined in every function that uses the
// conversion macros

#define USES_CONVERSION int nSize; PVOID pIn; PVOID pOut

//////////////////////////////////////////////////////////////////////////
//
// W2A
//
// Routine Description:
//   Converts a UNICODE string to ASCII. Allocates the coversion buffer
//   off the stack using _alloca
//
// Arguments:
//	 pStr          UNICODE string
//
// Return Value:
//   the converted ASCII string
//

#define W2A(pStr)								\
												\
	(pIn = (PVOID) (pStr),						\
												\
	pIn == 0 ? (PSTR) 0 : (						\
												\
	nSize = WideCharToMultiByte(				\
		CP_ACP,									\
		0,										\
		(PWSTR) pIn,							\
		-1,										\
		0,										\
		0,										\
		0,										\
		0										\
	),											\
												\
	pOut = _alloca(nSize),						\
												\
	WideCharToMultiByte(						\
		CP_ACP,									\
		0,										\
		(PWSTR) pIn,							\
		-1,										\
		(PSTR) pOut,							\
		nSize,									\
		0,										\
		0										\
	),											\
												\
	(PSTR) pOut))								\

//////////////////////////////////////////////////////////////////////////
//
// A2W
//
// Routine Description:
//   Converts an ASCII string to UNICODE. Allocates the coversion buffer
//   off the stack using _alloca
//
// Arguments:
//	 pStr          ASCII string
//
// Return Value:
//   the converted UNICODE string
//

#define A2W(pStr)								\
												\
	(pIn = (PVOID) (pStr),						\
												\
	pIn == 0 ? (PWSTR) 0 : (					\
												\
	nSize = MultiByteToWideChar(				\
		CP_ACP,									\
		MB_PRECOMPOSED,							\
		(PSTR) pIn,								\
		-1,										\
		0,										\
		0										\
	),											\
												\
	pOut = _alloca(nSize * sizeof(WCHAR)),		\
												\
	MultiByteToWideChar(						\
		CP_ACP,									\
		MB_PRECOMPOSED,							\
		(PSTR) pIn,								\
		-1,										\
		(PWSTR) pOut,							\
		nSize									\
	),											\
												\
	(PWSTR) pOut))								\

//////////////////////////////////////////////////////////////////////////
//
// T2A, A2T, T2W, W2T
//
// Routine Description:
//   These macros expand to the corresponding correct form according to the
//   #definition of UNICODE. 
//
//   We use the cryptic form (nSize, pIn, pOut, pStr) to avoid the compiler
//   warning "symbol defined but not used" due to the variables defined 
//   in USES_CONVERSION macro.
//

#ifdef UNICODE
	#define T2A(pStr) W2A(pStr)
	#define A2T(pStr) A2W(pStr)
	#define T2W(pStr) (nSize, pIn, pOut, pStr)
	#define W2T(pStr) (nSize, pIn, pOut, pStr)
#else //UNICODE
	#define T2A(pStr) (nSize, pIn, pOut, pStr)
	#define A2T(pStr) (nSize, pIn, pOut, pStr)
	#define T2W(pStr) A2W(pStr)
	#define W2T(pStr) W2A(pStr)
#endif //UNICODE


#endif //USES_CONVERSION
