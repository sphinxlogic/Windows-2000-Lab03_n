package com.ms.debug;
import com.ms.com.*;

public interface IEnumRemoteThreadGroup extends IUnknown
{
  public void Skip(int celt);
  public void Reset();
  public IJavaEnumRemoteThreadGroup Clone();
}
