package com.ms.debug;
import com.ms.com.*;

public interface IEnumRemoteValue extends IUnknown
{
  public void Skip(int celt);
  public void Reset();
  public IEnumRemoteValue Clone();
  public int GetCount();
}
