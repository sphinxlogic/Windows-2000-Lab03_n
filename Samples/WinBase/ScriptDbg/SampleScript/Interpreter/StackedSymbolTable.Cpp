/******************************************************************************
*
*  File: StackedSymbolTable.cpp
*
*  Author:  Joel Alley
*
*  Date: November 3, 1998
*
*  Description:   This file contains the definition of the 
*                 CStackedSymbolTable class, which maintains a stack of 
*                 CSymbolTables for scoping purposes.
*
*  Modifications: 
******************************************************************************/
#define STACKEDSYMBOLTABLE
#include "depends.h"

/******************************************************************************
*  CStackedSymbolTable -- This class handles the scoping issues related to 
*  the symbol table, allowing correct resolution of variable references.
******************************************************************************/

/******************************************************************************
*  Initialize -- This method intializes the stacked symbol table with its name
*  and creates a new stack for the symbol tables.
******************************************************************************/
void CStackedSymbolTable::Initialize( LPCOLESTR name )
{
   //tracing purposes only
   CSTACKEDSYMBOLTABLETRACE("CStackedSymbolTable::Initialize\n");

   if (name == NULL)
      m_Name = L"";

   //Create a new stack for the symbol tables.
   m_pSymbolTableStack = new TStack< CSymbolTable* >();
   PushScope( L"Global" );
}

/******************************************************************************
*  PushScope -- This method creates a new symbol table and pushes it onto the
*  symbol table stack.  The top symbol table on the stack represents the
*  innermost symbol scope.
******************************************************************************/
void CStackedSymbolTable::PushScope( LPCOLESTR scopeName ) 
{
   //tracing purposes only
   CSTACKEDSYMBOLTABLETRACE("CStackedSymbolTable::PushScope\n");

   CSymbolTable* newSymbolTable = NULL;

   //We have to have a name for this scope, so if we got NULL, then use L""
   if (scopeName == NULL)
      newSymbolTable = new CSymbolTable( L"" );
   else
      newSymbolTable = new CSymbolTable( scopeName );

   //Add the new symboltable to the stack
   m_pSymbolTableStack->Push( newSymbolTable );
}

/******************************************************************************
*  TopScope -- This method retrieves the topmost symbol table from the symbol
*  table stack, and passes it back to the caller without removing it.
******************************************************************************/
CSymbolTable* CStackedSymbolTable::TopScope()
{
   //tracing purposes only
   CSTACKEDSYMBOLTABLETRACE("CStackedSymbolTable::TopScope\n");

   return (CSymbolTable*)m_pSymbolTableStack->Top();
}

/******************************************************************************
*  PopScope -- This method pops the topmost symbol table off the stack, 
*  destroying it in the process.  Any symbols in this table have gone out of
*  scope and should not be found in a symbol search.
******************************************************************************/
void CStackedSymbolTable::PopScope() 
{
   //tracing purposes only
   CSTACKEDSYMBOLTABLETRACE("CStackedSymbolTable::PopScope\n");

   CSymbolTable* pSymbolTable = (CSymbolTable*)m_pSymbolTableStack->Top();
   m_pSymbolTableStack->Pop();
   delete pSymbolTable;
}

/******************************************************************************
*  FindSymbol -- This method searches the symbol table for the symbol
*  we're looking for.
*  Parameters: symbolName -- LPCOLESTR which contains the name of the desired
*                            symbol.
*              pp_theSymbol -- CSymbol** which receives the address of the
*                              CSymbol, or NULL if no symbol is found.
*  Returns: true if the symbol is found.
*           false otherwise.
******************************************************************************/
BOOL CStackedSymbolTable::FindSymbol( LPCOLESTR symbolName, 
                                     CSymbol** pp_theSymbol )
{
   //tracing purposes only
   CSTACKEDSYMBOLTABLETRACE("CStackedSymbolTable::FindSymbol\n");

   CSymbolTable* currentSymbolTable = NULL;
   BOOL bFound = false;
   PFOREACH( m_pSymbolTableStack, 
      currentSymbolTable = (CSymbolTable*)m_pSymbolTableStack->Retrieve();
      bFound = currentSymbolTable->FindSymbol( symbolName, pp_theSymbol );

      if (bFound)
         break;
   );
   
   //Restore the stack so push and pop work correctly.
   m_pSymbolTableStack->Reset();
   return bFound;
}

/******************************************************************************
*  AddSymbol -- This method adds a CSymbol* to the topmost symbol table on the
*  stack.
*  Parameters: p_theSymbol -- address of the CSymbol to be added to the symbol
*                             table.
*  Returns:
******************************************************************************/
void CStackedSymbolTable::AddSymbol( CSymbol* p_theSymbol ) 
{
   //tracing purposes only
   CSTACKEDSYMBOLTABLETRACE("CStackedSymbolTable::AddSymbol\n");

   CSymbolTable* topSymbolTable = NULL;
   topSymbolTable = (CSymbolTable*)m_pSymbolTableStack->Top();
   topSymbolTable->AddSymbol( p_theSymbol );
}