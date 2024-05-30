package com.ms.debug;
import com.ms.com.*;

public interface IRemoteClassField extends IRemoteContainerField
{
  public String GetFileName();
  public String GetSourceFileName();
  public IRemoteClassField GetSuperclass();
  public IJavaEnumRemoteField GetInterfaces();
  // Use ConstantPoolHelper for GetConstantPoolItem().
}
