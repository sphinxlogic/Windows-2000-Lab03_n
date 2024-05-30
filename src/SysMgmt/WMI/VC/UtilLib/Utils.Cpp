// **************************************************************************
// Copyright (c) 1999 Microsoft Corporation.
//
// File:  utils.cpp
//
// Description:
//    Set of sample routines
//
// History:
//
// **************************************************************************

#pragma warning(disable:4201)  // nonstandard extension nameless struct (used in windows.h)
#pragma warning(disable:4514)  // unreferenced inline function has been removed (used in windows.h)

//#include <windows.h>  // Not needed since wbemsvc includes it again
#include <stdio.h>

#include <wbemidl.h>
#include <sys\timeb.h>
#include "utillib.h"

//*****************************************************************************
// Function:   WbemErrorString
// Purpose:    Turns sc into a text string
//*****************************************************************************
WCHAR *WbemErrorString(SCODE sc)
{
   WCHAR szBuffer2[MAXITOA];
   static WCHAR szBuffer[sizeof(szBuffer2) + 4];
   WCHAR *psz;

   switch(sc) {
   case WBEM_NO_ERROR:
      psz = L"WBEM_NO_ERROR/WBEM_S_NO_ERROR/WBEM_S_SAME";
      break;
   case WBEM_S_FALSE:
      psz = L"WBEM_S_FALSE";
      break;
   case WBEM_S_ALREADY_EXISTS:
      psz = L"WBEM_S_ALREADY_EXISTS";
      break;
   case WBEM_S_RESET_TO_DEFAULT:
      psz = L"WBEM_S_RESET_TO_DEFAULT";
      break;
   case WBEM_S_DIFFERENT:
      psz = L"WBEM_S_DIFFERENT";
      break;
   case WBEM_S_TIMEDOUT:
      psz = L"WBEM_S_TIMEDOUT";
      break;
   case WBEM_S_NO_MORE_DATA:
      psz = L"WBEM_S_NO_MORE_DATA";
      break;
   case WBEM_S_OPERATION_CANCELLED:
      psz = L"WBEM_OPERATION_CANCELLED";
      break;
   case WBEM_S_PENDING:
      psz = L"WBEM_S_PENDING";
      break;
   case WBEM_S_DUPLICATE_OBJECTS:
      psz = L"WBEM_S_DUPLICATE_OBJECTS";
      break;
   case WBEM_E_FAILED:
      psz = L"WBEM_E_FAILED";
      break;
   case WBEM_E_NOT_FOUND:
      psz = L"WBEM_E_NOT_FOUND";
      break;
   case WBEM_E_ACCESS_DENIED:
      psz = L"WBEM_E_ACCESS_DENIED";
      break;
   case WBEM_E_PROVIDER_FAILURE:
      psz = L"WBEM_E_PROVIDER_FAILURE";
      break;
   case WBEM_E_TYPE_MISMATCH:
      psz = L"WBEM_E_TYPE_MISMATCH";
      break;
   case WBEM_E_OUT_OF_MEMORY:
      psz = L"WBEM_E_OUT_OF_MEMORY";
      break;
   case WBEM_E_INVALID_CONTEXT:
      psz = L"WBEM_E_INVALID_CONTEXT";
      break;
   case WBEM_E_INVALID_PARAMETER:
      psz = L"WBEM_E_INVALID_PARAMETER";
      break;
   case WBEM_E_NOT_AVAILABLE:
      psz = L"WBEM_E_NOT_AVAILABLE";
      break;
   case WBEM_E_CRITICAL_ERROR:
      psz = L"WBEM_E_CRITICAL_ERROR";
      break;
   case WBEM_E_INVALID_STREAM:
      psz = L"WBEM_E_INVALID_STREAM";
      break;
   case WBEM_E_NOT_SUPPORTED:
      psz = L"WBEM_E_NOT_SUPPORTED";
      break;
   case WBEM_E_INVALID_SUPERCLASS:
      psz = L"WBEM_E_INVALID_SUPERCLASS";
      break;
   case WBEM_E_INVALID_NAMESPACE:
      psz = L"WBEM_E_INVALID_NAMESPACE";
      break;
   case WBEM_E_INVALID_OBJECT:
      psz = L"WBEM_E_INVALID_OBJECT";
      break;
   case WBEM_E_INVALID_CLASS:
      psz = L"WBEM_E_INVALID_CLASS";
      break;
   case WBEM_E_PROVIDER_NOT_FOUND:
      psz = L"WBEM_E_PROVIDER_NOT_FOUND";
      break;
   case WBEM_E_INVALID_PROVIDER_REGISTRATION:
      psz = L"WBEM_E_INVALID_PROVIDER_REGISTRATION";
      break;
   case WBEM_E_PROVIDER_LOAD_FAILURE:
      psz = L"WBEM_E_PROVIDER_LOAD_FAILURE";
      break;
   case WBEM_E_INITIALIZATION_FAILURE:
      psz = L"WBEM_E_INITIALIZATION_FAILURE";
      break;
   case WBEM_E_TRANSPORT_FAILURE:
      psz = L"WBEM_E_TRANSPORT_FAILURE";
      break;
   case WBEM_E_INVALID_OPERATION:
      psz = L"WBEM_E_INVALID_OPERATION";
      break;
   case WBEM_E_INVALID_QUERY:
      psz = L"WBEM_E_INVALID_QUERY";
      break;
   case WBEM_E_INVALID_QUERY_TYPE:
      psz = L"WBEM_E_INVALID_QUERY_TYPE";
      break;
   case WBEM_E_ALREADY_EXISTS:
      psz = L"WBEM_E_ALREADY_EXISTS";
      break;
   case WBEM_E_OVERRIDE_NOT_ALLOWED:
      psz = L"WBEM_E_OVERRIDE_NOT_ALLOWED";
      break;
   case WBEM_E_PROPAGATED_QUALIFIER:
      psz = L"WBEM_E_PROPAGATED_QUALIFIER";
      break;
   case WBEM_E_PROPAGATED_PROPERTY:
      psz = L"WBEM_E_PROPAGATED_PROPERTY";
      break;
   case WBEM_E_UNEXPECTED:
      psz = L"WBEM_E_UNEXPECTED";
      break;
   case WBEM_E_ILLEGAL_OPERATION:
      psz = L"WBEM_E_ILLEGAL_OPERATION";
      break;
   case WBEM_E_CANNOT_BE_KEY:
      psz = L"WBEM_E_CANNOT_BE_KEY";
      break;
   case WBEM_E_INCOMPLETE_CLASS:
      psz = L"WBEM_E_INCOMPLETE_CLASS";
      break;
   case WBEM_E_INVALID_SYNTAX:
      psz = L"WBEM_E_INVALID_SYNTAX";
      break;
   case WBEM_E_NONDECORATED_OBJECT:
      psz = L"WBEM_E_NONDECORATED_OBJECT";
      break;
   case WBEM_E_READ_ONLY:
      psz = L"WBEM_E_READ_ONLY";
      break;
   case WBEM_E_PROVIDER_NOT_CAPABLE:
      psz = L"WBEM_E_PROVIDER_NOT_CAPABLE";
      break;
   case WBEM_E_CLASS_HAS_CHILDREN:
      psz = L"WBEM_E_CLASS_HAS_CHILDREN";
      break;
   case WBEM_E_CLASS_HAS_INSTANCES:
      psz = L"WBEM_E_CLASS_HAS_INSTANCES";
      break;
   case WBEM_E_QUERY_NOT_IMPLEMENTED:
      psz = L"WBEM_E_QUERY_NOT_IMPLEMENTED";
      break;
   case WBEM_E_ILLEGAL_NULL:
      psz = L"WBEM_E_ILLEGAL_NULL";
      break;
   case WBEM_E_INVALID_QUALIFIER_TYPE:
      psz = L"WBEM_E_INVALID_QUALIFIER_TYPE";
      break;
   case WBEM_E_INVALID_PROPERTY_TYPE:
      psz = L"WBEM_E_INVALID_PROPERTY_TYPE";
      break;
   case WBEM_E_VALUE_OUT_OF_RANGE:
      psz = L"WBEM_E_VALUE_OUT_OF_RANGE";
      break;
   case WBEM_E_CANNOT_BE_SINGLETON:
      psz = L"WBEM_E_CANNOT_BE_SINGLETON";
      break;
   case WBEM_E_INVALID_CIM_TYPE:
      psz = L"WBEM_E_INVALID_CIM_TYPE";
      break;
   case WBEM_E_INVALID_METHOD:
      psz = L"WBEM_E_INVALID_METHOD";
      break;
   case WBEM_E_INVALID_METHOD_PARAMETERS:
      psz = L"WBEM_E_INVALID_METHOD_PARAMETERS";
      break;
   case WBEM_E_SYSTEM_PROPERTY:
      psz = L"WBEM_E_SYSTEM_PROPERTY";
      break;
   case WBEM_E_INVALID_PROPERTY:
      psz = L"WBEM_E_INVALID_PROPERTY";
      break;
   case WBEM_E_CALL_CANCELLED:
      psz = L"WBEM_E_CALL_CANCELLED";
      break;
   case WBEM_E_SHUTTING_DOWN:
      psz = L"WBEM_E_SHUTTING_DOWN";
      break;
   case WBEM_E_PROPAGATED_METHOD:
      psz = L"WBEM_E_PROPAGATED_METHOD";
      break;
   case WBEM_E_UNSUPPORTED_PARAMETER:
      psz = L"WBEM_E_UNSUPPORTED_PARAMETER";
      break;
   case WBEM_E_MISSING_PARAMETER_ID:
      psz = L"WBEM_E_MISSING_PARAMETER_ID";
      break;
   case WBEM_E_INVALID_PARAMETER_ID:
      psz = L"WBEM_E_INVALID_PARAMETER_ID";
      break;
   case WBEM_E_NONCONSECUTIVE_PARAMETER_IDS:
      psz = L"WBEM_E_NONCONSECUTIVE_PARAMETER_IDS";
      break;
   case WBEM_E_PARAMETER_ID_ON_RETVAL:
      psz = L"WBEM_E_PARAMETER_ID_ON_RETVAL";
      break;
   case WBEM_E_INVALID_OBJECT_PATH:
      psz = L"WBEM_E_INVALID_OBJECT_PATH";
      break;
   case WBEMESS_E_REGISTRATION_TOO_BROAD:
      psz = L"WBEMESS_E_REGISTRATION_TOO_BROAD";
      break;
   case WBEMESS_E_REGISTRATION_TOO_PRECISE:
      psz = L"WBEMESS_E_REGISTRATION_TOO_PRECISE";
      break;
   default:
      _ltow(sc, szBuffer2, 16);
      wcscpy(szBuffer, L"0x");
      wcscat(szBuffer, szBuffer2);
      psz = szBuffer;
      break;
   }

   return psz;
}

//***************************************************************************
// Function:  PrintError
// Purpose:   Formats and prints the error message
//***************************************************************************
void PrintError(char *pszFailureReason, SCODE psc)
{
   VARIANT varString;
   SCODE sc;
   IWbemClassObject *pErrorObject = NULL;
   IErrorInfo* pEI = NULL;

   fprintf(stdout, "%s\n", pszFailureReason);
   fprintf(stdout, "FunctionReturn: %S(0x%08lx)\n", WbemErrorString(psc), psc);

   if(GetErrorInfo(0, &pEI) == S_OK) {
      pEI->QueryInterface(IID_IWbemClassObject, (void**)&pErrorObject);
      pEI->Release();
   }

   if (pErrorObject != NULL) {

      VariantInit(&varString);

      if (pErrorObject->InheritsFrom(CBString(L"__NotifyStatus")) != WBEM_NO_ERROR) {
         fprintf(stdout, "Unrecognized Error Object type\n");
      } else if (pErrorObject->InheritsFrom(CBString(L"__ExtendedStatus")) == WBEM_NO_ERROR) {

         sc = pErrorObject->Get(CBString(L"Description"), 0L, &varString, NULL, NULL);
         if (sc != S_OK) {
            fprintf(stdout, "Can't get Description: %d\n", sc);
         } else if (V_VT(&varString) == VT_BSTR) {
            FWPRINTF(stdout, L"Description: %wS\n", V_BSTR(&varString));
         }
         VariantClear(&varString);

         pErrorObject->Get(CBString(L"Operation"), 0L, &varString, NULL, NULL);
         if (sc != S_OK) {
            fprintf(stdout, "Can't get Operation: %d\n", sc);
         } else if (V_VT(&varString) == VT_BSTR) {
            FWPRINTF(stdout, L"Operation: %wS\n", V_BSTR(&varString));
         }
         VariantClear(&varString);

         pErrorObject->Get(CBString(L"ParameterInfo"), 0L, &varString, NULL, NULL);
         if (sc != S_OK) {
            fprintf(stdout, "Can't get ParameterInfo: %d\n", sc);
         } else if (V_VT(&varString) == VT_BSTR) {
            FWPRINTF(stdout, L"ParameterInfo: %wS\n", V_BSTR(&varString));
         }
         VariantClear(&varString);

         pErrorObject->Get(CBString(L"ProviderName"), 0L, &varString, NULL, NULL);
         if (sc != S_OK) {
            fprintf(stdout, "Can't get ProviderName: %d\n", sc);
         } else if (V_VT(&varString) == VT_BSTR) {
            FWPRINTF(stdout, L"ProviderName: %wS\n", V_BSTR(&varString));
         }
         VariantClear(&varString);
      }

      RELEASE(pErrorObject);

   }

}

//***************************************************************************
// Function:  PrintErrorAndExit
// Purpose:   Formats an error message & exits program
//***************************************************************************
void PrintErrorAndExit(char *pszFailureReason, SCODE psc)
{

   PrintError(pszFailureReason, psc);

   // Clean up and exit
   OleUninitialize();
   printf("Abnormal Termination\n");
   exit(1);

};

//***************************************************************************
// Function:  PrintErrorAndAsk
// Purpose:   Prints the error message and prompts to continue
//***************************************************************************
void PrintErrorAndAsk(char *pszFailureReason, SCODE psc)
{

   int c;

   PrintError(pszFailureReason, psc);
   printf("Continue (Y/N)? ");

   c = getchar();
   while (getchar() != '\n') {
   }

   if ((c != 'Y') && (c != 'y')) {

      // Clean up and exit
      OleUninitialize();
      exit(1);
   }

};

//*****************************************************************************
// Function:   TypeToString
// Purpose:    Takes a variant, returns a pointer to a string that is the variant type
//*****************************************************************************
const WCHAR *TypeToString(VARIANT *p)
{
   return TypeToString(p->vt);
}

//*****************************************************************************
// Function:   TypeToString
// Purpose:    Takes a VARTYPE, returns a pointer to a string that is the variant type
//*****************************************************************************
const WCHAR *TypeToString(VARTYPE v)
{
    const static WCHAR *pVT_NULL  = L"VT_NULL";
    const static WCHAR *pVT_EMTPY = L"VT_EMPTY";
    const static WCHAR *pVT_I1    = L"VT_I1";
    const static WCHAR *pVT_UI1   = L"VT_UI1";
    const static WCHAR *pVT_I2    = L"VT_I2";
    const static WCHAR *pVT_UI2   = L"VT_UI2";
    const static WCHAR *pVT_I4    = L"VT_I4";
    const static WCHAR *pVT_UI4   = L"VT_UI4";
    const static WCHAR *pVT_I8    = L"VT_I8";
    const static WCHAR *pVT_UI8   = L"VT_UI8";
    const static WCHAR *pVT_R4    = L"VT_R4";
    const static WCHAR *pVT_R8    = L"VT_R8";
    const static WCHAR *pVT_BOOL  = L"VT_BOOL";
    const static WCHAR *pVT_BSTR  = L"VT_BSTR";
    const static WCHAR *pVT_DISPATCH = L"VT_DISPATCH";
    const static WCHAR *pVT_UNKNOWN = L"VT_UNKNOWN";
    const static WCHAR *pVT_I1_ARRAY = L"VT_I1 | VT_ARRAY";
    const static WCHAR *pVT_UI1_ARRAY  = L"VT_UI1 | VT_ARRAY";
    const static WCHAR *pVT_I2_ARRAY   = L"VT_I2 | VT_ARRAY";
    const static WCHAR *pVT_UI2_ARRAY  = L"VT_UI2 | VT_ARRAY";
    const static WCHAR *pVT_I4_ARRAY   = L"VT_I4 | VT_ARRAY";
    const static WCHAR *pVT_UI4_ARRAY  = L"VT_UI4 | VT_ARRAY";
    const static WCHAR *pVT_I8_ARRAY   = L"VT_I8 | VT_ARRAY";
    const static WCHAR *pVT_UI8_ARRAY  = L"VT_UI8 | VT_ARRAY";
    const static WCHAR *pVT_R4_ARRAY   = L"VT_R4 | VT_ARRAY";
    const static WCHAR *pVT_R8_ARRAY   = L"VT_R8 | VT_ARRAY";
    const static WCHAR *pVT_BOOL_ARRAY = L"VT_BOOL | VT_ARRAY";
    const static WCHAR *pVT_BSTR_ARRAY = L"VT_BSTR | VT_ARRAY";
    const static WCHAR *pVT_DISPATCH_ARRAY = L"VT_DISPATCH | VT_ARRAY";
    const static WCHAR *pVT_UNKNOWN_ARRAY = L"VT_UNKNOWN | VT_ARRAY";

    const WCHAR *pRetVal;

    switch (v)
    {
        case VT_NULL: pRetVal = pVT_NULL; break;

        case VT_I1: pRetVal = pVT_I1; break;
        case VT_UI1: pRetVal = pVT_UI1; break;
        case VT_I2: pRetVal = pVT_I2; break;
        case VT_UI2: pRetVal = pVT_UI2; break;
        case VT_I4: pRetVal = pVT_I4; break;
        case VT_UI4: pRetVal = pVT_UI4; break;
        case VT_I8: pRetVal = pVT_I8; break;
        case VT_UI8: pRetVal = pVT_UI8; break;
        case VT_R4: pRetVal = pVT_R4; break;
        case VT_R8: pRetVal = pVT_R8; break;
        case VT_BOOL: pRetVal = pVT_BOOL; break;
        case VT_BSTR: pRetVal = pVT_BSTR; break;
        case VT_DISPATCH: pRetVal = pVT_DISPATCH; break;
        case VT_UNKNOWN: pRetVal = pVT_UNKNOWN; break;

        case VT_I1|VT_ARRAY: pRetVal = pVT_I1_ARRAY; break;
        case VT_UI1|VT_ARRAY: pRetVal = pVT_UI1_ARRAY; break;
        case VT_I2|VT_ARRAY: pRetVal = pVT_I2_ARRAY; break;
        case VT_UI2|VT_ARRAY: pRetVal = pVT_UI2_ARRAY; break;
        case VT_I4|VT_ARRAY: pRetVal = pVT_I4_ARRAY; break;
        case VT_UI4|VT_ARRAY: pRetVal = pVT_UI4_ARRAY; break;
        case VT_I8|VT_ARRAY: pRetVal = pVT_I8_ARRAY; break;
        case VT_UI8|VT_ARRAY: pRetVal = pVT_UI8_ARRAY; break;
        case VT_R4|VT_ARRAY: pRetVal = pVT_R4_ARRAY; break;
        case VT_R8|VT_ARRAY: pRetVal = pVT_R8_ARRAY; break;
        case VT_BOOL|VT_ARRAY: pRetVal = pVT_BOOL_ARRAY; break;
        case VT_BSTR|VT_ARRAY: pRetVal = pVT_BSTR_ARRAY; break;
        case VT_DISPATCH|VT_ARRAY: pRetVal = pVT_DISPATCH_ARRAY; break;
        case VT_UNKNOWN|VT_ARRAY: pRetVal = pVT_UNKNOWN_ARRAY; break;

        default: pRetVal = L"<unknown>";
    }

    return pRetVal;
}

//*****************************************************************************
// Function:   TypeToString
// Purpose:    Takes a CIMTYPE, returns a pointer to a string that is the variant type
//*****************************************************************************
const WCHAR *TypeToString(CIMTYPE v)
{
    const static WCHAR *pCIM_UNKNOWN = L"CIM_UNKNOWN";

    const static WCHAR *pCIM_ILLEGAL = L"CIM_ILLEGAL";
    const static WCHAR *pCIM_EMPTY = L"CIM_EMPTY";
    const static WCHAR *pCIM_SINT8 = L"CIM_SINT8";
    const static WCHAR *pCIM_UINT8 = L"CIM_UINT8";
    const static WCHAR *pCIM_SINT16 = L"CIM_SINT16";
    const static WCHAR *pCIM_UINT16 = L"CIM_UINT16";
    const static WCHAR *pCIM_SINT32 = L"CIM_SINT32";
    const static WCHAR *pCIM_UINT32 = L"CIM_UINT32";
    const static WCHAR *pCIM_SINT64 = L"CIM_SINT64";
    const static WCHAR *pCIM_UINT64 = L"CIM_UINT64";
    const static WCHAR *pCIM_REAL32 = L"CIM_REAL32";
    const static WCHAR *pCIM_REAL64 = L"CIM_REAL64";
    const static WCHAR *pCIM_BOOLEAN = L"CIM_BOOLEAN";
    const static WCHAR *pCIM_STRING = L"CIM_STRING";
    const static WCHAR *pCIM_DATETIME = L"CIM_DATETIME";
    const static WCHAR *pCIM_REFERENCE = L"CIM_REFERENCE";
    const static WCHAR *pCIM_OBJECT = L"CIM_OBJECT";

    const static WCHAR *pCIM_ILLEGAL_ARRAY = L"CIM_ILLEGAL | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_EMPTY_ARRAY = L"CIM_EMPTY | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_SINT8_ARRAY = L"CIM_SINT8 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_UINT8_ARRAY = L"CIM_UINT8 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_SINT16_ARRAY = L"CIM_SINT16 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_UINT16_ARRAY = L"CIM_UINT16 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_SINT32_ARRAY = L"CIM_SINT32 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_UINT32_ARRAY = L"CIM_UINT32 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_SINT64_ARRAY = L"CIM_SINT64 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_UINT64_ARRAY = L"CIM_UINT64 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_REAL32_ARRAY = L"CIM_REAL32 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_REAL64_ARRAY = L"CIM_REAL64 | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_BOOLEAN_ARRAY = L"CIM_BOOLEAN | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_STRING_ARRAY = L"CIM_STRING | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_DATETIME_ARRAY = L"CIM_DATETIME | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_REFERENCE_ARRAY = L"CIM_REFERENCE | CIM_FLAG_ARRAY";
    const static WCHAR *pCIM_OBJECT_ARRAY = L"CIM_OBJECT | CIM_FLAG_ARRAY";

    const WCHAR *pRetVal;

    switch (v)
    {

    case CIM_ILLEGAL: pRetVal = pCIM_ILLEGAL; break;
    case CIM_EMPTY: pRetVal = pCIM_EMPTY; break;
    case CIM_SINT8: pRetVal = pCIM_SINT8; break;
    case CIM_UINT8: pRetVal = pCIM_UINT8; break;
    case CIM_SINT16: pRetVal = pCIM_SINT16; break;
    case CIM_UINT16: pRetVal = pCIM_UINT16; break;
    case CIM_SINT32: pRetVal = pCIM_SINT32; break;
    case CIM_UINT32: pRetVal = pCIM_UINT32; break;
    case CIM_SINT64: pRetVal = pCIM_SINT64; break;
    case CIM_UINT64: pRetVal = pCIM_UINT64; break;
    case CIM_REAL32: pRetVal = pCIM_REAL32; break;
    case CIM_REAL64: pRetVal = pCIM_REAL64; break;
    case CIM_BOOLEAN: pRetVal = pCIM_BOOLEAN; break;
    case CIM_STRING: pRetVal = pCIM_STRING; break;
    case CIM_DATETIME: pRetVal = pCIM_DATETIME; break;
    case CIM_REFERENCE: pRetVal = pCIM_REFERENCE; break;
    case CIM_OBJECT: pRetVal = pCIM_OBJECT; break;

    case CIM_SINT8 | CIM_FLAG_ARRAY: pRetVal = pCIM_SINT8_ARRAY; break;
    case CIM_UINT8 | CIM_FLAG_ARRAY: pRetVal = pCIM_UINT8_ARRAY; break;
    case CIM_SINT16 | CIM_FLAG_ARRAY: pRetVal = pCIM_SINT16_ARRAY; break;
    case CIM_UINT16 | CIM_FLAG_ARRAY: pRetVal = pCIM_UINT16_ARRAY; break;
    case CIM_SINT32 | CIM_FLAG_ARRAY: pRetVal = pCIM_SINT32_ARRAY; break;
    case CIM_UINT32 | CIM_FLAG_ARRAY: pRetVal = pCIM_UINT32_ARRAY; break;
    case CIM_SINT64 | CIM_FLAG_ARRAY: pRetVal = pCIM_SINT64_ARRAY; break;
    case CIM_UINT64 | CIM_FLAG_ARRAY: pRetVal = pCIM_UINT64_ARRAY; break;
    case CIM_REAL32 | CIM_FLAG_ARRAY: pRetVal = pCIM_REAL32_ARRAY; break;
    case CIM_REAL64 | CIM_FLAG_ARRAY: pRetVal = pCIM_REAL64_ARRAY; break;
    case CIM_BOOLEAN | CIM_FLAG_ARRAY: pRetVal = pCIM_BOOLEAN_ARRAY; break;
    case CIM_STRING | CIM_FLAG_ARRAY: pRetVal = pCIM_STRING_ARRAY; break;
    case CIM_DATETIME | CIM_FLAG_ARRAY: pRetVal = pCIM_DATETIME_ARRAY; break;
    case CIM_REFERENCE | CIM_FLAG_ARRAY: pRetVal = pCIM_REFERENCE_ARRAY; break;
    case CIM_OBJECT | CIM_FLAG_ARRAY: pRetVal = pCIM_OBJECT_ARRAY; break;

    default: pRetVal = pCIM_UNKNOWN; break;
    }

    return pRetVal;
}

//*****************************************************************************
// Function:   ValueToString 
// Purpose:    Takes a variant, returns a string representation of that variant
//*****************************************************************************
WCHAR *ValueToString(CIMTYPE dwType, VARIANT *pValue, WCHAR **pbuf, WCHAR *fnHandler(VARIANT *pv))
{
    DWORD iTotBufSize, iLen;
    
    WCHAR *vbuf = NULL;
    WCHAR *buf = NULL;
    
    WCHAR lbuf[BLOCKSIZE];
    
    switch (pValue->vt) 
    {
        
    case VT_EMPTY:
        buf = (WCHAR *)malloc(BLOCKSIZE);
        wcscpy(buf, L"<empty>");
        break;
        
    case VT_NULL:
        buf = (WCHAR *)malloc(BLOCKSIZE);
        wcscpy(buf, L"<null>");
        break;
        
    case VT_BOOL: 
        {
            VARIANT_BOOL b = pValue->boolVal;
            buf = (WCHAR *)malloc(BLOCKSIZE);
            
            if (!b) {
                wcscpy(buf, L"FALSE");
            } else {
                wcscpy(buf, L"TRUE");
            }
            break;
        }
        
    case VT_I1: 
        {
            char b = pValue->bVal;
            buf = (WCHAR *)malloc(BLOCKSIZE);
            if (b >= 32) {
                swprintf(buf, L"'%c' (%hd, 0x%hX)", b, (signed char)b, b);
            } else {
                swprintf(buf, L"%hd (0x%hX)", (signed char)b, b);
            }
            break;
        }
        
    case VT_UI1: 
        {
            unsigned char b = pValue->bVal;
            buf = (WCHAR *)malloc(BLOCKSIZE);
            if (b >= 32) {
                swprintf(buf, L"'%c' (%hu, 0x%hX)", b, (unsigned char)b, b);
            } else {
                swprintf(buf, L"%hu (0x%hX)", (unsigned char)b, b);
            }
            break;
        }
        
    case VT_I2:
        {
            SHORT i = pValue->iVal;
            buf = (WCHAR *)malloc(BLOCKSIZE);
            swprintf(buf, L"%hd (0x%hX)", i, i);
            break;
        }
        
    case VT_UI2:
        {
            USHORT i = pValue->uiVal;
            buf = (WCHAR *)malloc(BLOCKSIZE);
            swprintf(buf, L"%hu (0x%hX)", i, i);
            break;
        }
        
    case VT_I4: 
        {
            LONG l = pValue->lVal;
            buf = (WCHAR *)malloc(BLOCKSIZE);
            swprintf(buf, L"%d (0x%X)", l, l);
            break;
        }
        
    case VT_UI4: 
        {
            ULONG l = pValue->ulVal;
            buf = (WCHAR *)malloc(BLOCKSIZE);
            swprintf(buf, L"%u (0x%X)", l, l);
            break;
        }
        
    case VT_R4: 
        {
            float f = pValue->fltVal;
            buf = (WCHAR *)malloc(CVTBUFSIZE * sizeof(WCHAR));
            swprintf(buf, L"%10.4f", f);
            break;
        }
        
    case VT_R8: 
        {
            double d = pValue->dblVal;
            buf = (WCHAR *)malloc(CVTBUFSIZE * sizeof(WCHAR));
            swprintf(buf, L"%10.4f", d);
            break;
        }
        
    case VT_BSTR: 
        {
            if (dwType == CIM_SINT64)
            {
                // a little redundant, but it makes me feel better
                LPWSTR pWStr = pValue->bstrVal;
                __int64 l = _wtoi64(pWStr);
                
                buf = (WCHAR *)malloc(BLOCKSIZE);
                swprintf(buf, L"%I64d", l, l);
            } 
            else if (dwType == CIM_UINT64)
            {
                // a little redundant, but it makes me feel better
                LPWSTR pWStr = pValue->bstrVal;
                __int64 l = _wtoi64(pWStr);
                
                buf = (WCHAR *)malloc(BLOCKSIZE);
                swprintf(buf, L"%I64u", l, l);
            }
            else // string, datetime, reference
            {
                LPWSTR pWStr = pValue->bstrVal;
                buf = (WCHAR *)malloc((wcslen(pWStr) * sizeof(WCHAR)) + sizeof(WCHAR) + (2 * sizeof(WCHAR)));
                swprintf(buf, L"\"%wS\"", pWStr);
            }
            break;
        }
        
    case VT_BOOL|VT_ARRAY: 
        {
            SAFEARRAY *pVec = pValue->parray;
            long iLBound, iUBound;
            BOOL bFirst = TRUE;
            
            SafeArrayGetLBound(pVec, 1, &iLBound);
            SafeArrayGetUBound(pVec, 1, &iUBound);
            if ((iUBound - iLBound + 1) == 0) {
                buf = (WCHAR *)malloc(BLOCKSIZE);
                wcscpy(buf, L"<empty array>");
                break;
            }
            
            buf = (WCHAR *)malloc((iUBound - iLBound + 1) * BLOCKSIZE);
            wcscpy(buf, L"");
            
            for (long i = iLBound; i <= iUBound; i++) {
                if (!bFirst) {
                    wcscat(buf, L",");
                } else {
                    bFirst = FALSE;
                }
                
                VARIANT_BOOL v;
                SafeArrayGetElement(pVec, &i, &v);
                if (v) {
                    wcscat(buf, L"TRUE");
                } else {
                    wcscat(buf, L"FALSE");
                }
            }
            
            break;
        }
        
    case VT_I1|VT_ARRAY: 
        {
            SAFEARRAY *pVec = pValue->parray;
            long iLBound, iUBound;
            BOOL bFirst = TRUE;
            
            SafeArrayGetLBound(pVec, 1, &iLBound);
            SafeArrayGetUBound(pVec, 1, &iUBound);
            if ((iUBound - iLBound + 1) == 0) {
                buf = (WCHAR *)malloc(BLOCKSIZE);
                wcscpy(buf, L"<empty array>");
                break;
            }
            
            buf = (WCHAR *)malloc((iUBound - iLBound + 1) * BLOCKSIZE);
            wcscpy(buf, L"");
            WCHAR *pos = buf;
            DWORD len;
            
            BYTE *pbstr;
            SafeArrayAccessData(pVec, (void HUGEP* FAR*)&pbstr);
            
            for (long i = iLBound; i <= iUBound; i++) {
                if (!bFirst) {
                    wcscpy(pos, L",");
                    pos += 1;
                } else {
                    bFirst = FALSE;
                }
                
                char v;
                //            SafeArrayGetElement(pVec, &i, &v);
                v = pbstr[i];
                
                if (v < 32) {
                    len = swprintf(lbuf, L"%hd (0x%X)", v, v);
                } else {
                    len = swprintf(lbuf, L"'%c' %hd (0x%X)", v, v, v);
                }
                
                wcscpy(pos, lbuf);
                pos += len;
                
            }
            
            SafeArrayUnaccessData(pVec);
            
            break;
        }
        
    case VT_UI1|VT_ARRAY: 
        {
            SAFEARRAY *pVec = pValue->parray;
            long iLBound, iUBound;
            BOOL bFirst = TRUE;
            
            SafeArrayGetLBound(pVec, 1, &iLBound);
            SafeArrayGetUBound(pVec, 1, &iUBound);
            if ((iUBound - iLBound + 1) == 0) {
                buf = (WCHAR *)malloc(BLOCKSIZE);
                wcscpy(buf, L"<empty array>");
                break;
            }
            
            buf = (WCHAR *)malloc((iUBound - iLBound + 1) * BLOCKSIZE);
            wcscpy(buf, L"");
            WCHAR *pos = buf;
            DWORD len;
            
            BYTE *pbstr;
            SafeArrayAccessData(pVec, (void HUGEP* FAR*)&pbstr);
            
            for (long i = iLBound; i <= iUBound; i++) {
                if (!bFirst) {
                    wcscpy(pos, L",");
                    pos += 1;
                } else {
                    bFirst = FALSE;
                }
                
                unsigned char v;
                //            SafeArrayGetElement(pVec, &i, &v);
                v = pbstr[i];
                
                if (v < 32) {
                    len = swprintf(lbuf, L"%hu (0x%X)", v, v);
                } else {
                    len = swprintf(lbuf, L"'%c' %hu (0x%X)", v, v, v);
                }
                
                wcscpy(pos, lbuf);
                pos += len;
                
            }
            
            SafeArrayUnaccessData(pVec);
            
            break;
        }
        
    case VT_I2|VT_ARRAY: 
        {
            SAFEARRAY *pVec = pValue->parray;
            long iLBound, iUBound;
            BOOL bFirst = TRUE;
            
            SafeArrayGetLBound(pVec, 1, &iLBound);
            SafeArrayGetUBound(pVec, 1, &iUBound);
            if ((iUBound - iLBound + 1) == 0) {
                buf = (WCHAR *)malloc(BLOCKSIZE);
                wcscpy(buf, L"<empty array>");
                break;
            }
            
            buf = (WCHAR *)malloc((iUBound - iLBound + 1) * BLOCKSIZE);
            wcscpy(buf, L"");
            
            for (long i = iLBound; i <= iUBound; i++) {
                if (!bFirst) {
                    wcscat(buf, L",");
                } else {
                    bFirst = FALSE;
                }
                
                SHORT v;
                SafeArrayGetElement(pVec, &i, &v);
                swprintf(lbuf, L"%hd", v);
                wcscat(buf, lbuf);
            }
            
            break;
        }
        
    case VT_UI2|VT_ARRAY: 
        {
            SAFEARRAY *pVec = pValue->parray;
            long iLBound, iUBound;
            BOOL bFirst = TRUE;
            
            SafeArrayGetLBound(pVec, 1, &iLBound);
            SafeArrayGetUBound(pVec, 1, &iUBound);
            if ((iUBound - iLBound + 1) == 0) {
                buf = (WCHAR *)malloc(BLOCKSIZE);
                wcscpy(buf, L"<empty array>");
                break;
            }
            
            buf = (WCHAR *)malloc((iUBound - iLBound + 1) * BLOCKSIZE);
            wcscpy(buf, L"");
            
            for (long i = iLBound; i <= iUBound; i++) {
                if (!bFirst) {
                    wcscat(buf, L",");
                } else {
                    bFirst = FALSE;
                }
                
                USHORT v;
                SafeArrayGetElement(pVec, &i, &v);
                swprintf(lbuf, L"%hu", v);
                wcscat(buf, lbuf);
            }
            
            break;
        }
        
    case VT_I4|VT_ARRAY: 
        {
            SAFEARRAY *pVec = pValue->parray;
            long iLBound, iUBound;
            BOOL bFirst = TRUE;
            
            SafeArrayGetLBound(pVec, 1, &iLBound);
            SafeArrayGetUBound(pVec, 1, &iUBound);
            if ((iUBound - iLBound + 1) == 0) {
                buf = (WCHAR *)malloc(BLOCKSIZE);
                wcscpy(buf, L"<empty array>");
                break;
            }
            
            buf = (WCHAR *)malloc((iUBound - iLBound + 1) * BLOCKSIZE);
            wcscpy(buf, L"");
            
            for (long i = iLBound; i <= iUBound; i++) {
                if (!bFirst) {
                    wcscat(buf, L",");
                } else {
                    bFirst = FALSE;
                }
                
                LONG v;
                SafeArrayGetElement(pVec, &i, &v);
                _ltow(v, lbuf, 10);
                wcscat(buf, lbuf);
            }
            
            break;
        }
        
    case VT_UI4|VT_ARRAY: 
        {
            SAFEARRAY *pVec = pValue->parray;
            long iLBound, iUBound;
            BOOL bFirst = TRUE;
            
            SafeArrayGetLBound(pVec, 1, &iLBound);
            SafeArrayGetUBound(pVec, 1, &iUBound);
            if ((iUBound - iLBound + 1) == 0) {
                buf = (WCHAR *)malloc(BLOCKSIZE);
                wcscpy(buf, L"<empty array>");
                break;
            }
            
            buf = (WCHAR *)malloc((iUBound - iLBound + 1) * BLOCKSIZE);
            wcscpy(buf, L"");
            
            for (long i = iLBound; i <= iUBound; i++) {
                if (!bFirst) {
                    wcscat(buf, L",");
                } else {
                    bFirst = FALSE;
                }
                
                ULONG v;
                SafeArrayGetElement(pVec, &i, &v);
                _ultow(v, lbuf, 10);
                wcscat(buf, lbuf);
            }
            
            break;
        }
        
    case CIM_REAL32|VT_ARRAY: 
        {
            SAFEARRAY *pVec = pValue->parray;
            long iLBound, iUBound;
            BOOL bFirst = TRUE;
            
            SafeArrayGetLBound(pVec, 1, &iLBound);
            SafeArrayGetUBound(pVec, 1, &iUBound);
            if ((iUBound - iLBound + 1) == 0) {
                buf = (WCHAR *)malloc(BLOCKSIZE);
                wcscpy(buf, L"<empty array>");
                break;
            }
            
            buf = (WCHAR *)malloc((iUBound - iLBound + 1) * (CVTBUFSIZE * sizeof(WCHAR)));
            wcscpy(buf, L"");
            
            for (long i = iLBound; i <= iUBound; i++) {
                if (!bFirst) {
                    wcscat(buf, L",");
                } else {
                    bFirst = FALSE;
                }
                
                FLOAT v;
                SafeArrayGetElement(pVec, &i, &v);
                swprintf(lbuf, L"%10.4f", v);
                wcscat(buf, lbuf);
            }
            
            break;
        }
        
    case CIM_REAL64|VT_ARRAY: 
        {
            SAFEARRAY *pVec = pValue->parray;
            long iLBound, iUBound;
            BOOL bFirst = TRUE;
            
            SafeArrayGetLBound(pVec, 1, &iLBound);
            SafeArrayGetUBound(pVec, 1, &iUBound);
            if ((iUBound - iLBound + 1) == 0) {
                buf = (WCHAR *)malloc(BLOCKSIZE);
                wcscpy(buf, L"<empty array>");
                break;
            }
            
            buf = (WCHAR *)malloc((iUBound - iLBound + 1) * (CVTBUFSIZE * sizeof(WCHAR)));
            wcscpy(buf, L"");
            
            for (long i = iLBound; i <= iUBound; i++) {
                if (!bFirst) {
                    wcscat(buf, L",");
                } else {
                    bFirst = FALSE;
                }
                
                double v;
                SafeArrayGetElement(pVec, &i, &v);
                swprintf(lbuf, L"%10.4f", v);
                wcscat(buf, lbuf);
            }
            
            break;
        }
        
    case VT_BSTR|VT_ARRAY: 
        {
            
            if (dwType == (CIM_UINT64|VT_ARRAY))
            {
                SAFEARRAY *pVec = pValue->parray;
                long iLBound, iUBound;
                BOOL bFirst = TRUE;
                
                SafeArrayGetLBound(pVec, 1, &iLBound);
                SafeArrayGetUBound(pVec, 1, &iUBound);
                if ((iUBound - iLBound + 1) == 0) {
                    buf = (WCHAR *)malloc(BLOCKSIZE);
                    wcscpy(buf, L"<empty array>");
                    break;
                }
                
                buf = (WCHAR *)malloc((iUBound - iLBound + 1) * BLOCKSIZE);
                wcscpy(buf, L"");
                
                for (long i = iLBound; i <= iUBound; i++) {
                    if (!bFirst) {
                        wcscat(buf, L",");
                    } else {
                        bFirst = FALSE;
                    }
                    
                    BSTR v = NULL;
                    
                    SafeArrayGetElement(pVec, &i, &v);
                    
                    swprintf(lbuf, L"%I64u", _wtoi64(v));
                    wcscat(buf, lbuf);
                }
            }
            else if (dwType == (CIM_SINT64|VT_ARRAY))
            {
                SAFEARRAY *pVec = pValue->parray;
                long iLBound, iUBound;
                BOOL bFirst = TRUE;
                
                SafeArrayGetLBound(pVec, 1, &iLBound);
                SafeArrayGetUBound(pVec, 1, &iUBound);
                if ((iUBound - iLBound + 1) == 0) {
                    buf = (WCHAR *)malloc(BLOCKSIZE);
                    wcscpy(buf, L"<empty array>");
                    break;
                }
                
                buf = (WCHAR *)malloc((iUBound - iLBound + 1) * BLOCKSIZE);
                wcscpy(buf, L"");
                
                for (long i = iLBound; i <= iUBound; i++) {
                    if (!bFirst) {
                        wcscat(buf, L",");
                    } else {
                        bFirst = FALSE;
                    }
                    
                    BSTR v = NULL;
                    
                    SafeArrayGetElement(pVec, &i, &v);
                    
                    swprintf(lbuf, L"%I64d", _wtoi64(v));
                    wcscat(buf, lbuf);
                }
            }
            else // string, datetime, reference
            {
                
                SAFEARRAY *pVec = pValue->parray;
                long iLBound, iUBound;
                DWORD iNeed;
                DWORD iVSize;
                DWORD iCurBufSize;
                
                SafeArrayGetLBound(pVec, 1, &iLBound);
                SafeArrayGetUBound(pVec, 1, &iUBound);
                if ((iUBound - iLBound + 1) == 0) {
                    buf = (WCHAR *)malloc(BLOCKSIZE);
                    wcscpy(buf, L"<empty array>");
                    break;
                }
                
                iTotBufSize = (iUBound - iLBound + 1) * BLOCKSIZE;
                buf = (WCHAR *)malloc(iTotBufSize);
                buf[0] = L'\0';
                iCurBufSize = 0;
                iVSize = BLOCKSIZE;
                vbuf = (WCHAR *)malloc(BLOCKSIZE);
                
                for (long i = iLBound; i <= iUBound; i++) {
                    BSTR v = NULL;
                    SafeArrayGetElement(pVec, &i, &v);
                    iLen = (wcslen(v) + 1) * sizeof(WCHAR);
                    if (iLen > iVSize) {
                        vbuf = (WCHAR *)realloc(vbuf, iLen + sizeof(WCHAR));
                        iVSize = iLen;
                    }
                    
                    // String size + (quotes + comma + null)
                    iNeed = (swprintf(vbuf, L"%wS", v) + 4) * sizeof(WCHAR);
                    if (iNeed + iCurBufSize > iTotBufSize) {
                        iTotBufSize += (iNeed * 2);  // Room enough for 2 more entries
                        buf = (WCHAR *)realloc(buf, iTotBufSize);
                    }
                    wcscat(buf, L"\"");
                    wcscat(buf, vbuf);
                    if (i + 1 <= iUBound) {
                        wcscat(buf, L"\",");
                    } else {
                        wcscat(buf, L"\"");
                    }
                    iCurBufSize += iNeed;
                    SysFreeString(v);
                    
                }
                free(vbuf);
            }
            
            break;
      }
      
      default: 
          {
              if (fnHandler != NULL) {
                  buf = fnHandler(pValue);
              } else {
                  buf = (WCHAR *)malloc(BLOCKSIZE);
                  wcscpy(buf, L"<conversion error>");
              }
          }
          
   }
   
   *pbuf = buf;   
   return buf;
}

//*****************************************************************************
// Function:   cvt
// Purpose:    Converts unicode to oem for console output
// Note:       y must be freed by caller
//*****************************************************************************
char *cvt(WCHAR *x, char **y)
{
   int dwRet, i;
   i = WideCharToMultiByte( CP_OEMCP, 
                        0,
                        x, 
                        -1, 
                        NULL, 
                        0, 
                        NULL, 
                        NULL);

      *y = (char *)calloc(i, 1);
      dwRet = WideCharToMultiByte( CP_OEMCP, 
                           0,
                           x, 
                           -1, 
                           *y, 
                           i, 
                           NULL, 
                           NULL);
   if (dwRet == 0) {
      free(*y);
      *y = (char *)malloc(sizeof(CVTFAILED));
      memcpy(*y, CVTFAILED, sizeof(CVTFAILED));
   }

   return *y;
};

//*****************************************************************************
// Function:   myWFPrintf
// Purpose:    Checks to see if outputing to console and converts strings
//             to oem if necessary.
// Note:       Returns number of characters written (ie if we write 3 oem
//             chars, it returns 3.  If it writes 4 wchars, it returns 4).
//*****************************************************************************
int myFWPrintf(FILE *f, WCHAR *fmt, ...)

{
   va_list    argptr;
   char *z;
   int i;

   int iSize = PAGESIZE;
   WCHAR *wszBuff = (WCHAR *)malloc(iSize);

   va_start(argptr, fmt);  // Init variable arguments

   // Format the string into a buffer.  Make sure the buffer is big enough
   while (_vsnwprintf(wszBuff, iSize/sizeof(WCHAR), fmt, argptr) == -1) {
      iSize += PAGESIZE;
      wszBuff = (WCHAR *)realloc(wszBuff, iSize);
   }

   if (f == stdout) {
      fputs(cvt(wszBuff,&z), f);
      i = strlen(z);
      free(z);
   } else {
      i = wcslen(wszBuff);
      fwrite(wszBuff, i * sizeof(WCHAR), 1, f);
   }

   free(wszBuff);
   va_end(argptr);

   return i;
}

//*****************************************************************************
// Function:   difftime
// Purpose:    Returns the elapsed time between two _timeb structures
// Note:       This is different from the crt routine which works on time_t
//             structures.
//*****************************************************************************
double difftime(struct _timeb finish, struct _timeb start)
{
   double dRet;

   if (start.millitm > finish.millitm) {
      dRet = ((finish.time - start.time) - 1) + (double)(((1000 + finish.millitm) - start.millitm) / 1000.0);
   } else {
      dRet = (finish.time - start.time) + (double)((finish.millitm - start.millitm) / 1000.0);
   }
   return dRet;
}
