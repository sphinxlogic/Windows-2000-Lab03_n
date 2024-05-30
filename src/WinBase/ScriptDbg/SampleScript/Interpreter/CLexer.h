/******************************************************************************
* 
*  File: CLexer.h
*
*  Author:  Joel Alley
*
*  Date: June 18, 1998
*
*  Description:   This file contains the declaration of the CLexer which reads
*                 a stream of characters and parses it into tokens.  The lexer
*                 is implemented as a Finite-State-Automaton which consumes the
*                 character stream using a principle of maximal munch.
*                 This file also contains the declaration of the CToken class,
*                 which serves as the output of the Lexer, and maintains 
*                 important information like the source position and type of 
*                 the token.
*
*  Modifications: 11/4 -- Added Offset and Context to CToken for Active 
*                         Debugging and made appropriate adjustments to CLexer, 
*                         CParser, CInterpreter, and SampleScript.
******************************************************************************/
// define some values for use in CLexer
#define MAX_TOKEN_LENGTH 1024
#define MAX_LEXER_LENGTH 1024
#define TABSIZE 4

//enumerate the possible token types.  Some tokens here, such as LBRACKET, are
//never used.
enum MY_TOKEN_TYPE {
   TOKEN_IDENTIFIER, TOKEN_HEXCONSTANT, TOKEN_INTCONSTANT, TOKEN_FLOATCONSTANT, 
      TOKEN_STRING_LITERAL, TOKEN_SIZEOF, TOKEN_PTR_OP, TOKEN_INC_OP, 
      TOKEN_DEC_OP, TOKEN_LEFT_OP, TOKEN_RIGHT_OP, TOKEN_CONDITIONAL, 
      TOKEN_LE_OP, TOKEN_GE_OP, TOKEN_EQ_OP, TOKEN_NE_OP, TOKEN_AND_OP,
      TOKEN_OR_OP, TOKEN_MUL_ASSIGN, TOKEN_DIV_ASSIGN, TOKEN_MOD_ASSIGN,
      TOKEN_ADD_ASSIGN, TOKEN_SUB_ASSIGN, TOKEN_LEFT_ASSIGN, TOKEN_RIGHT_ASSIGN,
      TOKEN_AND_ASSIGN, TOKEN_XOR_ASSIGN, TOKEN_OR_ASSIGN, TOKEN_TYPE_NAME,
      TOKEN_TYPEDEF, TOKEN_EXTERN, TOKEN_STATIC, TOKEN_AUTO, TOKEN_REGISTER,
      TOKEN_CHAR, TOKEN_SHORT, TOKEN_INT, TOKEN_LONG, TOKEN_SIGNED,
      TOKEN_UNSIGNED, TOKEN_FLOAT, TOKEN_DOUBLE, TOKEN_CONST, TOKEN_VOLATILE,
      TOKEN_VOID, TOKEN_STRUCT, TOKEN_UNION, TOKEN_ENUM, TOKEN_ELLIPSIS,
      TOKEN_CASE, TOKEN_DEFAULT, TOKEN_IF, TOKEN_ELSE, TOKEN_SWITCH, 
      TOKEN_WHILE, TOKEN_DO, TOKEN_FOR, TOKEN_GOTO, TOKEN_CONTINUE, 
      TOKEN_BREAK, TOKEN_RETURN, TOKEN_SEMICOLON, TOKEN_LCURLY, TOKEN_RCURLY,
      TOKEN_COMMA, TOKEN_COLON, TOKEN_ASSIGN, TOKEN_LPAREN, TOKEN_RPAREN,
      TOKEN_LBRACKET, TOKEN_RBRACKET, TOKEN_FIELD, TOKEN_BITWISE_AND,
      TOKEN_BOOLEAN_NOT, TOKEN_BITWISE_NOT, TOKEN_ADD, TOKEN_SUB, TOKEN_MUL,
      TOKEN_DIV, TOKEN_MOD, TOKEN_LT, TOKEN_GT, TOKEN_XOR, TOKEN_BITWISE_OR, 
      TOKEN_ERROR, TOKEN_COMMENT, TOKEN_EOF, EPSILON
};

//define a structure to contain the position of each token
struct TEXTPOS{
   int row;
   int col;
};

/******************************************************************************
*  CToken -- This class encapsulates the tokens that CLexer creates.  It serves
*  to encapsulate the information for OOD purposes.
******************************************************************************/
class CToken {
private:
   //Data members
   MY_TOKEN_TYPE m_theType;
   LPCOLESTR m_theSource;
   TEXTPOS m_theTextPosition;
   ULONG m_charOffset;
   DWORD m_dwSourceContext;
   
public:
   //Constructor
   CToken( MY_TOKEN_TYPE theType, LPCOLESTR theSource, TEXTPOS theTextPosition,
      ULONG charOffset, DWORD dwSourceContext ): m_theType( theType ), 
      m_theTextPosition( theTextPosition ), m_charOffset( charOffset ), 
      m_dwSourceContext( dwSourceContext )
   {
      m_theSource = new WCHAR[ wcslen(theSource)];
      wcscpy( (unsigned short*)m_theSource, theSource );
   }
   
   CToken( const CToken& source )
   {
      m_theType = source.m_theType;
      m_theSource = new WCHAR[ wcslen( source.m_theSource)];
      wcscpy( (unsigned short*)m_theSource, source.m_theSource );
      m_theTextPosition = source.m_theTextPosition;
      m_charOffset = source.m_charOffset;
      m_dwSourceContext = source.m_dwSourceContext;
   }
   
   //Destructor
   ~CToken() 
   {;}
   
   //Read-only data member access
   //returns the MY_TOKEN_TYPE of this token
   MY_TOKEN_TYPE Type() { return m_theType; }
   
   //returns the source associated with this token
   LPCOLESTR Source() { return m_theSource; }
   
   //returns the text position of this token
   TEXTPOS Position() { return m_theTextPosition; }
   
   //returns the offset from the beginning of the script block
   ULONG Offset() { return m_charOffset; }
   
   //return the dwSourceContextCookie this instruction was created under.
   DWORD Context() { return m_dwSourceContext; }
};

//Enumerate the comment types for use in CLexer
enum COMMENT_TYPE {
   COMMENT_STAR,
   COMMENT_SLASH
};

/******************************************************************************
*  CLexer -- This class is created with a string of unicode characters and a 
*  starting position, which it uses to create a series of CTokens based on the 
*  script.  Its purpose is to break down the characters into "words" for the
*  parser.
******************************************************************************/
class CLexer {
private:
   //Data members
   LPCOLESTR m_theSource;
   TEXTPOS m_theTextPosition;
   ULONG m_Offset;
   ULONG m_TokOffset;
   DWORD m_dwSourceContext;
   WCHAR* m_curChar;

public:
   //Constructor
   CLexer( LPCOLESTR theSource, TEXTPOS theStartingPosition, 
      DWORD dwSourceContext ) : m_theSource( theSource ), m_theTextPosition( 
      theStartingPosition ), m_dwSourceContext( dwSourceContext )
      {
         m_curChar = (WCHAR*)m_theSource;
         m_Offset = 0;
         m_TokOffset = 0;
      }
      
      //Destructor
      ~CLexer() {;}
      
      //public member functions
      STDMETHODIMP getNextToken(CToken** theToken);
      
private:
   //private member functions
   STDMETHODIMP Comment(COMMENT_TYPE theType);
   STDMETHODIMP Identifier(CToken** theToken);
   STDMETHODIMP StringLiteral( CToken** theToken);
   STDMETHODIMP Number(CToken** theToken);
   STDMETHODIMP Symbol(CToken** theToken);
};
