package com.ms.debug;
import com.ms.com.*;

public interface IRemoteProcess extends IUnknown
{
  public void RegisterCallback(IRemoteProcessCallback callback);
  public void Detach();
  public void Break();
  public IRemoteContainerObject GetGlobalContainerObject();
  public IRemoteClassField FindClass(String className);
  public void TraceMethods(int bTraceOn);
  public IJavaEnumRemoteThreadGroup GetThreadGroups();
}
