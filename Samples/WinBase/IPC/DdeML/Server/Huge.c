
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright 1993 - 1998 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

/***************************************************************************
 *                                                                         *
 *  MODULE      : huge.c                                                   *
 *                                                                         *
 *  PURPOSE     : This contains functions useful for generating and        *
 *                verifying huge text data blocks.                         *
 *                                                                         *
 ***************************************************************************/

#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <ddeml.h>
#include "huge.h"

extern DWORD idInst;
#define BUFSZ   435

LONG lseed, lmult, ladd;
TCHAR szT[BUFSZ];

VOID SetMyRand(LONG seed, LONG mult, LONG add);
TCHAR MyRand(VOID);
BOOL RandTest(LONG length, LONG seed, LONG mult, LONG add);

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : SetMyRand()                                                *
 *                                                                          *
 *  PURPOSE    : Transfers random sequence generation variables to globals. *
 *                                                                          *
 ****************************************************************************/
VOID SetMyRand(
LONG seed,
LONG mult,
LONG add)
{
    lseed = seed;
    lmult = mult;
    ladd = add;
}


/****************************************************************************
 *                                                                          *
 *  FUNCTION   : MyRand()                                                   *
 *                                                                          *
 *  PURPOSE    : Generates the next random character in a sequence.         *
 *                                                                          *
 *  RETURNS    : the character generated                                    *
 *                                                                          *
 ****************************************************************************/
TCHAR MyRand()
{
    TCHAR c;

    lseed = lseed * lmult + ladd;
    c = (TCHAR)(LOWORD(lseed) ^ HIWORD(lseed));
    return((TCHAR)((c & (TCHAR)0x4f) + TEXT(' ')));   // 0x20 - 0x6f - all printable
}


/*
 * This function allocates and fills a HUGE data handle with a verifiable
 * text string.
 *
 * The format of the text string is:
 * "<length>=<seed>*<mult>+<add>;---data of length <length>---\0"
 * all values are stored in base 16 numbers.
 */
/****************************************************************************
 *                                                                          *
 *  FUNCTION   : CreateHugeDataHandle()                                     *
 *                                                                          *
 *  PURPOSE    : Generates a huge pseudo-random sequence of printable       *
 *               characters of the length given and places then into        *
 *               a DDEML data handle.                                       *
 *                                                                          *
 *  RETURNS    : The data handle created or 0 on failure.                   *
 *                                                                          *
 ****************************************************************************/
HDDEDATA CreateHugeDataHandle(
LONG length,
LONG seed,
LONG mult,
LONG add,
HSZ hszItem,
UINT wFmt,
WORD afCmd)
{
    register WORD cb;
    HDDEDATA hData;
    DWORD cbData;
    TCHAR *psz;

    wsprintf(szT, TEXT("%ld=%ld*%ld+%ld;"), length, seed, mult, add);
    cb = (_tcslen(szT) + 1) * sizeof(TCHAR);
    hData = DdeCreateDataHandle(idInst, (PBYTE)szT, cb, 0,
            hszItem, wFmt, afCmd);
    if (hData)
        hData = DdeAddData(hData, NULL, 0, cb + length);
    cbData = cb;
    SetMyRand(seed, mult, add);
    while (hData && (length > 0)) {
        psz = szT;
        cb = BUFSZ;
        while (cb--)
            *psz++ = MyRand();
        hData = DdeAddData(hData, (PBYTE)szT, min(length, BUFSZ), cbData);
        cbData += BUFSZ;
        length -= BUFSZ;
    }
    return(hData);
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : CheckHugeData()                                            *
 *                                                                          *
 *  PURPOSE    : Verifies the correctness of a pseudo-random character      *
 *               sequence generated by CreateHugeData.                      *
 *                                                                          *
 *  RETURNS    : TRUE if verified ok, FALSE otherwise.                      *
 *                                                                          *
 ****************************************************************************/
BOOL CheckHugeData(
HDDEDATA hData)
{
    LONG length;
    LONG seed;
    LONG mult;
    LONG add;
    TCHAR *psz;
    DWORD cbOff;
    WORD cb;

    if (!DdeGetData(hData, (PBYTE)szT, BUFSZ, 0))
        return(FALSE);
    szT[BUFSZ - 1] = TEXT('\0');
    psz = _tcschr(szT, TEXT(';'));
    if (psz == NULL)
        return(FALSE);
    *psz = TEXT('\0');

    if (_stscanf(szT, TEXT("%ld=%ld*%ld+%ld"), &length, &seed, &mult, &add) != 4)
        return(FALSE);

    if (length < 0)
        return(FALSE);
    SetMyRand(seed, mult, add);
    cbOff = (_tcslen(szT) + 1) * sizeof(TCHAR);
    while (length > 0) {
        DdeGetData(hData, (PBYTE)szT, BUFSZ, cbOff);
        psz = szT;
        cb = BUFSZ;
        while (length-- && cb--)
            if (*psz++ != MyRand())
                return(FALSE);
        cbOff += BUFSZ;
        length -= BUFSZ;
    }
    return(TRUE);
}

#if 0
/****************************************************************************
 *                                                                          *
 *  FUNCTION   : RandTest()                                                 *
 *                                                                          *
 *  PURPOSE    : Verifies the correctness of CreateHugeDataHandle() and     *
 *               CheckHugeData().                                           *
 *                                                                          *
 *  RETURNS    :                                                            *
 *                                                                          *
 ****************************************************************************/
BOOL RandTest(
LONG length,
LONG seed,
LONG mult,
LONG add)
{
    HDDEDATA hData;
    BOOL fSuccess;

    hData = CreateHugeDataHandle(length, seed, mult, add, 0, 1, 0);
    if (!hData)
        return(FALSE);
    fSuccess = CheckHugeData(hData);
    DdeFreeDataHandle(hData);
    return(fSuccess);
}
#endif
