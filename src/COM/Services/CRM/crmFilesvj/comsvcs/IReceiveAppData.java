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

// VTable-only interface IReceiveAppData
/** @com.interface(iid=413DAFB0-BCF4-11D1-861D-0080C729264D, thread=AUTO) */
public interface IReceiveAppData extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] pAppGuid, [in,type=U4] dwAppProcessId, [out,size=1,type=ARRAY] pidApp, [out,size=1,type=ARRAY] pPushRate) */
  public void Register(String pAppGuid, int dwAppProcessId, int[] pidApp, int[] pPushRate);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=U4] idApp, [in,size=16,type=STRUCT] appData, [in,type=U4] nCLSIDs, [in,type=PTR] clsids) */
  public void PushAppData(int idApp, comsvcs.CAppStatistics appData, int nCLSIDs, comsvcs.CCLSIDData clsids);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=U4] idApp) */
  public void Unregister(int idApp);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x413dafb0, (short)0xbcf4, (short)0x11d1, (byte)0x86, (byte)0x1d, (byte)0x0, (byte)0x80, (byte)0xc7, (byte)0x29, (byte)0x26, (byte)0x4d);
}
