package com.ms.debug;
import com.ms.com.*;

public interface IRemoteByteObject extends IRemoteObject
{
  public byte GetValue();
  public void SetValue(byte value);
}
