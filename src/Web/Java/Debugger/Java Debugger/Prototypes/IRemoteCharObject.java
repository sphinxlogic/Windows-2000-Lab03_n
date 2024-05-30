package com.ms.debug;
import com.ms.com.*;

public interface IRemoteCharObject extends IRemoteObject
{
  public char GetValue();
  public void SetValue(char value);
}
