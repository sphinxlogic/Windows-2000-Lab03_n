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

// VTable-only interface IObjectContextActivity
/** @com.interface(iid=51372AFC-CAE7-11CF-BE81-00AA00A2FA25, thread=AUTO) */
public interface IObjectContextActivity extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([out,type=PTR] pGUID) */
  public void GetActivityId(com.ms.com._Guid pGUID);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x51372afc, (short)0xcae7, (short)0x11cf, (byte)0xbe, (byte)0x81, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xa2, (byte)0xfa, (byte)0x25);
}
