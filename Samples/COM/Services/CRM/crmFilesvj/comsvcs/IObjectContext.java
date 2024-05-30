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

// VTable-only interface IObjectContext
/** @com.interface(iid=51372AE0-CAE7-11CF-BE81-00AA00A2FA25, thread=AUTO) */
public interface IObjectContext extends IUnknown
{
  // return UNMAPPABLE: Too many indirections.
  //  public UNMAPPABLE CreateInstance(com.ms.com._Guid rclsid, com.ms.com._Guid riid);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters() */
  public void SetComplete();

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters() */
  public void SetAbort();

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters() */
  public void EnableCommit();

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters() */
  public void DisableCommit();

  /** @com.method(vtoffset=5, returntype=VOID)
      @com.parameters([type=I4] return) */
  public int IsInTransaction();

  /** @com.method(vtoffset=6, returntype=VOID)
      @com.parameters([type=I4] return) */
  public int IsSecurityEnabled();

  /** @com.method(vtoffset=7, addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrRole, [type=I4] return) */
  public int IsCallerInRole(String bstrRole);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x51372ae0, (short)0xcae7, (short)0x11cf, (byte)0xbe, (byte)0x81, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xa2, (byte)0xfa, (byte)0x25);
}
