/******************************************************************************
*
*  File: depends.h
*
*  Author:  Joel Alley
*
*  Date: October 4, 1998
*
*  Description:   This file centralizes the #include directives of the various
*                 source files of this project so they're easier to maintain.
*                 It uses conditional compilation to select which headers to
*                 #include with each source file.
*
*  Modifications:
******************************************************************************/

/******************************************************************************
*  Dependencies -- These #define statements control dependencies between 
*  various files in the project.
******************************************************************************/
#ifdef CINTERPRETER
#define SCRIPTVARIANT
#define STACKEDSYMBOLTABLE
#define CPARSER
#define CINSTRUCTION
#define LIST
#define STACK
#define ERRORHANDLER
#define DEBUGRESUME
#endif

#ifdef STACKEDSYMBOLTABLE
#define STACK
#define SYMBOLTABLE
#endif

#ifdef SYMBOLTABLE
#define LIST
#endif

#ifdef CPARSER
#define CLEXER
#define CINSTRUCTION
#define LIST
#define STACK
#define ERRORHANDLER
#endif

//We have to be REALLY careful about dependencies here.
#ifdef CINSTRUCTION
#define CLEXER
#endif

#ifdef CLEXER
#define ERRORHANDLER
#endif

#ifdef ERRORHANDLER
#define CLEXER
#define CINSTRUCTION
#define DEBUGRESUME
#endif

#ifdef STACK
#define LIST
#endif

#ifdef LIST
#endif

#ifdef SCRIPTVARIANT
#endif

/******************************************************************************
*  #includes -- These #include statements include the files in order such that
*  each files dependencies have been included before they're required.
******************************************************************************/
#include "InterpreterTrace.h"
#include "activscp.h"

#ifdef SCRIPTVARIANT
#include "ScriptVariant.h"
#endif

#ifdef LIST
#include "TList.h"
#endif

#ifdef STACK
#include "TStack.h"
#endif

#ifdef CLEXER
#include "CLexer.h"
#endif

#ifdef CINSTRUCTION
#include "CInstruction.h"
#endif

#ifdef DEBUGRESUME
#include "DebugResume.h"
#endif

#ifdef ERRORHANDLER
#include "ErrorHandler.h"
#endif

#ifdef CPARSER
#include "CProductions.h"
#include "CParserSet.h"
#include "CParser.h"
#include "stdio.h"
#endif

#ifdef SYMBOLTABLE
#include "SymbolTable.h"
#endif

#ifdef STACKEDSYMBOLTABLE
#include "StackedSymbolTable.h"
#endif

#ifdef CINTERPRETER
#include "CInterpreter.h"
#endif