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

// Dual interface SecurityProperty
/** @com.interface(iid=E74A7215-014D-11D1-A63C-00A0C911B4E0, thread=AUTO, type=DUAL) */
public interface SecurityProperty extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=METHOD, name="GetDirectCallerName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String GetDirectCallerName();

  /** @com.method(vtoffset=5, dispid=1610743809, type=METHOD, name="GetDirectCreatorName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String GetDirectCreatorName();

  /** @com.method(vtoffset=6, dispid=1610743810, type=METHOD, name="GetOriginalCallerName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String GetOriginalCallerName();

  /** @com.method(vtoffset=7, dispid=1610743811, type=METHOD, name="GetOriginalCreatorName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String GetOriginalCreatorName();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xe74a7215, (short)0x14d, (short)0x11d1, (byte)0xa6, (byte)0x3c, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x11, (byte)0xb4, (byte)0xe0);
}
