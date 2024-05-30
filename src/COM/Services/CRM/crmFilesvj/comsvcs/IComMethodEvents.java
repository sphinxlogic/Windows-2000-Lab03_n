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

// VTable-only interface IComMethodEvents
/** @com.interface(iid=683130A9-2E50-11D2-98A5-00C04F8EE1C4, thread=AUTO) */
public interface IComMethodEvents extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] oid, [in,type=PTR] guidCid, [in,type=PTR] guidRid, [in,type=U4] iMeth) */
  public void OnMethodCall(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long oid, com.ms.com._Guid guidCid, com.ms.com._Guid guidRid, int iMeth);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] oid, [in,type=PTR] guidCid, [in,type=PTR] guidRid, [in,type=U4] iMeth, [in,type=U4] hresult) */
  public void OnMethodReturn(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long oid, com.ms.com._Guid guidCid, com.ms.com._Guid guidRid, int iMeth, int hresult);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] oid, [in,type=PTR] guidCid, [in,type=PTR] guidRid, [in,type=U4] iMeth) */
  public void OnMethodException(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long oid, com.ms.com._Guid guidCid, com.ms.com._Guid guidRid, int iMeth);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x683130a9, (short)0x2e50, (short)0x11d2, (byte)0x98, (byte)0xa5, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
