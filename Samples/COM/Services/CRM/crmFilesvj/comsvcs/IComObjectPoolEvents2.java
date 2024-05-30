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

// VTable-only interface IComObjectPoolEvents2
/** @com.interface(iid=683130AE-2E50-11D2-98A5-00C04F8EE1C4, thread=AUTO) */
public interface IComObjectPoolEvents2 extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidObject, [in,type=U4] dwObjsCreated, [in,type=U8] oid) */
  public void OnObjPoolCreateObject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, int dwObjsCreated, long oid);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidObject, [in,type=U4] dwObjsCreated, [in,type=U8] oid) */
  public void OnObjPoolDestroyObject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, int dwObjsCreated, long oid);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U4] dwThreadsWaiting, [in,type=U4] dwAvail, [in,type=U4] dwCreated, [in,type=U4] dwMin, [in,type=U4] dwMax) */
  public void OnObjPoolCreateDecision(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, int dwThreadsWaiting, int dwAvail, int dwCreated, int dwMin, int dwMax);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidObject, [in,type=PTR] guidActivity, [in,type=U4] dwTimeout) */
  public void OnObjPoolTimeout(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, com.ms.com._Guid guidActivity, int dwTimeout);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidObject, [in,type=U4] dwMin, [in,type=U4] dwMax, [in,type=U4] dwTimeout) */
  public void OnObjPoolCreatePool(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, int dwMin, int dwMax, int dwTimeout);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x683130ae, (short)0x2e50, (short)0x11d2, (byte)0x98, (byte)0xa5, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
