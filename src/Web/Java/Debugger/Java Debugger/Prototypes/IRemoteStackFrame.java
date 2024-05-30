package com.ms.debug;
import com.ms.com.*;

public interface IRemoteStackFrame extends IUnknown
{
  public IRemoteStackFrame GetCallingFrame();
  public IRemoteContainerObject GetMethodObject();
  public int GetPC();
  public void SetPC(int offPC);
  public int GetKind();
}
