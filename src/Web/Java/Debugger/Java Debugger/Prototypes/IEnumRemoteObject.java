package com.ms.debug;
import com.ms.com.*;

public interface IEnumRemoteObject extends IUnknown
{
  public void Skip(int celt);
  public void Reset();
  public IJavaEnumRemoteObject Clone();
  public int GetCount();
}
