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

/** @com.class(classid=ECABB0A9-7F19-11D2-978E-0000F8757E2A,DynamicCasts)
*/
public class Dummy30040732 implements IUnknown,com.ms.com.NoAutoScripting,IObjectContext,IObjectContextActivity,IObjectContextInfo,IObjectConstruct,IObjectConstructString,IObjectControl,IObjectContextTip,IPlaybackControl,ISecurityProperty,ICrmCompensator,ICrmCompensatorVariants,ICrmFormatLogRecords
{
  // return UNMAPPABLE: Too many indirections.
  //  /** @com.method() */
  //  public native UNMAPPABLE CreateInstance(com.ms.com._Guid rclsid, com.ms.com._Guid riid);

  /** @com.method() */
  public native void SetComplete();

  /** @com.method() */
  public native void SetAbort();

  /** @com.method() */
  public native void EnableCommit();

  /** @com.method() */
  public native void DisableCommit();

  /** @com.method() */
  public native int IsInTransaction();

  /** @com.method() */
  public native int IsSecurityEnabled();

  /** @com.method() */
  public native int IsCallerInRole(String bstrRole);

  /** @com.method() */
  public native void GetActivityId(com.ms.com._Guid pGUID);

  // IsInTransaction UNMAPPABLE: Name is a keyword or conflicts with another member.
  //  /** @com.method() */
  //  public native int IsInTransaction();

  /** @com.method() */
  public native void GetTransaction(IUnknown[] pptrans);

  /** @com.method() */
  public native void GetTransactionId(com.ms.com._Guid pGUID);

  // GetActivityId UNMAPPABLE: Name is a keyword or conflicts with another member.
  //  /** @com.method() */
  //  public native void GetActivityId(com.ms.com._Guid pGUID);

  /** @com.method() */
  public native void GetContextId(com.ms.com._Guid pGUID);

  /** @com.method() */
  public native void Construct(Object pCtorObj);

  /** @com.method() */
  public native String getConstructString();

  /** @com.method() */
  public native void Activate();

  /** @com.method() */
  public native void Deactivate();

  /** @com.method() */
  public native int CanBePooled();

  /** @com.method() */
  public native String GetTipUrl();

  /** @com.method() */
  public native void FinalClientRetry();

  /** @com.method() */
  public native void FinalServerRetry();

  // pSID UNMAPPABLE: Too many indirections.
  //  /** @com.method() */
  //  public native void GetDirectCreatorSID(UNMAPPABLE pSID);

  // pSID UNMAPPABLE: Too many indirections.
  //  /** @com.method() */
  //  public native void GetOriginalCreatorSID(UNMAPPABLE pSID);

  // pSID UNMAPPABLE: Too many indirections.
  //  /** @com.method() */
  //  public native void GetDirectCallerSID(UNMAPPABLE pSID);

  // pSID UNMAPPABLE: Too many indirections.
  //  /** @com.method() */
  //  public native void GetOriginalCallerSID(UNMAPPABLE pSID);

  // pSID UNMAPPABLE: Too many indirections.
  //  /** @com.method() */
  //  public native void ReleaseSID(UNMAPPABLE pSID);

  /** @com.method() */
  public native void SetLogControl(comsvcs.ICrmLogControl pLogControl);

  /** @com.method() */
  public native void BeginPrepare();

  /** @com.method() */
  public native int PrepareRecord(comsvcs.tagCrmLogRecordRead crmLogRec);

  /** @com.method() */
  public native int EndPrepare();

  /** @com.method() */
  public native void BeginCommit(int fRecovery);

  /** @com.method() */
  public native int CommitRecord(comsvcs.tagCrmLogRecordRead crmLogRec);

  /** @com.method() */
  public native void EndCommit();

  /** @com.method() */
  public native void BeginAbort(int fRecovery);

  /** @com.method() */
  public native int AbortRecord(comsvcs.tagCrmLogRecordRead crmLogRec);

  /** @com.method() */
  public native void EndAbort();

  /** @com.method() */
  public native void SetLogControlVariants(comsvcs.ICrmLogControl pLogControl);

  /** @com.method() */
  public native void BeginPrepareVariants();

  /** @com.method() */
  public native boolean PrepareRecordVariants(Variant pLogRecord);

  /** @com.method() */
  public native boolean EndPrepareVariants();

  /** @com.method() */
  public native void BeginCommitVariants(boolean bRecovery);

  /** @com.method() */
  public native boolean CommitRecordVariants(Variant pLogRecord);

  /** @com.method() */
  public native void EndCommitVariants();

  /** @com.method() */
  public native void BeginAbortVariants(boolean bRecovery);

  /** @com.method() */
  public native boolean AbortRecordVariants(Variant pLogRecord);

  /** @com.method() */
  public native void EndAbortVariants();

  /** @com.method() */
  public native void GetColumnCount(int[] plColumnCount);

  /** @com.method() */
  public native void GetColumnHeaders(Variant pHeaders);

  /** @com.method() */
  public native void GetColumn(comsvcs.tagCrmLogRecordRead crmLogRec, Variant pFormattedLogRecord);

  /** @com.method() */
  public native void GetColumnVariants(Variant LogRecord, Variant pFormattedLogRecord);


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0xecabb0a9, (short)0x7f19, (short)0x11d2, (byte)0x97, (byte)0x8e, (byte)0x0, (byte)0x0, (byte)0xf8, (byte)0x75, (byte)0x7e, (byte)0x2a);
}
