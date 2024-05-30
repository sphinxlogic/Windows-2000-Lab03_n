/*------------------------------------------------------------------------------
	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
	ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
	TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.

	Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.

	sample1.cpp

	All the code for the sample.

------------------------------------------------------------------------------*/
#include "stdafx.h"

/*------------------------------------------------------------------------------
Function main

argc 
   number of command line arguments
argv
   array of pointers to command line arguments
------------------------------------------------------------------------------*/
extern "C" int __cdecl wmain(int argc, wchar_t* argv[])
{
	HRESULT     hr = S_OK;
   LPWSTR      lpAction = argv[1];

   if(3 > argc)
	{
		//there has to be at least 4 arguments.  
      hr = E_INVALIDARG;
	}
	else
	{
      CoInitialize(NULL);

      argc -= 2; //skip the name of command and action
      argv += 2;

      //switch on the action to perform:
      if(0 == _wcsicmp(lpAction, L"download"))
      {
         hr = Download(argc, argv);
      }
      else if(0 == _wcsicmp(lpAction, L"upload"))
      {
         hr = Upload(argc, argv);
      }
      else if(0 == _wcsicmp(lpAction, L"enum"))
      {
         hr = Enum(argc, argv);
      }
      else if(0 == _wcsicmp(lpAction, L"search"))
      {
         hr = Search(argc, argv);
      }
      else if(0 == _wcsicmp(lpAction, L"mkdir"))
      {
         hr = ISO(ISO_MKDIR, argc, argv);
      }
      else if(0 == _wcsicmp(lpAction, L"copy"))
      {
         hr = ISO(ISO_COPY, argc, argv);
      }
      else if(0 == _wcsicmp(lpAction, L"move"))
      {
         hr = ISO(ISO_MOVE, argc, argv);
      }
      else if(0 == _wcsicmp(lpAction, L"delete"))
      {
         hr = ISO(ISO_DELETE, argc, argv);
      }
      else
      {
         hr = E_INVALIDARG;
      }

      CoUninitialize();
	}

   if(E_INVALIDARG == hr)
   {
      PrintUsage();
      return 1;
   }

   wprintf(L"\nOperation %s completed with code=0x%08x\n", lpAction, hr);

	return 0;
}

/*------------------------------------------------------------------------------
Function Download

  This function demonstrates how we download a file using MSDAIPP.
  We use the IStream interface synchronously.
  
argc
   number of string pointers in argv
argv
   array of string pointers for arguments
   possible values:
   REQUIRED u=URL to download
   OPTIONAL l=local file to write file to
   OPTIONAL n=user name to authenticate with
   OPTIONAL p=passowrd to authenticate with

returns HRESULT of the test, in particular, E_INVALIDARG when the command 
line arguments are suspect.
------------------------------------------------------------------------------*/
HRESULT Download(int argc, wchar_t* argv[])
{
   HRESULT     hr = S_OK;
   IStream     *pStream = NULL;
   LPWSTR      pwchUrl = NULL;
   LPWSTR      pwchLocalFile = NULL;
   LPWSTR      pwchUserName = NULL;
   LPWSTR      pwchPassword = NULL;
   HANDLE      hFile=INVALID_HANDLE_VALUE;
   BYTE        rgbBuf[1024]; //a 1-k buffer for reading
   ULONG       cbRead, cbWritten;
   int         i;

   //Parameter checking:
   if( (1 > argc) || (4 < argc) )
   {
      return E_INVALIDARG;
   }

   for(i = 0; i < argc; i++)
   {
      if(0 == _wcsnicmp(argv[i], L"u=", 2))
      {
         pwchUrl = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"l=", 2))
      {
         pwchLocalFile = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"n=", 2))
      {
         pwchUserName = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"p=", 2))
      {
         pwchPassword = argv[i] + 2;
      }
      else
      {
         return E_INVALIDARG;
      }
   }

   //URL is not optional:
   if( NULL == pwchUrl )
   {
      return E_INVALIDARG;
   }

   //You may not set one and not the other:
   if(  ( (NULL == pwchUserName) && (NULL != pwchPassword) )
      ||( (NULL != pwchUserName) && (NULL == pwchPassword) ) )
   {
      pwchUserName = NULL; 
      pwchPassword = NULL;
   }

   //open the local file to be written to:
   if(NULL != pwchLocalFile)
   {
      hFile = CreateFileW(pwchLocalFile,
                          GENERIC_WRITE,
                          FILE_SHARE_READ,
                          NULL,
                          CREATE_ALWAYS,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL);

      if(INVALID_HANDLE_VALUE == hFile)
      {
         return HRESULT_FROM_WIN32(GetLastError());
      }
   }

   //Bind to a stream:
   hr = Bind(pwchUrl,
             DBGUID_STREAM,
             IID_IStream,
             DBBINDURLFLAG_READ | DBBINDURLFLAG_SHARE_DENY_WRITE,
             (IUnknown **)&pStream,
             pwchUserName,
             pwchPassword,
             FALSE);
   if(FAILED(hr))
   {
      goto cleanup;
      return hr;
   }
   
   //loop through the reading of the file using IStream::Read, and 
   //then write to the local file if need to.
   while(TRUE)
   {
      hr = pStream->Read((void *)rgbBuf,
                          1024,
                          &cbRead);

      if(0 == cbRead)
      {
         break;
      }

      if(INVALID_HANDLE_VALUE != hFile)
      {
         if(FALSE == WriteFile(hFile, rgbBuf, cbRead, &cbWritten, NULL))
         {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto cleanup;
         }
      }
   }


cleanup:

   //cleaning up by releasing pStream
   if(NULL != pStream)
   {
      pStream->Release();
      pStream = NULL;
   }

   if(INVALID_HANDLE_VALUE != hFile)
   {
      CloseHandle(hFile);
      hFile = INVALID_HANDLE_VALUE;
   }

   return hr;
}

/*------------------------------------------------------------------------------
Function Upload

  This function demonstrates how we upload a file using MSDAIPP.
  We use the IStream interface synchronously.
  
argc
   number of string pointers in argv
argv
   array of string pointers for arguments
   possible values:
   REQUIRED u=URL to upload to
   REQUIRED l=local file to upload
   OPTIONAL n=user name to authenticate with
   OPTIONAL p=passowrd to authenticate with

returns HRESULT of the test, in particular, E_INVALIDARG when the command 
line arguments are suspect.
------------------------------------------------------------------------------*/
HRESULT Upload(int argc, wchar_t* argv[])
{
   HRESULT     hr = S_OK;
   IStream     *pStream = NULL;
   LPWSTR      pwchUrl = NULL;
   LPWSTR      pwchLocalFile = NULL;
   LPWSTR      pwchUserName = NULL;
   LPWSTR      pwchPassword = NULL;
   HANDLE      hFile=INVALID_HANDLE_VALUE;
   BYTE        rgbBuf[1024]; //a 1-k buffer for reading
   ULONG       cbRead, cbWritten;
   int         i;

   //parameter checking:
   if( (2 > argc) || (4 < argc) )
   {
      return E_INVALIDARG;
   }

   for(i = 0; i < argc; i++)
   {
      if(0 == _wcsnicmp(argv[i], L"u=", 2))
      {
         pwchUrl = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"l=", 2))
      {
         pwchLocalFile = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"n=", 2))
      {
         pwchUserName = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"p=", 2))
      {
         pwchPassword = argv[i] + 2;
      }
      else
      {
         return E_INVALIDARG;
      }
   }

   //you have to have the URL:
   if(NULL == pwchUrl)
   {
      return E_INVALIDARG;
   }

   //local file source is not optional
   if(NULL == pwchLocalFile)
   {
      return E_INVALIDARG;
   }

   //You may not set one and not the other:
   if(  ( (NULL == pwchUserName) && (NULL != pwchPassword) )
      ||( (NULL != pwchUserName) && (NULL == pwchPassword) ) )
   {
      pwchUserName = NULL; 
      pwchPassword = NULL;
   }

   //opening the local file to read from
   hFile = CreateFileW(pwchLocalFile,
                       GENERIC_READ,
                       FILE_SHARE_READ,
                       NULL,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);

   if(INVALID_HANDLE_VALUE == hFile)
   {
      return HRESULT_FROM_WIN32(GetLastError());
   }

   //Bind to a stream:
   //note the bindflags or STGM we use will make sure that we can overwrite
   //the target file if it exists
   hr = Bind(pwchUrl,
             DBGUID_STREAM,
             IID_IStream,
             DBBINDURLFLAG_WRITE 
               | DBBINDURLFLAG_SHARE_DENY_WRITE 
               | DBBINDURLFLAG_OVERWRITE,
             (IUnknown **)&pStream,
             pwchUserName,
             pwchPassword,
             TRUE);
   if(FAILED(hr))
   {
      goto cleanup;
   }
   
   //loop through the file.  read a chunk from the local file, then
   //write to the server with IStream::Write
   while(TRUE)
   {
      if(FALSE == ReadFile(hFile, rgbBuf, 1024, &cbRead, NULL))
      {
         hr = HRESULT_FROM_WIN32(GetLastError());
         goto cleanup;
      }

      if(0 == cbRead)
      {
         break;
      }

      hr = pStream->Write((void *)rgbBuf,
                           cbRead,
                           &cbWritten);
      if(FAILED(hr))
      {
         goto cleanup;
      }
   }

   //after writing completes, we must commit
   hr = pStream->Commit(STGC_DEFAULT);

cleanup:

   //clean up
   if(NULL != pStream)
   {
      pStream->Release();
      pStream = NULL;
   }

   if(INVALID_HANDLE_VALUE != hFile)
   {
      CloseHandle(hFile);
      hFile = INVALID_HANDLE_VALUE;
   }

   return hr;
}


/*------------------------------------------------------------------------------
Function Enum

  This function demonstrates how we enumerate a collection resource on the 
  server using MSDAIPP.
  This function just checks the validity of the parameters and then delegate
  the real work to Enumerate().  We use IRowset and other interfaces on 
  the rowset object to do this.
  
argc
   number of string pointers in argv
argv
   array of string pointers for arguments
   possible values:
   REQUIRED u=URL to enumerate
   OPTIONAL v=yes/no - whether to echo enum results to the console
   OPTIONAL n=user name to authenticate with
   OPTIONAL p=passowrd to authenticate with

returns HRESULT of the test, in particular, E_INVALIDARG when the command 
line arguments are suspect.
------------------------------------------------------------------------------*/
HRESULT Enum(int argc, wchar_t* argv[])
{
   HRESULT           hr = S_OK;

   IRowset           *pRowset = NULL;

   LPWSTR            pwchUrl = NULL;
   LPWSTR            pwchUserName = NULL;
   LPWSTR            pwchPassword = NULL;
   BOOL              fVerbose = FALSE;
   int               i;

   //parameter checking:
   if( (1 > argc) || (4 < argc) )
   {
      return E_INVALIDARG;
   }

   for(i = 0; i < argc; i++)
   {
      if(0 == _wcsnicmp(argv[i], L"v=", 2))
      {
         if(0 == _wcsicmp(argv[i] + 2, L"yes"))
         {
            fVerbose = TRUE;
         }
         else if (0 == _wcsicmp(argv[i] + 2, L"no"))
         {
            fVerbose = FALSE;
         }
         else
         {
            return E_INVALIDARG;
         }
      }
      else if(0 == _wcsnicmp(argv[i], L"u=", 2))
      {
         pwchUrl = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"n=", 2))
      {
         pwchUserName = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"p=", 2))
      {
         pwchPassword = argv[i] + 2;
      }
      else
      {
         return E_INVALIDARG;
      }
   }

   //this is not optional:
   if( NULL == pwchUrl )
   {
      return E_INVALIDARG;
   }

   //You may not set one and not the other:
   if(  ( (NULL == pwchUserName) && (NULL != pwchPassword) )
      ||( (NULL != pwchUserName) && (NULL == pwchPassword) ) )
   {
      pwchUserName = NULL; 
      pwchPassword = NULL;
   }

   //Bind the resource to the IRowset interface
   hr = Bind(pwchUrl,
             DBGUID_ROWSET,
             IID_IRowset,
             DBBINDURLFLAG_READ,
             (IUnknown **)&pRowset,
             pwchUserName,
             pwchPassword,
             FALSE);
   if(FAILED(hr))
   {
      return hr;
   }

   //calling Enumerate:
   hr = EnumerateWithRowsetPointer(pRowset, fVerbose);

   pRowset->Release();

   return hr;
}

/*------------------------------------------------------------------------------
Function Search

  This function demonstrates how we use the OLEDB Command object to perform 
  searches against a data source.  Currently, search is only supported on DAV 
  servers.  There is no search performed against a FrontPage server.

  DAV server implementation on Windows 2000 supports SQL queries.  By executing
  the SQL query, we obtain a pointer to a rowset, which is enumerated to find 
  all the rows and columns fitting the search criteria.
  
argc
   number of string pointers in argv
argv
   array of string pointers for arguments
   possible values:
   REQUIRED u=URL to enumerate
   OPTIONAL q="query" - the SQL query to execute.
   OPTIONAL v=yes/no - whether to echo enum results to the console
   OPTIONAL n=user name to authenticate with
   OPTIONAL p=passowrd to authenticate with

returns HRESULT of the test, in particular, E_INVALIDARG when the command 
line arguments are suspect.
------------------------------------------------------------------------------*/
HRESULT Search(int argc, wchar_t* argv[])
{
   HRESULT           hr = S_OK;
   LPWSTR            pwchUrl = NULL;
   LPWSTR            pwchQuery = NULL;
   LPWSTR            pwchUserName = NULL;
   LPWSTR            pwchPassword = NULL;
   BOOL              fVerbose = FALSE;
   int               i;

   IDBCreateCommand  *pCreateCommand = NULL;
   ICommand          *pCommand = NULL;
   ICommandText      *pCommandText = NULL;
   IRowset           *pRowset = NULL;
   LONG              cRowsAffected = 0;


   //parameter checking:
   if( (1 > argc) || (5 < argc) )
   {
      hr = E_INVALIDARG;
      goto cleanup;
   }

   for(i = 0; i < argc; i++)
   {
      if(0 == _wcsnicmp(argv[i], L"v=", 2))
      {
         if(0 == _wcsicmp(argv[i] + 2, L"yes"))
         {
            fVerbose = TRUE;
         }
         else if (0 == _wcsicmp(argv[i] + 2, L"no"))
         {
            fVerbose = FALSE;
         }
         else
         {
            hr = E_INVALIDARG;
            goto cleanup;
         }
      }
      else if(0 == _wcsnicmp(argv[i], L"u=", 2))
      {
         pwchUrl = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"q=", 2))
      {
         DWORD    cwchQuery = 0;

         cwchQuery = wcslen(argv[i] + 2);
         
         if(NULL != pwchQuery)
         {
            //if the user has two q="xxx", we might have a leak, unless
            //we do this.

            delete [] pwchQuery;
         }

         //no need to add one since we're stripping the last "
         pwchQuery = new WCHAR[cwchQuery + 1]; 
         if(NULL == pwchQuery)
         {
            hr = E_OUTOFMEMORY;
            goto cleanup;
         }

         wcscpy(pwchQuery, argv[i] + 2);
      }
      else if(0 == _wcsnicmp(argv[i], L"n=", 2))
      {
         pwchUserName = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"p=", 2))
      {
         pwchPassword = argv[i] + 2;
      }
      else
      {
         hr = E_INVALIDARG;
         goto cleanup;
      }
   }

   //this is not optional:
   if( NULL == pwchUrl )
   {
      hr = E_INVALIDARG;
      goto cleanup;
   }

   //You may not set one and not the other:
   if(  ( (NULL == pwchUserName) && (NULL != pwchPassword) )
      ||( (NULL != pwchUserName) && (NULL == pwchPassword) ) )
   {
      pwchUserName = NULL; 
      pwchPassword = NULL;
   }

   //now on to the real processing.  In order to get a command object,
   // we have to bind to a session first.

   hr = Bind(pwchUrl,
             DBGUID_SESSION,
             IID_IDBCreateCommand,
             DBBINDURLFLAG_READ,
             (IUnknown **)&pCreateCommand,
             pwchUserName,
             pwchPassword,
             FALSE);
   if(FAILED(hr))
   {
      goto cleanup;
   }

   //now we should create the command:

   hr = pCreateCommand->CreateCommand(
                           NULL,
                           IID_ICommandText,
                           (IUnknown **)&pCommandText);
   pCreateCommand->Release(); //we don't need this anymore
   if(FAILED(hr))
   {
      goto cleanup;
   }

   if(NULL == pwchQuery)
   {
      //we use the default query:
      LPWSTR   wszQueryFormat = L"SELECT \"DAV:name\" FROM SCOPE ('SHALLOW TRAVERSAL OF \"%s\"')";
      int      cwchQuery = wcslen(wszQueryFormat) + wcslen(pwchUrl) + 1;
      int      nRet;

      pwchQuery = new WCHAR[cwchQuery];
      if(NULL == pwchQuery)
      {
         hr = E_OUTOFMEMORY;
         goto cleanup;
      }

      nRet = swprintf(pwchQuery, wszQueryFormat, pwchUrl);
      if((0 >= nRet) || (cwchQuery <= nRet))
      {
         //the number of chars don't add up
         hr = E_FAIL;
         goto cleanup;
      }
   }

   //we have to set the command text now:
   hr = pCommandText->SetCommandText(
               DBGUID_DEFAULT,
               pwchQuery);
   if(FAILED(hr))
   {
      pCommandText->Release();
      goto cleanup;
   }

   hr = pCommandText->QueryInterface(
                        IID_ICommand, 
                        (void **)&pCommand);
   pCommandText->Release();
   if(FAILED(hr))
   {
      goto cleanup;
   }


   //Finally, execute the command to get the IRowset pointer
   hr = pCommand->Execute(
                        NULL,
                        IID_IRowset,
                        NULL,
                        &cRowsAffected,
                        (IUnknown**)&pRowset);
   pCommand->Release();
   if(FAILED(hr))
   {
      goto cleanup;
   }

   hr = EnumerateWithRowsetPointer(pRowset, fVerbose);
   pRowset->Release();
   
cleanup:

   if(NULL != pwchQuery)
   {
      delete [] pwchQuery;
      pwchQuery = NULL;
   }

   return hr;
}


/*------------------------------------------------------------------------------
Function ISO

  This function demonstrates how the various things you can do with the 
  IScopedOperations interface.  You may 
  1. create a collection resource (aka, a folder, a directory) on the server
  2. Delete a resource
  3. copy or move a resource to another.  with these two operations, you may
     in fact specify one of them as a local file resource 
     (e.g., file://c:\file.txt)  You may also specify two resource on two 
     different servers, as well as the emulation flag, to copy or move 
     across servers.  The ability to copy or move multiple local resources 
     enables the consumer to use this interface for bulk upload/download of
     resources.  The provider packages the operations more efficiently for 
     better performance.
  
argc
   number of string pointers in argv
argv
   array of string pointers for arguments

   possible values for mkdir and delete:
   REQUIRED u=URL
   OPTIONAL n=user name to authenticate with
   OPTIONAL p=passowrd to authenticate with

   posilble values for copy and delete:
   REQUIRED us=Source URL
   REQUIRED ud=Destination URL
   OPTIONAL ns=user name to authenticate with to the source 
   OPTIONAL ps=passowrd to authenticate with to the source
   OPTIONAL nd=user name to authenticate with to the destination
   OPTIONAL pd=passowrd to authenticate with to the destination

returns HRESULT of the test, in particular, E_INVALIDARG when the command 
line arguments are suspect.
------------------------------------------------------------------------------*/
HRESULT ISO(ISO_OPS op, int argc, wchar_t* argv[])
{
   HRESULT              hr = S_OK;
   IScopedOperations    *pISO = NULL;
   LPWSTR               pwchUrl = NULL;
   LPWSTR               pwchUserName = NULL;
   LPWSTR               pwchPassword = NULL;

   LPWSTR               pwchUrlSrc = NULL;
   LPWSTR               pwchUserNameSrc = NULL;
   LPWSTR               pwchPasswordSrc = NULL;

   LPWSTR               pwchUrlDest = NULL;
   LPWSTR               pwchUserNameDest = NULL;
   LPWSTR               pwchPasswordDest = NULL;

   LPWSTR               pwchUrlBind = NULL;
   LPWSTR               pwchUserNameBind = NULL;
   LPWSTR               pwchPasswordBind = NULL;

   IAuthenticate        *pAuth = NULL;

   int                  i;
   DWORD                dwFlags = 0;
   DWORD                dwStatus = 0;
   BOOL                 fAlloc = FALSE;

   //parameter checking
   if((1 > argc) || (6 < argc))
   {
      return E_INVALIDARG;
   }

   for(i = 0; i < argc; i++)
   {
      if(0 == _wcsnicmp(argv[i], L"u=", 2))
      {
         pwchUrl = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"us=", 2))
      {
         pwchUrlSrc = argv[i] + 3;
      }
      else if(0 == _wcsnicmp(argv[i], L"ud=", 2))
      {
         pwchUrlDest = argv[i] + 3;
      }
      else if(0 == _wcsnicmp(argv[i], L"n=", 2))
      {
         pwchUserName = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"p=", 2))
      {
         pwchPassword = argv[i] + 2;
      }
      else if(0 == _wcsnicmp(argv[i], L"ns=", 2))
      {
         pwchUserNameSrc = argv[i] + 3;
      }
      else if(0 == _wcsnicmp(argv[i], L"ps=", 2))
      {
         pwchPasswordSrc = argv[i] + 3;
      }
      else if(0 == _wcsnicmp(argv[i], L"nd=", 2))
      {
         pwchUserNameDest = argv[i] + 3;
      }
      else if(0 == _wcsnicmp(argv[i], L"pd=", 2))
      {
         pwchPasswordDest = argv[i] + 3;
      }
      else
      {
         return E_INVALIDARG;
      }
   }

   //You may not set one and not the other:
   if(  ( (NULL == pwchUserName) && (NULL != pwchPassword) )
      ||( (NULL != pwchUserName) && (NULL == pwchPassword) ) )
   {
      pwchUserName = NULL; 
      pwchPassword = NULL;
   }

   if(  ( (NULL == pwchUserNameSrc) && (NULL != pwchPasswordSrc) )
      ||( (NULL != pwchUserNameSrc) && (NULL == pwchPasswordSrc) ) )
   {
      pwchUserNameSrc = NULL; 
      pwchPasswordSrc = NULL;
   }

   if(  ( (NULL == pwchUserNameDest) && (NULL != pwchPasswordDest) )
      ||( (NULL != pwchUserNameDest) && (NULL == pwchPasswordDest) ) )
   {
      pwchUserNameDest = NULL; 
      pwchPasswordDest = NULL;
   }


   //if we're making a collection or deleting something, we do similar processing:
   if(ISO_MKDIR == op)
   {
      //this is not optional:
      if( NULL == pwchUrl )
      {
         return E_INVALIDARG;
      }

      //For creation of collection, merely binding is enough.
      hr = Bind(pwchUrl, 
                DBGUID_ROW, 
                IID_IScopedOperations,
                DBBINDURLFLAG_WRITE 
                  | DBBINDURLFLAG_OVERWRITE 
                  | DBBINDURLFLAG_COLLECTION,
                (IUnknown **)&pISO,
                pwchUserName,
                pwchPassword,
                TRUE);

      if(FAILED(hr))
      {
         return hr;
      }
   }
   else if(ISO_DELETE == op)
   {
      //this is not optional:
      if( NULL == pwchUrl )
      {
         return E_INVALIDARG;
      }

      hr = Bind(pwchUrl,
                DBGUID_ROW,
                IID_IScopedOperations,
                DBBINDURLFLAG_WRITE,
                (IUnknown **)&pISO,
                pwchUserName,
                pwchPassword,
                FALSE);
      if(FAILED(hr))
      {
         return hr;
      }

      hr = pISO->Delete(1,
                        (LPCWSTR *)&pwchUrl,
                        0,
                        &dwStatus);
   }
   else if((ISO_COPY == op) || (ISO_MOVE == op))
   {
      //we require both URLs
      if((NULL == pwchUrlSrc) || (NULL == pwchUrlDest))
      {
         return E_INVALIDARG;
      }

      //when we bind, we have to bind to a remote server.  If the 
      //source URL is a file, we have to bind to the destination instead.
      //we cannot accept two file:// urls though.
      if(0 != _wcsnicmp(pwchUrlSrc, L"file://", 7))
      {
         pwchUrlBind = pwchUrlSrc;
         pwchUserNameBind = pwchUserNameSrc;
         pwchPasswordBind = pwchPasswordSrc;
      }
      else if (0 != _wcsnicmp(pwchUrlDest, L"file://", 7))
      {
         //we need to bind to the parent folder of the destination URL 
         //in this case:
         hr = GetParentUrl(pwchUrlDest, &pwchUrlBind);
         if(FAILED(hr))
         {
            return hr;
         }
         fAlloc = TRUE;
         pwchUserNameBind = pwchUserNameDest;
         pwchPasswordBind = pwchPasswordDest;
      }
      else
      {
         return E_INVALIDARG;
      }

      //binding.  we have to make sure to pass in the right set of 
      //credentials
      hr = Bind(pwchUrlBind, 
                DBGUID_ROW,
                IID_IScopedOperations,
                DBBINDURLFLAG_READWRITE,
                (IUnknown **)&pISO,
                pwchUserNameBind,
                pwchPasswordBind,
                FALSE);
      if(fAlloc && (NULL != pwchUrlBind))
      {
         //cleanup while we can
         delete [] pwchUrlBind;
      }
      if(FAILED(hr))
      {
         return hr;
      }

      //the Copy/Move call takes an IAuthenticate interface pointer
      //for the destination resourecs as one of the arguments.  
      //This way, we may authenticate to the source and destination 
      //with different sets of credentials
      if((NULL != pwchUserNameDest) && (NULL != pwchPasswordDest))
      {
         pAuth = new CImpAuth;
         if(NULL == pAuth)
         {
            pISO->Release();

            return E_OUTOFMEMORY;
         }

         hr = ((CImpAuth *)pAuth)->Set(pwchUserNameDest, pwchPasswordDest);
         if(FAILED(hr))
         {
            delete pAuth;

            pISO->Release();

            return hr;
         }

         pAuth->AddRef();
      }

      //finally, the calls
      if(ISO_COPY == op)
      {
         hr = pISO->Copy(1,
                         (LPCWSTR *)&pwchUrlSrc,
                         (LPCWSTR *)&pwchUrlDest,
                         DBCOPY_REPLACE_EXISTING
                           | DBCOPY_ALLOW_EMULATION,
                         pAuth,
                         &dwStatus,
                         NULL,
                         NULL);
      }
      else if (ISO_MOVE == op)
      {
         hr = pISO->Move(1,
                         (LPCWSTR *)&pwchUrlSrc,
                         (LPCWSTR *)&pwchUrlDest,
                         DBMOVE_REPLACE_EXISTING
                           | DBMOVE_DONT_UPDATE_LINKS
                           | DBMOVE_ALLOW_EMULATION,
                         pAuth,
                         &dwStatus,
                         NULL,
                         NULL);
      }

      //cleaning up:
      if(NULL != pAuth)
      {
         pAuth->Release();
      }
   }
   else 
   {
      return E_INVALIDARG;
   }

   //cleanup:
   if(NULL != pISO)
   {
      pISO->Release();
   }

   return hr;
}

/*------------------------------------------------------------------------------
Function Bind
   A function to allow us to easily bind to a resource synchronously  This 
   function instantiates the IAuthenticate callback if neccessary.  An 
   implementation of IAuthenticate is included with this sample.  We 
   demonstrates how we bind to MSDAIPP through the Rootbinder.

Parameters:
  pwchUrl 
   the URL to bind to
  rguid
   a guid to denote the OLEDB object to bind to, only for the binders.
  riid
   the interface to bind to
  dwFlags
   the DBBINDURLFLAG for binding through the binders
  ppUnk
   pointer to return interface pointer requested
  pwchUserName
   user name for authentication
  pwchPassword
   password for authentication
  fCreate
   whether to call IBindResource or ICreateRow

returns HRESULT of the Bind.
------------------------------------------------------------------------------*/
HRESULT Bind(LPWSTR     pwchUrl,
             REFGUID    rguid,
             REFIID     riid,
             DWORD      dwFlags,
             IUnknown** ppUnk,
             LPWSTR     pwchUserName,
             LPWSTR     pwchPassword,
             BOOL       fCreate)
{
   HRESULT           hr = S_OK;
   IAuthenticate     *pAuth = NULL;
   IBindResource     *pBindResource = NULL;
   ICreateRow        *pCreateRow = NULL;
   DBBINDURLSTATUS   dwBindStatus;


   //instantiation of the IAuthenticate callback
   if((NULL != pwchUserName) && (NULL != pwchPassword))
   {
      pAuth = new CImpAuth;
      if(NULL == pAuth)
      {
         return E_OUTOFMEMORY;
      }
      
      hr = ((CImpAuth *)pAuth)->Set(pwchUserName, pwchPassword);
      if(FAILED(hr))
      {
         delete pAuth;
         return hr;
      }

      pAuth->AddRef();
   }

   if(TRUE == fCreate)
   {
      //Calling CoCreateInstance to get the ICreateRow interface
      //on the binder.
      hr = CoCreateInstance(CLSID_RootBinder, 
                            NULL, 
                            CLSCTX_ALL, 
                            IID_ICreateRow, 
                            (void **)&pCreateRow);
      if(FAILED(hr))
      {
         if(NULL != pAuth)
         {  
            pAuth->Release();
         }
         return hr;
      }

      //Creating!
      hr = pCreateRow->CreateRow(NULL,
	                              pwchUrl,
	                              dwFlags,
	                              rguid,
	                              riid,
	                              pAuth,
	                              NULL,
	                              &dwBindStatus,
                                 NULL,
	                              ppUnk);

      pCreateRow->Release();
   }
   else
   {
      //Calling CoCreateInstance to get the IBindResource interface
      //on the binder.
      hr = CoCreateInstance(CLSID_RootBinder, 
                            NULL, 
                            CLSCTX_ALL, 
                            IID_IBindResource, 
                            (void **)&pBindResource);
      if(FAILED(hr))
      {
         if(NULL != pAuth)
         {  
            pAuth->Release();
         }
         return hr;
      }

      //Binding!
      hr = pBindResource->Bind(  NULL,
	                              pwchUrl,
	                              dwFlags,
	                              rguid,
	                              riid,
	                              pAuth,
	                              NULL,
	                              &dwBindStatus,
	                              ppUnk);

      pBindResource->Release();
   }

   if(NULL != pAuth)
   {  
      pAuth->Release();
   }

   return hr;
}


/*------------------------------------------------------------------------------
FUNCTION EnumerateWithRowsetPointer

  this function demonstrate how to enumerate a collection resource.  Those
  familiar with OLEDB rowset should not have problem following.  The steps are
  1. discover all the columns of the rowset
  2. create an accessor to the columns
  3. get the rows
  4. get the data with the accessor

  parameters
  pRowset
   A pointer to an IRowset pointer
  fVerbose
   flag to indicate whether to echo the rows and columns to stdout

------------------------------------------------------------------------------*/
HRESULT EnumerateWithRowsetPointer(
                  IRowset  *pRowset, 
                  BOOL     fVerbose)
{
   HRESULT           hr = S_OK;
   DWORD             i;

   IColumnsInfo      *pColumnsInfo = NULL;
   DWORD             cColumn;
   DBCOLUMNINFO      *pInfo = NULL;
   OLECHAR           *pStringsBuf = NULL;

   IAccessor         *pAccessor = NULL;
   DBBINDING         *pBindings = NULL;
   HACCESSOR         hAccessor = NULL;
   DBBINDSTATUS      *pBindStatus = NULL;

   BYTE              *pData = NULL;
   DWORD             cRowsObtained;
   HROW              *pRow = NULL;
   DWORD             cRow;
   ULONG             *pStatus = NULL;
   ULONG             *pLength = NULL;

   if(NULL == pRowset)
   {
      return E_INVALIDARG;
   }

   //since there are a number of places where things may fail and need to 
   //be cleaned up, we wrap the code in a while(FALSE) loop for easy 
   //clean up.

   do{
      //finding out all the columns supported by the rowset.  This is
      //accomplished through the IColumnsInfo interface
      hr = pRowset->QueryInterface(IID_IColumnsInfo, (void **)&pColumnsInfo);
      if(FAILED(hr))
      {
         break;
      }

      hr = pColumnsInfo->GetColumnInfo(&cColumn, &pInfo, &pStringsBuf);
      if(FAILED(hr))
      {
         break;
      }

      if(0 == cColumn)
      {
         if(fVerbose)
         {
            printf("There are no columns for our rowset\n");
         }
         hr = S_OK;
         break;
      }

      //next we need to create an accessor.
      hr = pRowset->QueryInterface(IID_IAccessor, (void **)&pAccessor);
      if(FAILED(hr))
      {
         break;
      }

      pBindings = new DBBINDING [cColumn];
      if(NULL == pBindings)
      {
         hr = E_OUTOFMEMORY;
         break;
      }
      memset(pBindings, 0, cColumn * sizeof(DBBINDING));

      pBindStatus = new DBBINDSTATUS [cColumn];
      if(NULL == pBindStatus)
      {
         hr = E_OUTOFMEMORY;
         break;
      }
      memset(pBindStatus, 0, cColumn * sizeof(DBBINDSTATUS));

      //We have to transfer the information in the DBCOLUMNINFO
      //to our new DBBINDING.  However, we're asking for all the
      //columns in WSTR to display them if neccessary.  Almost all
      //types can be converted to DBTYPE_WSTR
      for(i = 0; i < cColumn; i++)
      {
         //we are going to ask for all the columns as DBTYPE_WSTR.
         pBindings[i].iOrdinal   = pInfo[i].iOrdinal;
         pBindings[i].obValue    = i * MAX_PATH;
         pBindings[i].obLength   = (cColumn * MAX_PATH) + (i * sizeof(ULONG));
         pBindings[i].obStatus   = (cColumn * (MAX_PATH + sizeof(ULONG)))
                                    + (i * sizeof(ULONG));
         pBindings[i].pTypeInfo  = pInfo[i].pTypeInfo;
         pBindings[i].pObject    = NULL;
         pBindings[i].pBindExt   = NULL;
         pBindings[i].dwPart     = DBPART_VALUE | DBPART_LENGTH | DBPART_STATUS;
         pBindings[i].dwMemOwner = DBMEMOWNER_CLIENTOWNED;
         pBindings[i].eParamIO   = 0;
         pBindings[i].cbMaxLen   = MAX_PATH;
         pBindings[i].dwFlags    = 0;
         pBindings[i].wType      = DBTYPE_WSTR;
         pBindings[i].bPrecision = pInfo[i].bPrecision;
         pBindings[i].bScale     = pInfo[i].bScale;
      }

      hr = pAccessor->CreateAccessor(DBACCESSOR_ROWDATA,
                                     cColumn,
                                     pBindings,
                                     0,
                                     &hAccessor,
                                     pBindStatus);

      if(FAILED(hr))
      {
         break;
      }

      //We need to pass a buffer into the GetData call.  here
      //we allocate it.
      pData = new BYTE [cColumn * (MAX_PATH + (2 * sizeof(ULONG)))];
      if(NULL == pData)
      {
         hr = E_OUTOFMEMORY;
         break;
      }
      pStatus = (ULONG *)( pData + (cColumn * MAX_PATH) );
      pLength = (ULONG *)( pData + (cColumn * (MAX_PATH + sizeof(ULONG))) );

      //getting the rows row by row and print them to stdout if neccessary.
      cRow=0;
      while(TRUE)
      {
         hr = pRowset->GetNextRows(NULL, 0, 1, &cRowsObtained, &pRow);
         if(FAILED(hr) || (DB_S_ENDOFROWSET == hr))
         {
            break;
         }

         hr = pRowset->GetData(pRow[0], hAccessor, (void *)pData);
         pRowset->ReleaseRows(1, pRow, NULL, NULL, NULL);

         if(FAILED(hr))
         {
            break;
         }

         if(fVerbose)
         {
            printf("Columns for Row %i:\n", cRow);

            for(i = 0; i < cColumn; i++)
            {
               LPWSTR   lpColData;

               lpColData = (LPWSTR) (pData + (i * MAX_PATH));

               //making sure the data is terminated.
               //The data we get back has the right length, but they may not be
               //null-terminated.
               if(DBSTATUS_S_OK == pStatus[i])
               {
                  lpColData[ pLength[i] / sizeof(WCHAR) ] = L'\0';
               }
               else if(DBSTATUS_S_TRUNCATED == pStatus[i])
               {
                  lpColData[ (MAX_PATH / sizeof(WCHAR)) - 1 ] = L'\0';
               }

               printf("  Column %i: %ls\n", i, lpColData);
            }
         }

         cRow++;
      }


   }while(FALSE);

   //cleanup:
   if (NULL != pColumnsInfo)
   {
      pColumnsInfo->Release();
   }

   if (NULL != pInfo)
   {
      CoTaskMemFree(pInfo);
   }

   if (NULL != pStringsBuf)
   {
      CoTaskMemFree(pStringsBuf);
   }

   if (NULL != pAccessor)
   {
      if (NULL != hAccessor)
      {
         pAccessor->ReleaseAccessor(hAccessor, NULL);
      }
      pAccessor->Release();
   }

   if (NULL != pBindings)
   {
      delete [] pBindings;
   }

   if (NULL != pBindStatus)
   {
      delete [] pBindStatus;
   }

   if (NULL != pData)
   {
      delete [] pData;
   }

   return hr;
}

/*------------------------------------------------------------------------------
FUNCTION EnumerateParent

  This is just a helper function that enumerates the parent of a resource whose
  URL is given.  It strips the last token from the URL and then calls Enumerate.

  pwchUrl
    the URL whose parent to bind to
  pwchUserName
    the user name for authentication
  pwchPassword
    the password for authentication
------------------------------------------------------------------------------*/
HRESULT EnumerateParent(LPWSTR    pwchUrl, 
                        LPWSTR    pwchUserName, 
                        LPWSTR    pwchPassword)
{
   HRESULT  hr = S_OK;
   LPWSTR   lpParent;
   IRowset  *pRowset;

   hr = GetParentUrl(pwchUrl, &lpParent);
   if(FAILED(hr))
   {
      return hr;
   }

   hr = Bind(pwchUrl,
             DBGUID_ROWSET,
             IID_IRowset,
             DBBINDURLFLAG_READ,
             (IUnknown **)&pRowset,
             pwchUserName,
             pwchPassword,
             FALSE);
   if(FAILED(hr))
   {
      delete [] lpParent;
      return hr;
   }
   
   hr = EnumerateWithRowsetPointer(pRowset, FALSE);

   delete [] lpParent;

   return hr;
}

/*------------------------------------------------------------------------------
FUNCTION GetParentUrl

  This is just a helper function that extracts the URL of the parent folder of
  the URL passed in.

  pwchUrl
    [IN] the URL whose parent you want
  ppwchParent
    [OUT] the URL of the parent.  De-allocate with delete []
------------------------------------------------------------------------------*/
HRESULT GetParentUrl(LPWSTR    pwchUrl,
                     LPWSTR    *ppwchParent)
{
   HRESULT     hr = S_OK;
   LPWSTR      lpParent = NULL;
   PWCHAR      pwchLast;
   DWORD       cwchUrl = wcslen(pwchUrl);

   if(NULL == ppwchParent)
   {
      return E_INVALIDARG;
   }
   *ppwchParent = NULL;

   lpParent = new WCHAR [cwchUrl + 1];
   if (NULL == lpParent)
   {
      return E_OUTOFMEMORY;
   }
   wcscpy(lpParent, pwchUrl);

   pwchLast = wcsrchr(lpParent, L'/');
   if(NULL == pwchLast)
   {
      delete [] lpParent;
      return E_INVALIDARG;
   }

   if(pwchLast == (lpParent + cwchUrl - 1))
   {
      //The last character is a NULL
      lpParent[cwchUrl-1] = L'\0';
      pwchLast = wcsrchr(lpParent, L'/');
      if(NULL == pwchLast)
      {
         delete [] lpParent;
         return E_INVALIDARG;
      }
   }

   if(L'/' == *(pwchLast - 1))
   {
      //The '/' pointed to by pchLast is the // in the URL.
      delete [] lpParent;
      return S_OK;
   }

   *pwchLast = L'\0'; //cutting the URL off at the last '/'

   *ppwchParent = lpParent;

   return hr;
}



/*------------------------------------------------------------------------------
FUNCTION PrintUsage

  Helper function that prints the usage
------------------------------------------------------------------------------*/
void PrintUsage()
{
   wprintf(L"sample1.exe\n");
   wprintf(L"Usage:\n");
   wprintf(L"   sample1 <action> [action specific parameters]\n");
   wprintf(L"      where <action> is one of the followings:\n");
   wprintf(L"                download\n");
   wprintf(L"                upload\n");
   wprintf(L"                enum\n");
   wprintf(L"                search\n");
   wprintf(L"                mkdir\n");
   wprintf(L"                copy\n");
   wprintf(L"                move\n");
   wprintf(L"                delete\n");
   wprintf(L"      action specific parameters:\n");
   wprintf(L"         download: u=url [l=local_dest] [n=username p=password]\n");
   wprintf(L"         upload:   u=url l=local_src [n=username p=password]\n");
   wprintf(L"         enum:     u=url [v=yes/no] [n=username p=password]\n");
   wprintf(L"         search:   u=url [q=\"SQL query\"] [v=yes/no] [n=username p=password]\n");
   wprintf(L"                   note that '\"' in the query should be typed as '\\\"'\n");
   wprintf(L"         mkdir:    u=url [n=username p=password]\n");
   wprintf(L"         copy:     us=src ud=dest [ns=username ps=password]\n");
   wprintf(L"                                  [nd=username pd=password]\n");
   wprintf(L"         move:     us=src ud=dest [ns=username ps=password]\n");
   wprintf(L"                                  [nd=username pd=password]\n");
   wprintf(L"         delete:   u=url [n=username p=password]\n");
}

/*------------------------------------------------------------------------------
FUNCTION DuplicateWSTR

  Helper function duplicates a WSTR by first allocating memory to hold it and 
  copying the content from the old string to the new string.
  The caller should free the memory by calling delete [] on the pointer 
  returned.

  paremeter:
  wsz
    pointer to the wide char string to be duplicated

  returns
  the pointer to the freshly allocated memory with the content.
------------------------------------------------------------------------------*/
LPWSTR DuplicateWSTR(LPWSTR wsz)
{
   int      cwch = wcslen(wsz) + 1;
   LPWSTR   pwchNew = new WCHAR[cwch];

   if(NULL == wsz)
   {
      return NULL;
   }
   
   wcscpy(pwchNew, wsz);

   return pwchNew;
}
