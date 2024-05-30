//
// JavaDebugger.java
//
// (C) Copyright 1996, 1997 Microsoft Corporation, All rights reserved.
//


import com.ms.com.*;
import com.ms.debug.*;
import com.ms.lang.*;


public class JavaDebugger implements IRemoteDebugManagerCallback,
                                     IRemoteProcessCallback
{
    /* Constants
     ************/

    // Set a breakpoint at PC 0 in Hello.main().

    protected final String sDebugClass      = "Hello";
    protected final String sDebugMethod     = "main";
    protected final int cnBreakpointPC      = 0;

    // Debug registry key

    protected final String sJavaVMKey       = "Software\\Microsoft\\Java VM";
    protected final String sDebug           = "Debug";


    /* Fields
    *********/

    protected IRemoteDebugManager m_irdm;
    protected IRemoteProcess m_irp;
    protected RegKey m_rkJavaVM;


    /* Methods
    **********/

    public static void main(String asCmdLine[])
    {
        JavaDebugger jd;

        jd = new JavaDebugger();

        jd.RunDebugger(asCmdLine);
    }

    public synchronized void RunDebugger(String asCmdLine[])
    {
        // Exit on notify() or interrupt().

        try
        {
            RemoteDebugManager rdm = new RemoteDebugManager();

            System.out.println("Created RemoteDebugManager.");

            Initialize(rdm);

            System.out.println("Initialized debugger.");

            Run(asCmdLine);

            System.out.println("Running debuggee...");

            wait();
        }
        catch (InterruptedException ex)
        {
            ;
        }
        finally
        {
            Terminate();

            System.out.println("Terminated debugger.");
        }
    }

    public void Initialize(IRemoteDebugManager irdm)
    {
        m_irdm = irdm;

        m_irdm.RegisterCallback(this);

        System.out.println("Registered IRemoteDebugManagerCallback.");

        CreateDebugKey();
    }

    public void Terminate()
    {
        DeleteDebugKey();

        if (m_irp != null)
        {
            m_irp.Detach();
            m_irp = null;

            System.out.println("Detached IRemoteProcessCallback from IRemoteProcess.");
        }

        if (m_irdm != null)
        {
            m_irdm.Detach();
            m_irdm = null;

            System.out.println("Detached IRemoteDebugManagerCallback from IRemoteDebugManager.");
        }
    }

    public void CreateDebugKey()
    {
        try
        {
            RegKey rkDebug;

            m_rkJavaVM = new RegKey(RegKey.getRootKey(RegKey.LOCALMACHINE_ROOT), sJavaVMKey, RegKey.KEYOPEN_CREATE);
            rkDebug = new RegKey(m_rkJavaVM, sDebug, RegKey.KEYOPEN_CREATE);
        }
        catch (RegKeyException rkex)
        {
            ;
        }
    }

    public void DeleteDebugKey()
    {
        try
        {
            m_rkJavaVM.deleteSubKey(sDebug);
        }
        catch (Exception ex)
        {
            ;
        }
    }

    public void Run(String asCmdLine[])
    {
        String sCmdLine;
        int i;
        DebuggeeProcess dp;
        int nProcessID;

        sCmdLine = new String();

        for (i = 0; i < asCmdLine.length; i++)
            sCmdLine += asCmdLine[i] + " ";

        System.out.println("Debuggee command line is \"" + sCmdLine + "\".");

        dp = new DebuggeeProcess();

        dp.CreateSuspendedProcess(sCmdLine);

        System.out.println("Created suspended debuggee process.");

        nProcessID = dp.GetProcessID();

        System.out.println("Debuggee process ID is " + nProcessID + ".");

        m_irdm.RequestCreateEvent(sDebugClass, nProcessID);

        System.out.println("Requested creation event on debuggee class " + sDebugClass + " in process " + nProcessID + ".");

        dp.ResumeProcess();

        System.out.println("Resumed debuggee process.");
    }

    //
    // Dumps the method bytecodes for the given method.  Demonstrates use of the
    // LockBytesHelper class.
    //
    static void DumpMethodBytes(IRemoteMethodField irmf)
    {
        ILockBytes ilb;
        byte[] abyteCode;
        int i;

        ilb = irmf.GetBytes();

        abyteCode = LockBytesHelper.GetBytes(ilb);

        System.out.println(abyteCode.length + " method bytecodes:");

        for (i = 0; i < abyteCode.length; i++)
            System.out.println("\tPC[" + i + "] = " + abyteCode[i]);
    }

    //
    // Dumps the line number information for the given method.
    //
    static void DumpMethodLineInfo(IRemoteMethodField irmf)
    {
        try
        {
            IJavaEnumLINEINFO ijeli;
            LINEINFO li = new LINEINFO();

            ijeli = irmf.GetLineInfo();

            System.out.println("Method line number information:");

            while (true)
            {
                try
                {
                    ijeli.GetNext(li);

                    System.out.println("\tPC = " + li.offPC + ", line = " + li.iLine);
                }
                catch (ComSuccessException cse)
                {
                    break;
                }
            }
        }
        catch (ComFailException cfe)
        {
            System.out.println("No line information for " + irmf.GetName() + "().");
        }
    }

    //
    // Dumps the bytes for the given constant pool item.  Demonstrates use of
    // the ConstantPoolHelper class.
    //
    static void DumpConstantPoolItem(IRemoteClassField ircf, int niItem)
    {
        ConstantPoolHelper cph;
        byte[] abyteItem;
        int i;

        cph = new ConstantPoolHelper(ircf);

        abyteItem = cph.GetConstantPoolItem(niItem);

        System.out.println(abyteItem.length + " bytes for constant pool item " + niItem + ":");

        for (i = 0; i < abyteItem.length; i++)
            System.out.println("\titem[" + i + "] = " + abyteItem[i]);
    }

    //
    // Debugger event notification methods return an HRESULT as an int as
    // follows:
    //
    //      S_FALSE     Continue execution.
    //
    //      S_OK        Suspend execution of all threads in this namespace until
    //                  an IRemoteThread method is called on this thread to
    //                  resume execution.
    //
    //      E_...       Error.
    //

    // IRemoteDebugManagerCallback methods

    public void ProcessCreateEvent(IRemoteProcess irpNew, IRemoteProcess irpParent)
    {
        // Register process callback.

        System.out.println("Received IRemoteProcessCallback::ProcessCreateEvent().");

        irpNew.RegisterCallback(this);
        m_irp = irpNew;

        System.out.println("Registered IRemoteProcessCallback.");

        DeleteDebugKey();

        throw new ComSuccessException();
    }

    // IRemoteProcessCallback methods

    public synchronized void ProcessDestroyEvent(IRemoteThread irth)
    {
        // Unregister process callback.

        System.out.println("Received IRemoteProcessCallback::ProcessDestroyEvent().");

        m_irp.Detach();
        m_irp = null;

        System.out.println("Detached IRemoteProcessCallback from IRemoteProcess.");

        notify();

        throw new ComSuccessException();
    }

    public void ClassLoadEvent(IRemoteThread irth, IRemoteClassField ircfClass)
    {
        String sClassName;

        System.out.println("Received IRemoteProcessCallback::ClassLoadEvent().");

        // Is this the class that a breakpoint is to be set on?

        sClassName = ((IRemoteField)ircfClass).GetName();

        if (sClassName.equals(sDebugClass))
        {
            IJavaEnumRemoteField ierf;
            IRemoteField irf;

            System.out.println("Loaded class " + sClassName + " is being debugged.");

            // Yes.  Look for the method to set a breakpoint on.

            ierf = ((IRemoteContainerField)ircfClass).GetFields(FIELDKIND.FIELD_KIND_METHOD, 0, sDebugMethod);

            irf = ierf.GetNext();

            // Found the method.  Set a breakpoint.

            ((IRemoteMethodField)irf).SetBreakpoint(cnBreakpointPC);

            System.out.println("Set breakpoint on " + sDebugClass + "." + sDebugMethod + "()." + cnBreakpointPC + ".");
        }

        throw new ComSuccessException();
    }

    public void CodeBreakpointEvent(IRemoteThread irth)
    {
        IRemoteMethodField irmf;
        IRemoteClassField ircf;

        // Clear the breakpoint.

        System.out.println("Received IRemoteProcessCallback::CodeBreakpointEvent().");

        System.out.println("Hit breakpoint at Hello.main().");

        // ((IRemoteMethodField)(irth.GetCurrentFrame().GetMethodObject().GetType())).ClearBreakpoint(cnBreakpointPC);

        irmf = (IRemoteMethodField)(irth.GetCurrentFrame().GetMethodObject().GetType());

        // Dump this method's bytecodes.

        DumpMethodBytes(irmf);

        // Dump this method's line number information.

        DumpMethodLineInfo(irmf);

        ircf = (IRemoteClassField)(irmf.GetContainer());

        // Dump constant pool item 5's bytes.

        DumpConstantPoolItem(ircf, 5);

        irmf.ClearBreakpoint(cnBreakpointPC);

        System.out.println("Cleared breakpoint.");

        throw new ComSuccessException();
    }

    public void DebugStringEvent(IRemoteThread irth, String sDebugMsg)
    {
        System.out.println("Received IRemoteProcessCallback::DebugStringEvent().");

        throw new ComSuccessException();
    }

    public void DataBreakpointEvent(IRemoteThread irth, IRemoteObject iro)
    {
        System.out.println("Received IRemoteProcessCallback::DataBreakpointEvent().");

        throw new ComSuccessException();
    }

    public void ExceptionEvent(IRemoteThread irth, IRemoteClassField ircfException, int exceptionKind)
    {
        System.out.println("Received IRemoteProcessCallback::ExceptionEvent().");

        throw new ComSuccessException();
    }

    public void StepEvent(IRemoteThread irth)
    {
        System.out.println("Received IRemoteProcessCallback::StepEvent().");

        throw new ComSuccessException();
    }

    public void CanStopEvent(IRemoteThread irth)
    {
        System.out.println("Received IRemoteProcessCallback::CanStopEvent().");

        throw new ComSuccessException();
    }

    public void BreakEvent(IRemoteThread irth)
    {
        System.out.println("Received IRemoteProcessCallback::BreakEvent().");

        throw new ComSuccessException();
    }

    public void ThreadCreateEvent(IRemoteThread irth)
    {
        System.out.println("Received IRemoteProcessCallback::ThreadCreateEvent().");

        throw new ComSuccessException();
    }

    public void ThreadDestroyEvent(IRemoteThread irth)
    {
        System.out.println("Received IRemoteProcessCallback::ThreadDestroyEvent().");

        throw new ComSuccessException();
    }

    public void ThreadGroupCreateEvent(IRemoteThread irth, IRemoteThreadGroup irthg)
    {
        System.out.println("Received IRemoteProcessCallback::ThreadGroupCreateEvent().");

        throw new ComSuccessException();
    }

    public void ThreadGroupDestroyEvent(IRemoteThread irth, IRemoteThreadGroup irthg)
    {
        System.out.println("Received IRemoteProcessCallback::ThreadGroupDestroyEvent().");

        throw new ComSuccessException();
    }

    public void ClassUnloadEvent(IRemoteThread irth, IRemoteClassField ircfClass)
    {
        System.out.println("Received IRemoteProcessCallback::ClassUnloadEvent().");

        throw new ComSuccessException();
    }

    public void TraceEvent(IRemoteThread irth)
    {
        System.out.println("Received IRemoteProcessCallback::TraceEvent().");

        throw new ComSuccessException();
    }

    public void LoadCompleteEvent(IRemoteThread irth)
    {
        System.out.println("Received IRemoteProcessCallback::LoadCompleteEvent().");

        throw new ComSuccessException();
    }
};

