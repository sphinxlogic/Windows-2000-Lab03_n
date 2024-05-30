//
// Auto-generated using JActiveX.EXE 4.79.2337
//   (jactivex /nologo /d . /e /l "comsvcs.lst" C:\WINNT\System32\comsvcs.dll)
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package comsvcs;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

/** @com.class(classid=ECABAFBC-7F19-11D2-978E-0000F8757E2A,DynamicCasts)
*/
public class EventServer implements IUnknown,com.ms.com.NoAutoScripting,IEventServer,IProcessTerminateNotify
{
  /** @com.method() */
  public native void DispatchManyEvents(int dwPid, com.ms.com._Guid appGuid, int dwEvents, int cbSize, byte[] pBuf);

  /** @com.method() */
  public native void DispatchOneEvent(int dwPid, com.ms.com._Guid appGuid, int cbSize, byte[] pBuf);

  /** @com.method() */
  public native void AddProcess(int dwPid, com.ms.com._Guid guidApp, int[] pdwInitialEventMask, IUnknown[] ppUnkCallfactory);

  /** @com.method() */
  public native void RemoveProcess(int dwPid);

  /** @com.method() */
  public native void GetCallFactoryObject(int dwPid, IUnknown[] ppUnkCallfactory);

  /** @com.method() */
  public native void ProcessShutdown(int dwPid);


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0xecabafbc, (short)0x7f19, (short)0x11d2, (byte)0x97, (byte)0x8e, (byte)0x0, (byte)0x0, (byte)0xf8, (byte)0x75, (byte)0x7e, (byte)0x2a);
}
