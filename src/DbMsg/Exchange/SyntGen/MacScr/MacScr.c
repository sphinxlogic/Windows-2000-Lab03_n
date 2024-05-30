// --macscr.c-----------------------------------------------------------------
//
//  Generate script for Mac Mail address template
//
//  Copyright (C) Microsoft Corp. 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

/*****************************************
                Constants
*****************************************/
// From MAPIDEFS.H
#define PROP_TAG(ulPropType,ulPropID)  ((((unsigned long)(ulPropID))<<16)|((unsigned long)(ulPropType)))
#define PT_STRING8      ((unsigned long) 30) /* Null terminated 8-bit character string */
#define PT_UNICODE      ((unsigned long) 31) /* Null terminated Unicode string */
#define PT_SYSTIME      ((unsigned long) 64) /* FILETIME 64-bit int w/ number of 100ns periods since Jan 1,1601 */
#define PT_TSTRING         PT_UNICODE

#define HALT    0L
#define ERRX    1L
#define EMIT    2L
#define JUMP    3L
#define JNX     4L
#define JE      5L

#define OP1_ADDR        0x80000000
#define OP2_ADDR        0x40000000

#define PR_FIRST        PROP_TAG( PT_STRING8, 0x6701)
#define PR_LAST         PROP_TAG( PT_STRING8, 0x6702)

unsigned long  inst[400];  // Instruction Array
int            i = 0;      // Array index
char           *p;         // Array pointer
unsigned long  x;          // Terminator offset

/*********************
Write out a script file.
*********************/

void main()
   {
   int               s1;
   FILE              *fOut;

   printf ("Mac Mail Address Template Script Generator\n");
   
   // EMIT the First Half
   inst[i++] = EMIT;
   inst[i++] = PR_FIRST;

   // EMIT the Seperator
   inst[i++] = EMIT | OP1_ADDR;
   s1 = i++; // save the offset index

   // EMIT the Post Office Name
   inst[i++] = EMIT;
   inst[i++] = PR_LAST;

   // Done
   inst[i++] = HALT;

   x = i * sizeof(unsigned long);      // Save the seperator offset
   p = (char *)&inst[i];               // Set the string pointer
   p += (sprintf(p, "@") + 4) & ~3;    // Copy the seperator string

   inst[s1] = x;                       // Set the delimiter offset


   // Save the instructions to a file
   if( !(fOut = fopen( "macscr.blt", "wb"))) { printf( "Can't create MACSCR.BLT\n"); return; }
   fwrite(inst, sizeof(char), p - (char *)inst, fOut);
   fclose(fOut);
   
   printf("Done\n");
   }
   
