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

// Dual interface ISharedPropertyGroupManager
/** @com.interface(iid=2A005C0D-A5DE-11CF-9E66-00AA00A3F464, thread=AUTO, type=DUAL) */
public interface ISharedPropertyGroupManager extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1, type=METHOD, name="CreatePropertyGroup", addFlagsVtable=4)
      @com.parameters([in,type=STRING] name, [in,out,size=1,elementType=I4,type=ARRAY] dwIsoMode, [in,out,size=1,elementType=I4,type=ARRAY] dwRelMode, [out,size=1,elementType=BOOLEAN,type=ARRAY] fExists, [iid=2A005C07-A5DE-11CF-9E66-00AA00A3F464,thread=AUTO,type=DISPATCH] return) */
  public comsvcs.ISharedPropertyGroup CreatePropertyGroup(String name, int[] dwIsoMode, int[] dwRelMode, boolean[] fExists);

  /** @com.method(vtoffset=5, dispid=2, type=PROPGET, name="Group", addFlagsVtable=4)
      @com.parameters([in,type=STRING] name, [iid=2A005C07-A5DE-11CF-9E66-00AA00A3F464,thread=AUTO,type=DISPATCH] return) */
  public comsvcs.ISharedPropertyGroup getGroup(String name);

  /** @com.method(vtoffset=6, dispid=4294967292, type=PROPGET, name="_NewEnum", addFlagsVtable=4)
      @com.parameters([iid=00000000-0000-0000-C000-000000000046,thread=AUTO,type=OBJECT] return) */
  public IUnknown get_NewEnum();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x2a005c0d, (short)0xa5de, (short)0x11cf, (byte)0x9e, (byte)0x66, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xa3, (byte)0xf4, (byte)0x64);
}
