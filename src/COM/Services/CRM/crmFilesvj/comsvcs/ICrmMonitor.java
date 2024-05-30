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

// VTable-only interface ICrmMonitor
/** @com.interface(iid=70C8E443-C7ED-11D1-82FB-00A0C91EEDE9, thread=AUTO) */
public interface ICrmMonitor extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([iid=70C8E442-C7ED-11D1-82FB-00A0C91EEDE9,thread=AUTO,type=DISPATCH] return) */
  public comsvcs.ICrmMonitorClerks GetClerks();

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index, [type=VARIANT] return) */
  public Variant HoldClerk(Variant Index);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x70c8e443, (short)0xc7ed, (short)0x11d1, (byte)0x82, (byte)0xfb, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x1e, (byte)0xed, (byte)0xe9);
}
