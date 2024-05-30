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

// VTable-only interface IComResourceEvents
/** @com.interface(iid=683130AB-2E50-11D2-98A5-00C04F8EE1C4, thread=AUTO) */
public interface IComResourceEvents extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ObjectID, [in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] pszType, [in,type=U8] resId, [in,type=I4] enlisted) */
  public void OnResourceCreate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, String pszType, long resId, int enlisted);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ObjectID, [in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] pszType, [in,type=U8] resId, [in,type=I4] enlisted, [in,type=U4] NumRated, [in,type=U4] Rating) */
  public void OnResourceAllocate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, String pszType, long resId, int enlisted, int NumRated, int Rating);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ObjectID, [in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] pszType, [in,type=U8] resId) */
  public void OnResourceRecycle(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, String pszType, long resId);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ObjectID, [in,type=U4] hr, [in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] pszType, [in,type=U8] resId) */
  public void OnResourceDestroy(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, int hr, String pszType, long resId);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ObjectID, [in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] pszType, [in,type=U8] resId, [in,type=I4] enlisted) */
  public void OnResourceTrack(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, String pszType, long resId, int enlisted);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x683130ab, (short)0x2e50, (short)0x11d2, (byte)0x98, (byte)0xa5, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
