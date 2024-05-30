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

// VTable-only interface IObjectContextTip
/** @com.interface(iid=92FD41CA-BAD9-11D2-9A2D-00C04F797BC9, thread=AUTO) */
public interface IObjectContextTip extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String GetTipUrl();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x92fd41ca, (short)0xbad9, (short)0x11d2, (byte)0x9a, (byte)0x2d, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x79, (byte)0x7b, (byte)0xc9);
}
