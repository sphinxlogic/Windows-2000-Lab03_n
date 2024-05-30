package com.ms.debug;
import com.ms.com.*;

public interface IRemoteThreadGroup extends IUnknown
{
  public String GetName();
  public IJavaEnumRemoteThread GetThreads();
  public IJavaEnumRemoteThreadGroup GetThreadGroups();
}
