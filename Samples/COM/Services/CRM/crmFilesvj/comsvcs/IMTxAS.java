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

// Dual interface IMTxAS
/** @com.interface(iid=74C08641-CEDB-11CF-8B49-00AA00B8A790, thread=AUTO, type=DUAL) */
public interface IMTxAS extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=METHOD, name="GetObjectContext", addFlagsVtable=4)
      @com.parameters([iid=74C08646-CEDB-11CF-8B49-00AA00B8A790,thread=AUTO,type=DISPATCH] return) */
  public comsvcs.ObjectContext GetObjectContext();

  /** @com.method(vtoffset=5, dispid=1610743809, type=METHOD, name="SafeRef", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] vRefIn, [type=VARIANT] return) */
  public Variant SafeRef(Variant vRefIn);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x74c08641, (short)0xcedb, (short)0x11cf, (byte)0x8b, (byte)0x49, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xb8, (byte)0xa7, (byte)0x90);
}
