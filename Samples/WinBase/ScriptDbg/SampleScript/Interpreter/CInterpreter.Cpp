/******************************************************************************
*
*  File: CInterpreter.cpp
*
*  Author:  Joel Alley
*
*  Date: October 4, 1998
*
*  Description:   This file contains the definition of a simple byte-code
*                 interpreter.  It maintains a stacked symbol table for data,
*                 and an instruction list for execution.
*
*  Modifications:
******************************************************************************/
#define CINTERPRETER
#include "depends.h"
#include <iostream.h>
#include <fstream.h>

//Constructor
CInterpreter::CInterpreter()
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter\n");
   
   m_pSymbolTable = NULL;
   m_pOleDispatch = NULL;
   m_bCallCompleted = false;
   m_bMainCompleted = false;
   m_bOwnsSymbolTable = true;
}

//Destructor
CInterpreter::~CInterpreter()
{
   //tracing purposes only
   CINTERPRETERTRACE("~CInterpreter\n");
   
   //In some cases, we let the symboltable out to play with other interpreters.
   //Here we make sure we own the table before we delete it.
   if ((m_bOwnsSymbolTable) && (m_pSymbolTable != NULL))
      delete m_pSymbolTable;
   
   if (m_pOleDispatch != NULL)
      m_pOleDispatch->Release();
}

/******************************************************************************
*  Initialize -- This method initializes the interpreter with a default name.
******************************************************************************/
void CInterpreter::Initialize( LPCOLESTR name )
{
   m_pSymbolTable = new CStackedSymbolTable( );
   m_pSymbolTable->Initialize( name );
}

/******************************************************************************
*  ParseText -- This method parses the text in scriptText into a string of
*               byte-codes for the interpreter to execute.
*  Parameters: scriptText -- an LPCOLESTR containing the script to be parsed.
*              startingLineNumber -- The line number the script starts on
*                                    (For use in HTML-based scripts)
*              dwSourceContext -- DWORD which contains a host provided context
*                                 for the script being parsed.
*  Returns: none
******************************************************************************/
void CInterpreter::ParseText( LPCOLESTR scriptText, ULONG startingLineNumber,
                             DWORD dwSourceContext )
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::ParseText\n");
   
   //Create a new Parser to use on this script
   CParser* pParser = new CParser();
   
   //Parse the script
   pParser->ParseText( &m_InstructionList, scriptText, startingLineNumber,
      dwSourceContext );
   
   //we're done with the parser, so delete it
   delete pParser;
}

/******************************************************************************
*  PutValue -- This method copies the VARIANT in pValue into the symbol
*  designated by variable.
*  Parameters: variable -- a LPCOLESTR which denotes which symbol to copy this
*                          value into.
*              pValue -- a pointer to a ScriptVariant which contains the value
*                        to be copied into the symbol.
*  Returns: S_OK
*           E_INVALIDARG
*           E_FAIL
******************************************************************************/
HRESULT CInterpreter::PutValue( LPCOLESTR variable, ScriptVariant* pValue )
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::PutValue\n");
   
   HRESULT hr = E_FAIL;
   
   //Check arguments
   if ((pValue == NULL) || (variable == NULL )){
      hr = E_INVALIDARG;
   }
   else{
      //Get the CSymbol that contains the VARIANT we need
      CSymbol* pSymbol = NULL;
      
      if (m_pSymbolTable->FindSymbol( variable, &pSymbol )){   
         //Clear the property of any previous value
         VariantClear( pSymbol->Value() );
         
         //Copy the valye from the argument to the CSymbol
         VariantCopy( pSymbol->Value(), pValue->Variant() );
         
         hr = S_OK;
      }
   }
   
   return hr;
}

/******************************************************************************
*  GetValue -- This method copies the VARIANT in the symbol designated by 
*              variable into the ScriptVariant.
*  Parameters: variable -- a LPCOLESTR which denotes which symbol to copy this
*                          value from.
*              pValue -- a pointer to a ScriptVariant into which to copy the
*                        value.
*  Returns: S_OK
*           E_INVALIDARG
*           E_FAIL
******************************************************************************/
HRESULT CInterpreter::GetValue( LPCOLESTR variable, ScriptVariant** ppValue )
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::GetValue\n");
   
   HRESULT hr = E_FAIL;
   
   VARIANT *pVarResult = new VARIANT;
   //initialize the result variant
   VariantInit( pVarResult );
   
   //Get the CSymbol that contains the VARIANT we need
   CSymbol* pSymbol = NULL;
   
   if (m_pSymbolTable->FindSymbol( variable, &pSymbol )){   
      //Copy the value from the symbol to the result VARIANT
      VariantCopy( pVarResult, pSymbol->Value() );
      hr = S_OK;
   }
   
   *ppValue = new ScriptVariant( pVarResult, false );
   
   return hr;
}

/******************************************************************************
*  Call -- This method calls the method designated by variable, assuming it
*          exists in the script somewhere.  If there is a return value, it is
*          placed into the pRetValue ScriptVariant.
*  Parameters: method -- a LPCOLESTR which denotes the method to call
*              pRetValue -- a pointer to a ScriptVariant which accepts the 
*                           return value, if any.
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
HRESULT CInterpreter::Call( LPCOLESTR method, ScriptVariant* pRetValue )
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::Call\n");
   
   HRESULT hr = E_FAIL;
   
   //If the method being called is "Assert" or "Alert", then execute the
   //runtime method provided by the interpreter
   if (!wcscmp( method, L"Assert")){
      //Pop the argument count off the stack
      ScriptVariant* pVariant1 = NULL;
      ScriptVariant* pVariant2 = NULL;

      pVariant1 = m_DataStack.Top();
      m_DataStack.Pop();
      delete pVariant1;
      
      //Pop the ScriptVariants for evaluation off the stack.
      pVariant1 = m_DataStack.Top();
      m_DataStack.Top();
      pVariant2 = m_DataStack.Top();
      m_DataStack.Top();
      
      //Call the Assert method
      Assert( pVariant1, pVariant2 );
      hr = S_OK;
   }
   else if (!wcscmp( method, L"Alert")){
      //Pop the argument count off the stack
      ScriptVariant* pVariant = NULL;
      pVariant = m_DataStack.Top();
      m_DataStack.Pop();
      delete pVariant;
      
      //Pop the ScriptVariant for evaluation off the stack.
      pVariant = m_DataStack.Top();
      m_DataStack.Top();
      
      //Call the Assert method
      Alert( pVariant );
      hr = S_OK;
   }
   
   //Search for the specified entry point.
   else if (m_InstructionList.FindByName( method ))
      hr = EvaluateCall();
   
   if (SUCCEEDED(hr)){
      //This may be a nested call, so if the label stack isn't empty, jump
      //back to where this call came from.
      if (m_LabelStack.Size() != 0){
         LPCOLESTR label = m_LabelStack.Top();
         m_LabelStack.Pop();
         m_InstructionList.FindByName( label );
         //m_InstructionList++;
      }
   }
   
   //Reset the m_bCallCompleted flag back to false
   m_bCallCompleted = false;
   
   return hr;
}

/******************************************************************************
*  EvaluateImmediate -- This method scans the instruction list and evaluates
*  any immediate code that may be present.  In the instruction list, immediate
*  code is preceeded by an IMMEDIATE instruction, and followed by a DEFERRED
*  instruction.
*  Parameters: none
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
STDMETHODIMP CInterpreter::EvaluateImmediate()
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::EvaluateImmediate\n");
   
   BOOL bImmediate = false;
   HRESULT hr = S_OK;
   CInstruction* pInstruction = NULL;
   
   //Run through all the instructions in the list, only executing those wrapped
   //by IMMEDIATE and DEFERRED.
   FOREACH( m_InstructionList, 
      pInstruction = m_InstructionList.Retrieve();
   
   //Don't bother instructions that have already been executed in immediate
   //mode
   if (!pInstruction->m_bImmediateCompleted){
      
      //Check the current mode
      if (pInstruction->m_OpCode == IMMEDIATE)
         bImmediate = true;
      else if (pInstruction->m_OpCode == DEFERRED)
         bImmediate = false;
      
      //If the current mode is Immediate, then evaluate the instruction
      if (bImmediate){
         hr = EvalInstruction();
         
         //each instruction is responsible for tracking whether or not it
         //has been executed in immediate mode.
         pInstruction->m_bImmediateCompleted = true;
      }
   }
   //If we failed, then we need to break out of this loop
   if (FAILED(hr))
      break;
   );
   
   //The "main" function isn't technically immediate code, but it is the well
   //known entry point into C code, so we call it as part of immediate execution.
   //Don't call "main" if it has already been called once.
   if (!m_bMainCompleted){
      ScriptVariant* pSVar = new ScriptVariant( (long)0, true );
      m_DataStack.Push( pSVar );
      hr = Call( L"main", NULL );
      
      if (SUCCEEDED(hr))
         //Set the m_bMainCompleted flag
         m_bMainCompleted = true;
   }
   
   return S_OK;
}

/******************************************************************************
*  EvaluateCall -- This method evaluates the byte-code of a single call into
*  this interpreter.
*  Parameters: none
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
STDMETHODIMP CInterpreter::EvaluateCall()
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::EvaluateCall\n");
   
   HRESULT hr = S_OK;
   
   //Evaluate instructions until an error occurs or until the m_bCallCompleted
   //flag is set to true.
   while(( SUCCEEDED(hr) ) && ( !m_bCallCompleted )){
      hr = EvalInstruction();
   }
   
   return hr;
}

/******************************************************************************
*  UNARYOP -- The unary ops( +, -, !, etc. ) all work the same, so this macro
*  helps clean up the code.  It pops one value off the stack, applies the 
*  specified operator to it, and pushes the result.
******************************************************************************/
#define UNARYOP(x) if (m_DataStack.Size() >= 1){ \
   pSVar1 = m_DataStack.Top(); \
   m_DataStack.Pop(); \
   \
   pRetVal = new ScriptVariant(); \
   *pRetVal = x(*pSVar1); \
   m_DataStack.Push( pSVar1 ); \
   } \
   else \
   HandleRuntimeError( pInstruction, STACK_FAILURE, this );

/******************************************************************************
*  BINARYOP -- The binary ops( +, -, <, ==, etc. ) all work the same, so this 
*  macro helps clean up the code.  It pops two values off the stack, applies
*  the specified operator to them, and pushes the result.
******************************************************************************/
#define BINARYOP(x) if (m_DataStack.Size() >= 2){ \
   pSVar2 = m_DataStack.Top(); \
   m_DataStack.Pop(); \
   pSVar1 = m_DataStack.Top(); \
   m_DataStack.Pop(); \
   \
   pRetVal = new ScriptVariant(); \
   *pRetVal = (*pSVar1 x *pSVar2); \
   m_DataStack.Push( pRetVal ); \
   \
   delete pSVar1; \
   delete pSVar2; \
   } \
   else \
   HandleRuntimeError( pInstruction, STACK_FAILURE, this );

/******************************************************************************
*  EvalInstruction -- This method evaluates a single byte-code instruction.
*  Parameters: none
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
STDMETHODIMP CInterpreter::EvalInstruction()
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::EvalInstruction\n");
   
   HRESULT hr = S_OK;
   
   //Retrieve the current instruction from the list
   CInstruction* pInstruction = NULL;
   pInstruction = m_InstructionList.Retrieve();
   
   if (pInstruction){
      
      //The OpCode will tell us what operation to perform.  We need a few 
      //variables for the switch statement
      CToken* pToken = NULL;
      CSymbol* pSymbol = NULL;
      LPCOLESTR pLabel = NULL;
      ScriptVariant* pSVar1 = NULL;
      ScriptVariant* pSVar2 = NULL;
      ScriptVariant* pRetVal = NULL;
      
      switch( pInstruction->m_OpCode ){
         //Push a constant string
      case CONSTSTR:
         pToken = pInstruction->m_pToken;
         pSVar1 = new ScriptVariant( pToken->Source() );
         m_DataStack.Push( pSVar1 );
         break;
         
         //Push a constant double
      case CONSTDBL:
         //The value of this constant may have been a CToken* or a LPCOLESTR
         if (pInstruction->m_pToken != NULL){
            pToken = pInstruction->m_pToken;
            pSVar1 = new ScriptVariant( wcstod( pToken->Source(), NULL ) );
         }
         else{
            pLabel = pInstruction->m_Label;
            pSVar1 = new ScriptVariant( wcstod( pLabel, NULL ) );
         }
         m_DataStack.Push( pSVar1 );
         break;
         
         //Load a value into the data stack
      case LOAD:
         pToken = pInstruction->m_pToken;
         hr = GetValue( pToken->Source(), &pSVar1 );
         
         //If the GetValue failed, then report and error
         if (FAILED(hr))
            HandleRuntimeError( pInstruction, INVALID_REFERENCE, this );
         
         m_DataStack.Push( pSVar1 );
         break;
         
         //Save a value from the data stack
      case SAVE:
         pToken = pInstruction->m_pToken;
         pSVar1 = m_DataStack.Top();
         m_DataStack.Pop();
         hr = PutValue( pToken->Source(), pSVar1 );
         
         //If the PutValue failed, then report and error
         if (FAILED(hr))
            HandleRuntimeError( pInstruction, INVALID_REFERENCE, this );
         
         delete pSVar1;
         break;
         
         //use the UNARYOP macro to do an AutoIncrement
      case INC:
         UNARYOP(++);
         break;
         
         //use the UNARYOP macro to do an AutoDecrement
      case DEC:
         UNARYOP(--);
         break;
         
         //use the UNARYOP macro to do a unary plus
      case POS:
         UNARYOP(+);
         break;
         
         //use the UNARYOP macro to do a unary minus
      case NEG:
         UNARYOP(-);
         break;
         
         //use the UNARYOP macro to do a logical not
      case NOT:
         UNARYOP(!);
         break; 
         
         //Use the BINARYOP macro to do a multipy
      case MUL:
         BINARYOP(*);
         break;
         
         //Use the BINARYOP macro to do a divide
      case DIV: 
         BINARYOP(/);
         break;
         
         //Use the BINARYOP macro to do an add
      case ADD:
         BINARYOP(+);
         break;
         
         //Use the BINARYOP macro to do a subtract
      case SUB: 
         BINARYOP(-);
         break;
         
         //Use the BINARYOP macro to do a greater than- equal
      case GE:
         BINARYOP(>=);
         break; 
         
         //Use the BINARYOP macro to do a less than- equal
      case LE:
         BINARYOP(<=);
         break;
         
         //Use the BINARYOP macro to do a less than
      case LT:
         BINARYOP(<);
         break;
         
         //Use the BINARYOP macro to do a greater than
      case GT:
         BINARYOP(>);
         break;
         
         //Use the BINARYOP macro to do an equality
      case EQ: 
         BINARYOP(==);
         break;
         
         //Use the BINARYOP macro to do a not-equal
      case NE: 
         BINARYOP(!=);
         break;
         
         //Use the BINARYOP macro to do a logical OR
      case OR:
         BINARYOP(||);
         break; 
         
         //Use the BINARYOP macro to do a logical AND
      case AND:
         BINARYOP(&&);
         break;
         
         //Create a new CSymbol and add it to the symbol table
      case DATA:
         pToken = pInstruction->m_pToken;
         pSymbol = new CSymbol( pToken->Source(), 0 );
         m_pSymbolTable->AddSymbol( pSymbol );
         break;
         
         //Create a new CSymbol from a value on the stack and add it to the 
         //symbol table.
      case PARAM: 
         pToken = pInstruction->m_pToken;
         if (m_DataStack.Size() >= 1){
            pSVar1 = m_DataStack.Top();
            m_DataStack.Pop();
            pSymbol = new CSymbol( pToken->Source(), 0, pSVar1->Variant() );
            m_pSymbolTable->AddSymbol( pSymbol );
            delete pSVar1;
         }
         else
            HandleRuntimeError( pInstruction, STACK_FAILURE, this );

         break; 
         
         //Pop the top element of the data stack, and check to see if it's an 
         //IDispatch pointer.  If so, put that pointer into m_pOleDispatch for
         //use in external references
      case FIELD:
         if (m_pOleDispatch != NULL)
            m_pOleDispatch->Release();
         
         pSVar1 = m_DataStack.Top();
         m_DataStack.Pop();
         
         if (pSVar1->Variant()->vt == VT_DISPATCH){
            m_pOleDispatch = pSVar1->Variant()->pdispVal;
            m_pOleDispatch->AddRef();
         }
         
         //If the top object on the stack is not an IDispatch pointer, report 
         //an error.
         else{
            HandleRuntimeError( pInstruction, OBJECT_REQUIRED, this );
            hr = E_FAIL;
         }
         delete pSVar1;
         
         break;
         
         //Call the specified method, and pass in a ScriptVariant* to receive the 
         //return value.  If it's not NULL, then push it onto the data stack.
      case CALL:
         //We need to be able to jump back to this instruction when the call is
         //over, so copy this instruction's label onto the label stack
         pLabel = m_InstructionList.GetName();
         m_LabelStack.Push( pLabel );
         
         pToken = pInstruction->m_pToken;
         hr = Call( pToken->Source(), pRetVal );
         
         //If the Call failed, then report an error
         if (FAILED(hr))
            HandleRuntimeError( pInstruction, INVALID_METHOD, this );
         
         if (pRetVal != NULL)
            m_DataStack.Push( pRetVal );
         
         //Reset the m_bCallCompleted flag back to false
         m_bCallCompleted = false;
         
         break;
         
         //Jump to the specified label
      case JUMP:
         pLabel = pInstruction->m_Label;
         m_InstructionList.FindByName( pLabel );
         break;
         
         //Jump if the top ScriptVariant resolves to false
      case Branch_FALSE:
         pLabel = pInstruction->m_Label;
         pSVar1 = m_DataStack.Top();
         m_DataStack.Pop();
         if (!pSVar1->isTrue())
            m_InstructionList.FindByName( pLabel );
         delete pSVar1;
         break;
         
         //Jump if the top ScriptVariant resolves to true
      case Branch_TRUE: 
         pLabel = pInstruction->m_Label;
         pSVar1 = m_DataStack.Top();
         m_DataStack.Pop();
         if (pSVar1->isTrue())
            m_InstructionList.FindByName( pLabel );
         pSVar1;
         break;
         
         //Set the m_bCallCompleted flag to true so we know to stop evalutating
         //instructions
      case RET:
         m_bCallCompleted = true;
         break;
         
         //Make sure the argument count on the top of the stack matches the
         //number of arguments we have
      case CHECKARG:
         pLabel = pInstruction->m_Label;
         pSVar1 = new ScriptVariant( wcstod( pLabel, NULL ) );
         
         pSVar2 = m_DataStack.Top();
         m_DataStack.Pop();
         
         //Don't report an error here.  If this is an internal call, then CALL
         //will catch it, and if it's external, then the caller's IDispatch
         //should catch it.
         if ((*pSVar1 != *pSVar2).isTrue())
            hr = DISP_E_BADPARAMCOUNT;
         
         delete pSVar1;
         delete pSVar2;
         break;
         
         //This instructs the interpreter to clean one value off the stack.
      case CLEAN:
         pSVar1 = m_DataStack.Top();
         m_DataStack.Pop();
         delete pSVar1;
         break;
         
         //This OpCode denotes an error in the instruction list
      case ERR:
         hr = E_FAIL;
         break;
         
         //This is a placeholder.  Don't do anything.
      case NOOP:
         break; 
         
         //This instructs the interpreter to push a symbol scope.
      case PUSH:
         m_pSymbolTable->PushScope();
         break; 
         
         //This instructs the interpreter to pop a symbol scope
      case POP:
         m_pSymbolTable->PopScope();
         break;
         
         //Ignore IMMEDIATE and DEFFERRED instructions, since they are only used
         //to mark immediate code.
      case IMMEDIATE: 
      case DEFERRED:
         break;
         
         //If we hit the default, then we got an unrecognized instruction
      default:
         hr = E_FAIL;
         
         //Report an error
         HandleRuntimeError( pInstruction, INVALID_INSTRUCTION, this );
         break;
      }
      
      //Increment the instruction list
      m_InstructionList++;
   }
   
   //return the result of this token evaluation
   return hr;
}

/******************************************************************************
*  OutputPCode -- This method creates a new text file called <fileName>.txt 
*                 that contains a pseudo-assembly representation of the PCode 
*                 stored in this CInterpreter object.  The file cannot be read 
*                 back into the interpreter.  It is created for debugging 
*                 purposes only.
*  Parameters: fileName -- an LPCOLESTR containing the name of the file to 
*                          store the pseudo-assembly code in.  An LPCOLESTR is
*                          used for consistency with the rest of the engine.
*  Returns: none
******************************************************************************/
void CInterpreter::OutputPCode( LPCOLESTR fileName )
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::OutputPCode\n");
   
   //Declare and initialize some string buffers.
   static char sz[256];
   static char buffer[256];
   memset(&sz, '\0', 256 );
   memset(&buffer, '\0', 256 );
   
   //Convert fileName down to ASCII so we can create a file stream
   WideCharToMultiByte(CP_ACP, 0, fileName, -1, sz, 256, NULL, NULL);
   
   //If the fileName is L"", then substitute "Main".
   if (!strcmp( sz, "" ))
      strcpy( sz, "Main" );
   
   //Add ".txt" to the end of the names so the files get created right
   strcat( sz, ".txt" );
   
   //Open an output stream for the productions enumeration.
   ofstream instStream(sz, ios::binary | ios.out);
   if (!instStream)
      return;
   
   //Iterate through the list of instructions
   CInstruction* pInstruction = NULL;
   LPCOLESTR pLabel = NULL;
   FOREACH( m_InstructionList, 
      //Get the next CInstruction
      pInstruction = m_InstructionList.Retrieve();
   
   //Re-initialize the buffers
   memset(&sz, '\0', 256 );
   memset(&buffer, '\0', 256 );
   
   //If this instruction has a label, then get it and write it to the output
   //buffer
   pLabel = m_InstructionList.GetName();
   if (pLabel != NULL)
      WideCharToMultiByte(CP_ACP, 0, pLabel, -1, buffer, 256, NULL, NULL );
   strcat( buffer, "\t" );
   
   //Get the pseudo-assembly representation of the CInstruction and concat 
   //it onto the output buffer
   WCHAR* pwStr = (unsigned short*)pInstruction->toString();
   WideCharToMultiByte(CP_ACP, 0, pwStr, -1, sz, 256, NULL, NULL);
   strcat( buffer, sz );
   
   strcat( buffer, "\n");

   //Write the output buffer to the output stream
   instStream << buffer;
   );
   
   //Close the output stream
   instStream.close();
}

/******************************************************************************
*  Assert -- This method is provided by the interpreter as a run-time function 
*            for debugging scripts.  It takes a ScriptVariant that must 
*            evaluate to true.  If it fails, then this method reports as much
*            information as possible about the failure.
*  Parameters: pVariant -- A ScriptVariant that evaluates to true or false
*              pMessage -- A ScriptVariant that the interpreter displays if 
*                          pVariant evaluates to false
*  Returns: none
******************************************************************************/
void CInterpreter::Assert( ScriptVariant* pVariant, ScriptVariant* pMessage )
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::Assert\n");
   
   static char buffer[80];
   memset( buffer, '\0', 80 );
   
   //Check the arguments to this method
   if ((pVariant == NULL) || (pMessage == NULL))
      CINTERPRETERTRACE("Invalid parameters passed to Assert!\n");

   else{
      if (!pVariant->isTrue()){
         //Get the string representation of the ScriptVariant
         LPCOLESTR SVString = pMessage->toString();
         
         // Convert down to ANSI
         WideCharToMultiByte(CP_ACP, 0, SVString, -1, buffer, 80, NULL, NULL);
         
         //Put up a message box with the string in it.
         MessageBox( NULL, buffer, "Sample Script Assertion", MB_SETFOREGROUND );
      }
   }
}

/******************************************************************************
*  Alert -- This method is provided by the interpreter as a run-time finction 
*           for debugging scripts.  It takes a ScriptVariant and attempts to
*           print a human-readable form of it in a message box.
*  Parameters: pVariant -- A ScriptVariant for display in a message box.
*  Returns: none
******************************************************************************/
void CInterpreter::Alert( ScriptVariant* pSVar1 )
{
   //tracing purposes only
   CINTERPRETERTRACE("CInterpreter::Alert\n");
   
   static char buffer[80];
   memset( buffer, '\0', 80 );
   
   //Get the string representation of the ScriptVariant
   LPCOLESTR SVString = pSVar1->toString();
   
   // Convert down to ANSI
   WideCharToMultiByte(CP_ACP, 0, SVString, -1, buffer, 80, NULL, NULL);
   
   //Put up a message box with the string in it.
   MessageBox( NULL, buffer, "Sample Script", MB_SETFOREGROUND );
}
