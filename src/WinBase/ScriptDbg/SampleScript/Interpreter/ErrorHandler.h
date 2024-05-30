/******************************************************************************
*
*  File: ErrorHandler.h
*
*  Author:  Joel Alley
*
*  Date: November 14, 1998
*
*  Description:   This file contains the declaration of the error handling
*                 functions and classes for the interpreter.
*
*  Modifications:
******************************************************************************/
enum ERRORVAL { PARSER_START, PARSER_EXTERNAL_DECL, PARSER_DECL_SPEC, 
                PARSER_DECL, PARSER_FUNCDECL, PARSER_FUNCDECL1, 
                PARSER_INITIALIZER, PARSER_PARM_DECL, PARSER_PARAM_LIST, 
                PARSER_PARAM_LIST2, PARSER_DECL_LIST, PARSER_DECL_LIST2, 
                PARSER_STMT_LIST, PARSER_STMT_LIST2, PARSER_STMT, 
                PARSER_EXPR_STMT, PARSER_COMP_STMT, PARSER_COMP_STMT2, 
                PARSER_COMP_STMT3, PARSER_SELECT_STMT, PARSER_OPT_ELSE, 
                PARSER_ITER_STMT, PARSER_OPT_EXPR_STMT, PARSER_DEFER_EXPR_STMT, 
                PARSER_JUMP_STMT, PARSER_OPT_EXPR, PARSER_EXPR, 
                PARSER_ASSIGNMENT_OP, PARSER_ASSIGNMENT_EXPR, 
                PARSER_ASSIGNMENT_EXPR2, PARSER_COSNT_EXPR, PARSER_LOG_OR_EXPR, 
                PARSER_LOG_OR_EXPR2, PARSER_LOG_AND_EXPR, PARSER_LOG_AND_EXPR2, 
                PARSER_EQ_OP, PARSER_EQUAL_EXPR, PARSER_EQUAL_EXPR2, 
                PARSER_REL_OP, PARSER_REL_EXPR, PARSER_REL_EXPR2, PARSER_ADD_OP,
                PARSER_ADD_EXPR, PARSER_ADD_EXPR2, PARSER_MULT_OP, 
                PARSER_MULT_EXPR, PARSER_MULT_EXPR2, PARSER_UNARY_EXPR, 
                PARSER_POSTFIX_EXPR, PARSER_POSTFIX_EXPR2, PARSER_ARG_EXPR_LIST,
                PARSER_ARG_EXPR_LIST2, PARSER_PRIMARY_EXPR, PARSER_CONSTANT, 
                UNRECOGNIZED_CHARACTER, INVALID_REFERENCE, OBJECT_REQUIRED, 
                INVALID_METHOD, INVALID_INSTRUCTION, STACK_FAILURE
};

typedef void (*CompileErrorHandler)( CToken* pToken, ERRORVAL errorVal );
typedef void (*RuntimeErrorHandler)( CInstruction* pInstruction, ERRORVAL errorVal, 
                                    DebugResume* pInterpreter );
extern CompileErrorHandler HandleCompileError;
extern RuntimeErrorHandler HandleRuntimeError;

class CErrorHandler
{
public:
   //constructor
   CErrorHandler();
   //destructor
   ~CErrorHandler();

protected:

   //static variables
protected:
   static HINSTANCE m_ResourceHInst;

   //static member functions
public:
   static void HandleCompileError( CToken* pToken, ERRORVAL errorVal );
   static void HandleRuntimeError( CInstruction* pInstruction, ERRORVAL errorVal,
      DebugResume* pInterpreter);
   static void SetLocale( LCID newLCID );
};
