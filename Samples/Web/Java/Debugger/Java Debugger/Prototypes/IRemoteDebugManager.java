package com.ms.debug;
import com.ms.com.*;

public interface IRemoteDebugManager extends IUnknown
{
  public void RegisterCallback(IRemoteDebugManagerCallback callback);
  public void Detach();
  public IJavaEnumRemoteProcess GetActiveProcesses();
  public void RequestCreateEvent(String processName, int dwParentProcessId);
}
