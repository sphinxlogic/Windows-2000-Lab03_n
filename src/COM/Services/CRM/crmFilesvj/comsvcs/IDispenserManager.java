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

// VTable-only interface IDispenserManager
/** @com.interface(iid=5CB31E10-2B5F-11CF-BE10-00AA00A2FA25, thread=AUTO) */
public interface IDispenserManager extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,iid=208B3651-2B48-11CF-BE10-00AA00A2FA25,thread=AUTO,type=OBJECT] __MIDL_0011, [in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] szDispenserName, [out,size=1,type=ARRAY] __MIDL_0012) */
  public void RegisterDispenser(comsvcs.IDispenserDriver __MIDL_0011, String szDispenserName, comsvcs.IHolder[] __MIDL_0012);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([out,size=1,type=ARRAY] __MIDL_0013, [out,size=1,type=ARRAY] __MIDL_0014) */
  public void GetContext(int[] __MIDL_0013, int[] __MIDL_0014);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x5cb31e10, (short)0x2b5f, (short)0x11cf, (byte)0xbe, (byte)0x10, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xa2, (byte)0xfa, (byte)0x25);
}
