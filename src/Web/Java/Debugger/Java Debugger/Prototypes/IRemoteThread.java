package com.ms.debug;
import com.ms.com.*;

public interface IRemoteThread extends IUnknown
{
  public String GetName();
  public IRemoteStackFrame GetCurrentFrame();
  public IRemoteThreadGroup GetThreadGroup();
  public void Go();
  public void Step();
  public void StepIn();
  public void StepOut();
  public void RangeStep(int offStart, int offEnd);
  public void RangeStepIn(int offStart, int offEnd);
  public void Destroy();
  public void Suspend();
  public void Resume();
  public int GetSuspendCount();
}
