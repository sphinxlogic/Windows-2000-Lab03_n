package com.ms.debug;
import com.ms.com.*;

public interface IRemoteField extends IUnknown
{
  public String GetName();
  public int GetKind();
  public IRemoteField GetType();
  public IRemoteContainerField GetContainer();
  public int GetModifiers();
}
