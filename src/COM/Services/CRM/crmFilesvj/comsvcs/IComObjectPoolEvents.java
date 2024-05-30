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

// VTable-only interface IComObjectPoolEvents
/** @com.interface(iid=683130AD-2E50-11D2-98A5-00C04F8EE1C4, thread=AUTO) */
public interface IComObjectPoolEvents extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidObject, [in,type=I4] nReason, [in,type=U4] dwAvailable, [in,type=U8] oid) */
  public void OnObjPoolPutObject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, int nReason, int dwAvailable, long oid);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidActivity, [in,type=PTR] guidObject, [in,type=U4] dwAvailable, [in,type=U8] oid) */
  public void OnObjPoolGetObject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, com.ms.com._Guid guidObject, int dwAvailable, long oid);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidActivity, [in,type=PTR] guidObject, [in,type=PTR] guidTx, [in,type=U8] objid) */
  public void OnObjPoolRecycleToTx(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, com.ms.com._Guid guidObject, com.ms.com._Guid guidTx, long objid);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidActivity, [in,type=PTR] guidObject, [in,type=PTR] guidTx, [in,type=U8] objid) */
  public void OnObjPoolGetFromTx(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, com.ms.com._Guid guidObject, com.ms.com._Guid guidTx, long objid);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x683130ad, (short)0x2e50, (short)0x11d2, (byte)0x98, (byte)0xa5, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
