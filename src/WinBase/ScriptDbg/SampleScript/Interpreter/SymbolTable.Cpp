/******************************************************************************
*  
*  File: SymbolTable.cpp
*
*  Author:  Joel Alley
*
*  Date: August 11, 1998
*
*  Description:   This file contains the definition of classes used in the
*                 implementation of a stacked symbol table which handles
*                 scope resolution of variables declared and referenced in a
*                 script.
*
*  Modifications:
******************************************************************************/
#define SYMBOLTABLE
#include "depends.h"

CSymbol::CSymbol()
{
   //tracing purposes only
   CSYMBOLTRACE("CSymbol\n");

   m_pName = L"";
   m_dwFlags = 0;
   m_pValue = new VARIANT;
   VariantInit( m_pValue );
}

CSymbol::CSymbol( LPCOLESTR name, DWORD flags )
{
   //tracing purposes only
   CSYMBOLTRACE("CSymbol\n");

   m_pName = name;
   m_dwFlags = flags;
   m_pValue = new VARIANT;
   VariantInit( m_pValue );
}

CSymbol::CSymbol( LPCOLESTR name, DWORD flags, VARIANT* pVariant )
{
   //tracing purposes only
   CSYMBOLTRACE("CSymbol\n");

   m_pName = name;
   m_dwFlags = flags;
   m_pValue = new VARIANT;
   VariantInit( m_pValue );
   VariantCopy( m_pValue, pVariant );
}

//Destructor
CSymbol::~CSymbol()
{
   //tracing purposes only
   CSYMBOLTRACE("~CSymbol\n");

   if (m_pValue != NULL){
      VariantClear( m_pValue );
      delete m_pValue;
   }
}

/******************************************************************************
*  CSymbolTable -- This class manages the list of symbols associated with this
*  scope.  It provides methods for adding and finding symbols in the table.
******************************************************************************/
//Constructor
CSymbolTable::CSymbolTable() 
{
   //tracing purposes only
   CSYMBOLTABLETRACE("CSymbolTable\n");

   m_nextSymbolCount = 0;
   m_pName = L"\0";
}

CSymbolTable::CSymbolTable(LPCOLESTR name )
{
   //tracing purposes only
   CSYMBOLTABLETRACE("CSymbolTable\n");

   m_nextSymbolCount = 0;
   m_pName = name;
}

//Destructor
CSymbolTable::~CSymbolTable() 
{
   //tracing purposes only
   CSYMBOLTABLETRACE("~CSymbolTable\n");

   //delete all the symbols that have been added to this table
   CSymbol* pSymbol = NULL;
   FOREACH( m_SymbolList, 
      pSymbol = m_SymbolList.Retrieve();
      delete pSymbol;
      );
}

/******************************************************************************
*  FindSymbol -- Using the name of the symbol, this method searches the symbol 
*  table.
*  Parameters: symbolName -- LPCOLESTR which contains the name of the desired
*                            symbol.
*              pp_theSymbol -- CSymbol** which receives the address of the
*                              CSymbol, or NULL if no symbol is found.
*  Returns: true if the symbol is found.
*           false otherwise.
******************************************************************************/
BOOL CSymbolTable::FindSymbol( LPCOLESTR symbolName, CSymbol** pp_theSymbol ) 
{
   //tracing purposes only
   CSYMBOLTABLETRACE("CSymbolTable::FindSymbol\n");

   if (m_SymbolList.FindByName( symbolName )){
      *pp_theSymbol = m_SymbolList.Retrieve();
      return true;
   }
   else
      return false;
}

/******************************************************************************
*  AddSymbol -- This method adds a CSymbol* to the symbol table.
*  Parameters: p_theSymbol -- address of the CSymbol to be added to the symbol
*                             table.
*  Returns:
******************************************************************************/
void CSymbolTable::AddSymbol( CSymbol* p_theSymbol ) 
{
   //tracing purposes only
   CSYMBOLTABLETRACE("CSymbolTable::AddSymbol\n");

   m_SymbolList.InsertAfter( p_theSymbol, p_theSymbol->Name() );
}

