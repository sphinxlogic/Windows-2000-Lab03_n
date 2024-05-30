/*++

Copyright (c) 1996  Microsoft Corporation

Module Name:

   jdebug.cpp

Abstract:

   Java debugger class implementation.

   The C++ debugger sample preforms the following steps:

    1) Connects to the debug manager.
    2) Runs the Java debuggee applet.
    3) Watches for the debuggee's Java VM to be created, and puts up a message box.
    4) Connects to the debuggee's Java VM.
    5) Watches for the debuggee class to be loaded.
    6) Sets a breakpoint in a method in the debuggee class.
    7) Watches for the breakpoint to be hit, and puts up a message box.
    8) Clears the breakpoint.
    9) Watches for the debuggee's Java VM to be destroyed, and puts up a message box.
   10) Disconnects from the debuggee's Java VM.
   11) Disconnects from the debug manager.
   12) Exits.

--*/


/* Headers
 **********/

#include "project.hpp"

#include <javadbg.h>
#include <jdbgguid.h>

#include "refcount.hpp"


/* Classes
 **********/

// sample Java debugger class

class JavaDebugger : public RefCount,
                     public IRemoteDebugManagerCallback,
                     public IRemoteProcessCallback
{
private:
   /* Fields
    *********/

   // debug manager
   IRemoteDebugManager *m_pirdm;

   // remote process
   IRemoteProcess *m_pirp;

   // debuggee class name
   LPWSTR m_pwszDebugClass;

   /* Methods
    **********/

   UINT RunMessageLoop(void);
   void QuitMessageLoop(UINT uResult);

public:
   /* Methods
    **********/

   JavaDebugger(void);
   ~JavaDebugger(void);
   HRESULT Initialize(IRemoteDebugManager *pirdm);
   void Terminate(void);
   HRESULT Debug(LPCSTR pcszDebugClass);

   // IRemoteDebugManagerCallback methods

   HRESULT STDMETHODCALLTYPE ProcessCreateEvent(IRemoteProcess *pirpNew, IRemoteProcess *pirpParent);

   // IRemoteProcessCallback methods

   HRESULT STDMETHODCALLTYPE DebugStringEvent(IRemoteThread *pirth, LPCWSTR pcwszDebugMsg);
   HRESULT STDMETHODCALLTYPE CodeBreakpointEvent(IRemoteThread *pirth);
   HRESULT STDMETHODCALLTYPE DataBreakpointEvent(IRemoteThread *pirth, IRemoteObject *piro);
   HRESULT STDMETHODCALLTYPE ExceptionEvent(IRemoteThread *pirth, IRemoteClassField *pircfException, EXCEPTIONKIND exk);
   HRESULT STDMETHODCALLTYPE StepEvent(IRemoteThread *pirth);
   HRESULT STDMETHODCALLTYPE CanStopEvent(IRemoteThread *pirth);
   HRESULT STDMETHODCALLTYPE BreakEvent(IRemoteThread *pirth);
   HRESULT STDMETHODCALLTYPE ThreadCreateEvent(IRemoteThread *pirth);
   HRESULT STDMETHODCALLTYPE ThreadDestroyEvent(IRemoteThread *pirth);
   HRESULT STDMETHODCALLTYPE ThreadGroupCreateEvent(IRemoteThread *pirth, IRemoteThreadGroup *pirthg);
   HRESULT STDMETHODCALLTYPE ThreadGroupDestroyEvent(IRemoteThread *pirth, IRemoteThreadGroup *pirthg);
   HRESULT STDMETHODCALLTYPE ClassLoadEvent(IRemoteThread *pirth, IRemoteClassField *pircfClass);
   HRESULT STDMETHODCALLTYPE ClassUnloadEvent(IRemoteThread *pirth, IRemoteClassField *pircfClass);
   HRESULT STDMETHODCALLTYPE ProcessDestroyEvent(IRemoteThread *pirth);
   HRESULT STDMETHODCALLTYPE TraceEvent(IRemoteThread *pirth);
   HRESULT STDMETHODCALLTYPE LoadCompleteEvent(IRemoteThread *pirth);

   // IUnknown methods

   DEFINE_DELEGATED_REFCOUNT_ADDREF(JavaDebugger);
   DEFINE_DELEGATED_REFCOUNT_RELEASE(JavaDebugger);
   HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObject);
};


/* Module Constants
 *******************/

#pragma data_seg(DATA_SEG_READ_ONLY)

const char SPACE                 = ' ';
const char TAB                   = '\t';
const char QUOTE                 = '\'';
const char QUOTES                = '"';

const char s_cszMsgBoxTitle[]    = "Sample Java Debugger";

const char s_cszDebugKey[]       = "Software\\Microsoft\\Java VM\\Debug";

const char s_cszDebugClass[]     = "Hello";
const WCHAR s_cwszDebugMethod[]  = L"main";
const ULONG s_ulcBreakpointPC    = 0;

#pragma data_seg()


/* Macros
 *********/

//
// Compile-time type check cast macro.
//
#define SAFE_CAST(type, obj) \
   (((type)(obj) == (obj) ? 0 : 0), (type)(obj))

//
// Safely delete an object.
//
#define SAFE_DELETE(ptr) \
   { \
      if (! (ptr)) \
          ; \
      else \
      { \
          delete(ptr); \
          (ptr) = NULL;  \
      } \
   } \


/***************************** Private Functions *****************************/


//
// Create a dynamically allocated Unicode copy of an ANSI string.
//
static HRESULT ANSIToUnicode(LPCSTR pcszANSI, LPWSTR *ppwszUnicode)
{
   HRESULT hr = E_UNEXPECTED;
   int ncchANSI;
   int ncchUnicode;

   // (+ 1) for null terminator.
   ncchANSI = lstrlen(pcszANSI) + 1;

   ncchUnicode = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pcszANSI, ncchANSI, NULL, 0);

   if (ncchUnicode > 0)
   {
      *ppwszUnicode = new(WCHAR[ncchUnicode]);

      if (*ppwszUnicode)
      {
         if (MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pcszANSI, ncchANSI, *ppwszUnicode, ncchUnicode) == ncchUnicode)
            hr = S_OK;
         else
         {
            delete(*ppwszUnicode);
            *ppwszUnicode = NULL;
         }
      }
      else
         hr = E_OUTOFMEMORY;
   }
   else
      *ppwszUnicode = NULL;

   return(hr);
}


//
// Skip over the white space at the beginning of a string.
//
LPCSTR SkipWhiteSpace(LPCSTR pcsz)
{
   while (*pcsz == SPACE ||
          *pcsz == TAB)
      pcsz = CharNext(pcsz);

   return(pcsz);
}


//
// Skip over the meat at the beginning of a string.
//
static LPCSTR SkipNonWhiteSpace(LPCSTR pcsz)
{
   while (*pcsz &&
          *pcsz != SPACE &&
          *pcsz != TAB)
      pcsz = CharNext(pcsz);

   return(pcsz);
}


//
// Skip over a quoted substring at the beginning of a string.
//
static LPCSTR SkipQuotedArg(LPCSTR pcsz)
{
   char chQ;

   // Skip over quoted argument past matching quote.

   chQ = *pcsz;
   pcsz = CharNext(pcsz);

   while (*pcsz &&
          *pcsz != chQ)
      pcsz = CharNext(pcsz);

   if (*pcsz == chQ)
      pcsz = CharNext(pcsz);

   return(pcsz);
}


//
// Skip over a possibly quoted substring at the beginning of a string.
//
static LPCSTR SkipPossiblyQuotedArg(LPCSTR pcsz)
{
   pcsz = SkipWhiteSpace(pcsz);

   switch (*pcsz)
   {
      case QUOTE:
      case QUOTES:
         pcsz = SkipQuotedArg(pcsz);
         break;

      default:
         pcsz = SkipNonWhiteSpace(pcsz);
         break;
   }

   return(pcsz);
}


//
// Display a printf()-style message box.
//
static BOOL MyMessageBox(HWND hwndParent, UINT uStyle, LPCSTR pcszFormat, ...)
{
   char szMsg[1024];
   va_list valArgs;

   // Lamely assume that wvsprintf() won't overflow szMsg[].

   va_start(valArgs, pcszFormat);
   wvsprintf(szMsg, pcszFormat, valArgs);
   va_end(valArgs);

   return(MessageBox(hwndParent, szMsg, s_cszMsgBoxTitle, uStyle));
}


//
// Create the Java VM Debug key.
//
static BOOL CreateDebugKey(void)
{
    BOOL bResult;
    DWORD dwDisposition;
    HKEY hkeyDebug;

    bResult = (RegCreateKeyEx(HKEY_LOCAL_MACHINE, s_cszDebugKey, 0, NULL, 0, KEY_WRITE, NULL, &hkeyDebug, &dwDisposition)
              == ERROR_SUCCESS);

    if (bResult)
      RegCloseKey(hkeyDebug);

   return(bResult);
}


//
// Delete the Java VM Debug key.
//
static BOOL DeleteDebugKey(void)
{
    return(RegDeleteKey(HKEY_LOCAL_MACHINE, s_cszDebugKey) == ERROR_SUCCESS);
}


/****************************** Public Functions *****************************/


#pragma warning(disable:4100)    // "unreferenced formal parameter" warning

int __cdecl main(int argc, char *argv[])
{
   HRESULT hr;

   // Initialize OLE on this thread.

   hr = CoInitialize(NULL);

   if (SUCCEEDED(hr))
   {
       IRemoteDebugManager *pirdm;

       // Create a RemoteJavaDebugManager from JDbgMgr.exe to initiate debugging.

       hr = CoCreateInstance(CLSID_RemoteJavaDebugManager, NULL,
                             CLSCTX_LOCAL_SERVER, IID_IRemoteDebugManager,
                             (PVOID *)&pirdm);

       if (hr == S_OK)
       {
           JavaDebugger *pjd;

           // Create a JavaDebugger object to run a simple debugging session.

           pjd = new(JavaDebugger);

           if (pjd)
           {
               hr = pjd->Initialize(pirdm);

               if (hr == S_OK)
               {
                   hr = pjd->Debug(s_cszDebugClass);

                   pjd->Terminate();
               }

               pjd->Release();
               pjd = NULL;
           }
           else
               hr = E_OUTOFMEMORY;

           pirdm->Release();
           pirdm = NULL;
       }

       // Uninitialize OLE on this thread.

       CoUninitialize();
   }

   return(hr);
}

#pragma warning(default:4100)    // "unreferenced formal parameter" warning


/********************************** Methods **********************************/


JavaDebugger::JavaDebugger(void)
{
   m_pirdm = NULL;
   m_pirp = NULL;
   m_pwszDebugClass = NULL;

   return;
}


JavaDebugger::~JavaDebugger(void)
{
   Terminate();

   return;
}


HRESULT JavaDebugger::Initialize(IRemoteDebugManager *pirdm)
{
   HRESULT hr;

   // Register this JavaDebugger's callback with the debug manager so it is notified when its debuggee target class is run.

   hr = pirdm->RegisterCallback(this);

   if (hr == S_OK)
   {
      m_pirdm = pirdm;
      m_pirdm->AddRef();
   }

   return(hr);
}


void JavaDebugger::Terminate(void)
{
   if (m_pirdm)
   {
      // Detach this JavaDebugger from the debug manager.

      m_pirdm->Detach();

      m_pirdm->Release();
      m_pirdm = NULL;
   }

   SAFE_DELETE(m_pwszDebugClass);

   return;
}


//
// Run a message loop on this thread until a WM_QUIT message is encountered.
//
UINT JavaDebugger::RunMessageLoop(void)
{
   MSG msg;

   // No accelerators to load.

   // Get and dispatch messages until a WM_QUIT message is received.

   ZeroMemory(&msg, sizeof(msg));

   while (GetMessage(&msg, NULL, 0, 0))
   {
      // Translate virtual key codes.

      TranslateMessage(&msg);

      // Dispatch message to target window.

      DispatchMessage(&msg);
   }

   return(msg.wParam);
}


//
// Terminate any message loop running on this thread.
//
void JavaDebugger::QuitMessageLoop(UINT uResult)
{
   PostQuitMessage(uResult);

   return;
}


//
// Initiate a simple debugging session.
//
HRESULT JavaDebugger::Debug(LPCSTR pcszDebugClass)
{
   HRESULT hr;

   // Create the Java VM Debug key to enable Java debugging.

   if (CreateDebugKey())
   {
      // Remember the debuggee class name.

      SAFE_DELETE(m_pwszDebugClass);

      hr = ANSIToUnicode(pcszDebugClass, &m_pwszDebugClass);

      if (hr == S_OK)
      {
         LPCSTR pcszCmdLine;
         STARTUPINFO si;
         PROCESS_INFORMATION pi;

         // Treat our command line arguments as the command line to run the debuggee class.

         pcszCmdLine = SkipWhiteSpace(SkipPossiblyQuotedArg(GetCommandLine()));

         ZeroMemory(&si, sizeof(si));
         si.cb = sizeof(si);

         // Start the debuggee class process suspended so we can get its process ID before it executes.

         hr = CreateProcess(NULL, (LPSTR)pcszCmdLine, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi) ? S_OK : E_FAIL;

         if (hr == S_OK)
         {
            HRESULT hrResume;

            // Ask the debug manager to notify us when the debuggee class is run.

            hr = m_pirdm->RequestCreateEvent(m_pwszDebugClass, pi.dwProcessId);

            // Resume the debuggee class process to begin debugging.

            hrResume = (ResumeThread(pi.hThread) != 0xffffffff) ? S_OK : E_FAIL;

            if (hr == S_OK)
               hr = hrResume;

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);

            // Run a message loop to dispatch OLE RPC messages.

            RunMessageLoop();
         }
      }

      // Delete the Java VM Debug key, if it hasn't already been deleted, to disable Java debugging.

      DeleteDebugKey();
   }

   return(hr);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::QueryInterface(REFIID riid,
                                                       PVOID *ppvObject)
{
    HRESULT hr = S_OK;

    if (riid == IID_IRemoteDebugManagerCallback)
       *ppvObject = SAFE_CAST(IRemoteDebugManagerCallback *, this);
    else if (riid == IID_IRemoteProcessCallback)
       *ppvObject = SAFE_CAST(IRemoteProcessCallback *, this);
    else if (riid == IID_IUnknown)
       *ppvObject = SAFE_CAST(IUnknown *, (IRemoteDebugManagerCallback *)this);
    else
    {
       *ppvObject = NULL;
       hr = E_NOINTERFACE;
    }

    if (hr == S_OK)
        AddRef();

    return(hr);
}


//
// Debugger event notification methods return an HRESULT as follows:
//
//      S_FALSE     Continue execution.
//
//      S_OK        Suspend execution of all threads in this VM until an
//                  IRemoteThread method is called on this thread to resume
//                  execution.
//
//      E_...       Error.
//

#pragma warning(disable:4100)    // "unreferenced formal parameter" warning

HRESULT STDMETHODCALLTYPE JavaDebugger::ProcessCreateEvent(
                                                    IRemoteProcess *pirpNew,
                                                    IRemoteProcess *pirpParent)
{
   HRESULT hr;

   // Register this JavaDebugger's callback with the Java VM so it is notified when interesting events occur in the debuggee.

   hr = pirpNew->RegisterCallback(this);

   if (hr == S_OK)
   {
      m_pirp = pirpNew;
      m_pirp->AddRef();
   }

   MyMessageBox(NULL, (MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND), "Process created.");

   // Delete the Java VM Debug key to disable Java debugging.

   DeleteDebugKey();

   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::DebugStringEvent(IRemoteThread *pirth, LPCWSTR pcwszDebugMsg)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::CodeBreakpointEvent(IRemoteThread *pirth)
{
   HRESULT hr;
   IRemoteStackFrame *pirsf;

   // Get the method object from the current thread's current stack frame.

   hr = pirth->GetCurrentFrame(&pirsf);

   if (hr == S_OK)
   {
      IRemoteContainerObject *pirco;

      hr = pirsf->GetMethodObject(&pirco);

      if (hr == S_OK)
      {
         IRemoteField *pirf;

         // Get the method field from the method object.

         hr = pirco->GetType(&pirf);

         if (hr == S_OK)
         {
            IRemoteMethodField *pirmf;

            hr = pirf->QueryInterface(IID_IRemoteMethodField, (PVOID *)&pirmf);

            if (hr == S_OK)
            {
               // Clear the breakpoint, and continue execution.

               hr = pirmf->ClearBreakpoint(s_ulcBreakpointPC);

               if (hr == S_OK)
                  MyMessageBox(NULL, (MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND), "Hit breakpoint %ls.%ls().%lu.",
                               m_pwszDebugClass,
                               s_cwszDebugMethod,
                               s_ulcBreakpointPC);

               pirmf->Release();
               pirmf = NULL;
            }

            pirf->Release();
            pirf = NULL;
         }

         pirco->Release();
         pirco = NULL;
      }

      pirsf->Release();
      pirsf = NULL;
   }

   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::DataBreakpointEvent(IRemoteThread *pirth, IRemoteObject *piro)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::ExceptionEvent(IRemoteThread *pirth, IRemoteClassField *pircfException, EXCEPTIONKIND exk)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::StepEvent(IRemoteThread *pirth)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::CanStopEvent(IRemoteThread *pirth)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::BreakEvent(IRemoteThread *pirth)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::ThreadCreateEvent(IRemoteThread *pirth)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::ThreadDestroyEvent(IRemoteThread *pirth)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::ThreadGroupCreateEvent(IRemoteThread *pirth, IRemoteThreadGroup *pirthg)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::ThreadGroupDestroyEvent(IRemoteThread *pirth, IRemoteThreadGroup *pirthg)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::ClassLoadEvent(IRemoteThread *pirth, IRemoteClassField *pircfClass)
{
   LPWSTR pwszClassName;

   // Get the name of the loaded class.

   if (pircfClass->GetName(&pwszClassName) == S_OK)
   {
      // Is this the class that a breakpoint is to be set in?

      if (! wcscmp(pwszClassName, m_pwszDebugClass))
      {
         IJavaEnumRemoteField *pijerf;

         // Yes.  Get the method field for the method to set a breakpoint in.

         if (pircfClass->GetFields(&pijerf, FIELD_KIND_METHOD, 0, s_cwszDebugMethod) == S_OK)
         {
            IRemoteField *pirf;
            ULONG ulcFetched;

            if (pijerf->Next(1, &pirf, &ulcFetched) == S_OK)
            {
               IRemoteMethodField *pirmf;

               if (pirf->QueryInterface(IID_IRemoteMethodField, (PVOID *)&pirmf) == S_OK)
               {
                  // Set the breakpoint, and continue execution.

                  pirmf->SetBreakpoint(s_ulcBreakpointPC);

                  pirmf->Release();
                  pirmf = NULL;
               }

               pirf->Release();
               pirf = NULL;
            }

            pijerf->Release();
            pijerf = NULL;
         }
      }

      CoTaskMemFree(pwszClassName);
      pwszClassName = NULL;
   }

   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::ClassUnloadEvent(IRemoteThread *pirth, IRemoteClassField *pircfClass)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::ProcessDestroyEvent(IRemoteThread *pirth)
{
   // Detach this JavaDebugger from the Java VM.

   m_pirp->Detach();

   m_pirp->Release();
   m_pirp = NULL;

   MyMessageBox(NULL, (MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND), "Process destroyed.");

   // Quit the message loop, and end the debugging session.

   QuitMessageLoop(0);

   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::TraceEvent(IRemoteThread *pirth)
{
   return(S_FALSE);
}


HRESULT STDMETHODCALLTYPE JavaDebugger::LoadCompleteEvent(IRemoteThread *pirth)
{
   return(S_FALSE);
}

#pragma warning(default:4100)    // "unreferenced formal parameter" warning

