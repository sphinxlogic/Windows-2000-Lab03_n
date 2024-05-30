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

// Dual interface ContextInfo
/** @com.interface(iid=19A5A02C-0AC8-11D2-B286-00C04F8EF934, thread=AUTO, type=DUAL) */
public interface ContextInfo extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=100671488, type=METHOD, name="IsInTransaction", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean IsInTransaction();

  /** @com.method(vtoffset=5, dispid=1610743811, type=METHOD, name="GetTransaction", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown GetTransaction();

  /** @com.method(vtoffset=6, dispid=1610743812, type=METHOD, name="GetTransactionId", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String GetTransactionId();

  /** @com.method(vtoffset=7, dispid=1610743813, type=METHOD, name="GetActivityId", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String GetActivityId();

  /** @com.method(vtoffset=8, dispid=1610743814, type=METHOD, name="GetContextId", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String GetContextId();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x19a5a02c, (short)0xac8, (short)0x11d2, (byte)0xb2, (byte)0x86, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xf9, (byte)0x34);
}
