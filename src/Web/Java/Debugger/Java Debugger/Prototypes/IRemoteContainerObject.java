package com.ms.debug;
import com.ms.com.*;

public interface IRemoteContainerObject extends IRemoteObject
{
  public IRemoteObject GetFieldObject(IRemoteField field);
}
