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

// VTable-only interface ICrmLogControl
/** @com.interface(iid=A0E174B3-D26E-11D2-8F84-00805FC7BCD9, thread=AUTO) */
public interface ICrmLogControl extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getTransactionUOW();

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] lpcwstrProgIdCompensator, [in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] lpcwstrDescription, [in,type=I4] lCrmRegFlags) */
  public void RegisterCompensator(String lpcwstrProgIdCompensator, String lpcwstrDescription, int lCrmRegFlags);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pLogRecord) */
  public void WriteLogRecordVariants(Variant pLogRecord);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters() */
  public void ForceLog();

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters() */
  public void ForgetLogRecord();

  /** @com.method(vtoffset=5, addFlagsVtable=4)
      @com.parameters() */
  public void ForceTransactionToAbort();

  /** @com.method(vtoffset=6, addFlagsVtable=4)
      @com.parameters([in,type=PTR] rgBlob, [in,type=U4] cBlob) */
  public void WriteLogRecord(comsvcs.tagBLOB rgBlob, int cBlob);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xa0e174b3, (short)0xd26e, (short)0x11d2, (byte)0x8f, (byte)0x84, (byte)0x0, (byte)0x80, (byte)0x5f, (byte)0xc7, (byte)0xbc, (byte)0xd9);
}
