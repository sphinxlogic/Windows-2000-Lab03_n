/******************************************************************************
*
*  File: CParserSet.h
*
*  Author:  Joel Alley
*
*  Date: July 2, 1998
*
*  Description:   This file contains a simple class which manages the FIRST and
*     FOLLOW sets for the parser.  It maintains a linked list of
*     the tokens which are members of each set.
*
*  Modifications: 1/27/99 -- incorporated First.txt and Follow.txt into 
*							 FirstFollow.h to avoid problem of having to have
*						     First.txt and Follow.txt in the same directory as
*							 SampleScript.dll.
******************************************************************************/
#include "FirstFollow.h"

#define COMPARETOKEN( x ) \
if (!strcmp( #x, theToken)) return x

class CParserSet{
private:
   //data members
   TList<MY_TOKEN_TYPE>* m_FirstSet;
   TList<MY_TOKEN_TYPE>* m_FollowSet;
   
public:
   //Constructor
   CParserSet()
   {
      //allocate the arrays for the first and follow sets
      m_FirstSet = new TList<MY_TOKEN_TYPE>[NUMPRODUCTIONS];
      m_FollowSet = new TList<MY_TOKEN_TYPE>[NUMPRODUCTIONS];
   }
   
   //Destructor
   ~CParserSet()
   {
      //release the arrays
      delete [] m_FirstSet;
      delete [] m_FollowSet;
   }

   BOOL BuildSets(char* firstFilePath, char* followFilePath)
   {
      char* buffer = NULL;
      char* bufferPointer = NULL;
      char seps[]   = " ,\t\n";
      char* token = NULL;
      int bufferSize = 0;
      
      for (int i = 0; i < NUMPRODUCTIONS; i++){
         //copy the firstStream for each production into a buffer.
         bufferSize = (strlen( firstStream[i] )) + 1;
         buffer = new char[ bufferSize ];
         memset( buffer, '\0', bufferSize );
         strcpy (buffer, firstStream[i] );
         bufferPointer = buffer;
         token = strtok(bufferPointer, seps);
         
         while(token != NULL){
            MY_TOKEN_TYPE value = LookupValue( token );
            if (!m_FirstSet[i].Includes( value ))
               m_FirstSet[i].InsertAfter( value );
            token = strtok(NULL, seps);
         }

         //delete the buffer.
         delete [] buffer;
      }
      
      for ( i = 0; i < NUMPRODUCTIONS; i++){
         //copy the firstStream for each production into a buffer.
         bufferSize = (strlen( followStream[i] )) + 1;
         buffer = new char[ bufferSize ];
         memset( buffer, '\0', bufferSize );
         strcpy (buffer, followStream[i] );
         bufferPointer = buffer;
         token = strtok(bufferPointer, seps);
         
         while(token != NULL){
            MY_TOKEN_TYPE value = LookupValue( token );
            if (!m_FollowSet[i].Includes( value ))
               m_FollowSet[i].InsertAfter( value );
            token = strtok(NULL, seps);
         }

         //delete the buffer
         delete [] buffer;
      }

      return true;
   }
   
   BOOL First(PRODUCTION theProduction, MY_TOKEN_TYPE theToken)
   {
      m_FirstSet[ theProduction ].Reset();
      return m_FirstSet[ theProduction ].Includes( theToken );
   }
   
   BOOL Follow(PRODUCTION theProduction, MY_TOKEN_TYPE theToken)
   {
      m_FirstSet[ theProduction ].Reset();
      return m_FollowSet[ theProduction ].Includes( theToken );
   }
   
private:
   MY_TOKEN_TYPE LookupValue( char* theToken)
   {
      COMPARETOKEN( TOKEN_IDENTIFIER ); COMPARETOKEN( TOKEN_HEXCONSTANT );
      COMPARETOKEN( TOKEN_INTCONSTANT ); COMPARETOKEN( TOKEN_FLOATCONSTANT );
      COMPARETOKEN( TOKEN_STRING_LITERAL ); COMPARETOKEN( TOKEN_SIZEOF );
      COMPARETOKEN( TOKEN_PTR_OP ); COMPARETOKEN( TOKEN_INC_OP );
      COMPARETOKEN( TOKEN_DEC_OP ); COMPARETOKEN( TOKEN_LEFT_OP );
      COMPARETOKEN( TOKEN_RIGHT_OP ); COMPARETOKEN( TOKEN_CONDITIONAL );
      COMPARETOKEN( TOKEN_LE_OP ); COMPARETOKEN( TOKEN_GE_OP );
      COMPARETOKEN( TOKEN_EQ_OP ); COMPARETOKEN( TOKEN_NE_OP );
      COMPARETOKEN( TOKEN_AND_OP ); COMPARETOKEN( TOKEN_OR_OP );
      COMPARETOKEN( TOKEN_MUL_ASSIGN ); COMPARETOKEN( TOKEN_DIV_ASSIGN );
      COMPARETOKEN( TOKEN_MOD_ASSIGN ); COMPARETOKEN( TOKEN_ADD_ASSIGN );
      COMPARETOKEN( TOKEN_SUB_ASSIGN ); COMPARETOKEN( TOKEN_LEFT_ASSIGN );
      COMPARETOKEN( TOKEN_RIGHT_ASSIGN ); COMPARETOKEN( TOKEN_AND_ASSIGN );
      COMPARETOKEN( TOKEN_XOR_ASSIGN ); COMPARETOKEN( TOKEN_OR_ASSIGN );
      COMPARETOKEN( TOKEN_TYPE_NAME ); COMPARETOKEN( TOKEN_TYPEDEF ); 
      COMPARETOKEN( TOKEN_EXTERN );  COMPARETOKEN( TOKEN_STATIC );
      COMPARETOKEN( TOKEN_AUTO ); COMPARETOKEN( TOKEN_REGISTER );
      COMPARETOKEN( TOKEN_CHAR );  COMPARETOKEN( TOKEN_SHORT );
      COMPARETOKEN( TOKEN_INT );  COMPARETOKEN( TOKEN_LONG );
      COMPARETOKEN( TOKEN_SIGNED ); COMPARETOKEN( TOKEN_UNSIGNED );
      COMPARETOKEN( TOKEN_FLOAT );  COMPARETOKEN( TOKEN_DOUBLE ); 
      COMPARETOKEN( TOKEN_CONST ); COMPARETOKEN( TOKEN_VOLATILE );
      COMPARETOKEN( TOKEN_VOID );  COMPARETOKEN( TOKEN_STRUCT ); 
      COMPARETOKEN( TOKEN_UNION ); COMPARETOKEN( TOKEN_ENUM ); 
      COMPARETOKEN( TOKEN_ELLIPSIS ); COMPARETOKEN( TOKEN_CASE ); 
      COMPARETOKEN( TOKEN_DEFAULT ); COMPARETOKEN( TOKEN_IF ); 
      COMPARETOKEN( TOKEN_ELSE ); COMPARETOKEN( TOKEN_SWITCH );
      COMPARETOKEN( TOKEN_WHILE ); COMPARETOKEN( TOKEN_DO ); 
      COMPARETOKEN( TOKEN_FOR );  COMPARETOKEN( TOKEN_GOTO ); 
      COMPARETOKEN( TOKEN_CONTINUE ); COMPARETOKEN( TOKEN_BREAK ); 
      COMPARETOKEN( TOKEN_RETURN ); COMPARETOKEN( TOKEN_SEMICOLON );
      COMPARETOKEN( TOKEN_LCURLY );  COMPARETOKEN( TOKEN_RCURLY ); 
      COMPARETOKEN( TOKEN_COMMA );  COMPARETOKEN( TOKEN_COLON ); 
      COMPARETOKEN( TOKEN_ASSIGN );  COMPARETOKEN( TOKEN_LPAREN ); 
      COMPARETOKEN( TOKEN_RPAREN );  COMPARETOKEN( TOKEN_LBRACKET );
      COMPARETOKEN( TOKEN_RBRACKET ); COMPARETOKEN( TOKEN_FIELD ); 
      COMPARETOKEN( TOKEN_BITWISE_AND ); COMPARETOKEN( TOKEN_BOOLEAN_NOT );
      COMPARETOKEN( TOKEN_BITWISE_NOT );  COMPARETOKEN( TOKEN_ADD ); 
      COMPARETOKEN( TOKEN_SUB ); COMPARETOKEN( TOKEN_MUL );
      COMPARETOKEN( TOKEN_DIV );  COMPARETOKEN( TOKEN_MOD ); 
      COMPARETOKEN( TOKEN_LT );  COMPARETOKEN( TOKEN_GT ); 
      COMPARETOKEN( TOKEN_XOR ); COMPARETOKEN( TOKEN_BITWISE_OR ); 
      COMPARETOKEN( TOKEN_ERROR );  COMPARETOKEN( TOKEN_COMMENT );
      COMPARETOKEN( TOKEN_EOF );
      
      //No token was found, so return -1
      return (MY_TOKEN_TYPE)-1;
   }
};