/*++

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998.  Microsoft Corporation.  All rights reserved.

Module Name:

    check.h

Abstract:

    Error / exception functions header file

--*/

#ifndef CHECK_H
#define CHECK_H

// 
// The error handling macros.
//
// Declare "USES_BRESULT;" the beginning of the function
// Declare "BEGIN_CLEANUP;" at the beginning of the cleanup block
// Exit the function with "return BRESULT";
//

#define USES_BRESULT	BOOL __bResult = TRUE; BOOL __bInCleanup = FALSE
#define EXIT_FUNCTION	__bResult = FALSE; if (!__bInCleanup) goto Cleanup
#define BEGIN_CLEANUP	Cleanup: __bInCleanup = TRUE
#define BRESULT			__bResult

//
// The CHECK_RESULT() macro is used for evaluating the return values of
// function calls. 
//
// CHECK_RESULT()
// - first sets the LastError to 0 (NO_ERROR)
// - calls the function 
// - if the return value satisfies the error condition 
//   - displays an error message based on the extended error code
//   - jumps out of the current block
// - sets the LastError to NO_UNHANDLED_ERROR to prevent nested error messages
//

#define NO_UNHANDLED_ERROR  ( (DWORD) -1 )

#define CHECK_RESULT(Expression, ErrorCondition, ErrorCode)		\
																\
	{															\
		DWORD __dwResult;										\
																\
		SetLastError(0);										\
																\
		__dwResult = (DWORD) (Expression);						\
																\
		if (__dwResult ErrorCondition) {						\
																\
			SystemErrorMessage(									\
				ErrorCode										\
				STAMP(_T(#Expression))						    \
			);													\
																\
			EXIT_FUNCTION;										\
		}														\
																\
		SetLastError(NO_UNHANDLED_ERROR);						\
	}															\

//
// The CHECK() macro can be used to evaluate the result of APIs that use
// LastError. These APIs typically return a non-zero value if there is 
// no error and if there is an error, they return zero and SetLastError()
// with the extended error information.
//

#define CHECK(Expression) \
	CHECK_RESULT(Expression, == 0, GetLastError())

//
// CHECK0 macro deals with the API functions that do not use the LastError 
// value. Typically registry APIs fall into this category, they directly 
// return the error code, or ERROR_SUCCESS if there is no error.
//

#define CHECK0(Expression) \
	CHECK_RESULT(Expression, != ERROR_SUCCESS, __dwResult)

//
// ERROR_MESSAGE() displays an error message and exits the function
//

#define ERROR_MESSAGE(pMessage)	\
	ErrorMessage(pMessage);		\
	EXIT_FUNCTION;				\

//
// SYSTEM_ERROR_MESSAGE() displays an error message based on system 
// message-table resources and exits the function
//

#define SYSTEM_ERROR_MESSAGE(dwError)				\
	SystemErrorMessage(dwError STAMP(_T("")));	    \
	EXIT_FUNCTION;									\

//
// On DEBUG builds, we include the location STAMP on the error message popup,
// i.e. we display the expression that raised the error, the module name and
// the line number 
//

#ifdef DEBUG
	#define STAMP(pExpr)	, pExpr, _T(__FILE__), __LINE__
	#define STAMP_DECL		, PCTSTR pExpr, PCTSTR pFile, INT nLine 
	#define STAMP_ARGS		, pExpr, pFile, nLine 
	#define STAMP_FORMAT	_T("%s\n%s: %d")
	#define STAMP_LENGTH	_tcslen(pExpr) + _tcslen(pFile) + 8
#else //DEBUG
	#define STAMP(pExpr)
	#define STAMP_DECL
	#define STAMP_ARGS
	#define STAMP_FORMAT
	#define STAMP_LENGTH 0
#endif //DEBUG

//
// Function prototypes
// 

VOID
SetUnknownErrorStr(
	PTSTR pUnknownError
);

int
ErrorMessage(
	PCTSTR pMessage
);

VOID
SystemErrorMessage(
	DWORD dwError
	STAMP_DECL
);

#ifdef IMPLEMENT_CHECK

//
// Implementation of the functions
//
// This gets compiled only if IMPLEMENT_CHECK is defined.
// Add #define IMPLEMENT_CHECK before #include check.h
// in only one of the project modules that include check.h
//

PTSTR g_pUnknownError = _T("Unknown error");

//////////////////////////////////////////////////////////////////////////
//
// SetUnknownErrorStr
//
// Routine Description:
//   Sets the localizable "unknown error" string. SystemErrorMessage() 
//   function will use this string when it cannot find an associated 
//   message string for the error number
//
// Arguments:
//   PTSTR pUnknownError  pointer to the string
//
// Return Value:
//   none
//

VOID
SetUnknownErrorStr(
	PTSTR pUnknownError
)
{
	g_pUnknownError = pUnknownError;
}

//////////////////////////////////////////////////////////////////////////
//
// ErrorMessage
//
// Routine Description:
//   Displays an error message
//
// Arguments:
//   PCTSTR pMessage  Message to display in the error message text
//
// Return Value:
//   return value of the MessageBox API
//

int
ErrorMessage(
	PCTSTR pMessage
)
{
	int bResult = MessageBox(
		0,
		pMessage,
		0,
		MB_OK | 
		MB_ICONERROR
	);

	// set the LastError value to prevent nested error messages

	SetLastError(NO_UNHANDLED_ERROR);

    return bResult;
}

//////////////////////////////////////////////////////////////////////////
//
// SystemErrorMessage
//
// Routine Description:
//   Displays an error message based on system message-table resources
//   On DEBUG builds, the error message includes the expression that 
//   raised the error, the module name and the line number
//
// Arguments:
//   DWORD dwError  Message identifier for the requested message
//
// Return Value:
//   none
//

VOID
SystemErrorMessage(
	DWORD dwError
	STAMP_DECL
)
{
	if (dwError != NO_UNHANDLED_ERROR) {

		PCTSTR pFormat        = _T("%d: %s\n") STAMP_FORMAT;
		PTSTR  pSystemMessage = 0;
		PTSTR  pErrorText     = 0;
		BOOL   bResult        = TRUE;

		// try to obtain a message string from system resources

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_MAX_WIDTH_MASK,
			0,
			dwError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(PTSTR) &pSystemMessage,
			0,
			0 
		);

		if (!pSystemMessage) {

			pSystemMessage = g_pUnknownError;
		}

		// allocate memory and prepare out message string

		bResult = bResult && (pErrorText = (PTSTR) LocalAlloc(
			LMEM_FIXED,
			(_tcslen(pFormat) + 8 + _tcslen(pSystemMessage) + STAMP_LENGTH)
			* sizeof(TCHAR)
		));

		bResult = bResult && wsprintf(
			pErrorText,
			pFormat,
			dwError,
			dwError ? pSystemMessage : g_pUnknownError
			STAMP_ARGS
		);

		// display the message

		bResult = bResult && ErrorMessage(pErrorText);

		// if there was an error in one of the above steps, send
		// the message to the kernel debugger instead

		if (!bResult) {

			OutputDebugString(g_pUnknownError);
			OutputDebugString(_T("\n"));
		}

		// free up the memory we allocated

		LocalFree(pErrorText);

		if (pSystemMessage != g_pUnknownError) {
		
			LocalFree(pSystemMessage);
		}
	}
}

#endif //IMPLEMENT_CHECK

#endif //CHECK_H
