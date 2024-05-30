/******************************************************************************
*
*  File: ErrorHandler.cpp
*
*  Author:  Joel Alley
*
*  Date: November 14, 1998
*
*  Description:   This file contains the definition of the error handling
*                 functions and classes for the sample script engine.
*
*  Modifications:
******************************************************************************/
#define ERRORHANDLER
#include "depends.h"
#include "stdio.h"

//the HINSTANCE of the resource-only dll that contains the localized error 
//messages.
HINSTANCE CErrorHandler::m_ResourceHInst = NULL;

//Set up function pointers to the error handling methods inside CErrorHandler.
//This allows new functionality to be added to error handling, without having
//to change the calls, which are mostly in the core Interpreter.
CompileErrorHandler HandleCompileError = &CErrorHandler::HandleCompileError;
RuntimeErrorHandler HandleRuntimeError = &CErrorHandler::HandleRuntimeError;

//constructor
CErrorHandler::CErrorHandler() 
{}

//destructor
CErrorHandler::~CErrorHandler() {;}

/******************************************************************************
*  Initialize -- This method initializes the CErrorHandler with the information
*  it needs to respond to IActiveScriptError method calls.
*  Parameters: pToken -- The token on which the error occurred, if available
*              errorVal -- The enumerated value indicating what error occurred.
*  Returns: none
******************************************************************************
void CErrorHandler::Initialize( CToken* pToken, ERRORVAL errorVal )
{
   //tracing purposes only
   CERRORHANDLERTRACE("CErrorHandler::Initialize\n");

   m_pErrorToken = pToken;
   m_ErrorVal = errorVal;
}

/******************************************************************************
*  HandleCompileError -- This method handles reporting compile errors.
*  Parameters: pToken -- The token where the compile error occurred.
*
*              errorVal -- The enumerated error value that occurred, indicating
*                          which string to display.
*  Returns: none
******************************************************************************/
void CErrorHandler::HandleCompileError( CToken* pToken, ERRORVAL errorVal )
{
   //tracing purposes only
   CERRORHANDLERTRACE("CErrorHandler::HandleCompileError\n");

   //At this level, we just put up a message box that contains the error info.
   static char buffer1[256];
   memset( buffer1, 0, 256 );
   static char buffer2[256];
   memset( buffer2, 0, 256 );

   //Load the description string into buffer1
   LoadString( m_ResourceHInst, (errorVal + 1), buffer1, 256 );

   //Write the source information into buffer2
   TEXTPOS thePos = pToken->Position();
   sprintf( buffer2, "\nSource: %S\nRow: %d\nColumn:%d\n", pToken->Source(), 
      thePos.row, thePos.col );

   //Concatenate the two buffers together
   strcat( buffer1, buffer2 );

   //Put up a message box
   MessageBox( NULL, buffer1, "Sample Script", MB_SETFOREGROUND );
}

/******************************************************************************
*  HandleRuntimeError -- This method handles reporting run-time errors
*  Parameters: pInstruction -- The instruction where the run-time error 
*                              occurred.
*              errorVal -- The enumerated error value that occurred, indicating
*                          which string to display.
*              pInterpreter -- The interpreter in which the runtime error 
*                              occurred.
*  Returns: none
******************************************************************************/
void CErrorHandler::HandleRuntimeError( CInstruction* pInstruction, 
                                       ERRORVAL errorVal, 
                                       DebugResume* pInterpreter )
{
   //tracing purposes only
   CERRORHANDLERTRACE("CErrorHandler::HandleRuntimeError\n");

}

/******************************************************************************
*  SetLocale -- This method sets, or resets, the locale used for displaying
*  error messages.  This method must be called once before any errors are 
*  reported.
*  Parameters:
*  Returns: none
******************************************************************************/
void CErrorHandler::SetLocale( LCID newLCID )
{
   //tracing purposes only
   CERRORHANDLERTRACE("CErrorHandler::SetLocale\n");

   //Make sure that any previous resource dlls are freed.
   if (m_ResourceHInst != NULL)
      FreeLibrary( m_ResourceHInst );

   //look up server's file name.  This will give us the path to the directory
   //where SampleScript.dll is installed.
   char szLangPath[255];
   HMODULE dllModule = GetModuleHandle("SampleScript.dll");
   GetModuleFileName(dllModule, szLangPath, 255);
   
   //Remove the Dll name
   *(szLangPath + strlen(szLangPath) - 16) = 0;
   
   //Load the appropriate resouce library for the requested locale.  If the 
   //requested locale isn't available, default to English.
   switch( newLCID ){
   case 0x0409:
      strcat( szLangPath, "English.dll" );
      break;
/*   case 0x0407:
      strcat( szLangPath, "German.dll" );
      break;
*/   default:
      strcat( szLangPath, "English.dll" );
   }

   m_ResourceHInst = LoadLibrary( szLangPath );

   if (m_ResourceHInst == NULL){
      DWORD error = GetLastError();
   }
}