#include <windows.h>
#include <stdio.h>

#define SIZEBUF     4096

__declspec( dllexport ) void   	WINAPI PrtFilterJobData(void *UniqueID, char **pBufPtr,DWORD *pBufLen);
__declspec( dllexport ) void * 	WINAPI PrtFilterAlloc(DWORD Buflen);
__declspec( dllexport ) void 	WINAPI PrtFilterFree(void *pBuf);
__declspec( dllexport ) void *	WINAPI PrtFilterJobStart(char *SessionName,DWORD LUType,char** pBufPtr,DWORD *pBuflen);
__declspec( dllexport ) void *	WINAPI PrtFilterJobEnd(char *SessionName,char** pBufPtr,DWORD *pBuflen);

BOOL APIENTRY DllMain( HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved );

void trace(char *text);
