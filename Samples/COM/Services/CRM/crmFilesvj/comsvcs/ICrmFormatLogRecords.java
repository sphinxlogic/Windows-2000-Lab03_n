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

// VTable-only interface ICrmFormatLogRecords
/** @com.interface(iid=9C51D821-C98B-11D1-82FB-00A0C91EEDE9, thread=AUTO) */
public interface ICrmFormatLogRecords extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([out,size=1,type=ARRAY] plColumnCount) */
  public void GetColumnCount(int[] plColumnCount);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([out,type=PTR] pHeaders) */
  public void GetColumnHeaders(Variant pHeaders);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,size=16,type=STRUCT] crmLogRec, [out,type=PTR] pFormattedLogRecord) */
  public void GetColumn(comsvcs.tagCrmLogRecordRead crmLogRec, Variant pFormattedLogRecord);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] LogRecord, [out,type=PTR] pFormattedLogRecord) */
  public void GetColumnVariants(Variant LogRecord, Variant pFormattedLogRecord);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x9c51d821, (short)0xc98b, (short)0x11d1, (byte)0x82, (byte)0xfb, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x1e, (byte)0xed, (byte)0xe9);
}
