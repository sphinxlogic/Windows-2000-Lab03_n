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

// VTable-only interface IObjectContextInfo
/** @com.interface(iid=75B52DDB-E8ED-11D1-93AD-00AA00BA3258, thread=AUTO) */
public interface IObjectContextInfo extends IUnknown
{
  /** @com.method(vtoffset=0, returntype=VOID)
      @com.parameters([type=I4] return) */
  public int IsInTransaction();

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,size=1,type=ARRAY] pptrans) */
  public void GetTransaction(IUnknown[] pptrans);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([out,type=PTR] pGUID) */
  public void GetTransactionId(com.ms.com._Guid pGUID);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([out,type=PTR] pGUID) */
  public void GetActivityId(com.ms.com._Guid pGUID);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([out,type=PTR] pGUID) */
  public void GetContextId(com.ms.com._Guid pGUID);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x75b52ddb, (short)0xe8ed, (short)0x11d1, (byte)0x93, (byte)0xad, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xba, (byte)0x32, (byte)0x58);
}
