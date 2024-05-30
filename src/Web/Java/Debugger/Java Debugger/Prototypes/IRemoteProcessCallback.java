package com.ms.debug;
import com.ms.com.*;

public interface IRemoteProcessCallback extends IUnknown
{
  public void DebugStringEvent(IRemoteThread thread, String debugString);
  public void CodeBreakpointEvent(IRemoteThread thread);
  public void DataBreakpointEvent(IRemoteThread thread, IRemoteObject obj);
  public void ExceptionEvent(IRemoteThread thread, IRemoteClassField exceptionClass, int exceptionKind);
  public void StepEvent(IRemoteThread thread);
  public void CanStopEvent(IRemoteThread thread);
  public void BreakEvent(IRemoteThread thread);
  public void ThreadCreateEvent(IRemoteThread thread);
  public void ThreadDestroyEvent(IRemoteThread thread);
  public void ThreadGroupCreateEvent(IRemoteThread thread, IRemoteThreadGroup threadGroup);
  public void ThreadGroupDestroyEvent(IRemoteThread thread, IRemoteThreadGroup threadGroup);
  public void ClassLoadEvent(IRemoteThread thread, IRemoteClassField classType);
  public void ClassUnloadEvent(IRemoteThread thread, IRemoteClassField classType);
  public void ProcessDestroyEvent(IRemoteThread thread);
  public void TraceEvent(IRemoteThread thread);
  public void LoadCompleteEvent(IRemoteThread thread);
}
