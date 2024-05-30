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

// VTable-only interface IGetAppData
/** @com.interface(iid=B60040E0-BCF3-11D1-861D-0080C729264D, thread=AUTO) */
public interface IGetAppData extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=U4] dwPushRate) */
  public void SetPushRate(int dwPushRate);

  // aAppData UNMAPPABLE: Too many indirections.
  //  public void GetApps(int[] nApps, UNMAPPABLE aAppData);

  // aAppData UNMAPPABLE: Too many indirections.
  //  public void GetAppData(int idApp, int[] nCLSIDs, UNMAPPABLE aAppData);

  // ppAppData UNMAPPABLE: Too many indirections.
  //  public void GetCLSIDData(int idApp, com.ms.com._Guid clsid, UNMAPPABLE ppAppData);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters() */
  public void Shutdown();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xb60040e0, (short)0xbcf3, (short)0x11d1, (byte)0x86, (byte)0x1d, (byte)0x0, (byte)0x80, (byte)0xc7, (byte)0x29, (byte)0x26, (byte)0x4d);
}
