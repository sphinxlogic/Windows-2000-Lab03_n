/******************************************************************************
*
*  File: CInstruction.cpp
*
*  Author:  Joel Alley
*
*  Date: September 28, 1998
*
*  Description:   This file contains the definition of the CInstruction class,
*                 which encapsulates the instructions run by the CInterpreter
*                 class.
*
*  Modifications:
******************************************************************************/
#define CINSTRUCTION
#include "depends.h"

//Constructor
CInstruction::CInstruction(OpCode code, CToken* pToken )
{
   m_OpCode = code;
   m_pToken = pToken;
   m_Label = NULL;
   this->m_bImmediateCompleted = false;
}

CInstruction::CInstruction( OpCode code, Label label )
{
   m_OpCode = code;
   m_pToken = NULL;
   m_Label = label;
   this->m_bImmediateCompleted = false;
}

CInstruction::CInstruction()
{
   m_pToken = NULL;
   m_Label = NULL;
   this->m_bImmediateCompleted = false;
}

//Destructor
CInstruction::~CInstruction()
{
   if (m_pToken != NULL)
      delete m_pToken;
   if (m_Label != NULL)
      delete m_Label;
}

/******************************************************************************
*  toString -- This method outputs an LPCOLESTR containing a human-readable
*  representation of the instruction with the form "OpCode Label".
*  Parameters: none
*  Returns: an LPCOLESTR containing the human-readable representation.
******************************************************************************/
LPCOLESTR CInstruction::toString()
{
   //A buffer for the string representation
   unsigned short* strRep = NULL;

   //If the label isn't NULL, then we need to take it's length into account
   //when allocating the string buffer.
   int strLength = 15;
   if (m_Label != NULL)
      strLength += wcslen( m_Label );
   if (m_pToken != NULL)
      strLength += wcslen( m_pToken->Source() );

   strRep = new WCHAR[strLength];

   //initialize the buffer
   memset( strRep, '\0', strLength );

   switch( m_OpCode ){
   case CONSTSTR:
      wcscpy( strRep, L"CONSTSTR " );
      break;
   case CONSTDBL:
      wcscpy( strRep, L"CONSTDBL " );
      break;
   case LOAD:
      wcscpy( strRep, L"LOAD " );
      break;
   case SAVE:
      wcscpy( strRep, L"SAVE " );
      break;
   case INC: 
      wcscpy( strRep, L"INC " );
      break; 
   case DEC:
      wcscpy( strRep, L"DEC " );
      break;
   case FIELD:
      wcscpy( strRep, L"FIELD " );
      break; 
   case CALL:
      wcscpy( strRep, L"CALL " );
      break;  
   case POS:
      wcscpy( strRep, L"POS " );
      break;
   case NEG:
      wcscpy( strRep, L"NEG " );
      break;
   case NOT:
      wcscpy( strRep, L"NOT " );
      break;
   case MUL:
      wcscpy( strRep, L"MUL " );
      break;
   case DIV:
      wcscpy( strRep, L"DEV " );
      break;
   case ERR:
      wcscpy( strRep, L"ERR " );
      break; 
   case ADD:
      wcscpy( strRep, L"ADD " );
      break;
   case SUB: 
      wcscpy( strRep, L"SUB " );
      break;
   case JUMP:
      wcscpy( strRep, L"JUMP " );
      break;
   case GE:
      wcscpy( strRep, L"GE " );
      break; 
   case LE:
      wcscpy( strRep, L"LE " );
      break; 
   case LT:
      wcscpy( strRep, L"LT " );
      break;
   case GT:
      wcscpy( strRep, L"GT " );
      break;
   case EQ: 
      wcscpy( strRep, L"EQ " );
      break;
   case NE:
      wcscpy( strRep, L"NE " );
      break;
   case OR:
      wcscpy( strRep, L"OR " );
      break;
   case AND:
      wcscpy( strRep, L"AND " );
      break;
   case NOOP: 
      wcscpy( strRep, L"NOOP " );
      break;
   case PUSH: 
      wcscpy( strRep, L"PUSH " );
      break;
   case POP:
      wcscpy( strRep, L"POP " );
      break;
   case Branch_FALSE:
      wcscpy( strRep, L"Branch_FALSE " );
      break; 
   case Branch_TRUE: 
      wcscpy( strRep, L"Branch_TRUE " );
      break; 
   case DATA: 
      wcscpy( strRep, L"DATA " );
      break;
   case PARAM:
      wcscpy( strRep, L"PARAM " );
      break;
   case IMMEDIATE:
      wcscpy( strRep, L"IMMEDIATE " );
      break; 
   case DEFERRED: 
      wcscpy( strRep, L"DEFERRED " );
      break;
   case RET:
      wcscpy( strRep, L"RET " );
      break;
   case CHECKARG:
      wcscpy( strRep, L"CHECKARG " );
      break;
   case CLEAN:
      wcscpy( strRep, L"CLEAN " );
      break;
   default:
      break;
   }

   //If the label isn't NULL, then copy that into the buffer as well
   if (m_Label != NULL)
      wcscat( strRep, m_Label );
   if (m_pToken != NULL )
      wcscat( strRep, m_pToken->Source() );

   //Return the completed string.
   return strRep;
}
