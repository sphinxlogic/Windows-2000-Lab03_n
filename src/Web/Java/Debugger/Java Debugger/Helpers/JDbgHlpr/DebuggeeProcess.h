/*  DO NOT EDIT - automatically generated by javah  */
#include <native.h>

/*  Header for class DebuggeeProcess  */

#ifndef _Included_DebuggeeProcess
#define _Included_DebuggeeProcess

typedef struct ClassDebuggeeProcess {
#pragma pack(push,1)
	int32_t MSReserved;
	long m_nMainThreadHandle;
	long m_nProcessID;
#pragma pack(pop)
} ClassDebuggeeProcess;
#define HDebuggeeProcess ClassDebuggeeProcess

#ifdef __cplusplus
extern "C" {
#endif
__declspec(dllexport) void __cdecl DebuggeeProcess_ResumeProcess (struct HDebuggeeProcess *);
__declspec(dllexport) void __cdecl DebuggeeProcess_CreateSuspendedProcess (struct HDebuggeeProcess *, struct Hjava_lang_String *);
#ifdef __cplusplus
}
#endif
#endif