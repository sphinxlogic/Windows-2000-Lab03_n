package com.ms.debug;
import com.ms.com.*;

public interface IEnumRemoteField extends IUnknown
{
  public void Skip(int celt);
  public void Reset();
  public IJavaEnumRemoteField Clone();
  public int GetCount();
}