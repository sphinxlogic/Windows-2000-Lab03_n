package com.ms.debug;
import com.ms.com.*;

public interface IRemoteObject extends IUnknown
{
  public IRemoteField GetType();
  public void SetBreakpoint();
  public void ClearBreakpoint();
}
