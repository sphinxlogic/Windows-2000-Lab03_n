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

// VTable-only interface IEventServer
/** @com.interface(iid=F1CB0608-EC04-11D1-93AE-00AA00BA3258, thread=AUTO) */
public interface IEventServer extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=U4] dwPid, [in,type=PTR] appGuid, [in,type=U4] dwEvents, [in,type=U4] cbSize, [in,size=1,type=ARRAY] pBuf) */
  public void DispatchManyEvents(int dwPid, com.ms.com._Guid appGuid, int dwEvents, int cbSize, byte[] pBuf);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=U4] dwPid, [in,type=PTR] appGuid, [in,type=U4] cbSize, [in,size=1,type=ARRAY] pBuf) */
  public void DispatchOneEvent(int dwPid, com.ms.com._Guid appGuid, int cbSize, byte[] pBuf);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=U4] dwPid, [in,type=PTR] guidApp, [out,size=1,type=ARRAY] pdwInitialEventMask, [out,size=1,type=ARRAY] ppUnkCallfactory) */
  public void AddProcess(int dwPid, com.ms.com._Guid guidApp, int[] pdwInitialEventMask, IUnknown[] ppUnkCallfactory);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,type=U4] dwPid) */
  public void RemoveProcess(int dwPid);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=U4] dwPid, [out,size=1,type=ARRAY] ppUnkCallfactory) */
  public void GetCallFactoryObject(int dwPid, IUnknown[] ppUnkCallfactory);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xf1cb0608, (short)0xec04, (short)0x11d1, (byte)0x93, (byte)0xae, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xba, (byte)0x32, (byte)0x58);
}
