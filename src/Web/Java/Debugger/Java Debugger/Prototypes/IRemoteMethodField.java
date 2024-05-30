package com.ms.debug;
import com.ms.com.*;

public interface IRemoteMethodField extends IRemoteContainerField
{
  public void SetBreakpoint(int offPC);
  public void ClearBreakpoint(int offPC);
  public IJavaEnumLINEINFO GetLineInfo();
  public ILockBytes GetBytes();
  // GetScope() returns the length of the field's scope.  poffStart is a
  // one-integer array whose only element will be filled in with the start
  // offset of the field's scope.
  public int GetScope(IRemoteField pField, int[] poffStart);
  public IRemoteField GetIndexedField(int slot, int offPC);
}
