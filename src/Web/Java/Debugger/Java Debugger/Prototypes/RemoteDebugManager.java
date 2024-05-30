package com.ms.debug;
import com.ms.com.*;

public class RemoteDebugManager implements IRemoteDebugManager
{
  public native void RegisterCallback(IRemoteDebugManagerCallback callback);
  public native void Detach();
  public native IJavaEnumRemoteProcess GetActiveProcesses();
  public native void RequestCreateEvent(String processName, int dwParentProcessId);
}
