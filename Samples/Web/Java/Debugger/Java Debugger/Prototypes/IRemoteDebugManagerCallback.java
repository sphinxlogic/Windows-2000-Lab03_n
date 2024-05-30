package com.ms.debug;
import com.ms.com.*;

public interface IRemoteDebugManagerCallback extends IUnknown
{
  public void ProcessCreateEvent(IRemoteProcess processNew, IRemoteProcess processParent);
}
