package com.ms.debug;
import com.ms.com.*;

public interface IEnumRemoteProcess extends IUnknown
{
  public void Skip(int celt);
  public void Reset();
  public IJavaEnumRemoteProcess Clone();
}
