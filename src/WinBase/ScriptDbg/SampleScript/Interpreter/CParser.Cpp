/******************************************************************************
*
*  File: CParser.cpp
*
*  Author:  Joel Alley
*
*  Date: September 28, 1998
*
*  Description:   This file contains the definition of a simple recursive
*                 descent parser which takes a stream of CTokens and generates
*                 a stream of stack-based instructions which can be run by the
*                 CInterpreter class.
*
*  Modifications:
******************************************************************************/
#define CPARSER
#include "depends.h"

CParser::CParser( )
{
   m_pLexer = NULL;
   m_pParserSet = new CParserSet();

   //look up server's file name.  This will give us the path to the directory
   //where SampleScript.dll is installed.
   char szFirst[255];
   char szFollow[255];
   HMODULE dllModule = GetModuleHandle("SampleScript.dll");
   GetModuleFileName(dllModule, szFirst, 255);

   //Remove the Dll name
   *(szFirst + strlen(szFirst) - 16) = 0;
   
   //copy the path into szFollow
   strcpy( szFollow, szFirst );

   //Add the file names to the paths
   strcat( szFirst, "FIRST.txt" );
   strcat( szFollow, "FOLLOW.txt" );

   //Build the first and follow sets.
   m_pParserSet->BuildSets( szFirst, szFollow );
   m_LabelCount = 0;

   m_pFieldToken = NULL;
}

CParser::~CParser(){;}

/******************************************************************************
*  ParseText -- This method begins the recursive-descent process for each global
*  variable and function definition.
*  Parameters: pIList -- pointer to a TList<CInstruction> which takes the
*                        stream of CInstructions representing the parsed text
*              scriptText -- LPCOLESTR which contains ths script to be parsed.
*              startingLineNumber -- Line on which this script starts.  The 
*                        lexer needs this information to maintain accurate
*                        line counts.
*  Returns:
******************************************************************************/
void CParser::ParseText( TList<CInstruction*>* pIList, LPCOLESTR scriptText,
                     ULONG startingLineNumber, DWORD dwSourceContext )
{
   //Delete any previous CLexers...
   if (m_pLexer != NULL){
      delete m_pLexer;
      m_pLexer = NULL;
   }

   //Create a new CLexer for this script text.
   TEXTPOS thePosition;
   thePosition.row = startingLineNumber;
   thePosition.col = 1;
   m_pLexer = new CLexer( scriptText, thePosition, dwSourceContext );

   //Get the first token from the CLexer.
   m_pLexer->getNextToken( &m_pNextToken );

   //Setup the instruction list so we can add instructions.
   m_pIList = pIList;

   //Make sure we're pointing at the end of that list
   m_pIList->GotoLast();

   //Parse the script text until you reach the end of the file, or until
   //an error occurs.
   while( m_pNextToken->Type() != TOKEN_EOF ){
      External_decl( );
   }
}

/******************************************************************************
*  ParseExpression -- This method begins the recursive-descent process for each
*  global variable and function definition.
*  Parameters: pIList -- pointer to a TList<CInstruction> which takes the
*                        stream of CInstructions representing the parsed text
*              scriptText -- LPCOLESTR which contains ths script to be parsed.
*              startingLineNumber -- Line on which this script starts.  The 
*                        lexer needs this information to maintain accurate
*                        line counts.
*  Returns:
******************************************************************************/
void CParser::ParseExpression( TList<CInstruction*>* pIList, LPCOLESTR scriptText,
                    ULONG startingLineNumber, DWORD dwSourceContext )
{
   //Append a semi-colon to the end of the expression, in order to use the
   //same grammar as regular script text.
   LPCOLESTR expressionText = new WCHAR[wcslen( scriptText )];
   wcscpy( (unsigned short*)expressionText, scriptText );
   wcscat( (unsigned short*)expressionText, L";" );

   //Delete any previous CLexers...
   if (m_pLexer != NULL){
      delete m_pLexer;
      m_pLexer = NULL;
   }

   //Create a new CLexer for this script text.
   TEXTPOS thePosition;
   thePosition.row = startingLineNumber;
   thePosition.col = 1;
   m_pLexer = new CLexer( expressionText, thePosition, dwSourceContext );

   //Get the first token from the CLexer.
   m_pLexer->getNextToken( &m_pNextToken );

   //Setup the instruction list so we can add instructions.
   m_pIList = pIList;

   //Make sure we're pointing at the end of that list
   m_pIList->GotoLast();

   //Parse the expression
   Expr();
}

/******************************************************************************
*  AddInstruction -- This method creates a new CInstruction and adds it to the
*  instruction list.  It serves to simplify the parser code slightly, and to
*  allow for easier extension of the CInstruction class for debugging.
*  Parameters: pCode -- OpCode of the new instruction
*              pToken -- CToken associated with the new instruction
*              label -- entry point label in the instruction list
******************************************************************************/
void CParser::AddInstruction( OpCode pCode, CToken* pToken, Label label )
{
   //tracing purposes only
   PARSETRACE("CParser::AddInstruction\n");

   CInstruction* pInstruction = new CInstruction(pCode, pToken);
   m_pIList->InsertAfter( pInstruction, label );
}

/******************************************************************************
*  AddInstruction -- This method creates a new CInstruction and adds it to the
*  instruction list.  It serves to simplify the parser code slightly, and to
*  allow for easier extension of the CInstruction class for debugging.
*  Parameters: pCode -- OpCode of the new instruction
*              instrLabel -- Label associated with this instruction
*              listLabel -- entry point label in the instruction list
******************************************************************************/
void CParser::AddInstruction( OpCode pCode, Label instrLabel, Label listLabel )
{
   //tracing purposes only
   PARSETRACE("CParser::AddInstruction\n");

   CInstruction* pInstruction = new CInstruction(pCode, instrLabel);
   m_pIList->InsertAfter( pInstruction, listLabel );
}

/******************************************************************************
*  Check -- This method compares the type of the current token with a specified
*  token type.
*  Parameters: theType -- MY_TOKEN_TYPE specifying the type to compare
*  Returns: true if the current token type matches theType
*           false otherwise.
******************************************************************************/
BOOL CParser::Check( MY_TOKEN_TYPE theType )
{
   //compare the token types
   if (m_pNextToken->Type() == theType){
      return true;
   }
   else
      return false;
}

/*****************************************************************************
*  Match -- This method consumes the current token and retrieves the next one.
*  Parameters:
*  Returns:
******************************************************************************/
void CParser::Match( void )
{
   //Don't delete the current token, because it's now part of a CInstruction.
   m_pLexer->getNextToken( &m_pNextToken );
}

/******************************************************************************
*   CreateLabel -- This method creates a label, unique within this parser, to
*   Serve as a target for jumps and calls.
*   Parameters: none
*   Returns: A unique Label
******************************************************************************/
Label CParser::CreateLabel( void )
{
   //Allocate a buffer for the new Label.  A long can take 10 characters at
   //most, so allocate that plus two extra for the "L" and the null 
   //terminator
   Label theLabel = new WCHAR[12];
   memset(theLabel, '\0', 23);
   wcscpy(theLabel, L"L");

   //Increment the label count.
   m_LabelCount++;

   //Get a string representation of the label value
   WCHAR* theValue = new WCHAR[10];
   memset( theValue, '\0', 19 );
   _ltow( m_LabelCount, theValue, 10 );

   //Copy the label value into the buffer
   wcscat( theLabel, theValue );

   return theLabel;
}

/******************************************************************************
*  Productions -- These methods recursively parse the token stream into an
*  Abstract Syntax Tree.
******************************************************************************/

void CParser::Start( )
{
   PARSETRACE("CParser::Start");
   if (m_pParserSet->First( external_decl, m_pNextToken->Type() )){
      External_decl( );
      Start( );
   }
   else if (m_pParserSet->Follow( start, m_pNextToken->Type() )){}
   else Error( start );
}

/******************************************************************************
*  Declaration evaluation -- These methods translate declarations into
*  appropriate instructions.
******************************************************************************/
void CParser::External_decl( )
{
   PARSETRACE("CParser::External_decl");
   if (m_pParserSet->First( decl_spec, m_pNextToken->Type() )){
      //ignore the type of this declaration
      Decl_spec( );
      Check( TOKEN_IDENTIFIER );
      CToken* pToken = m_pNextToken;
      Match();

      if (m_pParserSet->First( initializer, m_pNextToken->Type() )){
         //switch to immediate mode and allocate a variable.
         AddInstruction( IMMEDIATE, (CToken*)NULL, NULL );
         AddInstruction( DATA, pToken, NULL );

         //Get the initializer;
         Initializer( );
         Check( TOKEN_SEMICOLON );
         Match();

         //Save the initializer
         AddInstruction( SAVE, pToken, NULL );

         //Switch back to deferred mode
         AddInstruction( DEFERRED, (CToken*)NULL, NULL );
      }
      else if ( Check( TOKEN_SEMICOLON )){
         Match();
         //switch to immediate mode and allocate a variable.
         AddInstruction( IMMEDIATE, (CToken*)NULL, NULL );
         AddInstruction( DATA, pToken, NULL );

         //Switch back to deferred mode
         AddInstruction( DEFERRED, (CToken*)NULL, NULL );
      }
      else if (m_pParserSet->First( funcDecl, m_pNextToken->Type() )){
         AddInstruction( NOOP, pToken, (Label)pToken->Source() );
         AddInstruction( PUSH, (CToken*)NULL, NULL );
         FuncDecl( );
         Comp_stmt( &epiLabel );
         AddInstruction( POP, (CToken*)NULL, NULL );
         AddInstruction( RET, (CToken*)NULL, NULL );
      }
      
      else Error( external_decl );
   }
   
   else Error( external_decl );
}

void CParser::Decl_spec( )
{
   PARSETRACE("CParser::Decl_spec");
   if (Check( TOKEN_CONST )){
      Match();
   }

   if (Check( TOKEN_SIGNED )){
      Match();
   }
   else if (Check( TOKEN_UNSIGNED )){
      Match();
   }

   if (Check( TOKEN_VOID )){
      Match();
   }
   else if (Check( TOKEN_CHAR )){
      Match();
   }
   else if (Check( TOKEN_SHORT )){
      Match();
   }
   else if (Check( TOKEN_INT )){
      Match();
   }
   else if (Check( TOKEN_LONG )){
      Match();
   }
   else if (Check( TOKEN_FLOAT )){
      Match();
   }
   else if (Check( TOKEN_DOUBLE )){
      Match();
   }
   else Error( decl_spec );
}

void CParser::Decl( )
{
   PARSETRACE("CParser::Decl");
   if (m_pParserSet->First( decl_spec, m_pNextToken->Type() )){
      //ignore the type of this declaration
      Decl_spec( );
      Check( TOKEN_IDENTIFIER );
      CToken* pToken = m_pNextToken;
      Match();

      if (m_pParserSet->First( initializer, m_pNextToken->Type() )){
         AddInstruction( DATA, pToken, NULL );

         //Get the initializer;
         Initializer( );
         Check( TOKEN_SEMICOLON );
         Match();

         //Save the initializer
         AddInstruction( SAVE, pToken, NULL );
      }
      else if ( Check( TOKEN_SEMICOLON )){
         Match();
         AddInstruction( DATA, pToken, NULL );
      }
      else Error( decl );
   }
   else Error( decl );
}

void CParser::FuncDecl( )
{
   PARSETRACE("CParser::FuncDecl");
   if (Check( TOKEN_LPAREN )){
      Match();
      FuncDecl1( );
   }
   else if (m_pParserSet->Follow( funcDecl, m_pNextToken->Type() )){}
   else Error( funcDecl );
}

void CParser::FuncDecl1( )
{
   PARSETRACE("CParser::FuncDecl1");
   if (m_pParserSet->First( param_list, m_pNextToken->Type() )){
      Param_list( );
      Check( TOKEN_RPAREN );
      Match();
   }
   else if (Check( TOKEN_RPAREN )){
      AddInstruction( CHECKARG, L"0", NULL );
      Match();
   }
   else Error( funcDecl1 );
}

void CParser::Initializer( )
{
   PARSETRACE("CParser::Initializer");
   if (Check( TOKEN_ASSIGN )){
      Match();
      Assignment_expr( );
   }
   else if (m_pParserSet->Follow( initializer, m_pNextToken->Type() )){}
   else Error( initializer );
}

void CParser::Parm_decl( )
{
   PARSETRACE("CParser::Parm_decl");
   if (m_pParserSet->First( decl_spec, m_pNextToken->Type() )){
      Decl_spec( );
      
      if ( Check( TOKEN_IDENTIFIER )){
         AddInstruction( PARAM, m_pNextToken, NULL );
         Match();
      }
      else
         AddInstruction( PARAM, (CToken*)NULL, NULL );
   }
   else Error( parm_decl );
}

void CParser::Param_list( )
{
   PARSETRACE("CParser::Param_list");
   if (m_pParserSet->First( parm_decl, m_pNextToken->Type() )){
      Parm_decl( );
      Param_list2( );
   }
   else Error( param_list );
}

void CParser::Param_list2( )
{
   PARSETRACE("CParser::Param_list2");

   static int paramCount = 1;

   if (Check( TOKEN_COMMA )){
      Match();
      Parm_decl( );
      paramCount++;
      Param_list2( );
   }
   else if (m_pParserSet->Follow( param_list2, m_pNextToken->Type() ))
   {
      //Walk back up the Instruction list and insert before the first PARAM
      //instruction.
      int i = 0;
      for(i = 1; i < paramCount; i++ )
         (*m_pIList)--;

      WCHAR* pbuffer = new WCHAR[4];
      memset( pbuffer, '\0', 4 );
      swprintf( pbuffer, L"%d", paramCount );
      m_pIList->InsertBefore( new CInstruction(CHECKARG, pbuffer), NULL );

      //Walk back down the InstructionList to reset the insertion point
      for (i = 0; i < paramCount; i++ )
         (*m_pIList)++;
   }

   else Error( param_list2 );
}

void CParser::Decl_list( )
{
   PARSETRACE("CParser::Decl_list");
   if (m_pParserSet->First( decl, m_pNextToken->Type() )){
      Decl( );
      Decl_list2( );
   }
   else Error( decl_list );
}

void CParser::Decl_list2( )
{
   PARSETRACE("CParser::Decl_list2");
   if (m_pParserSet->First( decl, m_pNextToken->Type() )){
      Decl( );
      Decl_list2( );
   }
   else if (m_pParserSet->Follow( decl_list2, m_pNextToken->Type() )){}
   else Error( decl_list2 );
}

/******************************************************************************
*  Statement evaluation -- These methods translate statements into
*  appropriate instructions.
******************************************************************************/
void CParser::Stmt_list( )
{
   PARSETRACE("CParser::Stmt_list");
   if (m_pParserSet->First( stmt, m_pNextToken->Type() )){
      Stmt( );
      Stmt_list2( );
   }
   else Error( stmt_list );
}

void CParser::Stmt_list2( )
{
   PARSETRACE("CParser::Stmt_list2");
   if (m_pParserSet->First( stmt, m_pNextToken->Type() )){
      Stmt( );
      Stmt_list2( );
   }
   else if (m_pParserSet->Follow( stmt_list2, m_pNextToken->Type() )){}
   else Error( stmt_list2 );
}

void CParser::Stmt( )
{
   PARSETRACE("CParser::Stmt");
   if (m_pParserSet->First( expr_stmt, m_pNextToken->Type() )){
      Expr_stmt( );
   }
   else if (m_pParserSet->First( comp_stmt, m_pNextToken->Type() )){
      Comp_stmt( );
   }
   else if (m_pParserSet->First( select_stmt, m_pNextToken->Type() )){
      Select_stmt( );
   }
   else if (m_pParserSet->First( iter_stmt, m_pNextToken->Type() )){
      Iter_stmt( );
   }
   else if (m_pParserSet->First( jump_stmt, m_pNextToken->Type() )){
      Jump_stmt( );
   }
   else Error( stmt );
}

void CParser::Expr_stmt( )
{
   PARSETRACE("CParser::Expr_stmt");
   if (m_pParserSet->First( expr, m_pNextToken->Type() )){
      Expr( );
      AddInstruction( CLEAN, (CToken*)NULL, NULL );
      Check( TOKEN_SEMICOLON );
      Match();
   }
   else Error( expr_stmt );
}

void CParser::Comp_stmt( Label* pLabel )
{
   PARSETRACE("CParser::Comp_stmt");
   if (Check( TOKEN_LCURLY )){
      Match();
      AddInstruction( PUSH, (CToken*)NULL, NULL );
      *pLabel = CreateLabel();
      Comp_stmt2( );
      Comp_stmt3( );
      AddInstruction( NOOP, (CToken*)NULL, *pLabel );
      AddInstruction( POP, (CToken*)NULL, NULL );
      Check( TOKEN_RCURLY );
      Match();
   }
   else Error( comp_stmt );
}

void CParser::Comp_stmt( )
{
   PARSETRACE("CParser::Comp_stmt");
   if (Check( TOKEN_LCURLY )){
      Match();
      AddInstruction( PUSH, (CToken*)NULL, NULL );
      Label jumpLabel = CreateLabel();
      Comp_stmt2( );
      Comp_stmt3( );
      AddInstruction( NOOP, (CToken*)NULL, jumpLabel );
      AddInstruction( POP, (CToken*)NULL, NULL );
      Check( TOKEN_RCURLY );
      Match();
   }
   else Error( comp_stmt );
}

void CParser::Comp_stmt2( )
{
   PARSETRACE("CParser::Comp_stmt2");
   if (m_pParserSet->First( decl_list, m_pNextToken->Type() )){
      Decl_list( );
   }
   else if (m_pParserSet->Follow( comp_stmt2, m_pNextToken->Type() )){}
   else Error( comp_stmt2 );
}

void CParser::Comp_stmt3( )
{
   PARSETRACE("CParser::Comp_stmt3");
   if (m_pParserSet->First( stmt_list, m_pNextToken->Type() )){
      Stmt_list( );
   }
   else if (m_pParserSet->Follow( comp_stmt3, m_pNextToken->Type() )){}
   else Error( comp_stmt3 );
}

void CParser::Select_stmt( )
{
   PARSETRACE("CParser::Select_stmt");

   //Create some labels for jump targets
   Label falseLabel = CreateLabel();
   Label endLabel = CreateLabel();

   if (Check( TOKEN_IF )){
      Match();
      Check( TOKEN_LPAREN );
      Match();
      Expr( );
      Check( TOKEN_RPAREN );
      AddInstruction( Branch_FALSE, falseLabel, NULL );
      Match();
      Stmt( );
      AddInstruction( JUMP, endLabel, NULL );
      AddInstruction( NOOP, (CToken*)NULL, falseLabel );
      Opt_else( );
      AddInstruction( NOOP, (CToken*)NULL, endLabel );
   }
   else Error( select_stmt );
}

void CParser::Opt_else( )
{
   PARSETRACE("CParser::Opt_else");
   if (Check( TOKEN_ELSE )){
      Match();
      Stmt( );
   }
   else if (m_pParserSet->Follow( opt_else, m_pNextToken->Type() )){}
   else Error( opt_else );
}

void CParser::Iter_stmt( )
{
   PARSETRACE("CParser::Iter_stmt");

   //Create some labels for jump targets
   Label endLabel = CreateLabel();
   Label startLabel = CreateLabel();

   if (Check( TOKEN_WHILE )){
      Match();
      AddInstruction( NOOP, (CToken*)NULL, startLabel );
      Check( TOKEN_LPAREN );
      Match();
      Expr( );
      Check( TOKEN_RPAREN );
      AddInstruction( Branch_FALSE, endLabel, NULL );
      m_LabelStack.Push( endLabel );
      Match();
      Stmt( );
      m_LabelStack.Pop();
      AddInstruction( JUMP, startLabel, NULL );
      AddInstruction( NOOP, (CToken*)NULL, endLabel );
   }
   else if (Check( TOKEN_DO )){
      Match();
      AddInstruction( NOOP, (CToken*)NULL, startLabel );
      m_LabelStack.Push( endLabel );
      Stmt( );
      Check( TOKEN_WHILE );
      Match();
      Check( TOKEN_LPAREN );
      Match();
      Expr( );
      Check( TOKEN_RPAREN );
      AddInstruction( Branch_TRUE, startLabel, NULL );
      AddInstruction( NOOP, (CToken*)NULL, endLabel );
      m_LabelStack.Pop();
      Match();
      Check( TOKEN_SEMICOLON );
      Match();
   }
   else if (Check( TOKEN_FOR )){
      Match();
      Check( TOKEN_LPAREN );
      Match();

      //Add any initializer code
      Opt_expr_stmt( );

      //Set the flag for the conditional to jump back to.
      AddInstruction( NOOP, (CToken*)NULL, startLabel );

      //Build the conditional statement
      if (m_pParserSet->First( expr, m_pNextToken->Type() )){
         Expr();
         AddInstruction( Branch_FALSE, endLabel, NULL );
         Check( TOKEN_SEMICOLON );
         Match();
      }
      else if (m_pParserSet->Follow( opt_expr_stmt, m_pNextToken->Type() )){}
      else Error( opt_expr_stmt );

      //We need to defer adding the instructions related to the last parameter
      //of the for loop, so catch them.
      TList<CInstruction*>* pDefInst = NULL;
      pDefInst = Defer_expr_stmt( );
      Check( TOKEN_RPAREN );
      Match();
      Stmt( );

      //Add in the deferred instructions, if there were any.
      if (pDefInst){
         CInstruction* pInstruction = NULL;
         
         PFOREACH( pDefInst, 
            pInstruction = pDefInst->Retrieve();

            //We have to assume here that the expression didn't need labels.
            AddInstruction( pInstruction->m_OpCode, pInstruction->m_pToken, NULL );
         );

         delete pDefInst;
      }

      //Add the jump statement
      AddInstruction( JUMP, startLabel, NULL );

      //Add the end label.
      AddInstruction( NOOP, (CToken*)NULL, endLabel );
      m_LabelStack.Pop( );
   }
   else Error( iter_stmt );
}

void CParser::Opt_expr_stmt( )
{
   PARSETRACE("CParser::Opt_expr_stmt");
   if (m_pParserSet->First( expr_stmt, m_pNextToken->Type() )){
      Expr_stmt( );
   }
   else if (m_pParserSet->Follow( opt_expr_stmt, m_pNextToken->Type() )){}
   else Error( opt_expr_stmt );
}

TList<CInstruction*>* CParser::Defer_expr_stmt( )
{
   PARSETRACE("CParser::Defer_expr_stmt");
   //if (m_pParserSet->First( expr_stmt, m_pNextToken->Type() )){
   if (m_pParserSet->First( expr, m_pNextToken->Type() )){
      //We have to swap out instruction lists
      TList<CInstruction*>* pMainList = m_pIList;
      m_pIList = new TList<CInstruction*>();

      //Expr_stmt( );
      Expr();

      //Swap the instruction lists back and return the deferred list
      TList<CInstruction*>* pTemp = m_pIList;
      m_pIList = pMainList;

      return pTemp;
   }
   else if (m_pParserSet->Follow( defer_expr_stmt, m_pNextToken->Type() )){}
   else Error( defer_expr_stmt );

   return NULL;
}

void CParser::Jump_stmt( )
{
   PARSETRACE("CParser::Jump_stmt");
   if (Check( TOKEN_BREAK )){
      Match();
      Check( TOKEN_SEMICOLON );
      Match();

      Label breakTarget = m_LabelStack.Top();
      AddInstruction( JUMP, breakTarget, NULL );
   }
   else if (Check( TOKEN_RETURN )){
      Match();
      Opt_expr( );
      Check( TOKEN_SEMICOLON );
      Match();

      AddInstruction( JUMP, epiLabel, NULL );
   }
   else Error( jump_stmt );
}

/******************************************************************************
*  Expression Evaluation -- These methods translate expressions into 
*  appropriate instructions.
******************************************************************************/
void CParser::Opt_expr( )
{
   PARSETRACE("CParser::Opt_expr");
   if (m_pParserSet->First( expr, m_pNextToken->Type() )){
      Expr( );
   }
   else if (m_pParserSet->Follow( opt_expr, m_pNextToken->Type() )){}
   else Error( opt_expr );
}

void CParser::Expr( )
{
   PARSETRACE("CParser::Expr");
   if (m_pParserSet->First( assignment_expr, m_pNextToken->Type() )){
      Assignment_expr( );
   }
   else Error( expr );
}

OpCode CParser::Assignment_op( )
{
   PARSETRACE("CParser::Assignment_op");
   if (Check( TOKEN_ASSIGN )){
      Match();
      return NOOP;
   }
   else if (Check( TOKEN_MUL_ASSIGN )){
      Match();
      return MUL;
   }
   else if (Check( TOKEN_DIV_ASSIGN )){
      Match();
      return DIV;
   }
   else if (Check( TOKEN_ADD_ASSIGN )){
      Match();
      return ADD;
   }
   else if (Check( TOKEN_SUB_ASSIGN )){
      Match();
      return SUB;
   }
   else Error( assignment_op );

   return ERR;
}

void CParser::Assignment_expr( )
{
   PARSETRACE("CParser::Assignment_expr");
   if (m_pParserSet->First( log_or_expr, m_pNextToken->Type() )){
      Log_or_expr( );
      Assignment_expr2( );
   }
   else Error( assignment_expr );
}

void CParser::Assignment_expr2( )
{
   PARSETRACE("CParser::Assignment_expr2");
   if (m_pParserSet->First( assignment_op, m_pNextToken->Type() )){
      CInstruction* pInstruction = m_pIList->Retrieve();
      CToken* pToken = m_pFieldToken;
      m_pFieldToken = NULL;
      
      OpCode code = Assignment_op( );
      Log_or_expr( );
      AddInstruction( code, (CToken*)NULL, NULL );

      if (pToken != NULL){
         AddInstruction( LOAD, pToken, NULL );
         AddInstruction( FIELD, (CToken*)NULL, NULL );
      }

      AddInstruction( SAVE, pInstruction->m_pToken, NULL );
      Assignment_expr2( );
   }
   else if (m_pParserSet->Follow( assignment_expr2, m_pNextToken->Type() ))
   {
      m_pFieldToken = NULL;
   }
   else Error( assignment_expr2 );
}

void CParser::Const_expr( )
{
   PARSETRACE("CParser::Const_expr");
   if (m_pParserSet->First( log_or_expr, m_pNextToken->Type() )){
      Log_or_expr( );
   }
   else Error( const_expr );
}

void CParser::Log_or_expr( )
{
   PARSETRACE("CParser::Log_or_expr");
   if (m_pParserSet->First( log_and_expr, m_pNextToken->Type() )){
      Log_and_expr( );
      Log_or_expr2( );
   }
   else Error( log_or_expr );
}

void CParser::Log_or_expr2( )
{
   PARSETRACE("CParser::Log_or_expr2");
   if (Check( TOKEN_OR_OP )){
      Match();
      Log_and_expr( );
      AddInstruction( OR, (CToken*)NULL, NULL );
      Log_or_expr2( );
   }
   else if (m_pParserSet->Follow( log_or_expr2, m_pNextToken->Type() )){}
   else Error( log_or_expr2 );
}

void CParser::Log_and_expr( )
{
   PARSETRACE("CParser::Log_and_expr");
   if (m_pParserSet->First( equal_expr, m_pNextToken->Type() )){
      Equal_expr( );
      Log_and_expr2( );
   }
   else Error( log_and_expr );
}

void CParser::Log_and_expr2( )
{
   PARSETRACE("CParser::Log_and_expr2");
   if (Check( TOKEN_AND_OP )){
      Match();
      Equal_expr( );
      AddInstruction( AND, (CToken*)NULL, NULL );
      Log_and_expr2( );
   }
   else if (m_pParserSet->Follow( log_and_expr2, m_pNextToken->Type() )){}
   else Error( log_and_expr2 );
}

OpCode CParser::Eq_op( )
{
   PARSETRACE("CParser::Eq_op");
   if (Check( TOKEN_EQ_OP )){
      Match();
      return EQ;
   }
   else if (Check( TOKEN_NE_OP )){
      Match();
      return NE;
   }
   else Error( eq_op );

   return ERR;
}

void CParser::Equal_expr( )
{
   PARSETRACE("CParser::Equal_expr");
   if (m_pParserSet->First( rel_expr, m_pNextToken->Type() )){
      Rel_expr( );
      Equal_expr2( );
   }
   else Error( equal_expr );
}

void CParser::Equal_expr2( )
{
   PARSETRACE("CParser::Equal_expr2");
   if (m_pParserSet->First( eq_op, m_pNextToken->Type() )){
      OpCode code = Eq_op( );
      Rel_expr( );
      AddInstruction( code, (CToken*)NULL, NULL );
      Equal_expr2( );
   }
   else if (m_pParserSet->Follow( equal_expr2, m_pNextToken->Type() )){}
   else Error( equal_expr2 );
}

OpCode CParser::Rel_op( )
{
   PARSETRACE("CParser::Rel_op");
   if (Check( TOKEN_GE_OP )){
      Match();
      return GE;
   }
   else if (Check( TOKEN_LE_OP )){
      Match();
      return LE;
   }
   else if (Check( TOKEN_LT )){
      Match();
      return LT;
   }
   else if (Check( TOKEN_GT )){
      Match();
      return GT;
   }
   else Error( rel_op );

   return ERR;
}

void CParser::Rel_expr( )
{
   PARSETRACE("CParser::Rel_expr");
   if (m_pParserSet->First( add_expr, m_pNextToken->Type() )){
      Add_expr( );
      Rel_expr2( );
   }
   else Error( rel_expr );
}

void CParser::Rel_expr2( )
{
   PARSETRACE("CParser::Rel_expr2");
   if (m_pParserSet->First( rel_op, m_pNextToken->Type() )){
      OpCode code = Rel_op( );
      Add_expr( );
      AddInstruction( code, (CToken*)NULL, NULL );
      Rel_expr2( );
   }
   else if (m_pParserSet->Follow( rel_expr2, m_pNextToken->Type() )){}
   else Error( rel_expr2 );
}

OpCode CParser::Add_op( )
{
   PARSETRACE("CParser::Add_op");
   if (Check( TOKEN_ADD )){
      Match();
      return ADD;
   }
   else if (Check( TOKEN_SUB )){
      Match();
      return SUB;
   }
   else Error( add_op );

   return ERR;
}

void CParser::Add_expr( )
{
   PARSETRACE("CParser::Add_expr");
   if (m_pParserSet->First( mult_expr, m_pNextToken->Type() )){
      Mult_expr( );
      Add_expr2( );
   }
   else Error( add_expr );
}

void CParser::Add_expr2( )
{
   PARSETRACE("CParser::Add_expr2");
   if (m_pParserSet->First( add_op, m_pNextToken->Type() )){
      OpCode code = Add_op( );
      Mult_expr( );
      AddInstruction( code, (CToken*)NULL, NULL );
      Add_expr2( );
   }
   else if (m_pParserSet->Follow( add_expr2, m_pNextToken->Type() )){}
   else Error( add_expr2 );
}

OpCode CParser::Mult_op( )
{
   PARSETRACE("CParser::Mult_op");
   if (Check( TOKEN_MUL )){
      Match();
      return MUL;
   }
   else if (Check( TOKEN_DIV )){
      Match();
      return DIV;
   }
   else Error( mult_op );

   return ERR;
}

void CParser::Mult_expr( )
{
   PARSETRACE("CParser::Mult_expr");
   if (m_pParserSet->First( unary_expr, m_pNextToken->Type() )){
      Unary_expr( );
      Mult_expr2( );
   }
   else Error( mult_expr );
}

void CParser::Mult_expr2( )
{
   PARSETRACE("CParser::Mult_expr2");
   if (m_pParserSet->First( mult_op, m_pNextToken->Type() )){
      OpCode code = Mult_op( );
      Unary_expr( );
      AddInstruction( code, (CToken*)NULL, NULL );
      Mult_expr2( );
   }
   else if (m_pParserSet->Follow( mult_expr2, m_pNextToken->Type() )){}
   else Error( mult_expr2 );
}

void CParser::Unary_expr( )
{
   PARSETRACE("CParser::Unary_expr");
   if (m_pParserSet->First( postfix_expr, m_pNextToken->Type() )){
      Postfix_expr( );
   }
   else if (Check( TOKEN_INC_OP )){
      Match();
      Unary_expr( );
      AddInstruction( INC, (CToken*)NULL, NULL );
   }
   else if (Check( TOKEN_DEC_OP )){
      Match();
      Unary_expr( );
      AddInstruction( DEC, (CToken*)NULL, NULL );
   }
   else if (Check( TOKEN_ADD )){
      Match();
      Unary_expr( );
   }
   else if (Check( TOKEN_SUB )){
      Match();
      Unary_expr( );
      AddInstruction( NEG, (CToken*)NULL, NULL );
   }
   else if (Check( TOKEN_BOOLEAN_NOT )){
      Match();
      Unary_expr( );
      AddInstruction( NOT, (CToken*)NULL, NULL );
   }
   else Error( unary_expr );
}

void CParser::Postfix_expr( )
{
   PARSETRACE("CParser::Postfix_expr");
   if (m_pParserSet->First( primary_expr, m_pNextToken->Type() )){
      Primary_expr( );
      Postfix_expr2( );
   }
   else Error( postfix_expr );
}

void CParser::Postfix_expr2( )
{
   PARSETRACE("CParser::Postfix_expr2");
   if (Check( TOKEN_LPAREN )){
      //Remove the top instruction so we can get the arguments in first.
      CInstruction* pInstruction = m_pIList->Retrieve();
      m_pIList->Remove();

      Match();
      Arg_expr_list( );
      Check( TOKEN_RPAREN );
      Match();

      //Change the type of the instruction we removed from LOAD to CALL, create
      //a label for it, and add it back to the instruction list.
      Label pLabel = CreateLabel();
      pInstruction->m_OpCode = CALL;
      m_pIList->InsertAfter( pInstruction, pLabel );

      Postfix_expr2( );
   }
   else if (Check( TOKEN_FIELD )){
      //cache the token of the field source for assignment expressions.
      CInstruction* pInstruction = m_pIList->Retrieve();
      m_pFieldToken = pInstruction->m_pToken;

      AddInstruction( FIELD, m_pNextToken, NULL );
      Match();
      Check( TOKEN_IDENTIFIER );
      AddInstruction( LOAD, m_pNextToken, NULL );
      Match();
      Postfix_expr2( );
   }
   else if (Check( TOKEN_INC_OP )){
      CInstruction* pInstruction = m_pIList->Retrieve();
      AddInstruction( LOAD, pInstruction->m_pToken, NULL );
      AddInstruction( INC, m_pNextToken, NULL );
      Match();
      AddInstruction( SAVE, pInstruction->m_pToken, NULL );
      Postfix_expr2( );
   }
   else if (Check( TOKEN_DEC_OP )){
      CInstruction* pInstruction = m_pIList->Retrieve();
      AddInstruction( LOAD, pInstruction->m_pToken, NULL );
      AddInstruction( DEC, m_pNextToken, NULL );
      Match();
      AddInstruction( SAVE, pInstruction->m_pToken, NULL );
      Postfix_expr2( );
   }
   else if (m_pParserSet->Follow( postfix_expr2, m_pNextToken->Type() )){}
   else Error( postfix_expr2 );
}

void CParser::Arg_expr_list( )
{
   PARSETRACE("CParser::Arg_expr_list");
   if (m_pParserSet->First( assignment_expr, m_pNextToken->Type() )){
      Assignment_expr( );
      Arg_expr_list2( );
   }
   else if (m_pParserSet->Follow( arg_expr_list, m_pNextToken->Type() ))
   {
      //No arguments, so push a zero argument count onto the stack
      AddInstruction( CONSTDBL, L"0", NULL );
   }
   else Error( arg_expr_list );
}

void CParser::Arg_expr_list2( )
{
   PARSETRACE("CParser::Arg_expr_list2");

   //This is going to get us in trouble if we have function calls as arguments.
   static int argCount = 1;

   //We push the arguments onto the stack backwards so they come off right,
   //So back up one instruction before inserting.
   (*m_pIList)--;
   
   if (Check( TOKEN_COMMA )){
      Match();
      Assignment_expr( );
      argCount++;
      Arg_expr_list2( );
   }
   else if (m_pParserSet->Follow( arg_expr_list2, m_pNextToken->Type() ))
   {
      //Run back down the list to insert the argument count
      for (int i = 0; i < argCount; i++)
         (*m_pIList)++;

      WCHAR* pbuffer = new WCHAR[4];
      memset( pbuffer, '\0', 4 );
      swprintf( pbuffer, L"%d", argCount );
      AddInstruction( CONSTDBL, pbuffer, NULL );
   }
   else Error( arg_expr_list2 );
}

void CParser::Primary_expr( )
{
   PARSETRACE("CParser::Primary_expr");
   if (Check( TOKEN_IDENTIFIER )){
      AddInstruction( LOAD, m_pNextToken, NULL );
      Match();
   }
   else if (m_pParserSet->First( constant, m_pNextToken->Type() )){
      Constant( );
   }
   else if (Check( TOKEN_LPAREN )){
      Match();
      Expr( );
      Check( TOKEN_RPAREN );
      Match();
   }
   else Error( primary_expr );
}

void CParser::Constant( )
{
   PARSETRACE("CParser::Constant");
   if (Check( TOKEN_INTCONSTANT )){
      AddInstruction( CONSTDBL, m_pNextToken, NULL );
      Match();
   }
   else if (Check( TOKEN_FLOATCONSTANT )){
      AddInstruction( CONSTDBL, m_pNextToken, NULL );
      Match();
   }
   else if (Check( TOKEN_STRING_LITERAL )){
      AddInstruction( CONSTSTR, m_pNextToken, NULL );
      Match();
   }
   else Error( constant );
}

void CParser::Error( PRODUCTION offender )
{
   PARSETRACE("CParser::Error");

   //Report the offending token to the error handler, along with the production
   //it offended in.
   HandleCompileError( m_pNextToken, (ERRORVAL)offender );

   //The script is obviously not valid, but it's good to try and find all the
   //errors at one time.  Therefore go into Panic Mode error recovery -- keep 
   //grabbing tokens until we find one we can use
   while( (m_pNextToken->Type() != TOKEN_EOF) && 
      (!m_pParserSet->Follow( offender, m_pNextToken->Type() )))
      Match();

}
