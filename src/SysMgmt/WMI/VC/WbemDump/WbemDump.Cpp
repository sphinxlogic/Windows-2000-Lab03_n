// **************************************************************************
// Copyright (c) 1999 Microsoft Corporation.
//
// File:  wbemdump.cpp
//
// Description:
//    dumps the contents of the cimom database
//    see wbemdump /? for command line switches
//
// History:
//
// **************************************************************************

#define TIMEOUT -1
#define UNICODE_SIGNATURE "\xff\xfe"
#define _WIN32_DCOM

#pragma warning(disable:4201)  // nonstandard extension nameless struct (used in windows.h)
#pragma warning(disable:4514)  // unreferenced inline function has been removed (used in windows.h)

#include "wbemdump.h"    // this must come before windows.h

//#include <windows.h>  not needed since it is re-included in wbemidl.h
#include <wbemidl.h>     // wbem interface declarations
#include <stdio.h>      // fprintf
#include <stdlib.h>
#include <locale.h>
#include <sys/timeb.h>
#include <wbemsec.h>
#include <utillib.h>

// Function declarations
void DoIndent();
void EnumClasses(IWbemServices *pIWbemServices, WCHAR *pwcsClass);
void EnumInstances(IWbemServices *pIWbemServices, WCHAR *pwcsClassName );
void EnumNamespaces(IWbemServices *pIWbemServices, WCHAR *pwcsClassName);
WCHAR *EnumProperties(IWbemClassObject *pIWbemClassObject);
void Init(IWbemServices **ppIWbemServices, WCHAR *pNamespace);
IWbemClassObject *GetObj(IWbemServices *pIWbemServices, IWbemClassObject *pIWbemClassObject);
DWORD ProcessCommandLine(int argc, wchar_t *argv[]);
void ExecuteQuery(IWbemServices *pIWbemServices, WCHAR *pwcsQueryLanguage, WCHAR *pwcsQuery);
void PrintMof(IWbemClassObject *pIWbemClassObject);
void ShowClass(IWbemServices *pIWbemServices, IWbemClassObject *pIWbemClassObject);
BOOL CheckQualifiers(IWbemClassObject *pIWbemClassObject);
void ShowInstance(IWbemServices *pIWbemServices, IWbemClassObject *pIWbemClassObject);
void CheckAssocEndPoints(IWbemServices *pIWbemServices, IWbemClassObject *pIWbemClassObject);
int BstrCmp(const void *arg1,const void *arg2);
WCHAR *EscapeChars(WCHAR *szInBuf);
WCHAR *MyValueToString(VARIANT *pv);
void ShowInstanceHeader(WCHAR *pwcsClassName);
void ResetGlobalFlags();
bool ParseCommandLine(int *numargs, wchar_t **p);
static void __cdecl wparse_cmdline (
    WCHAR *cmdstart,
    WCHAR **argv,
    WCHAR *args,
    int *numargs,
    int *numchars
    );

// Global flags
BOOL bShowSystem = FALSE;     // Show system objects
BOOL bShowSystem1 = FALSE;    // Show system objects except __SERVER or __PATH
BOOL bShowInstance = FALSE;   // Show instance from ObjectPath
BOOL bShowProperties = TRUE;  // Show properties
BOOL bRecurseClass = FALSE;   // Recurse down class tree
BOOL bRecurseNS = FALSE;      // Recurse down ns's
BOOL bCheckGet = FALSE;       // Check the GetObject function
BOOL bCheckAssoc = FALSE;     // Check Association endpoints
BOOL bDoQuery = FALSE;        // Run a query instead of doing an enum
BOOL bClassMofs = FALSE;      // Show mofs for classes
BOOL bInstanceMofs = FALSE;   // Show mofs for instances
BOOL bMofTemplate = FALSE;    // Show instance mof templates
BOOL bUnicodeCmdFile = FALSE; // Whether the cmd file is unicode
BOOL bTime1 = FALSE;          // Show timings for /Q queries
BOOL bTime2 = FALSE;          // Alternate show timings for /Q queries
BOOL bWarningContinue = FALSE; // Show warning and continue
BOOL bWarning = FALSE;        // Show warning and ask

//
FILE *g_fOut = NULL;          // Handle for unicode file
FILE *g_fCmdFile = NULL;      // Handle for command file
int iIndent = 0;              // Current indention level

WCHAR *pwcsGNewLine = L"\n";    // Used to delimit lines
WCHAR *pwcsGNamespace = NULL;   // NameSpace to start from
WCHAR *pwcsGObjectPath = NULL;  // ObjectPath to show
WCHAR *pwcsQuery = NULL;        // Query (for /q commands)
WCHAR *pwcsGUserID = NULL;      // Userid for ConnectServer
WCHAR *pwcsGPassword = NULL;    // PW for ConnectServer
WCHAR *pwcsGAuthority = NULL;   // Authority for ConnectServer
WCHAR *pwcsGLocale = NULL;      // Locale for ConnectServer
WCHAR *pbstrGQualifierName = NULL; // Class Qualifier to filter on
WCHAR *pbstrGQualifierValue = NULL; // Class Qualifier value to filter on
long lGSFlags = 0;              // Security flags for ConnectServer
long lGImpFlag = RPC_C_IMP_LEVEL_IMPERSONATE;            // Impersonation level (-1 means use default)
long lGAuthFlag = -1;            // Impersonation level (-1 means use default)
IWbemContext *pGContext = NULL; // Pointer to ClassContext object
long lGEFlags = 0;              // Flags for CreateXxxEnum
long lGGFlags = 0;              // Flags for GetObject
DWORD dwGLoopCnt = 1;           // Loop count
//***************************************************************************
//
// wmain - used wmain since the command line parameters come in as wchar_t
//
//***************************************************************************
extern "C" int wmain(int argc, wchar_t *argv[])
{
   IWbemServices *pIWbemServices = NULL;
   wchar_t *largv;
   int largc;

   setlocale(LC_ALL, "");

   // Init Com
   if (OleInitialize(NULL) != S_OK) {
      PrintErrorAndExit("OleInitialize Failed");  //exits program
   }

   if (ProcessCommandLine(argc, argv) != S_OK) {
      return(1);
   }

   Init(&pIWbemServices, pwcsGNamespace);        // Connect to wbem
   if (g_fCmdFile) {
      while (!feof(g_fCmdFile)) {
         ResetGlobalFlags();

         if (ParseCommandLine(&largc, &largv)) {
            ProcessCommandLine(largc, (wchar_t **)largv);
            if (bDoQuery) {
               ExecuteQuery(pIWbemServices, pwcsGObjectPath, pwcsQuery);
            } else {
               EnumNamespaces(pIWbemServices, pwcsGObjectPath);   // Enumerate Namespaces
            }
         }
      }
   } else {
      if (bDoQuery) {
         ExecuteQuery(pIWbemServices, pwcsGObjectPath, pwcsQuery);
      } else {
         EnumNamespaces(pIWbemServices, pwcsGObjectPath);   // Enumerate Namespaces
      }
   }

   // Wrapup and exit
   RELEASE(pIWbemServices);
   if (g_fOut) {
      fclose(g_fOut);
   }
   if (g_fCmdFile) {
      fclose(g_fCmdFile);
   }
   if (pGContext != NULL) {
      pGContext->Release();
   }
   if (pbstrGQualifierName != NULL)
   {
       SysFreeString(pbstrGQualifierName);
   }
   if (pbstrGQualifierValue != NULL)
   {
       SysFreeString(pbstrGQualifierValue);
    }
   OleUninitialize();

   return 0;
}

//***************************************************************************
// Function:   Init
//
// Purpose:   1 - Create an instance of the WbemLocator interface
//            2 - Use the pointer returned in step two to connect to
//                the server using the specified namespace.
//***************************************************************************
void Init(IWbemServices **ppIWbemServices, WCHAR *pNamespace)
{
   DWORD   dwRes;
   SCODE  sc;
   IWbemLocator *pIWbemLocator = NULL;

   // Get a session object.
   // 1 - Create an instance of the WbemLocator interface

   dwRes = CoCreateInstance(CLSID_WbemLocator,
                      NULL,
                      CLSCTX_INPROC_SERVER,
                      IID_IWbemLocator,
                      (LPVOID *) &pIWbemLocator);

   if (dwRes != S_OK) {
      PrintErrorAndExit("Failed to create IWbemLocator object", dwRes); // exits program
   }

   //   2 - Use the pointer returned in step two to connect to
   //       the server using the passed in namespace.


   sc = pIWbemLocator->ConnectServer(CBString(pNamespace),  // Namespace
                            CBString(pwcsGUserID),          // Userid
                            CBString(pwcsGPassword),        // PW
                            CBString(pwcsGLocale),          // Locale
                            lGSFlags,                       // flags
                            pwcsGAuthority,                 // Authority
                            NULL,                           // Context
                            ppIWbemServices
                           );
   if (sc != WBEM_NO_ERROR) {
      PrintErrorAndExit("ConnectServer failed", sc); //exits program
   }

   DWORD dwAuthLevel, dwImpLevel;
   sc = GetAuthImp(*ppIWbemServices, &dwAuthLevel, &dwImpLevel);
   if (sc != S_OK) {
       PrintErrorAndExit("GetAuthImp Failed on ConnectServer", sc);
   }

   if (lGImpFlag != -1) {
       dwImpLevel = lGImpFlag;
   }

   if (lGAuthFlag != -1) {
       dwAuthLevel = lGAuthFlag;
   }

   sc = SetInterfaceSecurity(*ppIWbemServices, pwcsGAuthority, pwcsGUserID, pwcsGPassword, dwAuthLevel, dwImpLevel);
   if (sc != S_OK) {
      PrintErrorAndExit("SetInterfaceSecurity Failed on ConnectServer", sc);
   }

   RELEASE(pIWbemLocator);
}

//*****************************************************************************
// Function:   EnumClasses (Enumerate classes)
// Purpose:    Enumerates subclasses of parm2, then calls ShowClass for
//             each class.  ShowClass will call this routine (leading to
//             recursion).
//*****************************************************************************
void EnumClasses(IWbemServices *pIWbemServices, WCHAR *pwcsClass)
{
   SCODE  sc;
   ULONG uReturned;
   IWbemClassObject     *pIWbemClassObject = NULL;
   IEnumWbemClassObject *pIEnumWbemClassObject = NULL;

   // Create an enumeration of all subclasses of pwcsClass
   sc = pIWbemServices->CreateClassEnum(CBString(pwcsClass),
                              WBEM_FLAG_SHALLOW | lGEFlags,
                              pGContext,
                              &pIEnumWbemClassObject);
   if (sc != WBEM_NO_ERROR) {
       PrintErrorAndExit("Could not create Class enumerator", sc);  //Exits program
   }

   DWORD dwAuthLevel, dwImpLevel;
   sc = GetAuthImp(pIWbemServices, &dwAuthLevel, &dwImpLevel);
   if (sc != S_OK) {
       PrintErrorAndExit("GetAuthImp Failed on CreateClassEnum", sc);
   }

   if (lGImpFlag != -1) {
       dwImpLevel = lGImpFlag;
   }

   if (lGAuthFlag != -1) {
       dwAuthLevel = lGAuthFlag;
   }

   sc = SetInterfaceSecurity(pIEnumWbemClassObject, pwcsGAuthority, pwcsGUserID, pwcsGPassword, dwAuthLevel, dwImpLevel);
   if (sc != S_OK) {
      PrintErrorAndExit("SetInterfaceSecurity Failed on CreateClassEnum", sc);
   }

   // Get the first class
   sc = pIEnumWbemClassObject->Next(TIMEOUT,
                                 1,
                                 &pIWbemClassObject,
                                 &uReturned);

   // uReturned is the number of classes returned from Next.  When 0, we're done
   while (uReturned == 1) {

      ShowClass(pIWbemServices, pIWbemClassObject);

      // Release the class object (from the Next())
      RELEASE(pIWbemClassObject);

      // Set up to try again
      sc = pIEnumWbemClassObject->Next(TIMEOUT,
                                 1,
                                 &pIWbemClassObject,
                                 &uReturned);

    }

    // Make sure we ended on a positive note
    if (sc != S_FALSE) {
       PrintErrorAndExit("Could not get next class", sc);  //Exits program
    }

   // Release the enumerator
   RELEASE(pIEnumWbemClassObject);

}

//*****************************************************************************
// Function:   ShowClass
// Purpose:    Calls the appropriate functions to show the passed in class
// Note:       This routine calls EnumClasses, which leads to recursion
//*****************************************************************************
void ShowClass(IWbemServices *pIWbemServices, IWbemClassObject *pIWbemClassObject)
{
   SCODE sc;
   VARIANT varString;

   VariantInit(&varString);

   // Get the __class property
   sc = pIWbemClassObject->Get(CBString(CLASSPROP), 0L, &varString, NULL, NULL);
   if (sc != WBEM_NO_ERROR) {
      PrintErrorAndExit("Could not get __Class property for class", sc);  // Exits program
   }

   // we are showing system objs or this is not a system obj
   if ((bShowSystem) || (wcsncmp(V_BSTR(&varString), SYSTEMPREFIX, 2) != 0)) {

       if (CheckQualifiers(pIWbemClassObject))
       {
          // Either show the class mof, or show the instances
          if (bClassMofs) {
             PrintMof(pIWbemClassObject);
             if (bInstanceMofs) {
                EnumInstances(pIWbemServices, V_BSTR(&varString));
             }
          } else {
             EnumInstances(pIWbemServices, V_BSTR(&varString));
          }
       }
   }

   // If we are supposed to recurse
   if (bRecurseClass) {
       if ((!bMofTemplate) && (pbstrGQualifierName == NULL)) {
           iIndent++;  // Increase indention level
       }
       EnumClasses(pIWbemServices, V_BSTR(&varString));  // Enumerate all classes under this class
       if ((!bMofTemplate) && (pbstrGQualifierName == NULL)) {
           iIndent--;  // Decrease indention level
       }
   }

   VariantClear(&varString);

}

//*****************************************************************************
// Function:   EnumInstances
// Purpose:    Enumerates all instances of the class passed in pwcsClassName
//             and calls EnumProperties with each one.
// Note:       Shows instances in one of four ways.
//             1) Show the instance mof
//             2) Show the instance values
//             3) Show the wbemdump command line needed to dump this instance
//             4) Show a template instance mof
//*****************************************************************************
void EnumInstances(IWbemServices *pIWbemServices, WCHAR *pwcsClassName)
{
    SCODE  sc;
    ULONG uReturned;
    IWbemClassObject *pIWbemClassObject = NULL;
    IWbemClassObject *clObject = NULL;
    IEnumWbemClassObject *IEnumWbemClassObject = NULL;
    bool bFirst;
    
    if (bMofTemplate) {
        // For a template, all I need is a blank instance, so get the object...
        sc = pIWbemServices->GetObject(
            CBString(pwcsClassName),
            lGGFlags,
            pGContext,
            &pIWbemClassObject,
            NULL);
        if (sc != WBEM_NO_ERROR) {
            PrintErrorAndExit("Failed to GetObject in EnumInstances", sc);
        }
        
        // ... And spawn a blank one
        sc = pIWbemClassObject->SpawnInstance(0L, &clObject);
        RELEASE(pIWbemClassObject);  // Done with this object

        if (sc != WBEM_NO_ERROR) {
            PrintErrorAndExit("Failed to SpawnInstance in EnumInstances", sc);
        }
        
        // Now, print the properties
        ShowInstance(pIWbemServices, clObject);
        RELEASE(clObject);  // Done with this object
        
    } else {
        
        ShowInstanceHeader(pwcsClassName);
        bFirst = true;
        
        if (bShowProperties) {
            
            LARGE_INTEGER freq;
            QueryPerformanceFrequency(&freq);

            for (DWORD dwLoop = 0; dwLoop < dwGLoopCnt; dwLoop++) {
                
                struct _timeb start, finish;
                // If we are doing timings
                if (bTime1) {
                    _ftime(&start);
                }

                LARGE_INTEGER start2;
                if (bTime2) {
                    QueryPerformanceCounter(&start2);
                }

                // Create the enum
                sc = pIWbemServices->CreateInstanceEnum(CBString(pwcsClassName), // with this name
                    WBEM_FLAG_SHALLOW | lGEFlags,
                    pGContext,
                    &IEnumWbemClassObject);   // using this enumerator
                
                // If we are doing timings
                if (bTime1) {
                    _ftime(&finish);
                    fprintf(stdout, "CreateInstanceEnum: %6.4f seconds.\n", difftime(finish, start));
                }
                if (bTime2) {
                    LARGE_INTEGER finish2;
                    QueryPerformanceCounter(&finish2);
                    fprintf(stdout, "CreateInstanceEnum: %I64d (%6.4f)\n", finish2.QuadPart - start2.QuadPart, (double)(finish2.QuadPart - start2.QuadPart)/freq.QuadPart);
                }
        
                if (sc == WBEM_NO_ERROR) {
                    
                    DWORD dwAuthLevel, dwImpLevel;
                    sc = GetAuthImp(pIWbemServices, &dwAuthLevel, &dwImpLevel);
                    if (sc != S_OK) {
                        PrintErrorAndExit("GetAuthImp Failed on CreateInstanceEnum", sc);
                    }
                    
                    if (lGImpFlag != -1) {
                        dwImpLevel = lGImpFlag;
                    }
                    
                    if (lGAuthFlag != -1) {
                        dwAuthLevel = lGAuthFlag;
                    }
                    
                    sc = SetInterfaceSecurity(IEnumWbemClassObject, pwcsGAuthority, pwcsGUserID, pwcsGPassword, dwAuthLevel, dwImpLevel);
                    if (sc != S_OK) {
                        PrintErrorAndExit("SetInterfaceSecurity Failed on CreateInstanceEnum", sc);
                    }
                    
                    // If we are doing timings
                    if (bTime1) {
                        _ftime(&start);
                    }
        
                    if (bTime2) {
                        QueryPerformanceCounter(&start2);
                    }

                    sc = IEnumWbemClassObject->Next(TIMEOUT,
                        1,
                        &pIWbemClassObject,
                        &uReturned);

                    DWORD dwCount = 0;

                    while (sc == S_OK) {
                        
                        if (!bFirst) {
                            ShowInstanceHeader(pwcsClassName);
                        } else {
                            bFirst = false;
                        }
                        ShowInstance(pIWbemServices, pIWbemClassObject);
                        dwCount++;

                        RELEASE(pIWbemClassObject);  // Done with this object
                        sc = IEnumWbemClassObject->Next(TIMEOUT,
                            1,
                            &pIWbemClassObject,
                            &uReturned);
                    }
                    
                    // If we are doing timings
                    if (bTime1) {
                        _ftime(&finish);
                        fprintf(stdout, "ShowInstances: %6.4f seconds, %d instances.\n", difftime(finish, start), dwCount);
                    }
            
                    if (bTime2) {
                        LARGE_INTEGER finish2;
                        QueryPerformanceCounter(&finish2);
                        fprintf(stdout, "ShowInstances: %I64d (%6.4f), %d instances.\n", finish2.QuadPart - start2.QuadPart, (double)(finish2.QuadPart - start2.QuadPart)/freq.QuadPart, dwCount);
                    }
        
                    // Make sure we ended on a positive note
                    if (sc != S_FALSE) {
                        PrintErrorAndExit("Could not get next instance", sc);  //Exits program
                    }
                    
                    RELEASE(IEnumWbemClassObject);     // Done with this enumerator
                } else {
                    PrintErrorAndExit("Couldn't create instance enum", sc);
                }
            }
        }        
    }    
}

//*****************************************************************************
// Function:   EnumProperties
// Purpose:    Shows all property names of specified class
//*****************************************************************************
WCHAR *EnumProperties(IWbemClassObject *pIWbemClassObject)
{
   SCODE  sc;
   long lLower, lUpper, lCount;
   long plFlavor;
   SAFEARRAY *psaNames = NULL;
   BSTR PropName = NULL;
   IWbemQualifierSet *pQualSet = NULL;
   VARIANT varString, pVal;
   CIMTYPE dwType;
   WCHAR *pBuf;
   bool bKey = false;
   int x;
   MyString clMyBuff;
   BSTR bstrCimType = NULL;
   IWbemClassObject *clObject1 = NULL;
   IWbemClassObject *clObject2 = NULL;
   IWbemServices *pIWbemServices = NULL;
   void *vptr;

   VariantInit(&varString);
   VariantInit(&pVal);

   // Get the property names
   if (bShowSystem) {
      sc = pIWbemClassObject->GetNames(NULL, WBEM_FLAG_ALWAYS, NULL, &psaNames);
   } else {
      sc = pIWbemClassObject->GetNames(NULL, WBEM_FLAG_NONSYSTEM_ONLY, NULL, &psaNames);
   }

   if (sc != WBEM_NO_ERROR) {
      PrintErrorAndExit("Couldn't GetNames", sc); // Exits program
   }

   // Get the upper and lower bounds of the Names array
   sc = SafeArrayGetLBound(psaNames, 1, &lLower);
   if (S_OK != sc) {
      PrintErrorAndExit("Couldn't get safe array lbound", sc);  //Exits program
   }

   sc = SafeArrayGetUBound(psaNames, 1, &lUpper);
   if (S_OK != sc) {
      PrintErrorAndExit("Couldn't get safe array ubound", sc);  //Exits program
   }

   // Sort the array
   qsort(psaNames->pvData, lUpper - lLower + 1, sizeof(BSTR), BstrCmp);

   // For an instance template, print the 'INSTANCE OF <CLASS>' header
   if (bMofTemplate) {
      sc = pIWbemClassObject->Get(CBString(CLASSPROP), 0L, &varString, NULL, NULL);
      if (S_OK != sc) {
         PrintErrorAndExit("Couldn't get class property in enumproperties", sc);  //Exits program
      }

      for (x=0; x<iIndent; x++) {
         clMyBuff += L"\t";
      }

      clMyBuff += L"instance of ";
      clMyBuff += V_BSTR(&varString);
      clMyBuff += L" {";
      clMyBuff += pwcsGNewLine;
      iIndent++;

      VariantClear(&varString);
   }

   // For all properties...
   for (lCount = lLower; lCount <= lUpper; lCount++) {
      // get the property name for this element
      sc = SafeArrayGetElement(psaNames, &lCount, &PropName);
      if (S_OK != sc) {
         PrintErrorAndExit("Couldn't get safe array element", sc);  //Exits program
      }

      // Only print the property if
      //   we are showing all properties except __SERVER and __PATH and this is not them
      if (!((bShowSystem1) && ((_wcsicmp(PropName, SERVERPROP) == 0) || _wcsicmp(PropName, PATHPROP) == 0))) {
         for (x=0; x<iIndent; x++) {
            clMyBuff += L"\t";
         }

         clMyBuff += PropName;
         sc = pIWbemClassObject->Get(CBString(PropName), 0L, &varString, &dwType, NULL);  // Get the value for the property
         if (sc != WBEM_NO_ERROR) {
            PrintErrorAndExit("Couldn't get Property Value", sc);  //Exits program
         }

         // Get pointer to property qualifiers
         sc = pIWbemClassObject->GetPropertyQualifierSet(CBString(PropName), &pQualSet);

         // Get the QualifierSet
         if (sc == WBEM_NO_ERROR) {

            // Get CIMTYPE attribute (if any)
            sc = pQualSet->Get(CBString(CIMTYPEQUAL), 0L, &pVal, &plFlavor);
            if (sc == WBEM_NO_ERROR) {
               bstrCimType = SysAllocString(V_BSTR(&pVal));
            } else if (sc != WBEM_E_NOT_FOUND) {  // some other error
               PrintErrorAndExit("Could not get CIMTYPE qualifier", sc);  // Exits program
            }
            VariantClear(&pVal);

            // Determine if this is a key property
            sc = pQualSet->Get(CBString(KEYQUAL), 0L, &pVal, &plFlavor);
            if ((sc == WBEM_NO_ERROR) && (pVal.boolVal)) { // Yes, it's a key
               bKey = true;
            } else if (sc == WBEM_E_NOT_FOUND) {  // not a key qualifier
               bKey = false;
            } else { // some other error
               PrintErrorAndExit("Could not get key qualifier", sc);  // Exits program
            }
            RELEASE(pQualSet);

         // this mess is due to the fact that system properties don't have qualifiers
         } else if (sc != WBEM_E_SYSTEM_PROPERTY) {
             PrintErrorAndExit("Could not GetPropertyQualifierSet", sc);  // Exits program
         }

         // print variable type and key indicatory for property value
         if (!bMofTemplate) {
            clMyBuff += L" (";
            clMyBuff += TypeToString(dwType);

            if (bstrCimType != NULL) {
               clMyBuff += L"/";
               clMyBuff += bstrCimType;
            }

            // Mark the key fields
            if (bKey) {
               clMyBuff += L")* ";
            } else {
               clMyBuff += L") ";
            }
         }

         // If we are showing a mof template, and this property is an embedded object and
         // there is no default object, we will need to create a blank one.
         if ((bMofTemplate) && 
             (V_VT(&varString) == VT_NULL) && 
             ((dwType == CIM_OBJECT) || (dwType == (CIM_OBJECT | CIM_FLAG_ARRAY)))) {

            Init(&pIWbemServices, pwcsGNamespace);        // Connect to wbem

            // Get the object
            sc = pIWbemServices->GetObject(
                  CBString(&bstrCimType[7]),
                  lGGFlags,
                  pGContext,
                  &clObject1,
                  NULL);
            if (sc != WBEM_NO_ERROR) {
               PrintErrorAndExit("Failed to GetObject in EnumProperties", sc);
            }

            // and spawn an instance of it
            sc = clObject1->SpawnInstance(0L, &clObject2);
            if (sc != WBEM_NO_ERROR) {
               PrintErrorAndExit("Failed to SpawnInstance in EnumProperties", sc);
            }

            // If this is an array, create a safearray object
            if (dwType & CIM_FLAG_ARRAY) {
               // Create the array
               SAFEARRAYBOUND rgsabound[1];
               rgsabound[0].cElements = 1;
               rgsabound[0].lLbound = 0;

               V_ARRAY(&varString) = SafeArrayCreate((VARTYPE)(dwType & (~CIM_FLAG_ARRAY)), 1, rgsabound);

               // Put the object into the safearray
               SafeArrayAccessData(V_ARRAY(&varString), &vptr);
               clObject2->QueryInterface(IID_IUnknown, (void **)vptr);
               SafeArrayUnaccessData(V_ARRAY(&varString));

            } else {
               clObject2->QueryInterface(IID_IUnknown, (void **)&V_UNKNOWN(&varString));
            }

            // Reset the type from null to dwType
            V_VT(&varString) = (VARTYPE)dwType;

            // Cleanup
            RELEASE(clObject2);
            RELEASE(clObject1);
            RELEASE(pIWbemServices);
         }

         // Print the value
         clMyBuff += L" = ";
         if ((V_VT(&varString) == VT_UNKNOWN) || (V_VT(&varString) == (VT_UNKNOWN | VT_ARRAY))) {
            clMyBuff += pwcsGNewLine;
            clMyBuff += ValueToString(dwType, &varString, &pBuf, MyValueToString);
         } else {
            // For mof templates, if this is an array, add the braces
            if ((bMofTemplate) && ((V_VT(&varString) & VT_ARRAY) != 0)) {
               clMyBuff += L"{";
            }
            clMyBuff += ValueToString(dwType, &varString, &pBuf, MyValueToString);
            if ((bMofTemplate) && (V_VT(&varString) & VT_ARRAY) != 0) {
               clMyBuff += L"}";
            }
            // For mof templates, add the cimtype et al as a comment
            if (bMofTemplate) {
               clMyBuff += L"\t//\t";
               clMyBuff += TypeToString(dwType);
               clMyBuff += L"\t";
               clMyBuff += bstrCimType;
               clMyBuff += L"\t";
               BSTR bstrOrigin = NULL;
               pIWbemClassObject->GetPropertyOrigin(PropName, &bstrOrigin);
               clMyBuff += bstrOrigin;
               if (bKey) {
                  clMyBuff += L"\t*";
               }
               SysFreeString(bstrOrigin);
            }
            clMyBuff += pwcsGNewLine;
         }

         // Release and reset for next pass
         if (bstrCimType != NULL) {
            SysFreeString(bstrCimType);
            bstrCimType = NULL;
         }
         bKey = false;

         free(pBuf);

         VariantClear(&varString);
         VariantClear(&pVal);
      }
      SysFreeString(PropName);
   }

   SafeArrayDestroy(psaNames);

   if (bMofTemplate) {
      iIndent--;
      for (x=0; x<iIndent; x++) {
         clMyBuff += L"\t";
      }

      clMyBuff += L"};";
      clMyBuff += pwcsGNewLine;
   }

   return clMyBuff.GetCloneString();

}

//*****************************************************************************
// Function:   EnumNamespaces
// Purpose:    Enumerate NameSpaces
//*****************************************************************************
void EnumNamespaces(IWbemServices *pIWbemServices, WCHAR *pwcsClassName)
{
    SCODE sc;
    IWbemServices *pNewIWbemServices = NULL;
    VARIANT varString;
    
    VariantInit(&varString);
    
    IEnumWbemClassObject *IEnumWbemClassObject = NULL;
    IWbemClassObject     *pIWbemClassObject = NULL;
    
    ULONG uReturned;
    
    // If we aren't showing mofs or command lines
    if (!((bClassMofs) || (bInstanceMofs) || (bShowInstance) || (bMofTemplate))) {
        
        // Do this to get the right casing for the NameSpace
        // Call GetObject with a known-to-exist class
        sc = pIWbemServices->GetObject(
            CBString(SYSTEMCLASS),
            lGGFlags,
            pGContext,
            &pIWbemClassObject,
            NULL);
        
        if (sc != WBEM_NO_ERROR) {
            PrintErrorAndExit("Could not GetObject of __SystemClass in EnumNamespaces", sc);  // Exits program
        }
        
        sc = pIWbemClassObject->Get(CBString(NAMESPACEPROP), 0L, &varString, NULL, NULL);
        if (sc != WBEM_NO_ERROR) {
            PrintErrorAndExit("Could not get __NameSpace property for class", sc);  // Exits program
        }
        
        // Indent appropriate number of spaces and print namespace
        DoIndent();
        FWPRINTF(g_fOut, L"<%wS>%wS", V_BSTR(&varString), pwcsGNewLine);
        
        RELEASE(pIWbemClassObject);
        VariantClear(&varString);
        
        // Everything under this should be indented one more level
        iIndent++;
    }
    
    // If we are enumerating a specific class or instance, specify the class else pass null
    if (pwcsClassName != NULL) {
        // See if we are dealing with a single instance
        if (wcschr(pwcsClassName, L'=') != NULL) {
            for (DWORD x=0; x < dwGLoopCnt; x++)
            {
                sc = pIWbemServices->GetObject(
                    CBString(pwcsClassName),
                    lGGFlags,
                    pGContext,
                    &pIWbemClassObject,
                    NULL);
                
                if (sc != WBEM_NO_ERROR) {
                    fprintf(stderr, "%S\n", pwcsClassName);
                    PrintErrorAndExit("Could not GetObject of specified class in EnumNamespaces", sc);  // Exits program
                }
                
                sc = pIWbemClassObject->Get(CBString(CLASSPROP), 0L, &varString, NULL, NULL);
                if (sc != WBEM_NO_ERROR) {
                    PrintErrorAndExit("Could not get __Class property for class", sc);  // Exits program
                }
                ShowInstanceHeader(V_BSTR(&varString));
                ShowInstance(pIWbemServices, pIWbemClassObject);
                VariantClear(&varString);
                RELEASE(pIWbemClassObject);
            }
        }
        else 
        {
            sc = pIWbemServices->GetObject(
                CBString(pwcsClassName),
                lGGFlags,
                pGContext,
                &pIWbemClassObject,
                NULL);
            
            if (sc != WBEM_NO_ERROR) {
                fprintf(stderr, "%S\n", pwcsClassName);
                PrintErrorAndExit("Could not GetObject of specified class in EnumNamespaces", sc);  // Exits program
            }
            
            ShowClass(pIWbemServices, pIWbemClassObject);
            RELEASE(pIWbemClassObject);
        }
    } else {
        EnumClasses(pIWbemServices, L"");
    }
    
    // If the user did not specify /S on the command line, we're done
    if (!bRecurseNS) {
        return;
    }
    
    //Find any namespaces under the current namespace
    sc = pIWbemServices->CreateInstanceEnum(CBString(NAMESPACEPROP),         // with this name
        WBEM_FLAG_DEEP | lGEFlags,
        pGContext,
        &IEnumWbemClassObject);   // using this enumerator
    
    // If we find any namespaces, we'll want to enumerate them too
    if (sc == WBEM_NO_ERROR) {
        
        DWORD dwAuthLevel, dwImpLevel;
        sc = GetAuthImp(pIWbemServices, &dwAuthLevel, &dwImpLevel);
        if (sc != S_OK) {
            PrintErrorAndExit("GetAuthImp Failed on CreateInstanceEnum (ns)", sc);
        }
        
        if (lGImpFlag != -1) {
            dwImpLevel = lGImpFlag;
        }
        
        if (lGAuthFlag != -1) {
            dwAuthLevel = lGAuthFlag;
        }
                    
        sc = SetInterfaceSecurity(IEnumWbemClassObject, pwcsGAuthority, pwcsGUserID, pwcsGPassword, dwAuthLevel, dwImpLevel);
        if (sc != S_OK) {
            PrintErrorAndExit("SetInterfaceSecurity Failed on CreateInstanceEnum (ns)", sc);
        }
        
        // Get the name of the next namespace
        sc = IEnumWbemClassObject->Next(TIMEOUT,
            1,
            &pIWbemClassObject,
            &uReturned);
        
        while (uReturned == 1) {
            // Get the name
            sc = pIWbemClassObject->Get(CBString(NAMEPROP), 0L, &varString, NULL, NULL);
            if (sc != WBEM_NO_ERROR) {
                PrintErrorAndExit("Could not get name property", sc);  // Exits program
            }
            // Open it
            sc = pIWbemServices->OpenNamespace(CBString(V_BSTR(&varString)), 0L, NULL, &pNewIWbemServices, NULL);
            if (sc != WBEM_NO_ERROR) {
                PrintErrorAndExit("Failed to Open Namespace", sc);  // Exits program
            }
            
            // Now show all the classes/instances in the new Namespace
            EnumNamespaces(pNewIWbemServices, NULL);
            
            // Release
            VariantClear(&varString);
            RELEASE(pNewIWbemServices);
            RELEASE(pIWbemClassObject);
            
            // Get the name of the next namespace
            sc = IEnumWbemClassObject->Next(TIMEOUT,
                1,
                &pIWbemClassObject,
                &uReturned);
            
        }
        
        // Make sure we ended on a positive note
        if (sc != S_FALSE) {
            PrintErrorAndExit("Could not get next namespace", sc);  //Exits program
        }
        
        RELEASE(IEnumWbemClassObject);
    } else {
        PrintErrorAndExit("Failed to CreateInstanceEnum", sc);  // Exits program
    }
    
    // Back up one level of indention
    iIndent--;
    
}

//*****************************************************************************
// Function:   GetObj
// Purpose:    This is useful to test both enumerate and getobject
//*****************************************************************************
IWbemClassObject *GetObj(IWbemServices *pIWbemServices, IWbemClassObject *pIWbemClassObject)
{
   SCODE sc;
   VARIANT varString;
   IWbemClassObject *clObject = NULL;

   VariantInit(&varString);

   // Get the relative path of the current instance
   sc = pIWbemClassObject->Get(CBString(RELPATHPROP), 0L, &varString, NULL, NULL);
   if ((sc != WBEM_NO_ERROR) || (V_VT(&varString) != VT_BSTR)) {
      if (bWarningContinue) {
         PrintError("Could not get path of class", sc);
      } else if (bWarning) {
         PrintErrorAndAsk("Could not get path of class", sc);  // might exit program
      } else {
         PrintErrorAndExit("Could not get path of class", sc);  // might exit program
      }
      return NULL;
   }

   // Call GetObject with this path.  Obviously, this should succeed.
   sc = pIWbemServices->GetObject(
         CBString(V_BSTR(&varString)),
         lGGFlags,
         pGContext,
         &clObject,
         NULL);

   VariantClear(&varString);

   if (sc != WBEM_NO_ERROR) {
      if (bWarningContinue) {
         PrintError("Could not GetObject on class", sc);
      } else if (bWarning) {
         PrintErrorAndAsk("Could not GetObject on class", sc);  // might exit program
      } else {
         PrintErrorAndExit("Could not GetObject on class", sc);  // might exit program
      }
      return NULL;
   }

   return clObject;

}

//*****************************************************************************
// Function:   ExecuteQuery
// Purpose:    
// Note:       
//*****************************************************************************
void ExecuteQuery(IWbemServices *pIWbemServices, WCHAR *pwcsQueryLanguage, WCHAR *pwcsQuery)
{
    SCODE  sc;
    ULONG uReturned;
    IWbemClassObject *pIWbemClassObject = NULL;
    IEnumWbemClassObject *IEnumWbemClassObject = NULL;
    struct _timeb start, finish;
    
    DoIndent(); // Indent
    FWPRINTF(g_fOut, L"(%wS) %wS%wS", pwcsQueryLanguage, pwcsQuery, pwcsGNewLine); //Print class name
    
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    for (DWORD dwLoop = 0; dwLoop < dwGLoopCnt; dwLoop++) {

        LARGE_INTEGER start2;
        // If we are doing timings
        if (bTime1) {
            _ftime(&start);
        }

        if (bTime2) {
            QueryPerformanceCounter(&start2);
        }

        sc = pIWbemServices->ExecQuery(CBString(pwcsQueryLanguage),
            CBString(pwcsQuery),
            0L | lGEFlags,
            pGContext,
            &IEnumWbemClassObject);   // using this enumerator
        
        // If we are doing timings
        if (bTime1) {
            _ftime(&finish);
            fprintf(stdout, "ExecQuery %6.4f seconds.\n", difftime(finish, start));
        }
        if (bTime2) {
            LARGE_INTEGER finish2;
            QueryPerformanceCounter(&finish2);
            fprintf(stdout, "ExecQuery: %I64d (%6.4f)\n", finish2.QuadPart - start2.QuadPart, (double)(finish2.QuadPart - start2.QuadPart)/freq.QuadPart);
        }
        
        if (sc == WBEM_NO_ERROR) {
            
            DWORD dwCount = 0;

            // If we are doing timings
            if (bTime1) {
                _ftime(&start);
            }
            
            if (bTime2) {
                QueryPerformanceCounter(&start2);
            }

            DWORD dwAuthLevel, dwImpLevel;
            sc = GetAuthImp(pIWbemServices, &dwAuthLevel, &dwImpLevel);
            if (sc != S_OK) {
                PrintErrorAndExit("GetAuthImp Failed on ExecQuery", sc);
            }
            
            if (lGImpFlag != -1) {
                dwImpLevel = lGImpFlag;
            }
            
            if (lGAuthFlag != -1) {
                dwAuthLevel = lGAuthFlag;
            }
            
            sc = SetInterfaceSecurity(IEnumWbemClassObject, pwcsGAuthority, pwcsGUserID, pwcsGPassword, dwAuthLevel, dwImpLevel);
            if (sc != S_OK) {
                PrintErrorAndExit("SetInterfaceSecurity Failed on ExecQuery", sc);
            }
            
#pragma warning(disable:4127)
            while (1) {
#pragma warning(default:4127)
                // Get the next instance
                sc = IEnumWbemClassObject->Next(TIMEOUT,
                    1,
                    &pIWbemClassObject,
                    &uReturned);
                if(sc == S_OK) {
                    
                    ShowInstance(pIWbemServices, pIWbemClassObject);
                    RELEASE(pIWbemClassObject);  // Done with this object
                    dwCount++;
                    
                } else {
                    // Make sure we ended on a positive note
                    if (sc != S_FALSE) {
                        PrintErrorAndExit("Could not get next query instance", sc);  // Exits program
                    } else {
                        break;
                    }
                }
            }
            
            // If we are doing timings
            if (bTime1) {
                _ftime(&finish);
                fprintf(stdout, "ShowInstances %6.4f seconds, %d instances.\n", difftime(finish, start), dwCount);
            }
            
            if (bTime2) {
                LARGE_INTEGER finish2;
                QueryPerformanceCounter(&finish2);
                fprintf(stdout, "ShowInstances: %I64d (%6.4f), %d instances.\n", finish2.QuadPart - start2.QuadPart, (double)(finish2.QuadPart - start2.QuadPart)/freq.QuadPart, dwCount);
            }
        
            RELEASE(IEnumWbemClassObject);     // Done with this enumerator
        } else {
            PrintErrorAndExit("Error on query", sc);
        }
    }
    
}

//*****************************************************************************
// Function:   PrintMof
// Purpose:    Prints the mof file for the class that was passed in
// Note:       
//*****************************************************************************
void PrintMof(IWbemClassObject *clObject)
{
    SCODE sc;
    BSTR pObjectText = NULL;
    
    // Get the mof
    sc = clObject->GetObjectText(0L, &pObjectText);
    if (sc != WBEM_NO_ERROR) {
        PrintErrorAndExit("Failed to print mof", sc);  // Exits program
    }
    
    // Print it
    FWPRINTF(g_fOut, L"%wS", pObjectText);
    
    // Clean up
    SysFreeString(pObjectText);
    
}

//*****************************************************************************
// Function:   ShowInstance
// Purpose:    Shows the appropriate info for one specific instance
// Note:       
//*****************************************************************************
void ShowInstance(IWbemServices *pIWbemServices, IWbemClassObject *pIWbemClassObject)
{
   IWbemClassObject *clObject = NULL;
   WCHAR *buf;
   MyString clMyBuff;
   SCODE sc;
   VARIANT pVal;
   bool bGotOne = false;

   VariantInit(&pVal);

   // Get Object (useful to test both enumerate and getobject)
   if (bCheckGet) {
      clObject = GetObj(pIWbemServices, pIWbemClassObject);
      if (clObject == NULL) {
         clObject = pIWbemClassObject;
      } else {
         bGotOne = true;
      }
   } else {
      clObject = pIWbemClassObject;
   }

   if (bCheckAssoc)
   {
       CheckAssocEndPoints(pIWbemServices, pIWbemClassObject);
   }

   // If we are just showing the mof for each instance
   if (bInstanceMofs) {
      PrintMof(clObject);

   // If we are just printing the command line to show this instance
   } else if (bShowInstance) {
      // Start building the command line
      clMyBuff += L" \"";

      // Get the ns
      sc = clObject->Get(CBString(NAMESPACEPROP), 0L, &pVal, NULL, NULL);
      if (sc != WBEM_NO_ERROR) {
         PrintErrorAndExit("Could not get __namespace", sc);  // Exits program
      }
      VariantClear(&pVal);

      // Add the relpath
      sc = clObject->Get(CBString(RELPATHPROP), 0L, &pVal, NULL, NULL);
      if (sc != WBEM_NO_ERROR) {
         PrintErrorAndExit("Could not get __relpath", sc);  // Exits program
      }
      WCHAR *pW;
      pW = wcschr(V_BSTR(&pVal), L'=') + 1;
      buf = EscapeChars(pW);
      *(pW) = L'\0';
      clMyBuff += V_BSTR(&pVal);
      clMyBuff += buf;
      clMyBuff += L"\"";

      free(buf);
      VariantClear(&pVal);

      // Print it and we're done
      FWPRINTF(g_fOut, L"%wS%wS", clMyBuff.GetString(), pwcsGNewLine); // Print the command line
      clMyBuff.Empty();

   } else {
      // Otherwise we want to show the instance details
      if (!bMofTemplate) {
         iIndent++;              // Increase indention level
      }
      buf = EnumProperties(clObject);
      FWPRINTF(g_fOut, L"%wS%wS", buf, pwcsGNewLine); // Print the properties
      free(buf);
      if (!bMofTemplate) {
         iIndent--;              // Decrease the indention level
      }
   }

   if (bGotOne) {
      RELEASE(clObject);
   }
}

//*****************************************************************************
// Function:   BstrCmp
// Purpose:    Compares 2 bstr arguments
// Note:       Used by the qsort routine
//*****************************************************************************
int BstrCmp(const void *arg1,const void *arg2)
{
   return _wcsicmp( *(WCHAR **)arg1, *(WCHAR **)arg2 );
}

//*****************************************************************************
// Function:   DoIndent
// Purpose:    Indents iIndent tabs
//*****************************************************************************
void DoIndent()
{
   int x;

   for (x=0; x<iIndent; x++) {
      fputws(L"\t", g_fOut);
   }
}

//*****************************************************************************
// Function:   ProcessCommandLine
// Purpose:    This function processes the command line for the program,
//             filling in the global variables determining what the program
//             will do.
//*****************************************************************************
DWORD ProcessCommandLine(int argc, wchar_t *argv[])
{
   int iLoop, iPlace;
   char *z;
   WCHAR *pwcsName, *pwcsValue;
   SCODE sc;
   VARIANT vValue;
   char *szHelp = "WBEMDUMP - Dumps the contents of the CIMOM database.\n\n"
                  "Syntax: wbemdump [switches] [Namespace [Class|ObjectPath] ]\n"
                  "        wbemdump /Q [switches] Namespace QueryLanguage Query\n\n"
                  "Where:  'Namespace' is the namespace to dump (defaults to root\\default)\n"
                  "        'Class' is the name of a specific class to dump (defaults to none)\n"
                  "        'ObjectPath' is one instance (ex \"SClassA.KeyProp=\\\"foobar\\\"\")\n"
                  "        'QueryLanguage' is any WBEM supported query language (currently only\n"
                  "           \"WQL\" is supported).\n"
                  "        'Query' is a valid query for the specified language, enclosed in quotes\n"
                  "        'switches' is one of\n"
                  "           /S Recurse down the tree\n"
                  "           /S2 Recurse down Namespaces (implies /S)\n"
                  "           /E Show system classes and properties\n"
                  "           /E1 Like /E except don't show __SERVER or __PATH property\n"
                  "           /E2 Shows command lines for dumping instances (test mode)\n"
                  "           /D Don't show properties\n"
                  "           /G Do a GetObject on all enumerated instances\n"
                  "           /G2 Do a GetObject on all reference properties\n"
                  "           /G:<x> Like /G using x for flags (Amended=131072)\n"
                  "           /M Get Class MOFS instead of data values\n"
                  "           /M2 Get Instance MOFS instead of data values\n"
                  "           /M3 Produce instance template\n"
                  "           /B:<num> CreateEnum flags (SemiSync=16; Forward=32)\n"
                  "           /W  Prompt to continue on warning errors\n"
                  "           /WY Print warnings and continue\n"
                  "           /H:<name>:<value> Specify context object value (test mode)\n"
                  "           /CQV:<name>[:value] Specify a class qualifier on which to filter\n"
                  "           /T Print times on enumerations\n"
                  "           /T2 Print times on enumerations using alternate timer\n"
                  "           /O:<file> File name for output (creates Unicode file)\n"
                  "           /C:<file> Command file containing multiple WBEMDUMP command lines\n"
                  "           /U:<UserID> UserID to connect with (default: NULL)\n"
                  "           /P:<Password> Password to connect with (default: NULL)\n"
                  "           /A:<Authority> Authority to connect with\n"
                  "           /I:<ImpLevel> Anonymous=1 Identify=2 Impersonate=3(dflt) Delegate=4\n"
                  "           /AL:<AuthenticationLevel> None=1 Conn=2 Call=3 Pkt=4 PktI=5 PktP=6\n"
                  "           /Locale:<localid> Locale to pass to ConnectServer\n"
                  "           /L:<LoopCnt> Number of times to enumerate instances (leak check)\n"
                  "\n"
                  "Notes:  - You can redirect the output to a file using standard redirection.\n"
                  "        - If the /C switch is used, the namespace on the command line must\n"
                  "          be the same namespace that is used for each of the command lines.\n"
                  "          It is not possible to use different namespaces on the different lines\n"
                  "          in the command file.\n"
                  "\n"
                  "EXAMPLES:\n"
                  "\n"
                  "  WBEMDUMP /S /E root\\default            - Dumps everything in root\\default\n"
                  "  WBEMDUMP /S /E /M /M2 root\\default     - Dump all class & instance mofs\n"
                  "  WBEMDUMP root\\default foo              - Dumps all instances of the foo class\n"
                  "  WBEMDUMP root\\default foo.name=\\\"bar\\\" - Dumps one instance of the foo class\n"
                  "  WBEMDUMP /S2 /M root    - Dumps mofs for all non-system classes in all NS's\n"
                  "  WBEMDUMP /Q root\\default WQL \"SELECT * FROM Environment WHERE Name=\\\"Path\\\"\""
                  "\n";

   VariantInit(&vValue);

   // Process all the arguments.
   // ==========================
   if (pwcsGNamespace != NULL) { // Only applies to scripts
      iPlace = 1;
   } else {
      iPlace = 0;
   }

   // Set global flags depending on command line arguments
   for (iLoop = 1; iLoop < argc; ++iLoop) {
      if (_wcsicmp(argv[iLoop], L"/HELP") == 0 || _wcsicmp(argv[iLoop],L"-HELP") == 0 ||
         (wcscmp(argv[iLoop], L"/?") == 0) || (wcscmp(argv[iLoop], L"-?") == 0)) {
         fputs(szHelp, stdout);
         return(S_FALSE);
      } else if (_wcsicmp(argv[iLoop], L"/S") == 0 || _wcsicmp(argv[iLoop],L"-S") == 0) {
         bRecurseClass = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/S2") == 0 || _wcsicmp(argv[iLoop],L"-S2") == 0) {
         bRecurseClass = TRUE;
         bRecurseNS = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/Q") == 0 || _wcsicmp(argv[iLoop],L"-Q") == 0) {
         bDoQuery = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/E") == 0 || _wcsicmp(argv[iLoop],L"-E") == 0) {
         bShowSystem = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/E1") == 0 || _wcsicmp(argv[iLoop],L"-E1") == 0) {
         bShowSystem = TRUE;
         bShowSystem1 = TRUE;
         bShowInstance = FALSE;
      } else if (_wcsicmp(argv[iLoop], L"/E2") == 0 || _wcsicmp(argv[iLoop],L"-E2") == 0) {
         bShowSystem1 = FALSE;
         bShowInstance = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/D") == 0 || _wcsicmp(argv[iLoop],L"-D") == 0) {
         bShowProperties = FALSE;
      } else if (_wcsicmp(argv[iLoop], L"/G") == 0 || _wcsicmp(argv[iLoop],L"-G") == 0) {
         bCheckGet = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/G2") == 0 || _wcsicmp(argv[iLoop],L"-G2") == 0) {
         bCheckAssoc = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/M") == 0 || _wcsicmp(argv[iLoop],L"-M") == 0) {
         bClassMofs = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/M2") == 0 || _wcsicmp(argv[iLoop],L"-M2") == 0) {
         bInstanceMofs = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/M3") == 0 || _wcsicmp(argv[iLoop],L"-M3") == 0) {
         bMofTemplate = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/W") == 0 || _wcsicmp(argv[iLoop],L"-W") == 0) {
         bWarning = TRUE;
         bWarningContinue = FALSE;
      } else if (_wcsicmp(argv[iLoop], L"/WY") == 0 || _wcsicmp(argv[iLoop],L"-WY") == 0) {
         bWarningContinue = TRUE;
      } else if (_wcsicmp(argv[iLoop], L"/T") == 0 || _wcsicmp(argv[iLoop],L"-T") == 0) {
         bTime1 = TRUE;
      } else if (_wcsnicmp(argv[iLoop], L"/T2", 3) == 0 || _wcsnicmp(argv[iLoop],L"-T2", 3) == 0) {
         bTime2 = TRUE;
      } else if (_wcsnicmp(argv[iLoop], L"/G:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-G:", 3) == 0) {
         lGGFlags = _wtoi((argv[iLoop])+3);
      } else if (_wcsnicmp(argv[iLoop], L"/H:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-H:", 3) == 0) {
         if (pGContext == NULL) {
            sc = CoCreateInstance(CLSID_WbemContext, NULL, CLSCTX_INPROC_SERVER, IID_IWbemContext, (void **)&pGContext);
            if (S_OK != sc) {
               PrintErrorAndExit("Can't create context object", sc);
            }
         }
         pwcsName = (argv[iLoop])+3;
         pwcsValue = wcschr(pwcsName, L':');
         if (pwcsValue == NULL) {
            PrintErrorAndExit("Can't parse Context value");
         }
         *pwcsValue = L'\0';
         pwcsValue++;
         V_VT(&vValue) = VT_BSTR; V_BSTR(&vValue) = SysAllocString(pwcsValue);
         sc = pGContext->SetValue(CBString(pwcsName), 0L, &vValue);
         if (S_OK != sc) {
            PrintErrorAndExit("Failed to SetValue on context object");
         }
         VariantClear(&vValue);
      } else if (_wcsnicmp(argv[iLoop], L"/U:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-U:", 3) == 0) {
         pwcsGUserID = (argv[iLoop])+3;
      } else if (_wcsnicmp(argv[iLoop], L"/P:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-P:", 3) == 0) {
         pwcsGPassword = (argv[iLoop])+3;
        // Currently not implemented.
//      } else if (_wcsnicmp(argv[iLoop], L"/F:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-F:", 3) == 0) {
//         lGSFlags = _wtoi((argv[iLoop])+3);
      } else if (_wcsnicmp(argv[iLoop], L"/I:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-F:", 3) == 0) {
         lGImpFlag = _wtoi((argv[iLoop])+3);
      } else if (_wcsnicmp(argv[iLoop], L"/AL:", 4) == 0 || _wcsnicmp(argv[iLoop],L"-AL:", 4) == 0) {
         lGAuthFlag = _wtoi((argv[iLoop])+4);
      } else if (_wcsnicmp(argv[iLoop], L"/B:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-B:", 3) == 0) {
         lGEFlags = _wtoi((argv[iLoop])+3);
      } else if (_wcsnicmp(argv[iLoop], L"/Locale:", 8) == 0 || _wcsnicmp(argv[iLoop],L"-Locale:", 8) == 0) {
         pwcsGLocale = (argv[iLoop])+8;
      } else if (_wcsnicmp(argv[iLoop], L"/L:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-L:", 3) == 0) {
         dwGLoopCnt = _wtoi((argv[iLoop])+3);
      } else if (_wcsnicmp(argv[iLoop], L"/A:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-A:", 3) == 0) {
         pwcsGAuthority = (argv[iLoop])+3;
      } else if (_wcsnicmp(argv[iLoop], L"/O:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-O:", 3) == 0) {
         pwcsGNewLine = L"\r\n";
         // must convert to oem string since w95 doesn't support _wfopen
//         g_fOut = _wfopen(argv[iLoop], L"wb");
         g_fOut = fopen(cvt((argv[iLoop])+3, &z), "wb");
         free(z);
         if (g_fOut == NULL) {
            fprintf(stdout, "Can't open output file: %S (%d)\n", (argv[iLoop])+3, GetLastError());
            return(S_FALSE);
         }
         fputs(UNICODE_SIGNATURE, g_fOut);
      } else if (_wcsnicmp(argv[iLoop], L"/C:", 3) == 0 || _wcsnicmp(argv[iLoop],L"-C:", 3) == 0) {
         // must convert to oem string since w95 doesn't support _wfopen
         g_fCmdFile = fopen(cvt((argv[iLoop])+3, &z), "rb");
         free(z);
         if (g_fCmdFile == NULL) {
            fprintf(stdout, "Can't open command file: %S (%d)\n", (argv[iLoop])+3, GetLastError());
            return(S_FALSE);
         }

         // Now, let's see if we are dealing with a unicode file here
         z = (char *)malloc(2);
         fread(z, 2, 1, g_fCmdFile);

         if (memcmp(z, UNICODE_SIGNATURE, 2) != 0) {
            bUnicodeCmdFile = false;
            fseek(g_fCmdFile, 0, SEEK_SET);
         } else {
            bUnicodeCmdFile = true;
         }

         free(z);
      } else if (_wcsnicmp(argv[iLoop], L"/CQV:", 5) == 0 || _wcsnicmp(argv[iLoop],L"-CQV:", 5) == 0) {
         if (pbstrGQualifierName != NULL) {
           PrintErrorAndExit("Only 1 qualifer name can be filtered on");
         }
         pwcsName = (argv[iLoop])+5;
         pwcsValue = wcschr(pwcsName, L':');

         // all values
         if (pwcsValue == NULL) {
             pbstrGQualifierName = SysAllocString(pwcsName);
         }
         else
         {
             // Only specified value
             *pwcsValue = L'\0';
             pwcsValue++;
             pbstrGQualifierValue = SysAllocString(pwcsValue);
             pbstrGQualifierName = SysAllocString(pwcsName);
         }
      } else {
         switch (iPlace) {
         case 0:
            pwcsGNamespace = argv[iLoop];
            break;
         case 1:
            pwcsGObjectPath = argv[iLoop];
            break;
         case 2:
            pwcsQuery = argv[iLoop];
            break;
         default:
            break;
         }
         ++iPlace;
      }
   }

   // See if we got enough arguments.
   // ===============================

   if (((iPlace > 2) && !bDoQuery) || ((iPlace != 3) && bDoQuery)) {
      fputs(szHelp, stdout);
      return(S_FALSE);
   }

   if (!g_fOut) {
      g_fOut = stdout;
   }

   if (iPlace == 0) {
      pwcsGNamespace = L"root\\default";
   }

   // Finished.
   // =========

   return(S_OK);
}

//*****************************************************************************
// Function:   EscapeChars
// Purpose:    'Escapes' characters in a string by placing '\' in front of
//             the " and \ characters.
// Notes:      Caller must free returned buffer
//*****************************************************************************
WCHAR *EscapeChars(WCHAR *szInBuf)
{
   WCHAR *szOutBuf;
   int x;

   // Adding escape characters can't do more than double the string size
   szOutBuf = (WCHAR *)malloc(((wcslen(szInBuf) + 1) * sizeof(WCHAR)) * 2);
   x = 0;

   while (*szInBuf != 0) {
      if ((*szInBuf == L'\\') && (*(szInBuf + 1) == L'\"')) {
         szOutBuf[x++] = '\\';
      } else if (*szInBuf == L'"') {
         szOutBuf[x++] = '\\';
      }
      szOutBuf[x++] = *(szInBuf ++);
   }
   szOutBuf[x] = L'\0';

   return szOutBuf;
}

//*****************************************************************************
// Function:   MyValueToString
// Purpose:    A callback routine from utillib.  It is designed to handle any
//             variant types that ValueToString doesn't.  Specifically it
//             handles embedded objects.
//*****************************************************************************
WCHAR *MyValueToString(VARIANT *pv)
{
   WCHAR *buf, *vbuf;

   switch (V_VT(pv)) {
      case VT_UNKNOWN: { // Currently only used for embedded objects
         extern int iIndent;
         iIndent++;
         buf = EnumProperties((IWbemClassObject *)pv->punkVal);  // May result in recursion
         iIndent--;
         break;
      }

      case VT_UNKNOWN | VT_ARRAY: {

         iIndent++;              // Increase indention level

         SAFEARRAY *pVec = pv->parray;
         long iLBound, iUBound;

         SafeArrayGetLBound(pVec, 1, &iLBound);
         SafeArrayGetUBound(pVec, 1, &iUBound);
         if ((iUBound - iLBound + 1) == 0) {
            buf = (WCHAR *)calloc(1, BLOCKSIZE);
            for (int x=0; x<iIndent; x++) {
               buf[x] = L'\t';
            }
            wcscat(buf, L"<empty array>");
            wcscat(buf, pwcsGNewLine);
            iIndent--;              // Decrease indention level
            break;
         }

         //buf = (WCHAR *)calloc(1, sizeof(WCHAR));
		 buf = (WCHAR *)calloc(BLOCKSIZE, sizeof(WCHAR));

         for (long i = iLBound; i <= iUBound; i++) {
            IUnknown __RPC_FAR *__RPC_FAR v;
            SafeArrayGetElement(pVec, &i, &v);

			VARIANT varString;
			IWbemClassObject* pCO = (IWbemClassObject *)v;
			MyString clMyBuff;
					
			HRESULT sc = pCO->Get(CBString(CLASSPROP), 0L, &varString, NULL, NULL);
			if (S_OK != sc) {
			 PrintErrorAndExit("Couldn't get class property in enumproperties", sc);  //Exits program
			}

			//clMyBuff += pwcsGNewLine;
			for (int x=0; x<iIndent; x++) {
			clMyBuff += L"\t";
			}
			clMyBuff += L"instance of ";
			clMyBuff += V_BSTR(&varString);
			clMyBuff += L" {";
			clMyBuff += pwcsGNewLine;
			iIndent++;

			VariantClear(&varString);

			vbuf = clMyBuff.GetCloneString();

			// Copy into buffer
			buf = (WCHAR *)realloc(buf, (wcslen(buf) + wcslen(vbuf) + 1) * sizeof(WCHAR));
            wcscat(buf, vbuf);

 
            vbuf = EnumProperties((IWbemClassObject *)v);
			
			// Copy into buffer
            buf = (WCHAR *)realloc(buf, (wcslen(buf) + wcslen(vbuf) + 1) * sizeof(WCHAR));
            wcscat(buf, vbuf);

			// Add }
			MyString clMyBuff2;

			for (x=0; x<iIndent-1; x++) {
			clMyBuff2 += L"\t";
			}
			clMyBuff2 += L" }";
			clMyBuff2 += pwcsGNewLine;
			vbuf = clMyBuff2.GetCloneString();

			// Copy into buffer
            buf = (WCHAR *)realloc(buf, (wcslen(buf) + wcslen(vbuf) + 1) * sizeof(WCHAR));
            wcscat(buf, vbuf);

			iIndent--;

            free(vbuf);
            v->Release();
         }

         iIndent--;              // Decrease indention level
         break;
      }

      default:
         buf = (WCHAR *)malloc(BLOCKSIZE);
         wcscpy(buf, L"<conversion error>");
   }
   return buf;

}

//*****************************************************************************
// Function:   ShowInstanceHeader
// Purpose:    Prints the header at the top of each instance, unless we are
//             printing instance mofs
//*****************************************************************************
void ShowInstanceHeader(WCHAR *pwcsClassName)
{
   if ((!bInstanceMofs) && (!bShowInstance)) {
      DoIndent(); // Indent
      FWPRINTF(g_fOut, L"%wS%wS", pwcsClassName, pwcsGNewLine); //Print class name
   }

}

//*****************************************************************************
// Function:   ResetGlobalFlags
// Purpose:    Resets the global flags to their default values.  This is
//             called in between command lines in a command file.
//*****************************************************************************
void ResetGlobalFlags()
{
   bShowSystem = FALSE;     
   bShowSystem1 = FALSE;    
   bShowInstance = FALSE;   
   bShowProperties = TRUE;  
   bRecurseClass = FALSE;        
   bRecurseNS = FALSE;        
   bCheckGet = FALSE;
   bCheckAssoc = FALSE;
   bDoQuery = FALSE;        
   bClassMofs = FALSE;      
   bInstanceMofs = FALSE;   

   iIndent = 0;              // Current indention level
   lGGFlags = 0;

   pwcsGObjectPath = NULL;  // ObjectPath to show
   pwcsQuery = NULL;      // Query (for /q commands)

}

//*****************************************************************************
// Function:   ParseCommandLine
// Purpose:    Reads the command line from a file and sends it to the parsing
//             routine.
//*****************************************************************************
bool ParseCommandLine(int *numargs, wchar_t **argv)
{
   WCHAR wszLine[4096];
   char szLine[4096];
   int numchars;
   WCHAR *p;

   // The parsing routine expects to find a program name as the first arg, so
   // give it one
   wcscpy(wszLine, L"xx ");

   // If this is a unicode command file, read a wcs
   if (bUnicodeCmdFile) {
      if (!fgetws(wszLine + 3, sizeof(wszLine)/sizeof(WCHAR), g_fCmdFile)) {
         return false;
      }
   } else { // else convert to wcs
      szLine[0] = '\0';
      // If no more command lines
      if (!fgets(szLine, sizeof(wszLine), g_fCmdFile)) {
         return false;
      }
      swprintf(wszLine + 3, L"%S", szLine);
   }
   
   // Trim trailing cr, lf, space, and eof markers
   p = &wszLine[wcslen(wszLine)-1];
   while ((*p == L'\n') || (*p == L'\r') || (*p == L' ') || (*p == L'\x1a')) {
      *p = L'\0';
      p = &wszLine[wcslen(wszLine)-1];
   }

   // If we read a blank line
   if (wcscmp(wszLine, L"xx") == 0) {
      return false;
   }

   /* first find out how much space is needed to store args */
   wparse_cmdline(wszLine, NULL, NULL, numargs, &numchars);

   /* allocate space for argv[] vector and strings */
   p = (WCHAR *)malloc(*numargs * sizeof(WCHAR *) + numchars * sizeof(WCHAR));

   /* store args and argv ptrs in just allocated block */
   wparse_cmdline(wszLine, (wchar_t **)p, (wchar_t *)(((char *)p) + *numargs * sizeof(wchar_t *)), numargs, &numchars);

   *argv = p;
   (*numargs)--;

   return true;

}

/***
*static void parse_cmdline(cmdstart, argv, args, numargs, numchars)
*
*Purpose:
*       Parses the command line and sets up the argv[] array.
*       On entry, cmdstart should point to the command line,
*       argv should point to memory for the argv array, args
*       points to memory to place the text of the arguments.
*       If these are NULL, then no storing (only coujting)
*       is done.  On exit, *numargs has the number of
*       arguments (plus one for a final NULL argument),
*       and *numchars has the number of bytes used in the buffer
*       pointed to by args.
*
*Entry:
*       _TSCHAR *cmdstart - pointer to command line of the form
*           <progname><nul><args><nul>
*       _TSCHAR **argv - where to build argv array; NULL means don't
*                       build array
*       _TSCHAR *args - where to place argument text; NULL means don't
*                       store text
*
*Exit:
*       no return value
*       int *numargs - returns number of argv entries created
*       int *numchars - number of characters used in args buffer
*
*Exceptions:
*
*******************************************************************************/

#define DQUOTECHAR L'\"'
#define NULCHAR    L'\0'
#define SPACECHAR  L' '
#define TABCHAR    L'\t'
#define SLASHCHAR  L'\\'
static void __cdecl wparse_cmdline (
    WCHAR *cmdstart,
    WCHAR **argv,
    WCHAR *args,
    int *numargs,
    int *numchars
    )
{
        WCHAR *p;
        WCHAR c;
        int inquote;                /* 1 = inside quotes */
        int copychar;               /* 1 = copy char to *args */
        unsigned numslash;                  /* num of backslashes seen */

        *numchars = 0;
        *numargs = 1;       /* the program name at least */

        /* first scan the program name, copy it, and count the bytes */
        p = cmdstart;
        if (argv)
            *argv++ = args;

        /* A quoted program name is handled here. The handling is much
           simpler than for other arguments. Basically, whatever lies
           between the leading double-quote and next one, or a terminal null
           character is simply accepted. Fancier handling is not required
           because the program name must be a legal NTFS/HPFS file name.
           Note that the double-quote characters are not copied, nor do they
           contribute to numchars. */
        if ( *p == DQUOTECHAR ) {
            /* scan from just past the first double-quote through the next
               double-quote, or up to a null, whichever comes first */
            while ( (*(++p) != DQUOTECHAR) && (*p != NULCHAR) ) {

                ++*numchars;
                if ( args )
                    *args++ = *p;
            }
            /* append the terminating null */
            ++*numchars;
            if ( args )
                *args++ = NULCHAR;

            /* if we stopped on a double-quote (usual case), skip over it */
            if ( *p == DQUOTECHAR )
                p++;
        }
        else {
            /* Not a quoted program name */
            do {
                ++*numchars;
                if (args)
                    *args++ = *p;

                c = (WCHAR) *p++;

            } while ( c != SPACECHAR && c != NULCHAR && c != TABCHAR );

            if ( c == NULCHAR ) {
                p--;
            } else {
                if (args)
                    *(args-1) = NULCHAR;
            }
        }

        inquote = 0;

        /* loop on each argument */
        for(;;) {

            if ( *p ) {
                while (*p == SPACECHAR || *p == TABCHAR)
                    ++p;
            }

            if (*p == NULCHAR)
                break;              /* end of args */

            /* scan an argument */
            if (argv)
                *argv++ = args;     /* store ptr to arg */
            ++*numargs;

        /* loop through scanning one argument */
        for (;;) {
            copychar = 1;
            /* Rules: 2N backslashes + " ==> N backslashes and begin/end quote
               2N+1 backslashes + " ==> N backslashes + literal "
               N backslashes ==> N backslashes */
            numslash = 0;
            while (*p == SLASHCHAR) {
                /* count number of backslashes for use below */
                ++p;
                ++numslash;
            }
            if (*p == DQUOTECHAR) {
                /* if 2N backslashes before, start/end quote, otherwise
                    copy literally */
                if (numslash % 2 == 0) {
                    if (inquote) {
                        if (p[1] == DQUOTECHAR)
                            p++;    /* Double quote inside quoted string */
                        else        /* skip first quote char and copy second */
                            copychar = 0;
                    } else
                        copychar = 0;       /* don't copy quote */

                    inquote = !inquote;
                }
                numslash /= 2;          /* divide numslash by two */
            }

            /* copy slashes */
            while (numslash--) {
                if (args)
                    *args++ = SLASHCHAR;
                ++*numchars;
            }

            /* if at end of arg, break loop */
            if (*p == NULCHAR || (!inquote && (*p == SPACECHAR || *p == TABCHAR)))
                break;

            /* copy character into argument */
            if (copychar) {
                if (args)
                    *args++ = *p;
                ++*numchars;
            }
            ++p;
            }

            /* null-terminate the argument */

            if (args)
                *args++ = NULCHAR;          /* terminate string */
            ++*numchars;
        }

        /* We put one last argument in -- a null ptr */
        if (argv)
            *argv++ = NULL;
        ++*numargs;
}

//*****************************************************************************
// Function:   CheckQualifiers
// Purpose:    Checks to see if we are filtering on class qualifiers.  If
//             so, checks to see if the specified qualifier/value is present.
//*****************************************************************************
BOOL CheckQualifiers(IWbemClassObject *pIWbemClassObject)
{
    // If we are not filtering on qualifiers
    if (pbstrGQualifierName == NULL)
    {
        return TRUE;
    }

    BOOL bRet = TRUE;
    VARIANT vValue;

    VariantInit(&vValue);

    IWbemQualifierSet *pQualSet = NULL;
    HRESULT hr = pIWbemClassObject->GetQualifierSet(&pQualSet);

    // This should always work
    if (FAILED(hr))
        PrintErrorAndExit("Failed to get class qualifier set", hr); // exits program

    // However, this might reasonably fail
    hr = pQualSet->Get(pbstrGQualifierName, 0L, &vValue, NULL);
    if (SUCCEEDED(hr))
    {
        // Ok, the qualifier is there.  Did they request a specific value?
        if (pbstrGQualifierValue == NULL)
        {
            bRet = TRUE;
        }
        else
        {
            // Check to see if the value match
            if (VariantChangeType(&vValue, &vValue, 0, VT_BSTR) == S_OK)
                bRet = _wcsicmp(V_BSTR(&vValue), pbstrGQualifierValue) == 0;
        }
    }
    else
    {
        // We failed to Get the qualifier.  Was it because the thing just wasn't there?
        if (hr == WBEM_E_NOT_FOUND)
        {
            bRet = FALSE;
        }
        else
        {
            // Some other error
            PrintErrorAndExit("Failed to Get class qualifier value", hr); // exits program
        }
    }

    return bRet;

}

//*****************************************************************************
// Function:   CheckAssocEndPoints
// Purpose:    Checks to see if the references pointed to by the reference
//             properties of this class really exist.
//*****************************************************************************
void CheckAssocEndPoints(IWbemServices *pIWbemServices, IWbemClassObject *pIWbemClassObject)
{
    HRESULT hr;
    
    if (FAILED(hr = pIWbemClassObject->BeginEnumeration(WBEM_FLAG_REFS_ONLY)))
    {
        PrintErrorAndExit("Failed to get Refs Enumeration", hr); // exits program
    }
    
    BSTR bstrPropertyName = NULL;
    VARIANT vVal;
    
    VariantInit(&vVal);
    
    while (SUCCEEDED(hr = pIWbemClassObject->Next(0, &bstrPropertyName, &vVal, NULL, NULL)) && 
           (hr != WBEM_S_NO_MORE_DATA) )
    {
        if ( (V_VT(&vVal) == VT_BSTR) && (V_BSTR(&vVal) != NULL) )
        {
            if (FAILED(hr = pIWbemServices->GetObject(V_BSTR(&vVal), 0, NULL, NULL, NULL)))
            {
                char szBuff[_MAX_PATH];
                
                sprintf(szBuff, "Could not get endpoint for property %S", bstrPropertyName);
                
                if (bWarningContinue) 
                {
                    PrintError(szBuff, hr);
                } 
                else if (bWarning) 
                {
                    PrintErrorAndAsk(szBuff, hr);  // might exit program
                } 
                else 
                {
                    PrintErrorAndExit(szBuff, hr);  // might exit program
                }
            }
        }

        SysFreeString(bstrPropertyName);
        VariantClear(&vVal);
    }
}
