/******************************************************************************
*
*  File: CInterpreter.h
*
*  Author:  Joel Alley
*
*  Date: October 4, 1998
*
*  Description:   This file contains the declaration of a simple byte-code
*                 interpreter.  It maintains a stacked symbol table for data,
*                 and an instruction list for execution.
*
*  Modifications:
******************************************************************************/

class CInterpreter : public DebugResume{
protected:
   CStackedSymbolTable* m_pSymbolTable;
   TList<CInstruction*> m_InstructionList;
   TStack<ScriptVariant*> m_DataStack;
   TStack<LPCOLESTR> m_LabelStack;
   IDispatch* m_pOleDispatch;
   BOOL m_bCallCompleted;
   BOOL m_bMainCompleted;
   BOOL m_bOwnsSymbolTable;

public:
   //Constructor
   CInterpreter();
   //Destructor
   ~CInterpreter();

   virtual void ParseText( LPCOLESTR scriptText, ULONG startingLineNumber, 
      DWORD dwSourceContext );

   virtual HRESULT PutValue( LPCOLESTR variable, ScriptVariant* pValue );
   virtual HRESULT GetValue( LPCOLESTR variable, ScriptVariant** ppValue );
   virtual HRESULT Call( LPCOLESTR method, ScriptVariant* pRetValue );

   STDMETHODIMP EvaluateImmediate();
   virtual STDMETHODIMP EvaluateCall();
   virtual STDMETHODIMP EvalInstruction();
   virtual void Initialize( LPCOLESTR name = L"" );

   void OutputPCode( LPCOLESTR fileName );

protected:
   void Assert( ScriptVariant* pVariant, ScriptVariant* pMessage );
   void Alert( ScriptVariant* pVariant );
};
