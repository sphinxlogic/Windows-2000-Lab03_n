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

// VTable-only interface IProcessTerminateNotify
/** @com.interface(iid=3194B4CF-EF32-11D1-93AE-00AA00BA3258, thread=AUTO) */
public interface IProcessTerminateNotify extends IUnknown
{
  /** @com.method(vtoffset=0, returntype=VOID)
      @com.parameters([in,type=U4] dwPid) */
  public void ProcessShutdown(int dwPid);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x3194b4cf, (short)0xef32, (short)0x11d1, (byte)0x93, (byte)0xae, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xba, (byte)0x32, (byte)0x58);
}
