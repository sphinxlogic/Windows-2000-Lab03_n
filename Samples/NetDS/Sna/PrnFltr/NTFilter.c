#include "NtFilter.h"


int SessId =156789;
void *  Uid = (void *)&SessId ;
FILE *f;


BOOL APIENTRY DllMain( HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved )
{
    switch( ul_reason_for_call )
	{
		case DLL_PROCESS_ATTACH:
			trace("Initialization - Process Attach");
			break;
		case DLL_THREAD_ATTACH:
			trace("Thread Attach");
   			break;
		case DLL_THREAD_DETACH:
			trace("Thread Detach");
    		break;
		case DLL_PROCESS_DETACH:
			trace("Process Detach");
    		break;
    }
return TRUE;
}

__declspec( dllexport ) void * 	WINAPI PrtFilterAlloc(DWORD BufLen)
{
	/* MSFT - 3 lines for Debug OutPut - START */
	void * pBuf ;
	char TrBuf[50] ;
	trace("FilterAlloc");
	/* MSFT - 3 lines for Debug OutPut - END */

	pBuf = malloc(BufLen) ;

	/* MSFT - 2 lines for Debug OutPut - START */
	sprintf (TrBuf,"%x ",pBuf);
	trace (TrBuf) ;
	/* MSFT - 2 lines for Debug OutPut - END */

	return(pBuf);
}

__declspec( dllexport ) void 	WINAPI PrtFilterFree(void *pBuf)
{
	/* MSFT - 4 lines for Debug OutPut - START */
	char TrBuf[50] ;
	trace("FilterFree");
	sprintf (TrBuf,"%x ",pBuf);
	trace (TrBuf) ;
	/* MSFT - 4 lines for Debug OutPut - END */

	free(pBuf);

	/* MSFT - 1 line for Debug OutPut - START */
	trace("  Buffer library");
	/* MSFT - 1 line for Debug OutPut - END */

	return;
}

__declspec( dllexport ) void   	WINAPI PrtFilterJobData(void *UniqueID, char **pBufPtr,DWORD *pBufLen)
{
	/* MSFT - 4 lines for Debug OutPut - START */
	char TrBuf[50] ;
	trace("FilterJobData");
	sprintf (TrBuf,"%d ",*pBufLen);
	trace (TrBuf) ;
	/* MSFT - 4 lines for Debug OutPut - END */

	if (*pBufLen > 49)
	{
		strcpy(*pBufPtr,"- FILTER - FilterJobData --- FilterJobData --- Fil");
		*pBufLen=strlen(*pBufPtr);
	}
	else
		/* MSFT - 1 line for Debug OutPut - START */
		trace("Buffer too small - No modifications to the original data");
		/* MSFT - 1 line for Debug OutPut - END */
	return;
}

__declspec( dllexport ) void *	WINAPI PrtFilterJobStart(char *SessionName,DWORD LUType,char** pBufPtr,DWORD *pBuflen)
{
	/* MSFT - 1 line for Debug OutPut - START */
	trace("FilterJobStart");
	/* MSFT - 1 line for Debug OutPut - END */

	return((void *)(Uid));
}

__declspec( dllexport ) void *	WINAPI PrtFilterJobEnd(char *SessionName,char** pBufPtr,DWORD *pBufLen)
{
	/* MSFT - 1 line for Debug OutPut - START */
	trace("FilterJobEnd");
	/* MSFT - 1 line for Debug OutPut - END */

	return((void *)(Uid));
}

void trace(char *text)
{
	f= fopen("c:\\trfilter.txt","a+t");
	fprintf(f,"NTFILTER : %s \n",text);
	fclose(f);
}
