// --X400scr.c----------------------------------------------------------------
//
//  Generate script for X.400 address template
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

// From MAPITAGS.H
#define PR_MHS_COMMON_NAME                   PROP_TAG( PT_TSTRING,   0x3A0F)
#define PR_MHS_COMMON_NAME_W                 PROP_TAG( PT_UNICODE,   0x3A0F)
#define PR_MHS_COMMON_NAME_A                 PROP_TAG( PT_STRING8,   0x3A0F)

#define HALT    0L
#define ERRX    1L
#define EMIT    2L
#define JUMP    3L
#define JNX     4L
#define JE      5L

#define OP1_ADDR        0x80000000
#define OP2_ADDR        0x40000000

#define PR_GIVEN_NAME   PROP_TAG( PT_STRING8, 0x6701)
#define PR_SURNAME      PROP_TAG( PT_STRING8, 0x6702)
#define PR_INITIALS     PROP_TAG( PT_STRING8, 0x6703)
#define PR_GENERATION   PROP_TAG( PT_STRING8, 0x6704)
#define PR_COMMON_NAME  PROP_TAG( PT_STRING8, 0x6705)
#define PR_ORG          PROP_TAG( PT_STRING8, 0x6706)
#define PR_OU1          PROP_TAG( PT_STRING8, 0x6707)
#define PR_OU2          PROP_TAG( PT_STRING8, 0x6708)
#define PR_OU3          PROP_TAG( PT_STRING8, 0x6709)
#define PR_OU4          PROP_TAG( PT_STRING8, 0x670A)
#define PR_PRMD         PROP_TAG( PT_STRING8, 0x670B)
#define PR_ADMD         PROP_TAG( PT_STRING8, 0x670C)
#define PR_COUNTRY      PROP_TAG( PT_STRING8, 0x670D)
#define PR_DDAT1        PROP_TAG( PT_STRING8, 0x670E)
#define PR_DDAV1        PROP_TAG( PT_STRING8, 0x670F)
#define PR_DDAT2        PROP_TAG( PT_STRING8, 0x6710)
#define PR_DDAV2        PROP_TAG( PT_STRING8, 0x6711)
#define PR_DDAT3        PROP_TAG( PT_STRING8, 0x6712)
#define PR_DDAV3        PROP_TAG( PT_STRING8, 0x6713)
#define PR_DDAT4        PROP_TAG( PT_STRING8, 0x6714)
#define PR_DDAV4        PROP_TAG( PT_STRING8, 0x6715)
#define PR_NID          PROP_TAG( PT_STRING8, 0x6716)
#define PR_X121         PROP_TAG( PT_STRING8, 0x6717)
#define PR_TTY          PROP_TAG( PT_STRING8, 0x6718)
#define PR_TID          PROP_TAG( PT_STRING8, 0x6719)

unsigned long  inst[400];  // Instruction Array
int            i = 0;      // Array index
char           *p;         // Array pointer
unsigned long  dda;        // "dda:" offset
unsigned long  equals;     // "=" offset
unsigned long  semi;       // ";" offset
unsigned long  nul;        // "" offset

int   AddEMIT(unsigned long op);
void  AddText(int n, char *s);
int   AddDDAn(unsigned long typ, unsigned long val);
void  SetText(int n);

/*********************
Write out a script file.
*********************/

void main()
   {
   int               nG, nS, nI, nGQ, nCN, nO, nOU1, nOU2, nOU3, nOU4, nP, nA, nC;
   int               nDDA1, nDDA2, nDDA3, nDDA4;
   int               nNID, nX121, nTTY, nTID;
   FILE              *fOut;

   printf ("X.400 Address Template Script Generator\n");
   
   // Save the instructions
   nG    = AddEMIT(PR_GIVEN_NAME);
   nS    = AddEMIT(PR_SURNAME);
   nI    = AddEMIT(PR_INITIALS);
   nGQ   = AddEMIT(PR_GENERATION);
   nCN   = AddEMIT(PR_COMMON_NAME);
   nX121 = AddEMIT(PR_X121);
   nNID  = AddEMIT(PR_NID);
   nTTY  = AddEMIT(PR_TTY);
   nTID  = AddEMIT(PR_TID);
   nO    = AddEMIT(PR_ORG);
   nOU1  = AddEMIT(PR_OU1);
   nOU2  = AddEMIT(PR_OU2);
   nOU3  = AddEMIT(PR_OU3);
   nOU4  = AddEMIT(PR_OU4);
   nP    = AddEMIT(PR_PRMD);
   nA    = AddEMIT(PR_ADMD);
   nC    = AddEMIT(PR_COUNTRY);
   nDDA1 = AddDDAn(PR_DDAT1, PR_DDAV1);
   nDDA2 = AddDDAn(PR_DDAT2, PR_DDAV2);
   nDDA3 = AddDDAn(PR_DDAT3, PR_DDAV3);
   nDDA4 = AddDDAn(PR_DDAT4, PR_DDAV4);
   inst[i++] = HALT;

   // Save all the text
   dda = i * sizeof(unsigned long);    // Save the "dda:" terminator offset
   p = (char *)&inst[i];               // Set the string pointer
   p += (sprintf(p, "dda:") + 4) & ~3; // Copy the string
   i +=2;
   
   equals = i * sizeof(unsigned long); // Save the "=" offset
   p = (char *)&inst[i];               // Set the string pointer
   p += (sprintf(p, "=") + 4) & ~3;    // Copy the string
   i++;
   
   semi = i * sizeof(unsigned long);   // Save the ";" offset
   p = (char *)&inst[i];               // Set the string pointer
   p += (sprintf(p, ";") + 4) & ~3;    // Copy the string
   i++;
   
   nul = i * sizeof(unsigned long);    // Save the "" offset
   p = (char *)&inst[i];               // Set the string pointer
   p += (sprintf(p, "") + 4) & ~3;     // Copy the string

   AddText(nG,    "g=");
   AddText(nS,    "s=");
   AddText(nI,    "i=");
   AddText(nGQ,   "q=");
   AddText(nCN,   "cn=");
   AddText(nX121, "x.121=");
   AddText(nNID,  "n-id=");
   AddText(nTTY,  "t-ty=");
   AddText(nTID,  "t-id=");
   AddText(nO,    "o=");
   AddText(nOU1,  "ou1=");
   AddText(nOU2,  "ou2=");
   AddText(nOU3,  "ou3=");
   AddText(nOU4,  "ou4=");
   AddText(nP,    "p=");
   AddText(nA,    "a=");
   AddText(nC,    "c=");
   SetText(nDDA1);
   SetText(nDDA2);
   SetText(nDDA3);
   SetText(nDDA4);


   // Save the instructions to a file
   if( !(fOut = fopen( "x400scr.blt", "wb"))) { printf( "Can't create X400SCR.BLT\n"); return; }
   fwrite(inst, sizeof(char), p - (char *)inst, fOut);
   fclose(fOut);
   
   printf("Done\n");
   }

// *********************************************** Add a general EMIT set
int AddEMIT(unsigned long op)
   {
   int n;

   // Skip if the control is not dirty
   inst[i++] = JNX;                                // instruction op-code
   inst[i++] = op;                                 // property tag
   inst[i++] = (i + 11) * sizeof(unsigned long);   // jump address

#ifndef OLD
   // Skip if the data is null
   inst[i++] = JE | OP2_ADDR;                      // instruction op-code
   inst[i++] = op;                                 // property tag
   n = i++;                                        // save address -- literal string ("")
   inst[i++] = (i + 7) * sizeof(unsigned long);    // jump address
#else
   inst[i++] = JUMP;                               // jump
   inst[i++] = (i + 3) * sizeof(unsigned long);    // jump address
   n = i++;                                        // save address -- literal string ("")
   inst[i++] = 10L;
#endif
      
   // Write the tag string
   inst[i++] = EMIT | OP1_ADDR;                    // instruction op-code
   i++;                                            // literal string ("g=")
   
   // Write the control data
   inst[i++] = EMIT;                               // instruction op-code
   inst[i++] = op;                                 // property tag

   // Write the tag terminator
   inst[i++] = EMIT | OP1_ADDR;                    // instruction op-code
   i++;                                            // literal string (";")

   return(n);
   }

// *********************************** Add text and set the instruction offset
void  AddText(int n, char *s)
   {
   inst[n]   = nul;                 // Set the null string offset
   inst[n+3] = p - (char *)inst;    // Set the tag string offset
   inst[n+7] = semi;                // Set the semi-colon string offset
   p += (sprintf(p, s) + 4) & ~3;   // Append the string and adjust the pointer
   }

// ************************************************ Add a DDA EMIT set
int AddDDAn(unsigned long typ, unsigned long val)
   {
   int n;

   // JNZ instruction
   inst[i++] = JNX;                                // instruction op-code
   inst[i++] = typ;                                // skip if TYPE is empty
   inst[i++] = (i + 15) * sizeof(unsigned long);   // jump address

#ifndef OLD
   // Skip if the data is null
   inst[i++] = JE | OP2_ADDR;                      // instruction op-code
   inst[i++] = typ;                                // property tag
   n = i++;                                        // save offset -- literal string ("")
   inst[i++] = (i + 11) * sizeof(unsigned long);   // jump address
#else
   inst[i++] = JUMP;                               // jump
   inst[i++] = (i + 3) * sizeof(unsigned long);    // jump address
   n = i++;                                        // save address -- literal string ("")
   inst[i++] = 10L;
#endif

   // EMIT instruction for the "DDA:" tag
   inst[i++] = EMIT | OP1_ADDR;                    // instruction op-code
   i++;                                            // literal string ("dda:")
   
   // EMIT instruction for TYPE data
   inst[i++] = EMIT;                               // instruction op-code
   inst[i++] = typ;                                // property tag
   
   // EMIT instruction for the "="
   inst[i++] = EMIT | OP1_ADDR;                    // instruction op-code
   i++;                                            // literal string ("=")
   
   // EMIT instruction for VALUE data
   inst[i++] = EMIT;                               // instruction op-code
   inst[i++] = val;                                // property tag

   // EMIT instruction for ";"
   inst[i++] = EMIT | OP1_ADDR;                    // instruction op-code
   i++;                                            // literal string ("=")

   return(n);
   }

// ************************************************ Set DDA text
void  SetText(int n)
   {
   inst[n]     = nul;               // Set the "" offset
   inst[n+3]   = dda;               // Set the "dda:" offset
   inst[n+7]   = equals;            // Set the "=" offset
   inst[n+11]  = semi;              // Set the ";" offset
   }
   