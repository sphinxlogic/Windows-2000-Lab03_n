/*--

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999  Microsoft Corporation.  All rights reserved.

Module Name:

    klist.c

Abstract:

    Sample program that demonstrates how to retrieve 
    and/or purge Kerberos ticket information.

Author:

    David Mowers (davemo)   14-October-98

Revision History:

--*/


//
// Common include files.
//
#define UNICODE
#define _UNICODE

#include <windows.h>
#include <stdio.h>      
#include <stdlib.h>     
#include <conio.h>      
#define SECURITY_WIN32
#include <security.h>   
#include <ntsecapi.h>

#define INTERACTIVE_PURGE 1

#define SEC_SUCCESS(Status) ((Status) >= 0) 

VOID
InitUnicodeString(
    PUNICODE_STRING DestinationString,
    PCWSTR SourceString OPTIONAL
    );

VOID 
ShowLastError(
    LPSTR szAPI, 
    DWORD dwError
    );

VOID 
ShowNTError( 
    LPSTR szAPI, 
    NTSTATUS Status 
    );

BOOL 
PackageConnectLookup(
    HANDLE *pLogonHandle, 
    ULONG *pPackageId
    );

DWORD 
ShowTickets(
    HANDLE LogonHandle,
    ULONG PackageId,
    DWORD dwMode
    );

DWORD 
ShowTgt(
    HANDLE LogonHandle,
    ULONG PackageId
    );

int 
wmain(
    int argc, 
    wchar_t  *argv[]
    )
{

    HANDLE LogonHandle = NULL;
    ULONG PackageId;
    
    if (argc < 2)
    {
        printf("Usage: %S <tickets | tgt | purge>\n",argv[0]);
        return FALSE;
    }

    //
    // Get the logon handle and package ID from the
    // Kerberos package
    //
    if(!PackageConnectLookup(&LogonHandle, &PackageId))
        return FALSE;

    if(!_wcsicmp(argv[1],L"tickets"))
    {
        ShowTickets(LogonHandle, PackageId, 0);
    }
    else if(!_wcsicmp(argv[1],L"tgt"))
    {
        ShowTgt(LogonHandle, PackageId);
    }
    else if(!_wcsicmp(argv[1],L"purge"))
    {
        ShowTickets(LogonHandle, PackageId, INTERACTIVE_PURGE);
    }
    else
    {
        printf("Usage: %S <tickets | tgt | purge>\n",argv[0]);
        return FALSE;
    }

    return TRUE;
    
}


VOID 
PrintTime(
    LPSTR Comment,
    TimeStamp ConvertTime
    )
{

    printf( "%s", Comment );

    //
    // If the time is infinite,
    //  just say so.
    //
    if ( ConvertTime.HighPart == 0x7FFFFFFF && ConvertTime.LowPart == 0xFFFFFFFF ) {
        printf( "Infinite\n" );

    //
    // Otherwise print it more clearly
    //
    } else {

        SYSTEMTIME SystemTime;
        FILETIME LocalFileTime;

        FileTimeToLocalFileTime(
            (PFILETIME) &ConvertTime,
            &LocalFileTime
            );
        FileTimeToSystemTime(
            &LocalFileTime,
            &SystemTime
            );

        printf( "%ld/%ld/%ld %ld:%2.2ld:%2.2ld\n",
                SystemTime.wMonth,
                SystemTime.wDay,
                SystemTime.wYear,
                SystemTime.wHour,
                SystemTime.wMinute,
                SystemTime.wSecond );
    }

}

VOID 
PrintEType(
    int etype
    )
{

    printf("      KerbTicket Encryption Type: ");

    switch (etype)
    {
        case KERB_ETYPE_NULL:
            printf("NULL CS\n");
            break;
        case KERB_ETYPE_DES_CBC_CRC:
            printf("Kerberos DES-CBC-CRC\n");
            break;
        case KERB_ETYPE_DES_CBC_MD5:
            printf("Kerberos DES-CBC-MD5\n");
            break;
        case KERB_ETYPE_RC4_MD4:
            printf("RSADSI RC4-MD4\n");
            break;
        case KERB_ETYPE_RC4_PLAIN2:
            printf("RSADSI RC4-PLAIN\n");
            break;
        case KERB_ETYPE_RC4_LM:
            printf("RSADSI RC4-LM\n");
            break;
        case KERB_ETYPE_DES_PLAIN:
            printf("Kerberos DES-Plain\n");
            break;
        case KERB_ETYPE_RC4_HMAC_NT:
            printf("RSADSI RC4-HMAC(NT)\n");
            break;
        case KERB_ETYPE_RC4_PLAIN:
            printf("RSADSI RC4\n");
            break;
        case KERB_ETYPE_RC4_HMAC_NT_EXP:
            printf("RSADSI RC4-HMAC(NT)(Export)\n");
            break;
        case KERB_ETYPE_RC4_PLAIN_EXP:
            printf("RSADSI RC4(Export)\n");
            break;
        case KERB_ETYPE_RC4_HMAC_OLD:
            printf("RSADSI RC4-HMAC(Old)\n");
            break;
        default:
            printf("Unknown (%d)\n",etype);
            break;
    }
}

BOOL 
PackageConnectLookup(
    HANDLE *pLogonHandle, 
    ULONG *pPackageId
    )
{
    LSA_STRING Name;
    NTSTATUS Status;

    Status = LsaConnectUntrusted(
                pLogonHandle
                );

    if (!SEC_SUCCESS(Status))
    {
        ShowNTError("LsaConnectUntrusted", Status);
        return FALSE;
    }

    Name.Buffer = MICROSOFT_KERBEROS_NAME_A;
    Name.Length = strlen(Name.Buffer);
    Name.MaximumLength = Name.Length + 1;

    Status = LsaLookupAuthenticationPackage(
                *pLogonHandle,
                &Name,
                pPackageId
                );

    if (!SEC_SUCCESS(Status))
    {
        ShowNTError("LsaLookupAuthenticationPackage", Status);
        return FALSE;
    }

    return TRUE;

}

BOOL 
PurgeTicket(
    HANDLE LogonHandle,
    ULONG PackageId,
    LPWSTR Server, 
    DWORD  cbServer,
    LPWSTR Realm,
    DWORD  cbRealm
    )
{
    NTSTATUS Status;
    PVOID Response;
    ULONG ResponseSize;
    NTSTATUS SubStatus=0;

    PKERB_PURGE_TKT_CACHE_REQUEST pCacheRequest = NULL;

    pCacheRequest = (PKERB_PURGE_TKT_CACHE_REQUEST)
        LocalAlloc(LMEM_ZEROINIT, 
        cbServer + cbRealm + sizeof(KERB_PURGE_TKT_CACHE_REQUEST));

    pCacheRequest->MessageType = KerbPurgeTicketCacheMessage;
    pCacheRequest->LogonId.LowPart = 0;
    pCacheRequest->LogonId.HighPart = 0;

    CopyMemory((LPBYTE)pCacheRequest+sizeof(KERB_PURGE_TKT_CACHE_REQUEST),
        Server,cbServer);
    CopyMemory((LPBYTE)pCacheRequest+sizeof(KERB_PURGE_TKT_CACHE_REQUEST)+cbServer,
        Realm,cbRealm);

    pCacheRequest->ServerName.Buffer = 
        (LPWSTR)((LPBYTE)pCacheRequest+sizeof(KERB_PURGE_TKT_CACHE_REQUEST));
    
    pCacheRequest->ServerName.Length = 
        (unsigned short)cbServer;
    
    pCacheRequest->ServerName.MaximumLength = 
        (unsigned short)cbServer;
    
    pCacheRequest->RealmName.Buffer = 
        (LPWSTR)((LPBYTE)pCacheRequest+sizeof(KERB_PURGE_TKT_CACHE_REQUEST)+cbServer);
    
    pCacheRequest->RealmName.Length = 
        (unsigned short)cbRealm;
    
    pCacheRequest->RealmName.MaximumLength = 
        (unsigned short)cbRealm;

    printf("\tDeleting ticket: \n");
    printf("\t   ServerName = %wZ (cb=%lu)\n",&pCacheRequest->ServerName,cbServer);
    printf("\t   RealmName  = %wZ (cb=%lu)\n",&pCacheRequest->RealmName,cbRealm);

    printf("Submit Buffer size = %lu\n", 
        sizeof(KERB_PURGE_TKT_CACHE_REQUEST)+cbServer+cbRealm);

    Status = LsaCallAuthenticationPackage(
                LogonHandle,
                PackageId,
                pCacheRequest,
                sizeof(KERB_PURGE_TKT_CACHE_REQUEST)+cbServer+cbRealm,
                &Response,
                &ResponseSize,
                &SubStatus
                );

    if (!SEC_SUCCESS(Status) || !SEC_SUCCESS(Status))
    {
        ShowNTError("LsaCallAuthenticationPackage(purge)", Status);
        printf("Substatus: 0x%x\n",SubStatus);
        ShowNTError("LsaCallAuthenticationPackage(purge SubStatus)", SubStatus);
        return FALSE;
    }
    else 
    {
        printf("\tTicket purged!\n");
        return TRUE;
    }

}


DWORD 
ShowTickets(
    HANDLE LogonHandle,
    ULONG PackageId,
    DWORD dwMode
    )
{
    NTSTATUS Status;
    KERB_QUERY_TKT_CACHE_REQUEST CacheRequest;
    PKERB_QUERY_TKT_CACHE_RESPONSE CacheResponse = NULL;
    ULONG ResponseSize;
    NTSTATUS SubStatus;
    ULONG Index;
    BOOLEAN Success = FALSE;


    CacheRequest.MessageType = KerbQueryTicketCacheMessage;
    CacheRequest.LogonId.LowPart = 0;
    CacheRequest.LogonId.HighPart = 0;

    Status = LsaCallAuthenticationPackage(
                LogonHandle,
                PackageId,
                &CacheRequest,
                sizeof(CacheRequest),
                (PVOID *) &CacheResponse,
                &ResponseSize,
                &SubStatus
                );
    if (!SEC_SUCCESS(Status) || !SEC_SUCCESS(SubStatus))
    {
        ShowNTError("LsaCallAuthenticationPackage", Status);
        printf("Substatus: 0x%x\n",SubStatus);
    }
    else
    {
        printf("\nCached Tickets: (%lu)\n", CacheResponse->CountOfTickets);
        for (Index = 0; Index < CacheResponse->CountOfTickets ; Index++ )
        {
            printf("\n   Server: %wZ@%wZ\n",
                &CacheResponse->Tickets[Index].ServerName,
                &CacheResponse->Tickets[Index].RealmName);
            PrintEType(CacheResponse->Tickets[Index].EncryptionType);
            PrintTime("      End Time: ",CacheResponse->Tickets[Index].EndTime);
            PrintTime("      Renew Time: ",CacheResponse->Tickets[Index].RenewTime);
            printf("\n");

            if(dwMode == INTERACTIVE_PURGE)
            {
                printf("Purge? (y/n) : ");
                if(_getche() == 'y')
                {
                    printf("\n");
                    PurgeTicket( 
                        LogonHandle,
                        PackageId,
                        CacheResponse->Tickets[Index].ServerName.Buffer,
                        CacheResponse->Tickets[Index].ServerName.Length,
                        CacheResponse->Tickets[Index].RealmName.Buffer,
                        CacheResponse->Tickets[Index].RealmName.Length
                        );
                }
                else
                    printf("\n\n");

            }
        }

        Success = TRUE;
    }

    if (LogonHandle != NULL)
    {
        LsaDeregisterLogonProcess(LogonHandle);
    }

    if (CacheResponse != NULL)
    {
        LsaFreeReturnBuffer(CacheResponse);
    }

    return Success;
}

DWORD 
ShowTgt(
    HANDLE LogonHandle,
    ULONG PackageId
    )
{
    NTSTATUS Status;
    KERB_QUERY_TKT_CACHE_REQUEST CacheRequest;
	PKERB_RETRIEVE_TKT_RESPONSE TicketEntry = NULL;
    PKERB_EXTERNAL_TICKET Ticket;
    ULONG ResponseSize;
    NTSTATUS SubStatus;
    BOOLEAN Trusted = TRUE;
    BOOLEAN Success = FALSE;

    WCHAR buffer[128];

    CacheRequest.MessageType = KerbRetrieveTicketMessage;
    CacheRequest.LogonId.LowPart = 0;
    CacheRequest.LogonId.HighPart = 0;

    Status = LsaCallAuthenticationPackage(
                LogonHandle,
                PackageId,
                &CacheRequest,
                sizeof(CacheRequest),
                (PVOID *) &TicketEntry,
                &ResponseSize,
                &SubStatus
                );

    if (!SEC_SUCCESS(Status) || !SEC_SUCCESS(SubStatus))
    {
        ShowNTError("LsaCallAuthenticationPackage", Status);
        printf("Substatus: 0x%x\n",SubStatus);
    }
    else
    {
        Ticket = &(TicketEntry->Ticket);

        printf("\nCached TGT:\n\n");

        printf("ServiceName: %wZ\n", Ticket->ServiceName->Names);

        printf("TargetName: %wZ\n", Ticket->TargetName->Names);

        printf("FullServiceName: %wZ\n", Ticket->ClientName->Names);
        
        wcsncpy(buffer,Ticket->DomainName.Buffer,
            Ticket->DomainName.Length/sizeof(WCHAR));
        printf("DomainName: %S\n",buffer);
        
        wcsncpy(buffer,Ticket->TargetDomainName.Buffer,
            Ticket->TargetDomainName.Length/sizeof(WCHAR));
        printf("TargetDomainName: %S\n",buffer);

        wcsncpy(buffer,Ticket->AltTargetDomainName.Buffer,
            Ticket->AltTargetDomainName.Length/sizeof(WCHAR));
        printf("AltTargetDomainName: %S\n",buffer);

        printf("TicketFlags: 0x%x\n",Ticket->TicketFlags);
        PrintTime("KeyExpirationTime: ",Ticket->KeyExpirationTime);
        PrintTime("StartTime: ",Ticket->StartTime);
        PrintTime("EndTime: ",Ticket->EndTime);
        PrintTime("RenewUntil: ",Ticket->RenewUntil);
        PrintTime("TimeSkew: ",Ticket->TimeSkew);

        Success = TRUE;
        
        LsaFreeMemory(TicketEntry);
    }

    if (LogonHandle != NULL)
    {
        LsaDeregisterLogonProcess(LogonHandle);
    }

    if (TicketEntry != NULL)
    {
        LsaFreeReturnBuffer(TicketEntry);
    }

    return Success;
}


VOID
InitUnicodeString(
	PUNICODE_STRING DestinationString,
    PCWSTR SourceString OPTIONAL
    )
{
    ULONG Length;

    DestinationString->Buffer = (PWSTR)SourceString;
    if (SourceString != NULL) {
        Length = wcslen( SourceString ) * sizeof( WCHAR );
        DestinationString->Length = (USHORT)Length;
        DestinationString->MaximumLength = (USHORT)(Length + sizeof(UNICODE_NULL));
        }
    else {
        DestinationString->MaximumLength = 0;
        DestinationString->Length = 0;
        }
}

VOID 
ShowLastError(
	LPSTR szAPI, 
	DWORD dwError
	)
{
   #define MAX_MSG_SIZE 256

   static WCHAR szMsgBuf[MAX_MSG_SIZE];
   DWORD dwRes;

   printf("Error calling function %s: %lu\n", szAPI, dwError);

   dwRes = FormatMessage (
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      dwError,
      MAKELANGID (LANG_ENGLISH, SUBLANG_ENGLISH_US),
      szMsgBuf,
      MAX_MSG_SIZE,
      NULL);
   if (0 == dwRes) {
      printf("FormatMessage failed with %d\n", GetLastError());
      ExitProcess(EXIT_FAILURE);
   }

   printf("%S",szMsgBuf);
}

VOID 
ShowNTError( 
	LPSTR szAPI, 
	NTSTATUS Status 
	) 
{     
    // 
    // Convert the NTSTATUS to Winerror. Then call ShowLastError().     
    // 
    ShowLastError(szAPI, LsaNtStatusToWinError(Status));
} 
