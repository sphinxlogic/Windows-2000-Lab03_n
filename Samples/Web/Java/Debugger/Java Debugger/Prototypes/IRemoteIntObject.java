package com.ms.debug;
import com.ms.com.*;

public interface IRemoteIntObject extends IRemoteObject
{
  public int GetValue();
  public void SetValue(int value);
}
