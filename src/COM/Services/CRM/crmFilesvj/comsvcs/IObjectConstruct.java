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

// VTable-only interface IObjectConstruct
/** @com.interface(iid=41C4F8B3-7439-11D2-98CB-00C04F8EE1C4, thread=AUTO) */
public interface IObjectConstruct extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,iid=00020400-0000-0000-C000-000000000046,thread=AUTO,type=DISPATCH] pCtorObj) */
  public void Construct(Object pCtorObj);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x41c4f8b3, (short)0x7439, (short)0x11d2, (byte)0x98, (byte)0xcb, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
