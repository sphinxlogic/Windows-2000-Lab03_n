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

/** @com.class(classid=ECABB0C3-7F19-11D2-978E-0000F8757E2A,DynamicCasts)
*/
public class ComServiceEvents implements IUnknown,com.ms.com.NoAutoScripting,IComThreadEvents,IComUserEvent,IComAppEvents,IComInstanceEvents,IComTransactionEvents,IComMethodEvents,IComObjectEvents,IComResourceEvents,IComSecurityEvents,IComObjectPoolEvents,IComObjectPoolEvents2,IComObjectConstructionEvents,IComActivityEvents,IComIdentityEvents,IComQCEvents,IComExceptionEvents,IComCRMEvents
{
  /** @com.method() */
  public native void OnThreadStart(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, int dwThread, int dwTheadCnt);

  /** @com.method() */
  public native void OnThreadTerminate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, int dwThread, int dwTheadCnt);

  /** @com.method() */
  public native void OnThreadBindToApartment(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long AptID, int dwActCnt, int dwLowCnt);

  /** @com.method() */
  public native void OnThreadUnBind(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long AptID, int dwActCnt);

  /** @com.method() */
  public native void OnThreadWorkEnque(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID, int QueueLen);

  /** @com.method() */
  public native void OnThreadWorkPrivate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID);

  /** @com.method() */
  public native void OnThreadWorkPublic(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID, int QueueLen);

  /** @com.method() */
  public native void OnThreadWorkRedirect(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID, int QueueLen, long ThreadNum);

  /** @com.method() */
  public native void OnThreadWorkReject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ThreadID, long MsgWorkID, int QueueLen);

  /** @com.method() */
  public native void OnThreadAssignApartment(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, long AptID);

  /** @com.method() */
  public native void OnThreadUnassignApartment(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long AptID);

  /** @com.method() */
  public native void OnUserEvent(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, Variant pvarEvent);

  /** @com.method() */
  public native void OnAppActivation(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidApp);

  /** @com.method() */
  public native void OnAppShutdown(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidApp);

  /** @com.method() */
  public native void OnAppForceShutdown(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidApp);

  /** @com.method() */
  public native void OnObjectCreate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, com.ms.com._Guid clsid, com.ms.com._Guid tsid, long CtxtID, long ObjectID);

  /** @com.method() */
  public native void OnObjectDestroy(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long CtxtID);

  /** @com.method() */
  public native void OnTransactionStart(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidTx, com.ms.com._Guid tsid, int fRoot);

  /** @com.method() */
  public native void OnTransactionPrepare(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidTx, int fVoteYes);

  /** @com.method() */
  public native void OnTransactionAbort(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidTx);

  /** @com.method() */
  public native void OnTransactionCommit(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidTx);

  /** @com.method() */
  public native void OnMethodCall(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long oid, com.ms.com._Guid guidCid, com.ms.com._Guid guidRid, int iMeth);

  /** @com.method() */
  public native void OnMethodReturn(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long oid, com.ms.com._Guid guidCid, com.ms.com._Guid guidRid, int iMeth, int hresult);

  /** @com.method() */
  public native void OnMethodException(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long oid, com.ms.com._Guid guidCid, com.ms.com._Guid guidRid, int iMeth);

  /** @com.method() */
  public native void OnObjectActivate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long CtxtID, long ObjectID);

  /** @com.method() */
  public native void OnObjectDeactivate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long CtxtID, long ObjectID);

  /** @com.method() */
  public native void OnDisableCommit(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long CtxtID);

  /** @com.method() */
  public native void OnEnableCommit(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long CtxtID);

  /** @com.method() */
  public native void OnSetComplete(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long CtxtID);

  /** @com.method() */
  public native void OnSetAbort(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long CtxtID);

  /** @com.method() */
  public native void OnResourceCreate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, String pszType, long resId, int enlisted);

  /** @com.method() */
  public native void OnResourceAllocate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, String pszType, long resId, int enlisted, int NumRated, int Rating);

  /** @com.method() */
  public native void OnResourceRecycle(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, String pszType, long resId);

  /** @com.method() */
  public native void OnResourceDestroy(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, int hr, String pszType, long resId);

  /** @com.method() */
  public native void OnResourceTrack(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long ObjectID, String pszType, long resId, int enlisted);

  /** @com.method() */
  public native void OnAuthenticate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, long ObjectID, com.ms.com._Guid guidIID, int iMeth, int cbByteOrig, byte[] pSidOriginalUser, int cbByteCur, byte[] pSidCurrentUser, int bCurrentUserInpersonatingInProc);

  /** @com.method() */
  public native void OnAuthenticateFail(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, long ObjectID, com.ms.com._Guid guidIID, int iMeth, int cbByteOrig, byte[] pSidOriginalUser, int cbByteCur, byte[] pSidCurrentUser, int bCurrentUserInpersonatingInProc);

  /** @com.method() */
  public native void OnObjPoolPutObject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, int nReason, int dwAvailable, long oid);

  /** @com.method() */
  public native void OnObjPoolGetObject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, com.ms.com._Guid guidObject, int dwAvailable, long oid);

  /** @com.method() */
  public native void OnObjPoolRecycleToTx(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, com.ms.com._Guid guidObject, com.ms.com._Guid guidTx, long objid);

  /** @com.method() */
  public native void OnObjPoolGetFromTx(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, com.ms.com._Guid guidObject, com.ms.com._Guid guidTx, long objid);

  /** @com.method() */
  public native void OnObjPoolCreateObject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, int dwObjsCreated, long oid);

  /** @com.method() */
  public native void OnObjPoolDestroyObject(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, int dwObjsCreated, long oid);

  /** @com.method() */
  public native void OnObjPoolCreateDecision(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, int dwThreadsWaiting, int dwAvail, int dwCreated, int dwMin, int dwMax);

  /** @com.method() */
  public native void OnObjPoolTimeout(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, com.ms.com._Guid guidActivity, int dwTimeout);

  /** @com.method() */
  public native void OnObjPoolCreatePool(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, int dwMin, int dwMax, int dwTimeout);

  /** @com.method() */
  public native void OnObjectConstruct(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidObject, String sConstructString, long oid);

  /** @com.method() */
  public native void OnActivityCreate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity);

  /** @com.method() */
  public native void OnActivityDestroy(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity);

  /** @com.method() */
  public native void OnActivityEnter(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidCurrent, com.ms.com._Guid guidEntered, int dwThread);

  /** @com.method() */
  public native void OnActivityTimeout(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidCurrent, com.ms.com._Guid guidEntered, int dwThread, int dwTimeout);

  /** @com.method() */
  public native void OnActivityReenter(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidCurrent, int dwThread, int dwCallDepth);

  /** @com.method() */
  public native void OnActivityLeave(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidCurrent, com.ms.com._Guid guidLeft);

  /** @com.method() */
  public native void OnActivityLeaveSame(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidCurrent, int dwCallDepth);

  /** @com.method() */
  public native void OnIISRequestInfo(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long objid, String pszClientIP, String pszServerIP, String pszURL);

  // szQueue UNMAPPABLE: Untranslatable typelib object.
  //  /** @com.method() */
  //  public native void OnQCRecord(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long objid, UNMAPPABLE szQueue, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId, int msmqhr);

  // szQueue UNMAPPABLE: Untranslatable typelib object.
  //  /** @com.method() */
  //  public native void OnQCQueueOpen(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, UNMAPPABLE szQueue, long QueueID, int hr);

  /** @com.method() */
  public native void OnQCReceive(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long QueueID, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId, int hr);

  /** @com.method() */
  public native void OnQCReceiveFail(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long QueueID, int msmqhr);

  /** @com.method() */
  public native void OnQCMoveToReTryQueue(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId, int RetryIndex);

  /** @com.method() */
  public native void OnQCMoveToDeadQueue(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId);

  /** @com.method() */
  public native void OnQCPlayback(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, long objid, com.ms.com._Guid guidMsgId, com.ms.com._Guid guidWorkFlowId, int hr);

  /** @com.method() */
  public native void OnExceptionUser(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, int code, long address, String pszStackTrace);

  /** @com.method() */
  public native void OnCRMRecoveryStart(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidApp);

  /** @com.method() */
  public native void OnCRMRecoveryDone(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidApp);

  /** @com.method() */
  public native void OnCRMCheckpoint(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidApp);

  // szProgIdCompensator UNMAPPABLE: Untranslatable typelib object.
  // szDescription UNMAPPABLE: Untranslatable typelib object.
  //  /** @com.method() */
  //  public native void OnCRMBegin(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID, com.ms.com._Guid guidActivity, com.ms.com._Guid guidTx, UNMAPPABLE szProgIdCompensator, UNMAPPABLE szDescription);

  /** @com.method() */
  public native void OnCRMPrepare(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method() */
  public native void OnCRMCommit(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method() */
  public native void OnCRMAbort(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method() */
  public native void OnCRMIndoubt(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method() */
  public native void OnCRMDone(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method() */
  public native void OnCRMRelease(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method() */
  public native void OnCRMAnalyze(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID, int dwCrmRecordType, int dwRecordSize);

  /** @com.method() */
  public native void OnCRMWrite(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID, int fVariants, int dwRecordSize);

  /** @com.method() */
  public native void OnCRMForget(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method() */
  public native void OnCRMForce(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method() */
  public native void OnCRMDeliver(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID, int fVariants, int dwRecordSize);


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0xecabb0c3, (short)0x7f19, (short)0x11d2, (byte)0x97, (byte)0x8e, (byte)0x0, (byte)0x0, (byte)0xf8, (byte)0x75, (byte)0x7e, (byte)0x2a);
}
