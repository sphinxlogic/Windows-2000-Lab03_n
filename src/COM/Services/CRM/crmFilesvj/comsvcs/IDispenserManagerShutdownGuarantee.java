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

// VTable-only interface IDispenserManagerShutdownGuarantee
/** @com.interface(iid=5CB31E11-2B5F-11CF-BE10-00AA00A2FA25, thread=AUTO) */
public interface IDispenserManagerShutdownGuarantee extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([out,size=1,type=ARRAY] pfIsComPlusApp) */
  public void IsComPlusApp(int[] pfIsComPlusApp);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x5cb31e11, (short)0x2b5f, (short)0x11cf, (byte)0xbe, (byte)0x10, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xa2, (byte)0xfa, (byte)0x25);
}
