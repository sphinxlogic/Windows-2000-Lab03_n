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

// Dual interface ITransactionContext
/** @com.interface(iid=7999FC21-D3C6-11CF-ACAB-00A024A55AEF, thread=AUTO, type=DUAL) */
public interface ITransactionContext extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=0, type=METHOD, name="CreateInstance", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pszProgId, [type=VARIANT] return) */
  public Variant CreateInstance(String pszProgId);

  /** @com.method(vtoffset=5, dispid=1, type=METHOD, name="Commit", addFlagsVtable=4)
      @com.parameters() */
  public void Commit();

  /** @com.method(vtoffset=6, dispid=2, type=METHOD, name="Abort", addFlagsVtable=4)
      @com.parameters() */
  public void Abort();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x7999fc21, (short)0xd3c6, (short)0x11cf, (byte)0xac, (byte)0xab, (byte)0x0, (byte)0xa0, (byte)0x24, (byte)0xa5, (byte)0x5a, (byte)0xef);
}
