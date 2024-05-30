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

// Dual interface IMtsEvents
/** @com.interface(iid=BACEDF4D-74AB-11D0-B162-00AA00BA3258, thread=AUTO, type=DUAL) */
public interface IMtsEvents extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1, type=PROPGET, name="PackageName", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getPackageName();

  /** @com.method(vtoffset=5, dispid=2, type=PROPGET, name="PackageGuid", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getPackageGuid();

  /** @com.method(vtoffset=6, dispid=5, type=METHOD, name="PostEvent", addFlagsVtable=4)
      @com.parameters([in,elementType=VARIANT,type=PTR] vEvent) */
  public void PostEvent(Variant vEvent);

  /** @com.method(vtoffset=7, dispid=6, type=PROPGET, name="FireEvents", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean getFireEvents();

  /** @com.method(vtoffset=8, dispid=7, type=METHOD, name="GetProcessID", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int GetProcessID();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xbacedf4d, (short)0x74ab, (short)0x11d0, (byte)0xb1, (byte)0x62, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xba, (byte)0x32, (byte)0x58);
}
