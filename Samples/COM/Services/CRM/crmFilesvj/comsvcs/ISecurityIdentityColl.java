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

// Dual interface ISecurityIdentityColl
/** @com.interface(iid=CAFC823C-B441-11D1-B82B-0000F8757E2A, thread=AUTO, type=DUAL) */
public interface ISecurityIdentityColl extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=PROPGET, name="Count", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCount();

  /** @com.method(vtoffset=5, dispid=0, type=PROPGET, name="Item", addFlagsVtable=4)
      @com.parameters([in,type=STRING] name, [type=VARIANT] return) */
  public Variant getItem(String name);

  /** @com.method(vtoffset=6, dispid=4294967292, type=PROPGET, name="_NewEnum", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown get_NewEnum();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xcafc823c, (short)0xb441, (short)0x11d1, (byte)0xb8, (byte)0x2b, (byte)0x0, (byte)0x0, (byte)0xf8, (byte)0x75, (byte)0x7e, (byte)0x2a);
}
