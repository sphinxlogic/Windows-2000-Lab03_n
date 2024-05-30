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

// Dual interface IMtsGrp
/** @com.interface(iid=4B2E958C-0393-11D1-B1AB-00AA00BA3258, thread=AUTO, type=DUAL) */
public interface IMtsGrp extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1, type=PROPGET, name="Count", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCount();

  /** @com.method(vtoffset=5, dispid=2, type=METHOD, name="Item", addFlagsVtable=4)
      @com.parameters([in,type=I4] lIndex, [out,size=1,elementType=OBJECT,type=ARRAY] ppUnkDispatcher) */
  public void Item(int lIndex, IUnknown[] ppUnkDispatcher);

  /** @com.method(vtoffset=6, dispid=3, type=METHOD, name="Refresh", addFlagsVtable=4)
      @com.parameters() */
  public void Refresh();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x4b2e958c, (short)0x393, (short)0x11d1, (byte)0xb1, (byte)0xab, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xba, (byte)0x32, (byte)0x58);
}
