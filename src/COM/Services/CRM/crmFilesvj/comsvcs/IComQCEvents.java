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

// VTable-only interface IComQCEvents
/** @com.interface(iid=683130B2-2E50-11D2-98A5-00C04F8EE1C4, thread=AUTO) */
public interface IComQCEvents extends IUnknown
{
  // szQueue UNMAPPABLE: Untranslatable typelib object.
  //  public void OnQCRecord(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long objid, UNMAPPABLE szQueue, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId, int msmqhr);

  // szQueue UNMAPPABLE: Untranslatable typelib object.
  //  public void OnQCQueueOpen(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, UNMAPPABLE szQueue, long QueueID, int hr);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] QueueID, [in,type=PTR] guidMsgId, [in,type=PTR] guidWorkFlowId, [in,type=U4] hr) */
  public void OnQCReceive(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long QueueID, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId, int hr);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] QueueID, [in,type=U4] msmqhr) */
  public void OnQCReceiveFail(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long QueueID, int msmqhr);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidMsgId, [in,type=PTR] guidWorkFlowId, [in,type=U4] RetryIndex) */
  public void OnQCMoveToReTryQueue(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId, int RetryIndex);

  /** @com.method(vtoffset=5, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidMsgId, [in,type=PTR] guidWorkFlowId) */
  public void OnQCMoveToDeadQueue(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId);

  /** @com.method(vtoffset=6, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=U8] objid, [in,type=PTR] guidMsgId, [in,type=PTR] guidWorkFlowId, [in,type=U4] hr) */
  public void OnQCPlayback(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long objid, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId, int hr);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x683130b2, (short)0x2e50, (short)0x11d2, (byte)0x98, (byte)0xa5, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
