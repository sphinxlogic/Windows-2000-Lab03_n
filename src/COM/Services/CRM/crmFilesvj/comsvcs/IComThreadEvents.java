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

// VTable-only interface IComThreadEvents
/** @com.interface(iid=683130A5-2E50-11D2-98A5-00C04F8EE1C4, thread=AUTO) */
public interface IComThreadEvents extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ThreadID, [in,type=U4] dwThread, [in,type=U4] dwTheadCnt) */
  public void OnThreadStart(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, int dwThread, int dwTheadCnt);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ThreadID, [in,type=U4] dwThread, [in,type=U4] dwTheadCnt) */
  public void OnThreadTerminate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, int dwThread, int dwTheadCnt);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ThreadID, [in,type=U8] AptID, [in,type=U4] dwActCnt, [in,type=U4] dwLowCnt) */
  public void OnThreadBindToApartment(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long AptID, int dwActCnt, int dwLowCnt);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ThreadID, [in,type=U8] AptID, [in,type=U4] dwActCnt) */
  public void OnThreadUnBind(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long AptID, int dwActCnt);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ThreadID, [in,type=U8] MsgWorkID, [in,type=U4] QueueLen) */
  public void OnThreadWorkEnque(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID, int QueueLen);

  /** @com.method(vtoffset=5, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ThreadID, [in,type=U8] MsgWorkID) */
  public void OnThreadWorkPrivate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID);

  /** @com.method(vtoffset=6, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ThreadID, [in,type=U8] MsgWorkID, [in,type=U4] QueueLen) */
  public void OnThreadWorkPublic(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID, int QueueLen);

  /** @com.method(vtoffset=7, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ThreadID, [in,type=U8] MsgWorkID, [in,type=U4] QueueLen, [in,type=U8] ThreadNum) */
  public void OnThreadWorkRedirect(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID, int QueueLen, long ThreadNum);

  /** @com.method(vtoffset=8, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] ThreadID, [in,type=U8] MsgWorkID, [in,type=U4] QueueLen) */
  public void OnThreadWorkReject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID, int QueueLen);

  /** @com.method(vtoffset=9, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidActivity, [in,type=U8] AptID) */
  public void OnThreadAssignApartment(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, long AptID);

  /** @com.method(vtoffset=10, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] AptID) */
  public void OnThreadUnassignApartment(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long AptID);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x683130a5, (short)0x2e50, (short)0x11d2, (byte)0x98, (byte)0xa5, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
