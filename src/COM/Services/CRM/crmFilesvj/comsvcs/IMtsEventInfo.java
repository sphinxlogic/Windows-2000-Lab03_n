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

// Dual interface IMtsEventInfo
/** @com.interface(iid=D56C3DC1-8482-11D0-B170-00AA00BA3258, thread=AUTO, type=DUAL) */
public interface IMtsEventInfo extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=PROPGET, name="Names", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown getNames();

  /** @com.method(vtoffset=5, dispid=1, type=PROPGET, name="DisplayName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getDisplayName();

  /** @com.method(vtoffset=6, dispid=1610743810, type=PROPGET, name="EventID", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getEventID();

  /** @com.method(vtoffset=7, dispid=1610743811, type=PROPGET, name="Count", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCount();

  /** @com.method(vtoffset=8, dispid=1610743812, type=PROPGET, name="Value", addFlagsVtable=4)
      @com.parameters([in,type=STRING] sKey, [type=VARIANT] return) */
  public Variant getValue(String sKey);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xd56c3dc1, (short)0x8482, (short)0x11d0, (byte)0xb1, (byte)0x70, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xba, (byte)0x32, (byte)0x58);
}
