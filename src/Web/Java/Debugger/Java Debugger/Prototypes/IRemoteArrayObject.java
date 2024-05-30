package com.ms.debug;
import com.ms.com.*;

public interface IRemoteArrayObject extends IRemoteObject
{
  public IJavaEnumRemoteObject GetElementObjects();
  public int GetSize();
  public IEnumRemoteValue GetElementValues();
}
