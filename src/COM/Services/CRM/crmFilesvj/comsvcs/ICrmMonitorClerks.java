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

// Dual interface ICrmMonitorClerks
/** @com.interface(iid=70C8E442-C7ED-11D1-82FB-00A0C91EEDE9, thread=AUTO, type=DUAL) */
public interface ICrmMonitorClerks extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=0, type=METHOD, name="Item", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index, [type=VARIANT] return) */
  public Variant Item(Variant Index);

  /** @com.method(vtoffset=5, dispid=4294967292, type=PROPGET, name="_NewEnum", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown get_NewEnum();

  /** @com.method(vtoffset=6, dispid=1, type=PROPGET, name="Count", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCount();

  /** @com.method(vtoffset=7, dispid=2, type=METHOD, name="ProgIdCompensator", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index, [type=VARIANT] return) */
  public Variant ProgIdCompensator(Variant Index);

  /** @com.method(vtoffset=8, dispid=3, type=METHOD, name="Description", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index, [type=VARIANT] return) */
  public Variant Description(Variant Index);

  /** @com.method(vtoffset=9, dispid=4, type=METHOD, name="TransactionUOW", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index, [type=VARIANT] return) */
  public Variant TransactionUOW(Variant Index);

  /** @com.method(vtoffset=10, dispid=5, type=METHOD, name="ActivityId", addFlagsVtable=4)
      @com.parameters([in,type=VARIANT] Index, [type=VARIANT] return) */
  public Variant ActivityId(Variant Index);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x70c8e442, (short)0xc7ed, (short)0x11d1, (byte)0x82, (byte)0xfb, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x1e, (byte)0xed, (byte)0xe9);
}
