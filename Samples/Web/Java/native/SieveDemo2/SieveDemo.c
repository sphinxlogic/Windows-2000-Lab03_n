//
//  SieveDemo.c
//
//  Copyright (c) 1997, Microsoft Corporation.  All rights reserved.
//

#include <stdarg.h>
#include <native.h>
#include "Sieve.h"

DWORD __cdecl RNIGetCompatibleVersion()
{
    return RNIVER;
}

long __cdecl Sieve_CountPrimes(struct HSieve *phThis, HArrayOfByte *phFlags)
{
    unsigned long count = 0;
    unsigned long i;

    for (i = 0; i < obj_length(phFlags); i++)
        (phFlags->body)[i] = 1;

    for (i = 2; i < obj_length(phFlags); i++)
    {
        if ((phFlags->body)[i] != 0)
        {
            unsigned long k;
            for (k = i + i; k < obj_length(phFlags); k += i)
                (phFlags->body)[k] = 0;

            count++;
        }
    }

    return count;
}
