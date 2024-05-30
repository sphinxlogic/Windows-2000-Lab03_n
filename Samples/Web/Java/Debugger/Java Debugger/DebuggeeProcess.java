//
// DebuggeeProcess.java
//
// (C) Copyright 1996 Microsoft Corporation, All rights reserved.
//

import com.ms.com.*;

public class DebuggeeProcess
{
    protected int m_nMainThreadHandle;
    protected int m_nProcessID;

    public native void CreateSuspendedProcess(String sCommandLine);

    public int GetProcessID()
	{
		return(m_nProcessID);
	}

    public native void ResumeProcess();

	static
	{
		System.loadLibrary("JDbgHlpr");
	}
}

