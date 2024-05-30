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

/** @com.class(classid=5CB66670-D3D4-11CF-ACAB-00A024A55AEF,DynamicCasts)
*/
public class TransactionContextEx implements IUnknown,com.ms.com.NoAutoScripting,ITransactionContextEx
{
  // return UNMAPPABLE: Too many indirections.
  //  /** @com.method() */
  //  public native UNMAPPABLE CreateInstance(com.ms.com._Guid rclsid, com.ms.com._Guid riid);

  /** @com.method() */
  public native void Commit();

  /** @com.method() */
  public native void Abort();


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0x5cb66670, (short)0xd3d4, (short)0x11cf, (byte)0xac, (byte)0xab, (byte)0x0, (byte)0xa0, (byte)0x24, (byte)0xa5, (byte)0x5a, (byte)0xef);
}
