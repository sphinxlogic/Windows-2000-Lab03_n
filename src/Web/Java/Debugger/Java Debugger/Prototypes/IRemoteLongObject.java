package com.ms.debug;
import com.ms.com.*;

public interface IRemoteLongObject extends IRemoteObject
{
  public long GetValue();
  public void SetValue(long value);
}
