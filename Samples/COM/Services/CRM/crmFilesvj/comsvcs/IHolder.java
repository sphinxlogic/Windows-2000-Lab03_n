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

// VTable-only interface IHolder
/** @com.interface(iid=BF6A1850-2B45-11CF-BE10-00AA00A2FA25, thread=AUTO) */
public interface IHolder extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=U4] __MIDL_0015, [out,size=1,type=ARRAY] __MIDL_0016) */
  public void AllocResource(int __MIDL_0015, int[] __MIDL_0016);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=U4] __MIDL_0017) */
  public void FreeResource(int __MIDL_0017);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=U4] __MIDL_0018) */
  public void TrackResource(int __MIDL_0018);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] __MIDL_0019) */
  public void TrackResourceS(String __MIDL_0019);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=U4] __MIDL_0020, [in,type=I4] __MIDL_0021) */
  public void UntrackResource(int __MIDL_0020, int __MIDL_0021);

  /** @com.method(vtoffset=5, addFlagsVtable=4)
      @com.parameters([in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] __MIDL_0022, [in,type=I4] __MIDL_0023) */
  public void UntrackResourceS(String __MIDL_0022, int __MIDL_0023);

  /** @com.method(vtoffset=6, addFlagsVtable=4)
      @com.parameters() */
  public void Close();

  /** @com.method(vtoffset=7, addFlagsVtable=4)
      @com.parameters([in,type=U4] __MIDL_0024) */
  public void RequestDestroyResource(int __MIDL_0024);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xbf6a1850, (short)0x2b45, (short)0x11cf, (byte)0xbe, (byte)0x10, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xa2, (byte)0xfa, (byte)0x25);
}
