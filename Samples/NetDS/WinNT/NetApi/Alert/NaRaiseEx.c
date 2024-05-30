// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 1998
//
// FILE:          NARaiseEx.c
// DESCRIPTION:   Raising an administrators interrupting message
// LIBRAY:        NETAPI32.LIB
// PLATFORMS:     WINNT ONLY
// WRITTEN BY:    Gary Yukish
// DATE:          4/7/98
//

#define UNICODE
#include <windows.h>
#include <lm.h>
#include <stdio.h>
#include <time.h>

//Setup some default strings

#define PROGRAM_NAME    TEXT("NETALRT")
#define szComputerName  TEXT("\\\\GARYY3")
#define szUserName      TEXT("GARYY1")
#define szQueueName     TEXT("PQUEUE")
#define szDestName      TEXT("MYPRINTER")
#define szStatus        TEXT("OK")

//Setup some structure sizes
#define VAREDSIZE 312  //maximum size of the variable length message
char buff[VAREDSIZE];

int main()
{
   time_t             now;
   PADMIN_OTHER_INFO  pAdminInfo;
   PPRINT_OTHER_INFO  pPrintInfo;
   PUSER_OTHER_INFO   pUserInfo;
   TCHAR              *p;
   DWORD res; 

   time( &now );  //Get time for print time later
   
   //SendAdminAlert
   pAdminInfo = (PADMIN_OTHER_INFO) buff;    //Fill in specific ADMIN_OTHER_INFO data
   ZeroMemory(pAdminInfo, VAREDSIZE);
   pAdminInfo->alrtad_errcode = 2377;
   pAdminInfo->alrtad_numstrings = 1;
                                             //Macro to get location at end of structure
   p = (LPTSTR) ALERT_VAR_DATA(pAdminInfo);  //Fill in the strings that follow
   lstrcpy(p,TEXT("'C:\\MYLOG.TXT'"));       //the ADMIN_OTHER_INFO structure
                                             //Concatenate "numstrings" strings after
                                             //the structure
   
   res = NetAlertRaiseEx(ALERT_ADMIN_EVENT, pAdminInfo, 255 , TEXT("MYSERVICE"));
   printf("Admin Alert: %u\n", res);


     //SendPrintAlert
   pPrintInfo = (PPRINT_OTHER_INFO) buff;    //Fill in specific PRINT_OTHER_INFO data
   ZeroMemory(pPrintInfo, VAREDSIZE);        
   pPrintInfo->alrtpr_jobid = 5457;
   pPrintInfo->alrtpr_status = 0;
   pPrintInfo->alrtpr_submitted = now;
   pPrintInfo->alrtpr_size = 1000;
                                             //Fill in the strings that follow 
   p = (LPTSTR) ALERT_VAR_DATA(pPrintInfo);  //the PRINT_OTHER_INFO structure
   lstrcpy(p, szComputerName);               //ComputerName 
   p += lstrlen(p) + 1;
   lstrcpy(p, szUserName);                   //UserName
   p += lstrlen(p) + 1;
   lstrcpy(p, szQueueName);                  //Printer Queue Name
   p += lstrlen(p) + 1;
   lstrcpy(p, szDestName);                   //Printer Name (optional)
   p += lstrlen(p) + 1;
   lstrcpy(p, szStatus);                     //Status of Print job (optional)
   
   res = NetAlertRaiseEx(ALERT_PRINT_EVENT, pPrintInfo, VAREDSIZE, TEXT("MYSERVICE"));
   printf("Print Alert: %u\n", res);

   //SendUserAlert
   //To pass a user defined structure and pass valid strings you must 
   //create a message file and link it with your application, 
   //then register that application as the EventMessageFile in the 
   //event log section of the registry.

   //If there is no EventMessageFile available, then the alert will contain
   //whatever information you pas in the strings following the USER_OTHER_INFO
   //structure.
   
   pUserInfo  = (PUSER_OTHER_INFO)  buff;    //Fill in specific USER_OTHER_INFO data
   ZeroMemory(pUserInfo, VAREDSIZE);
   pUserInfo->alrtus_errcode = -1;
   pUserInfo->alrtus_numstrings = 1;
                                             //Fill in the strings that follow
   p = (LPTSTR) ALERT_VAR_DATA(pUserInfo);   //the USER_OTHER_INFO structure
   lstrcpy(p,TEXT("C:\\USERLOG.TXT"));
   p += lstrlen(p) + 1;
   lstrcpy(p, szUserName);

   res = NetAlertRaiseEx(ALERT_USER_EVENT, pUserInfo, VAREDSIZE, TEXT("MYSERVICE"));
   printf("User  Alert: %u\n", res);

   return(res);   
}
