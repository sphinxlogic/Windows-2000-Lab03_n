/******************************************************************************
*
*  File: CInstruction.h
*
*  Author:  Joel Alley
*
*  Date: September 28, 1998
*
*  Description:   This file contains the declaration of the CInstruction class,
*                 which encapsulates the instructions run by the CInterpreter
*                 class.
*
*  Modifications:
******************************************************************************/

enum OpCode{ CONSTSTR, CONSTDBL, LOAD, SAVE, INC, DEC, FIELD, CALL, POS, NEG, 
             NOT, MUL, DIV, ERR, ADD, SUB, JUMP, GE, LE, LT, GT, EQ, NE, OR, 
             AND, NOOP, PUSH, POP, Branch_FALSE, Branch_TRUE, DATA, PARAM, 
             IMMEDIATE, DEFERRED, RET, CHECKARG, CLEAN
};

typedef unsigned short* Label;

class CInstruction{
public:
   OpCode m_OpCode;
   CToken* m_pToken;
   Label m_Label;
   BOOL m_bImmediateCompleted;

   //Constructor
   CInstruction( OpCode code, CToken* pToken = NULL );
   CInstruction( OpCode code, Label pLabel );
   CInstruction();
   //Destructor
   ~CInstruction();

   //public methods
   LPCOLESTR toString();
};
