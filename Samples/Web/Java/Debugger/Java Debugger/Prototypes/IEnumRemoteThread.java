package com.ms.debug;
import com.ms.com.*;

public interface IEnumRemoteThread extends IUnknown
{
  public void Skip(int celt);
  public void Reset();
  public IJavaEnumRemoteThread Clone();
}
