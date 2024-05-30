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

/** @com.struct(noAutoOffset) */


public final class __MIDL___MIDL_itf_autosvcs_0283_0001
{
  /** @com.structmap([offset=0,type=U4] cbSize) */
  public int cbSize;

  /** @com.structmap([offset=4,type=U4] dwPid) */
  public int dwPid;

  /** @com.structmap([offset=8,type=I4] lTime) */
  public int lTime;

  /** @com.structmap([offset=12,type=I4] lMicroTime) */
  public int lMicroTime;

  /** @com.structmap([offset=16,type=I8] perfCount) */
  public long perfCount;

// UNMAPPABLE: guidApp: Cannot be used as a structure field.
//   /** @com.structmap(UNMAPPABLE guidApp) */
//  public UNMAPPABLE guidApp;

  /** @com.structmap([offset=24,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] sMachineName) */
  public String sMachineName;

}
