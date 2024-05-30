/*---------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.

TABLE.H
---------------------------------------------------------------------------*/


#ifndef TABLE_INCLUDED
#define TABLE_INCLUDED

typedef struct elem
{
   LPTSTR displayed;
   LPTSTR hidden;
   struct elem *next;
} ELEM;

typedef struct table
{
   ELEM *pCurrentFiles;
   INT iNumElems;
} *TABLE;

TABLE   TableNew                (VOID);
BOOL    TableFree               (TABLE);
BOOL    TableAdd                (TABLE, LPTSTR, LPTSTR);
BOOL    TableInsert             (TABLE, LPTSTR, LPTSTR, INT);
BOOL    TableRemove             (TABLE, INT);
BOOL    TableSort               (TABLE, INT compare(LPCTSTR, LPCTSTR));
BOOL    TableSend               (TABLE, HWND);
BOOL    TableGetHidden          (TABLE, INT, LPTSTR);
BOOL    SimplifyFileName        (LPTSTR, LPTSTR);
VOID    CheckHeap               (LPTSTR);
INT     CFilerlstrcmp           (LPCTSTR, LPCTSTR);
INT     GetSize                 (TABLE);
BOOL    ReplaceEscapeCharacters (LPTSTR, LPTSTR);
BOOL    TableFind               (TABLE, LPTSTR);

#endif
