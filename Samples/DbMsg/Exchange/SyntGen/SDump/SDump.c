// --sdump.c------------------------------------------------------------------
//
//  Dump an address template
//
//  Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#define HALT    0L
#define ERRX    1L
#define EMIT    2L
#define JUMP    3L
#define JNX     4L
#define JE      5L
#define EMITUPPER    6L

#define OP1_ADDR        0x80000000
#define OP2_ADDR        0x40000000

#define NUL     0
#define OP      1
#define ADR     2
#define PROP    3

int            i;
unsigned long  *buf;

void instruction(char *s, int type1, int type2, int type3);
void operand(int type, int oper);

// Main routine
void main(int argc, char *argv[])
   {
   int      n;
   fpos_t   pos;                      
   FILE     *fh;
   
   if (argc != 2) { printf("Microsoft Exchange Script Dump Version 1.0\n\nUsage: SDUMP FILE\n"); exit(1); }
   
   // Read the script into the buffer
   strupr(argv[1]);
   if ((fh = fopen(argv[1], "rb")) == NULL) { printf("File \"%s\" not found!\n", argv[1]); exit(2); }
   fseek(fh, 0l, SEEK_END);   // seek to eof
   fgetpos(fh, &pos);         // get file length
   fseek(fh, 0l, SEEK_SET);   // seek to beginning
   n = (int)pos;              // file size
   buf = malloc(n);
   fread(buf, 1, n, fh) / sizeof(unsigned long);
   fclose(fh);
   
   printf("Script Dump of %s\n\n", argv[1]);
   
   // Step through the script
   while(i<n)
      {
      printf("%04X: ", i* sizeof(unsigned long));
      switch(buf[i] & 0xFL)
         {
         case HALT:  instruction("HALT", NUL, NUL, NUL); i = n; break;
         case ERRX:  instruction("ERRX", NUL, NUL, NUL); break;
         case EMIT:  instruction("EMIT",  OP, NUL, NUL); break;
         case JUMP:  instruction("JUMP", ADR, NUL, NUL); break;
         case JNX:   instruction("JNX",   OP, ADR, NUL); break;
         case JE:    instruction("JE",    OP,  OP, ADR); break;
         case EMITUPPER:  instruction("EMTU",  OP, NUL, NUL); break;
         default:    instruction("<UNKNOWN>", NUL, NUL, NUL); break;
         }
      printf("\n");
      }
   }             

// Dump out an instruction
void instruction(char *s, int type1, int type2, int type3)
   {
   int   oper1, oper2;
   
   // Test the modifier bits
   if ((buf[i] & OP1_ADDR) == 0) oper1 = PROP; else oper1 = ADR;
   if ((buf[i] & OP2_ADDR) == 0) oper2 = PROP; else oper2 = ADR;

   printf("%-4s", s); i++;                   // Print the Instruction
   if (type1 != NUL) operand(type1, oper1);  // Print the first operand
   if (type2 != NUL) operand(type2, oper2);  // Print the second operand
   if (type3 != NUL) operand(type3, ADR);    // Print the third operand
   }

// Dump out an operand
void operand(int type, int oper)
   {
   // override the operand if the instruction type is an address
   if (type == ADR) oper = ADR;
   
   switch(oper)
      {
      case ADR:   
         if (type == ADR) printf(" %08lX", buf[i]); 
         else printf(" \"%s\"", (char *)buf + buf[i]);
         break;
         
      case PROP:  
         printf(" %04lX+%04lX", buf[i] >> 16, buf[i] & 0xFFFF); 
         break;
      }         
   i++;  // Increment the instruction pointer
   }
