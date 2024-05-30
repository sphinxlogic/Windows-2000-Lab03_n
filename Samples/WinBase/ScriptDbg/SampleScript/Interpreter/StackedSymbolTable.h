/******************************************************************************
*
*  File: StackedSymbolTable.h
*
*  Author:  Joel Alley
*
*  Date: November 3, 1998
*
*  Description:   This file contains the declarations of the 
*                 CStackedSymbolTable class, which maintains a stack of 
*                 CSymbolTables for scoping purposes.
*
*  Modifications:
******************************************************************************/

class CStackedSymbolTable
{
protected:
   TStack<CSymbolTable*>* m_pSymbolTableStack;
   LPCOLESTR m_Name;

public:
   //Constructor
   CStackedSymbolTable( ){;}
   //Destructor
   virtual ~CStackedSymbolTable(){ PopScope(); }

   void Initialize( LPCOLESTR name );
   LPCOLESTR Name() { return m_Name; }

   void PushScope( LPCOLESTR scopeName = NULL );
   CSymbolTable* TopScope();
   void PopScope();
   BOOL FindSymbol( LPCOLESTR symbolName, CSymbol** pp_theSymbol );
   void AddSymbol( CSymbol* p_theSymbol );
};
