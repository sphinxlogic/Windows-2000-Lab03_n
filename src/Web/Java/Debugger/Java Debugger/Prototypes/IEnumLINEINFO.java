package com.ms.debug;
import com.ms.com.*;

public interface IEnumLINEINFO extends IUnknown
{
  public void Skip(int celt);
  public void Reset();
  public IJavaEnumLINEINFO Clone();
  public int GetCount();
}
