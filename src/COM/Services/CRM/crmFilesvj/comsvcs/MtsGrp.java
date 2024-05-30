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

/** @com.class(classid=4B2E958D-0393-11D1-B1AB-00AA00BA3258,DynamicCasts)
*/
public class MtsGrp implements IUnknown,com.ms.com.NoAutoScripting,IMtsGrp
{
  /** @com.method() */
  public native int getCount();

  /** @com.method() */
  public native void Item(int lIndex, IUnknown[] ppUnkDispatcher);

  /** @com.method() */
  public native void Refresh();


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0x4b2e958d, (short)0x393, (short)0x11d1, (byte)0xb1, (byte)0xab, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xba, (byte)0x32, (byte)0x58);
}
