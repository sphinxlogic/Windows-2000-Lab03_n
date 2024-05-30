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

// Dual interface IMTSLocator
/** @com.interface(iid=D19B8BFD-7F88-11D0-B16E-00AA00BA3258, thread=AUTO, type=DUAL) */
public interface IMTSLocator extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1, type=METHOD, name="GetEventDispatcher", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown GetEventDispatcher();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xd19b8bfd, (short)0x7f88, (short)0x11d0, (byte)0xb1, (byte)0x6e, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xba, (byte)0x32, (byte)0x58);
}
