package com.ms.debug;
import com.ms.com.*;

public interface IRemoteContainerField extends IRemoteField
{
  public IJavaEnumRemoteField GetFields(int ulKind, int ulModifiers, String lpcszName);
}
