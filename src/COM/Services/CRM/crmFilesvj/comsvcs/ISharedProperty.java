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

// Dual interface ISharedProperty
/** @com.interface(iid=2A005C01-A5DE-11CF-9E66-00AA00A3F464, thread=AUTO, type=DUAL) */
public interface ISharedProperty extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=0, type=PROPGET, name="Value", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getValue();

  /** @com.method(vtoffset=5, dispid=0, type=PROPPUT, name="Value", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] pVal) */
  public void setValue(Variant pVal);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x2a005c01, (short)0xa5de, (short)0x11cf, (byte)0x9e, (byte)0x66, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xa3, (byte)0xf4, (byte)0x64);
}
