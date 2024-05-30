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

// Dual interface ObjectContext
/** @com.interface(iid=74C08646-CEDB-11CF-8B49-00AA00B8A790, thread=AUTO, type=DUAL) */
public interface ObjectContext extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=METHOD, name="CreateInstance", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrProgID, [type=VARIANT] return) */
  public Variant CreateInstance(String bstrProgID);

  /** @com.method(vtoffset=5, dispid=1610743809, type=METHOD, name="SetComplete", addFlagsVtable=4)
      @com.parameters() */
  public void SetComplete();

  /** @com.method(vtoffset=6, dispid=1610743810, type=METHOD, name="SetAbort", addFlagsVtable=4)
      @com.parameters() */
  public void SetAbort();

  /** @com.method(vtoffset=7, dispid=1610743811, type=METHOD, name="EnableCommit", addFlagsVtable=4)
      @com.parameters() */
  public void EnableCommit();

  /** @com.method(vtoffset=8, dispid=1610743812, type=METHOD, name="DisableCommit", addFlagsVtable=4)
      @com.parameters() */
  public void DisableCommit();

  /** @com.method(vtoffset=9, dispid=1610743813, type=METHOD, name="IsInTransaction", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean IsInTransaction();

  /** @com.method(vtoffset=10, dispid=1610743814, type=METHOD, name="IsSecurityEnabled", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean IsSecurityEnabled();

  /** @com.method(vtoffset=11, dispid=1610743815, type=METHOD, name="IsCallerInRole", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrRole, [type=BOOLEAN] return) */
  public boolean IsCallerInRole(String bstrRole);

  /** @com.method(vtoffset=12, dispid=1610743840, type=PROPGET, name="Count", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCount();

  /** @com.method(vtoffset=13, dispid=0, type=PROPGET, name="Item", addFlagsVtable=4)
      @com.parameters([in,type=STRING] name, [type=VARIANT] return) */
  public Variant getItem(String name);

  /** @com.method(vtoffset=14, dispid=4294967292, type=PROPGET, name="_NewEnum", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown get_NewEnum();

  /** @com.method(vtoffset=15, dispid=1610743843, type=PROPGET, name="Security", addFlagsVtable=4)
      @com.parameters([iid=E74A7215-014D-11D1-A63C-00A0C911B4E0,thread=AUTO,type=DISPATCH] return) */
  public comsvcs.SecurityProperty getSecurity();

  /** @com.method(vtoffset=16, dispid=1610743844, type=PROPGET, name="ContextInfo", addFlagsVtable=4)
      @com.parameters([iid=19A5A02C-0AC8-11D2-B286-00C04F8EF934,thread=AUTO,type=DISPATCH] return) */
  public comsvcs.ContextInfo getContextInfo();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x74c08646, (short)0xcedb, (short)0x11cf, (byte)0x8b, (byte)0x49, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xb8, (byte)0xa7, (byte)0x90);
}
