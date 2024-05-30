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

// VTable-only interface ObjectControl
/** @com.interface(iid=7DC41850-0C31-11D0-8B79-00AA00B8A790, thread=AUTO) */
public interface ObjectControl extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters() */
  public void Activate();

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters() */
  public void Deactivate();

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean CanBePooled();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x7dc41850, (short)0xc31, (short)0x11d0, (byte)0x8b, (byte)0x79, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xb8, (byte)0xa7, (byte)0x90);
}
