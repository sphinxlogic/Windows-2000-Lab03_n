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

/** @com.class(classid=71E38F91-7E88-11CF-9EDE-0080C78B7F89,DynamicCasts)
*/
public class AppServer implements IUnknown,com.ms.com.NoAutoScripting,IMTxAS
{
  /** @com.method() */
  public native comsvcs.ObjectContext GetObjectContext();

  /** @com.method() */
  public native Variant SafeRef(Variant vRefIn);


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0x71e38f91, (short)0x7e88, (short)0x11cf, (byte)0x9e, (byte)0xde, (byte)0x0, (byte)0x80, (byte)0xc7, (byte)0x8b, (byte)0x7f, (byte)0x89);
}
