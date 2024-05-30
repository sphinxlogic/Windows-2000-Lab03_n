/******************************************************************************\
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996-1999.  Microsoft Corporation.  All rights reserved.
\******************************************************************************/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wincrypt.h>

/*****************************************************************************/
void _cdecl main(void)
{
    HCRYPTPROV hProv;
    HCRYPTKEY hKey;
    CHAR szUserName[100];
    DWORD dwUserNameLen = 100;

    // Attempt to acquire a handle to the default key container.
    if(!CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, 0)) {
        // Some sort of error occured.

        // Create default key container.
        if(!CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
            printf("Error creating key container!\n");
            exit(1);
        }

        // Get name of default key container.
        if(!CryptGetProvParam(hProv, PP_CONTAINER, szUserName, &dwUserNameLen, 0)) {
            // Error getting key container name.
            szUserName[0] = 0;
        }

        printf("Create key container '%s'\n",szUserName);
    }

    // Attempt to get handle to signature key.
    if(!CryptGetUserKey(hProv, AT_SIGNATURE, &hKey)) {
        if(GetLastError() == NTE_NO_KEY) {
            // Create signature key pair.
            printf("Create signature key pair\n");

            if(!CryptGenKey(hProv,AT_SIGNATURE,0,&hKey)) {
                printf("Error %x during CryptGenKey!\n", GetLastError());
                exit(1);
            } else {
                CryptDestroyKey(hKey);
            }
        } else {
            printf("Error %x during CryptGetUserKey!\n", GetLastError());
            exit(1);
        }
    }

    // Attempt to get handle to exchange key.
    if(!CryptGetUserKey(hProv,AT_KEYEXCHANGE,&hKey)) {
        if(GetLastError()==NTE_NO_KEY) {
            // Create key exchange key pair.
            printf("Create key exchange key pair\n");

            if(!CryptGenKey(hProv,AT_KEYEXCHANGE,0,&hKey)) {
                printf("Error %x during CryptGenKey!\n", GetLastError());
                exit(1);
            } else {
                CryptDestroyKey(hKey);
            }
        } else {
            printf("Error %x during CryptGetUserKey!\n", GetLastError());
            exit(1);
        }
    }

    CryptReleaseContext(hProv,0);

    printf("OK\n");

    exit(0);
}
