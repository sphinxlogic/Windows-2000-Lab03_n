/******************************************************************************
*
*  File: CParser.h
*
*  Author:  Joel Alley
*
*  Date: September 28, 1998
*
*  Description:   This file contains the declaration of a simple recursive
*                 descent parser which takes a stream of CTokens and generates
*                 a stream of self-executing, stack-based instructions which
*                 can be run by the CInterpreter class.
*
*  Modifications:
******************************************************************************/

class CParser{
public:
   //Constructor
   CParser( );
   //Destructor
   ~CParser();
   
   void ParseText( TList<CInstruction*>* pIList, LPCOLESTR scriptText,
      ULONG startingLineNumber, DWORD dwSourceContext );
   
   void ParseExpression( TList<CInstruction*>* pIList, LPCOLESTR scriptText,
      ULONG startingLineNumber, DWORD dwSourceContext );
   
protected:
   //Private data members
   CLexer* m_pLexer;                    //A pointer to this parser's lexer
   CParserSet* m_pParserSet;            //A pointer to this parsers' parserSet
   CToken* m_pNextToken;                //A pointer to the next token
   TList<CInstruction*>* m_pIList;       //A pointer to the instruction list
   long m_LabelCount;                   //A counter to track the number of labels
   TStack<Label> m_LabelStack;          //A stack of labels for use in jumps
   Label epiLabel;                      //A label which holds the target of returns
   CToken* m_pFieldToken;               //A pointer to the field source token

   //Private Methods
   virtual void AddInstruction( OpCode pCode, CToken* pToken = NULL, 
      Label label = NULL );
   virtual void AddInstruction( OpCode pCode, Label instrLabel, Label listLabel );
   Label CreateLabel( void );
   BOOL Check(MY_TOKEN_TYPE p_theType);
   void Match( void );

   void Start( );
   void External_decl( );
   void Decl_spec( );
   void Decl( );
   void FuncDecl( );
   void FuncDecl1( );
   void Initializer( );
   void Parm_decl( );
   void Param_list( );
   void Param_list2( );
   void Decl_list( );
   void Decl_list2( );
   void Stmt_list( );
   void Stmt_list2( );
   void Stmt( );
   void Expr_stmt( );
   void Comp_stmt( Label* pLabel );
   void Comp_stmt( );
   void Comp_stmt2( );
   void Comp_stmt3( );
   void Select_stmt( );
   void Opt_else( );
   void Iter_stmt( );
   void Opt_expr_stmt( );
   TList<CInstruction*>* Defer_expr_stmt( );
   void Jump_stmt( );
   void Opt_expr( );
   void Expr( );
   OpCode Assignment_op( );
   void Assignment_expr( );
   void Assignment_expr2( );
   void Const_expr( );
   void Log_or_expr( );
   void Log_or_expr2( );
   void Log_and_expr( );
   void Log_and_expr2( );
   OpCode Eq_op( );
   void Equal_expr( );
   void Equal_expr2( );
   OpCode Rel_op( );
   void Rel_expr( );
   void Rel_expr2( );
   OpCode Add_op( );
   void Add_expr( );
   void Add_expr2( );
   OpCode Mult_op( );
   void Mult_expr( );
   void Mult_expr2( );
   void Unary_expr( );
   void Postfix_expr( );
   void Postfix_expr2( );
   void Arg_expr_list( );
   void Arg_expr_list2( );
   void Primary_expr( );
   void Constant( );
   void Error( PRODUCTION offender );

   PRODUCTION LookupValue( char* theProduction )
{
      COMPAREPRODUCTION( start );
      COMPAREPRODUCTION( external_decl );
      COMPAREPRODUCTION( decl_spec );
      COMPAREPRODUCTION( decl );
      COMPAREPRODUCTION( funcDecl );
      COMPAREPRODUCTION( funcDecl1 );
      COMPAREPRODUCTION( initializer );
      COMPAREPRODUCTION( parm_decl );
      COMPAREPRODUCTION( param_list );
      COMPAREPRODUCTION( param_list2 );
      COMPAREPRODUCTION( decl_list );
      COMPAREPRODUCTION( decl_list2 );
      COMPAREPRODUCTION( stmt_list );
      COMPAREPRODUCTION( stmt_list2 );
      COMPAREPRODUCTION( stmt );
      COMPAREPRODUCTION( expr_stmt );
      COMPAREPRODUCTION( comp_stmt );
      COMPAREPRODUCTION( comp_stmt2 );
      COMPAREPRODUCTION( comp_stmt3 );
      COMPAREPRODUCTION( select_stmt );
      COMPAREPRODUCTION( opt_else );
      COMPAREPRODUCTION( iter_stmt );
      COMPAREPRODUCTION( opt_expr_stmt );
      COMPAREPRODUCTION( defer_expr_stmt );
      COMPAREPRODUCTION( jump_stmt );
      COMPAREPRODUCTION( opt_expr );
      COMPAREPRODUCTION( expr );
      COMPAREPRODUCTION( assignment_op );
      COMPAREPRODUCTION( assignment_expr );
      COMPAREPRODUCTION( assignment_expr2 );
      COMPAREPRODUCTION( const_expr );
      COMPAREPRODUCTION( log_or_expr );
      COMPAREPRODUCTION( log_or_expr2 );
      COMPAREPRODUCTION( log_and_expr );
      COMPAREPRODUCTION( log_and_expr2 );
      COMPAREPRODUCTION( eq_op );
      COMPAREPRODUCTION( equal_expr );
      COMPAREPRODUCTION( equal_expr2 );
      COMPAREPRODUCTION( rel_op );
      COMPAREPRODUCTION( rel_expr );
      COMPAREPRODUCTION( rel_expr2 );
      COMPAREPRODUCTION( add_op );
      COMPAREPRODUCTION( add_expr );
      COMPAREPRODUCTION( add_expr2 );
      COMPAREPRODUCTION( mult_op );
      COMPAREPRODUCTION( mult_expr );
      COMPAREPRODUCTION( mult_expr2 );
      COMPAREPRODUCTION( unary_expr );
      COMPAREPRODUCTION( postfix_expr );
      COMPAREPRODUCTION( postfix_expr2 );
      COMPAREPRODUCTION( arg_expr_list );
      COMPAREPRODUCTION( arg_expr_list2 );
      COMPAREPRODUCTION( primary_expr );
      COMPAREPRODUCTION( constant );
      COMPAREPRODUCTION( error );
      return (PRODUCTION)-1;
   }
};
