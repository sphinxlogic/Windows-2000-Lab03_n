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

// VTable-only interface ICrmCompensator
/** @com.interface(iid=BBC01830-8D3B-11D1-82EC-00A0C91EEDE9, thread=AUTO) */
public interface ICrmCompensator extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,iid=A0E174B3-D26E-11D2-8F84-00805FC7BCD9,thread=AUTO,type=OBJECT] pLogControl) */
  public void SetLogControl(comsvcs.ICrmLogControl pLogControl);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters() */
  public void BeginPrepare();

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,size=16,type=STRUCT] crmLogRec, [type=I4] return) */
  public int PrepareRecord(comsvcs.tagCrmLogRecordRead crmLogRec);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int EndPrepare();

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=I4] fRecovery) */
  public void BeginCommit(int fRecovery);

  /** @com.method(vtoffset=5, addFlagsVtable=4)
      @com.parameters([in,size=16,type=STRUCT] crmLogRec, [type=I4] return) */
  public int CommitRecord(comsvcs.tagCrmLogRecordRead crmLogRec);

  /** @com.method(vtoffset=6, addFlagsVtable=4)
      @com.parameters() */
  public void EndCommit();

  /** @com.method(vtoffset=7, addFlagsVtable=4)
      @com.parameters([in,type=I4] fRecovery) */
  public void BeginAbort(int fRecovery);

  /** @com.method(vtoffset=8, addFlagsVtable=4)
      @com.parameters([in,size=16,type=STRUCT] crmLogRec, [type=I4] return) */
  public int AbortRecord(comsvcs.tagCrmLogRecordRead crmLogRec);

  /** @com.method(vtoffset=9, addFlagsVtable=4)
      @com.parameters() */
  public void EndAbort();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xbbc01830, (short)0x8d3b, (short)0x11d1, (byte)0x82, (byte)0xec, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x1e, (byte)0xed, (byte)0xe9);
}
