/******************************************************************************
* 
*  File: CLexer.cpp
*
*  Author:  Joel Alley
*
*  Date: June 18, 1998
*
*  Description:   This file contains the definition of the CLexer which reads
*                 a stream of characters and parses it into tokens.  The lexer
*                 is implemented as a Finite-State-Automaton which consumes the
*                 character stream using a principle of maximal munch.
*
*  Modifications:
******************************************************************************/
#define CLEXER
#include "depends.h"

//MACROS
/******************************************************************************
*  CONSUMECHARACTER -- This macro inserts code to remove a character from the 
*  input stream and add it to the current token buffer.
******************************************************************************/
#define CONSUMECHARACTER \
   wcsncat( theTokenSource, m_curChar, 1); \
   m_curChar++; \
   m_theTextPosition.col++; \
   m_Offset++;

/******************************************************************************
*  MAKETOKEN(x) -- This macro inserts code to create a new CToken object of 
*  type x, using the current token position, and source.
******************************************************************************/
#define MAKETOKEN(x) \
   *theNextToken = new CToken( x, theTokenSource, theTokenPosition, \
   m_TokOffset, m_dwSourceContext );

//Character buffer for the tokens
WCHAR* theTokenSource = new WCHAR[MAX_TOKEN_LENGTH];
TEXTPOS theTokenPosition;

/******************************************************************************
*  getNextToken -- Thie method searches the input stream and returns the next 
*  token found within that stream, using the principle of maximal munch.  It
*  embodies the start state of the FSA.
*  
*  Parameters: theNextToken -- address of the next CToken found in the stream
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
STDMETHODIMP CLexer::getNextToken(CToken** theNextToken)
{
   //start a whitespace-eating loop
   for(;;){
      memset(theTokenSource, '\0', MAX_TOKEN_LENGTH * 2);
      theTokenPosition = m_theTextPosition;
      m_TokOffset = m_Offset;
      
      //Whenever we get a new token, we need to watch out for the end-of-input.
      //Otherwise, we could walk right off the end of the stream.
      if ( !wcsncmp( m_curChar, L"\0", 1)){   //A null character marks the end
         //of the stream
         MAKETOKEN( TOKEN_EOF );
         return S_OK;
      }
      
      //getNextToken eats whitespace
      //newline
      else if ( !wcsncmp( m_curChar, L"\n", 1)){
         //increment the line counter and reset the offset counter
         m_theTextPosition.col = 0;
         m_theTextPosition.row++;
         m_curChar++;
         m_Offset++;
      }
      
      //tab
      else if ( !wcsncmp( m_curChar, L"\t", 1)){
         //increment the offset counter by TABSIZE
         m_theTextPosition.col += TABSIZE;
         m_curChar++;
         m_Offset++;
      }
      
      //carriage return
      else if ( !wcsncmp( m_curChar, L"\r", 1)){
         //reset the offset counter to zero
         m_theTextPosition.col = 0;
         //increment the line counter
         m_theTextPosition.row++;
         m_curChar++;
         m_Offset++;
      }
      
      //line feed
      else if ( !wcsncmp( m_curChar, L"\f", 1)){
         //increment the line counter
         m_theTextPosition.row++;
         m_curChar++;
         m_Offset++;
      }
      
      //space
      else if ( !wcsncmp(m_curChar, L" ", 1)){
         //increment the offset counter
         m_theTextPosition.col++;
         m_curChar++;
         m_Offset++;
      }
      
      //an Identifier starts with an alphabetical character or underscore
      else if ((iswalpha( *m_curChar )) || ( !wcsncmp( m_curChar, L"_", 1))){ 
         return Identifier( theNextToken );
      }
      
      //a Number starts with a numerical character
      else if (iswdigit( *m_curChar )){
         return Number( theNextToken );
      }
      
      else if (!wcsncmp( m_curChar, L"\"", 1)){
         return StringLiteral( theNextToken );
      }
      
      else if (!wcsncmp( m_curChar, L"'", 1)){
         CONSUMECHARACTER;
         if (!wcsncmp( m_curChar, L"\\", 1)){
            CONSUMECHARACTER;
            CONSUMECHARACTER;
            CONSUMECHARACTER;
            MAKETOKEN( TOKEN_STRING_LITERAL );
            return S_OK;
         }
         CONSUMECHARACTER;
         if (!wcsncmp( m_curChar, L"'", 1)){
            CONSUMECHARACTER;
            MAKETOKEN( TOKEN_STRING_LITERAL );
            return S_OK;
         }
         else{
            CONSUMECHARACTER;
            CONSUMECHARACTER;
            MAKETOKEN( TOKEN_ERROR );
            return S_OK;
         }
      }
      
      //Before checking for comments
      else if ( !wcsncmp( m_curChar, L"/", 1)){
         CONSUMECHARACTER;      
         if ( !wcsncmp( m_curChar, L"/", 1)){
            Comment(COMMENT_SLASH);
         }
         else if ( !wcsncmp( m_curChar, L"*", 1)){
            Comment(COMMENT_STAR);
         }
         
         //Now complete the symbol scan for regular symbols.
         else if ( !wcsncmp( m_curChar, L"=", 1)){
            CONSUMECHARACTER;         
            MAKETOKEN( TOKEN_DIV_ASSIGN );
            return S_OK;
         }
         else{
            MAKETOKEN( TOKEN_DIV);
            return S_OK;
         }
      }
      
      //a Symbol starts with one of these characters
      else if (( !wcsncmp( m_curChar, L">", 1)) || ( !wcsncmp( m_curChar, L"<", 1))
         || ( !wcsncmp( m_curChar, L"+", 1)) || ( !wcsncmp( m_curChar, L"-", 1)) 
         || ( !wcsncmp( m_curChar, L"*", 1)) || ( !wcsncmp( m_curChar, L"/", 1)) 
         || ( !wcsncmp( m_curChar, L"%", 1)) || ( !wcsncmp( m_curChar, L"&", 1)) 
         || ( !wcsncmp( m_curChar, L"^", 1)) || ( !wcsncmp( m_curChar, L"|", 1))
         || ( !wcsncmp( m_curChar, L"=", 1)) || ( !wcsncmp( m_curChar, L"!", 1)) 
         || ( !wcsncmp( m_curChar, L";", 1)) || ( !wcsncmp( m_curChar, L"{", 1))
         || ( !wcsncmp( m_curChar, L"}", 1)) || ( !wcsncmp( m_curChar, L",", 1))
         || ( !wcsncmp( m_curChar, L":", 1)) || ( !wcsncmp( m_curChar, L"(", 1)) 
         || ( !wcsncmp( m_curChar, L")", 1)) || ( !wcsncmp( m_curChar, L"[", 1)) 
         || ( !wcsncmp( m_curChar, L"]", 1)) || ( !wcsncmp( m_curChar, L".", 1))
         || ( !wcsncmp( m_curChar, L"~", 1)) || ( !wcsncmp( m_curChar, L"?", 1)))
      {
         return Symbol( theNextToken );
      }
      
      //If we get here, we've hit a character we don't recognize
      else{
         //Consume the character so it can be sent to the error handler
         CONSUMECHARACTER;

         //Create an error token, and send it to the error handler
         MAKETOKEN( TOKEN_ERROR );
         HandleCompileError( *theNextToken, UNRECOGNIZED_CHARACTER );
      }
   }
}

/******************************************************************************
*  Identifier -- This method extracts an identifier from the stream, once it's
*  recognized as an identifier.  After it is extracted, this method determines
*  if the identifier is a keyword.
*  Parameters: theNextToken -- address of the next CToken found in the stream
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
STDMETHODIMP CLexer::Identifier(CToken** theNextToken)
{
   //copy the source that makes up this token
   //an identifier is a string of letters, digits and/or underscores
   do{
      CONSUMECHARACTER;
   }while ((iswalpha( *m_curChar )) || (iswdigit( *m_curChar )) || 
      ( !wcsncmp( m_curChar, L"_", 1)));
   
   //Check the Identifier against current keywords
   if (!wcscmp( theTokenSource, L"auto")){
      MAKETOKEN( TOKEN_AUTO );}
   else if (!wcscmp( theTokenSource, L"break")){
      MAKETOKEN( TOKEN_BREAK );}
   else if (!wcscmp( theTokenSource, L"case")){
      MAKETOKEN( TOKEN_CASE );}
   else if (!wcscmp( theTokenSource, L"char")){
      MAKETOKEN( TOKEN_CHAR );}
   else if (!wcscmp( theTokenSource, L"const")){
      MAKETOKEN( TOKEN_CONST );}
   else if (!wcscmp( theTokenSource, L"continue")){
      MAKETOKEN( TOKEN_CONTINUE );}
   else if (!wcscmp( theTokenSource, L"default")){
      MAKETOKEN( TOKEN_DEFAULT );}
   else if (!wcscmp( theTokenSource, L"do")){
      MAKETOKEN( TOKEN_DO );}
   else if (!wcscmp( theTokenSource, L"double")){
      MAKETOKEN( TOKEN_DOUBLE );}
   else if (!wcscmp( theTokenSource, L"else")){
      MAKETOKEN( TOKEN_ELSE );}
   else if (!wcscmp( theTokenSource, L"enum")){
      MAKETOKEN( TOKEN_ENUM );}
   else if (!wcscmp( theTokenSource, L"extern")){
      MAKETOKEN( TOKEN_EXTERN );}
   else if (!wcscmp( theTokenSource, L"float")){
      MAKETOKEN( TOKEN_FLOAT );}
   else if (!wcscmp( theTokenSource, L"for")){
      MAKETOKEN( TOKEN_FOR );}
   else if (!wcscmp( theTokenSource, L"goto")){
      MAKETOKEN( TOKEN_GOTO );}
   else if (!wcscmp( theTokenSource, L"if")){
      MAKETOKEN( TOKEN_IF );}
   else if (!wcscmp( theTokenSource, L"int")){
      MAKETOKEN( TOKEN_INT );}
   else if (!wcscmp( theTokenSource, L"long")){
      MAKETOKEN( TOKEN_LONG );}
   else if (!wcscmp( theTokenSource, L"register")){
      MAKETOKEN( TOKEN_REGISTER );}
   else if (!wcscmp( theTokenSource, L"return")){
      MAKETOKEN( TOKEN_RETURN );}
   else if (!wcscmp( theTokenSource, L"short")){
      MAKETOKEN( TOKEN_SHORT );}
   else if (!wcscmp( theTokenSource, L"signed")){
      MAKETOKEN( TOKEN_SIGNED );}
   else if (!wcscmp( theTokenSource, L"sizeof")){
      MAKETOKEN( TOKEN_SIZEOF );}
   else if (!wcscmp( theTokenSource, L"static")){
      MAKETOKEN( TOKEN_STATIC );}
   else if (!wcscmp( theTokenSource, L"struct")){
      MAKETOKEN( TOKEN_STRUCT );}
   else if (!wcscmp( theTokenSource, L"switch")){
      MAKETOKEN( TOKEN_SWITCH );}
   else if (!wcscmp( theTokenSource, L"typedef")){
      MAKETOKEN( TOKEN_TYPEDEF );}
   else if (!wcscmp( theTokenSource, L"union")){
      MAKETOKEN( TOKEN_UNION );}
   else if (!wcscmp( theTokenSource, L"unsigned")){
      MAKETOKEN( TOKEN_UNSIGNED );}
   else if (!wcscmp( theTokenSource, L"void")){
      MAKETOKEN( TOKEN_VOID );}
   else if (!wcscmp( theTokenSource, L"volatile")){
      MAKETOKEN( TOKEN_VOLATILE );}
   else if (!wcscmp( theTokenSource, L"while")){
      MAKETOKEN( TOKEN_WHILE );}
   else{
      MAKETOKEN( TOKEN_IDENTIFIER );}
   
   return S_OK;
}

/******************************************************************************
*  Number -- This method extracts a numerical constant from the stream.  It
*  only extracts the digits that make up the number.  No conversion from string
*  to numeral is performed here.
*  Parameters: theNextToken -- address of the next CToken found in the stream
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
STDMETHODIMP CLexer::Number(CToken** theNextToken)
{
   //copy the source that makes up this token
   //a constant is one of these:
   
   //0[xX][a-fA-F0-9]+{u|U|l|L}
   //0{D}+{u|U|l|L}
   if (( !wcsncmp( m_curChar, L"0X", 2)) || ( !wcsncmp( m_curChar, L"0x", 2))){
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      while ((iswdigit( *m_curChar )) || ( !wcsncmp( m_curChar, L"a", 1)) || 
         ( !wcsncmp( m_curChar, L"A", 1)) || ( !wcsncmp( m_curChar, L"b", 1)) ||
         ( !wcsncmp( m_curChar, L"B", 1)) || ( !wcsncmp( m_curChar, L"c", 1)) ||
         ( !wcsncmp( m_curChar, L"C", 1)) || ( !wcsncmp( m_curChar, L"d", 1)) ||
         ( !wcsncmp( m_curChar, L"D", 1)) || ( !wcsncmp( m_curChar, L"e", 1)) ||
         ( !wcsncmp( m_curChar, L"E", 1)) || ( !wcsncmp( m_curChar, L"f", 1)) ||
         ( !wcsncmp( m_curChar, L"F", 1)))
      {
         CONSUMECHARACTER;
      }
      
      if (( !wcsncmp( m_curChar, L"u", 1)) || ( !wcsncmp( m_curChar, L"U", 1)) || 
         ( !wcsncmp( m_curChar, L"l", 1)) || ( !wcsncmp( m_curChar, L"L", 1)))
      {
         CONSUMECHARACTER;
      }
      
      MAKETOKEN( TOKEN_HEXCONSTANT );
   }
   else{
      while (iswdigit( *m_curChar ))
      {
         CONSUMECHARACTER;
      }
      
      if (( !wcsncmp( m_curChar, L"E", 1)) || ( !wcsncmp( m_curChar, L"e", 1)))
      {
         CONSUMECHARACTER; 
         while (iswdigit( *m_curChar ))
         {
            CONSUMECHARACTER;
         }
         
         if (( !wcsncmp( m_curChar, L"f", 1)) || ( !wcsncmp( m_curChar, L"F", 1)) || 
            ( !wcsncmp( m_curChar, L"l", 1)) || ( !wcsncmp( m_curChar, L"L", 1)))
         {
            CONSUMECHARACTER;
         }
         
         MAKETOKEN( TOKEN_FLOATCONSTANT );
      }
      else if ( !wcsncmp( m_curChar, L".", 1))
      {
         CONSUMECHARACTER;         
         while (iswdigit( *m_curChar ))
         {
            CONSUMECHARACTER;
         }
         
         if (( !wcsncmp( m_curChar, L"E", 1)) || ( !wcsncmp( m_curChar, L"e", 1)))
         {
            CONSUMECHARACTER;
            
            while (iswdigit( *m_curChar ))
            {
               CONSUMECHARACTER;
            }
            
            if (( !wcsncmp( m_curChar, L"f", 1)) ||
               ( !wcsncmp( m_curChar, L"F", 1)) || 
               ( !wcsncmp( m_curChar, L"l", 1)) || 
               ( !wcsncmp( m_curChar, L"L", 1)))
            {
               CONSUMECHARACTER;
            }            
         }
         MAKETOKEN( TOKEN_FLOATCONSTANT );
         
      }
      else{
         MAKETOKEN( TOKEN_INTCONSTANT );
      }
   }
   return S_OK;
}

/******************************************************************************
*  StringLiteral -- This method extracts a string literal from the character
*  stream.
*  Parameters: theNextToken -- address of the next CToken found in the stream
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
STDMETHODIMP CLexer::StringLiteral(CToken** theNextToken)
{
   //copy the source that makes up this token
   //an identifier is a string of letters, digits and/or underscores
   do{
      CONSUMECHARACTER;
   }while ( wcsncmp( m_curChar, L"\"", 1));
   
   //consume that last quote mark
   CONSUMECHARACTER;
   
   MAKETOKEN( TOKEN_STRING_LITERAL );
   return S_OK;
}
/******************************************************************************
*  Symbol -- This method extracts a symbol from the character stream.  For the 
*  purposes of lexing, comments are considered symbols.
*  Parameters: theNextToken -- address of the next CToken found in the stream
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
STDMETHODIMP CLexer::Symbol(CToken** theNextToken)
{
   //">>="
   if ( !wcsncmp( m_curChar, L">>=", 3))
   {
      CONSUMECHARACTER;      
      CONSUMECHARACTER;      
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_RIGHT_ASSIGN );
   }
   
   //">>"
   else if ( !wcsncmp( m_curChar, L">>", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_RIGHT_OP );
   }

   //">="
   else if ( !wcsncmp( m_curChar, L">=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_GE_OP );
   }

   //">"
   else if ( !wcsncmp( m_curChar, L">", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_GT );
   }
   
   //"<<="
   else if ( !wcsncmp( m_curChar, L"<<=", 3))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_LEFT_ASSIGN );
   }
   
   //"<<"
   else if ( !wcsncmp( m_curChar, L"<<", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_LEFT_OP );
   }
   
   //"<="
   else if ( !wcsncmp( m_curChar, L"<=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_LE_OP );
   }

   //"<"
   else if ( !wcsncmp( m_curChar, L"<", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_LT );
   }
   
   //"++"
   else if ( !wcsncmp( m_curChar, L"++", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_INC_OP );
   }
   
   //"+="
   else if ( !wcsncmp( m_curChar, L"+=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_ADD_ASSIGN );
   }
   
   //"+"
   else if ( !wcsncmp( m_curChar, L"+", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_ADD );
   }
   
   //"--"
   else if ( !wcsncmp( m_curChar, L"--", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_DEC_OP );
   }
   
   //"-="
   else if ( !wcsncmp( m_curChar, L"-=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_SUB_ASSIGN );
   }
   
   //"-"
   else if ( !wcsncmp( m_curChar, L"-", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_SUB );
   }
   
   //"*="
   else if ( !wcsncmp( m_curChar, L"*=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_MUL_ASSIGN );
   }
   
   //"*"
   else if ( !wcsncmp( m_curChar, L"*", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_MUL );
   }
   
   //"%="
   else if ( !wcsncmp( m_curChar, L"%=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_MOD_ASSIGN );
   }
   
   //"%"
   else if ( !wcsncmp( m_curChar, L"%", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_MOD );
   }
   
   //"&&"
   else if ( !wcsncmp( m_curChar, L"&&", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_AND_OP );
   }
   
   //"&="
   else if ( !wcsncmp( m_curChar, L"&=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_AND_ASSIGN );
   }
   
   //"&"
   else if ( !wcsncmp( m_curChar, L"&", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_BITWISE_AND );
   }
   
   //"^="
   else if ( !wcsncmp( m_curChar, L"^=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_XOR_ASSIGN );
   }
   
   //"^"
   else if ( !wcsncmp( m_curChar, L"^", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_XOR );
   }
   
   //"||"
   else if ( !wcsncmp( m_curChar, L"||", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_OR_OP );
   }
   
   //"|="
   else if ( !wcsncmp( m_curChar, L"|=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_OR_ASSIGN );
   }
   
    //"|"
   else if ( !wcsncmp( m_curChar, L"|", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_BITWISE_OR );
   }
   
   //"=="
   else if ( !wcsncmp( m_curChar, L"==", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_EQ_OP );
   }
   
  //"="
   else if ( !wcsncmp( m_curChar, L"=", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_ASSIGN );
   }
   
   //"!="
   else if ( !wcsncmp( m_curChar, L"!=", 2))
   {
      CONSUMECHARACTER;
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_NE_OP );
   }
   
   //"!"
   else if ( !wcsncmp( m_curChar, L"!", 1))
   {
      CONSUMECHARACTER;
      MAKETOKEN( TOKEN_BOOLEAN_NOT );
   }
   
   //";"
   else if ( !wcsncmp( m_curChar, L";", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_SEMICOLON);
   }
   
   //"{"
   else if ( !wcsncmp( m_curChar, L"{", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_LCURLY);
   }
   
   //"}"
   else if ( !wcsncmp( m_curChar, L"}", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_RCURLY);
   }
   
   //","
   else if ( !wcsncmp( m_curChar, L",", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_COMMA);
   }
   
   //":"
   else if ( !wcsncmp( m_curChar, L":", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_COLON);
   }
   
   //"("
   else if ( !wcsncmp( m_curChar, L"(", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_LPAREN);
   }
   
   //")"
   else if ( !wcsncmp( m_curChar, L")", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_RPAREN);
   }
   
   //"["
   else if ( !wcsncmp( m_curChar, L"[", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_LBRACKET);
   }
   
   //"]"
   else if ( !wcsncmp( m_curChar, L"]", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_RBRACKET);
   }
   
   //"."
   else if ( !wcsncmp( m_curChar, L".", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_FIELD);
   }
   
   //"~"
   else if ( !wcsncmp( m_curChar, L"~", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_BITWISE_NOT);
   }
   
   //"?"
   else if ( !wcsncmp( m_curChar, L"?", 1))
   {
      CONSUMECHARACTER;      
      MAKETOKEN( TOKEN_CONDITIONAL);
   }
   
   return S_OK;
}

/******************************************************************************
*  Comment -- This method extracts a symbol from the character stream.
*  Parameters: theNextToken -- address of the next CToken found in the stream
*  Returns: S_OK
*           E_FAIL
******************************************************************************/
STDMETHODIMP CLexer::Comment(COMMENT_TYPE theType)
{
   
   if (theType == COMMENT_SLASH){
      do{
         CONSUMECHARACTER;
         //break out if we hit a new line
         if (!wcsncmp( m_curChar, L"\n", 1)){
            m_theTextPosition.col = 0;
            m_theTextPosition.row++;
            break;
         }
         else if (!wcsncmp( m_curChar, L"\r", 1)){
            m_theTextPosition.col = 0;
            m_theTextPosition.row++;
            break;
         }
         else if (!wcsncmp( m_curChar, L"\f", 1)){
            m_theTextPosition.row++;
            break;
         }
      }while (wcsncmp( m_curChar, L"\0", 1));
   }
   else if (theType == COMMENT_STAR){
      //consume the '*' that gets this comment started
      CONSUMECHARACTER;
      
      //loop through the characters till we hit '*/'
      while (wcsncmp( m_curChar, L"\0", 1)){
         if (!wcsncmp( m_curChar, L"*/", 2)){
            CONSUMECHARACTER;
            CONSUMECHARACTER;
            break;
         }
         else if (!wcsncmp( m_curChar, L"\n", 1)){
            m_theTextPosition.col = 0;
            m_theTextPosition.row++;
         }
         else if (!wcsncmp( m_curChar, L"\r", 1)){
            m_theTextPosition.col = 0;
            m_theTextPosition.row++;
         }
         else if (!wcsncmp( m_curChar, L"\f", 1)){
            m_theTextPosition.row++;
         }
         CONSUMECHARACTER;
      };
   }
   
   return S_OK;
}