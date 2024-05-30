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

/** @com.class(classid=ECABB0BD-7F19-11D2-978E-0000F8757E2A,DynamicCasts)
*/
public class CRMClerk implements IUnknown,com.ms.com.NoAutoScripting,ICrmLogControl,ICrmMonitorLogRecords
{
  /** @com.method() */
  public native String getTransactionUOW();

  /** @com.method() */
  public native void RegisterCompensator(String lpcwstrProgIdCompensator, String lpcwstrDescription, int lCrmRegFlags);

  /** @com.method() */
  public native void WriteLogRecordVariants(Variant pLogRecord);

  /** @com.method() */
  public native void ForceLog();

  /** @com.method() */
  public native void ForgetLogRecord();

  /** @com.method() */
  public native void ForceTransactionToAbort();

  /** @com.method() */
  public native void WriteLogRecord(comsvcs.tagBLOB rgBlob, int cBlob);

  /** @com.method() */
  public native int getCount();

  /** @com.method() */
  public native int getTransactionState();

  /** @com.method() */
  public native boolean getStructuredRecords();

  /** @com.method() */
  public native void GetLogRecord(int dwIndex, comsvcs.tagCrmLogRecordRead pCrmLogRec);

  /** @com.method() */
  public native Variant GetLogRecordVariants(Variant IndexNumber);


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0xecabb0bd, (short)0x7f19, (short)0x11d2, (byte)0x97, (byte)0x8e, (byte)0x0, (byte)0x0, (byte)0xf8, (byte)0x75, (byte)0x7e, (byte)0x2a);
}
