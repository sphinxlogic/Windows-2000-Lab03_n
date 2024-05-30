/******************************************************************************
*  
*  File: SymbolTable.h
*
*  Author:  Joel Alley
*
*  Date: August 7, 1998
*
*  Description:   This file contains the declaration of classes used in the
*                 implementation of a stacked symbol table which handles
*                 scope resolution of variables declared and referenced in a
*                 script.
*
*  Modifications: 10/31/98-- added Name property and new Constructor to 
*                         CSymbolTable to allow for property browsing of full 
*                         symbol stack.
*                 11/11/98-- added a GetSymbols method to CSymbolTable to allow
*                            property browsing.
******************************************************************************/
class CSymbol
{
protected:
   LPCOLESTR m_pName;
   DWORD m_dwFlags;
   VARIANT* m_pValue;

public:
   //Constructors
   CSymbol();
   CSymbol( LPCOLESTR name, DWORD flags );
   CSymbol( LPCOLESTR name, DWORD flags, VARIANT* pVariant );

   //Destructor
   virtual ~CSymbol();

   LPCOLESTR Name() {return m_pName; }
   DWORD Flags() {return m_dwFlags; }
   VARIANT* Value() {return m_pValue; }
};

class CSymbolTable
{
protected:
   TList<CSymbol*> m_SymbolList;
   int m_nextSymbolCount;
   LPCOLESTR m_pName;

public:
   //Constructor
   CSymbolTable();
   CSymbolTable( LPCOLESTR name );
   //Destructor
   virtual ~CSymbolTable();

   LPCOLESTR Name() { return m_pName; }
   virtual BOOL FindSymbol( LPCOLESTR symbolName, CSymbol** pp_theSymbol );
   virtual void AddSymbol( CSymbol* p_theSymbol );

   //Provided so we can browse the symbols later.
   TList<CSymbol*>* GetSymbols() { return &m_SymbolList; }
};
